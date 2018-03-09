#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;
template <typename t>
class DoublyLinkedList; // class declaration

template <typename t>					// list node
struct DListNode {
	t obj;
	DListNode<t> *prev, *next;
	DListNode(t e = t(), DListNode<t> *p = NULL, DListNode<t> *n = NULL)
		: obj(e), prev(p), next(n) {}
};

// doubly linked list
template <typename t>
class DoublyLinkedList {
private:
	DListNode<t> header, trailer;
public:
	DoublyLinkedList() : header(t()), trailer(t()) // constructor
	{
		header.next = &trailer; trailer.prev = &header;
	}
	DoublyLinkedList(const DoublyLinkedList<t>& dll); // copy constructor
	~DoublyLinkedList(); // destructor
	DoublyLinkedList& operator=(const DoublyLinkedList<t>& dll); // assignment operator
																 // return the pointer to the first node
	DListNode<t> *getFirst() const { return header.next; }
	// return the pointer to the trailer
	const DListNode<t> *getAfterLast() const { return &trailer; }
	// return if the list is empty
	bool isEmpty() const { return header.next == &trailer; }
	t first() const; // return the first object
	t last() const; // return the last object
	void insertFirst(t newobj); // insert to the first of the list
	t removeFirst(); // remove the first node
	void insertLast(t newobj); // insert to the last of the list
	t removeLast(); // remove the last node
	void insertAfter(DListNode<t> &p, t newobj);
	void insertBefore(DListNode<t> &p, t newobj);
	t removeAfter(DListNode<t> &p);
	t removeBefore(DListNode<t> &p);
};

// output operator
template <typename t>
ostream& operator<<(ostream& out, const DoublyLinkedList<t>& dll);
// return the list length
template <typename t>
int DoublyLinkedListLength(DoublyLinkedList<t>& dll);


// copy constructor
template <typename t>
DoublyLinkedList<t>::DoublyLinkedList(const DoublyLinkedList<t>& dll)
{
	// Initialize the list
	header.next = &trailer; trailer.prev = &header;
	DListNode<t>* curr = dll.getFirst();
	//DListNode* temp;

	if (dll.isEmpty()) {

		//do nothing
		return;
	}

	while (curr != dll.getAfterLast()) {

		this->insertLast(curr->obj);
		curr = curr->next;

	}
	trailer.prev = curr->prev;

}

// assignment operator
template <typename t>
DoublyLinkedList<t>& DoublyLinkedList<t>::operator=(const DoublyLinkedList<t>& dll)
{
	//check for self assigment
	if (header.next != dll.getFirst()) {

		// Delete the whole list
		DListNode<t>* curr = dll.getFirst();
		DListNode<t>* temp = curr;

		if (!isEmpty()) {
			while (curr != dll.getAfterLast()) { //deallocation 
				curr = curr->next;
				delete temp;
				temp = curr;
			}
		}

		//allocation
		header.next = curr;
		while (curr != dll.getAfterLast()) {

			this->insertLast(curr->obj);
			curr = curr->next;

		}
		trailer.prev = curr->prev;



	}

	return *this;
}

// insert the new object as the first one
template <typename t>
void DoublyLinkedList<t>::insertFirst(t newobj)
{
	DListNode<t>* newNode = new DListNode<t>(newobj, &header, header.next);

	header.next->prev = newNode;
	header.next = newNode;

}

// insert the new object as the last one
template <typename t>
void DoublyLinkedList<t>::insertLast(t newobj)
{
	DListNode<t>* newNode = new DListNode<t>(newobj, trailer.prev, &trailer);

	trailer.prev->next = newNode;
	trailer.prev = newNode;

}

// remove the first object from the list
template <typename t>
t DoublyLinkedList<t>::removeFirst()
{
	DListNode<t>* curr = header.next; //create a temp node and have it point to the first node

	header.next = curr->next; //header points to 2nd node
	curr->next->prev = &header; //2nd node points at header

	t obj = curr->obj;
	delete curr;

	return obj;

}

// remove the last object from the list
template <typename t>
t DoublyLinkedList<t>::removeLast()
{
	DListNode<t>* curr = trailer.prev; //temp assigned to prev

	trailer.prev = curr->prev; //trailer points last -1 node
	curr->prev->next = &trailer; //last - 1 node points at trailer

	t obj = curr->obj;
	delete curr;

	return obj;
}

// destructor
template <typename t>
DoublyLinkedList<t>::~DoublyLinkedList()
{
	DListNode<t>* curr = header.next;
	DListNode<t>* temp;

	while (curr != &trailer) {
		temp = curr;
		curr = curr->next;
		delete temp;
	}
	header.next = &trailer;
	trailer.prev = &header;
}

// return the first object
template <typename t>
t DoublyLinkedList<t>::first() const
{
	//check if empty
	if (header.next == &trailer) {
		throw runtime_error("Linked list is empty");
	}

	return header.next->obj;
}

// return the last object
template <typename t>
t DoublyLinkedList<t>::last() const
{
	//check if empty
	if (header.next == &trailer) {
		throw runtime_error("Linked list is empty");
	}

	return trailer.prev->obj;
}

// insert the new object after the node p
template <typename t>
void DoublyLinkedList<t>::insertAfter(DListNode<t> &p, t newobj)
{
	DListNode<t>* curr = p.next;
	DListNode<t>* newNode = new DListNode<t>(newobj,&p,curr);

	p.next = newNode;
	curr->prev = newNode;

}

// insert the new object before the node p
template <typename t>
void DoublyLinkedList<t>::insertBefore(DListNode<t> &p, t newobj)
{
	DListNode<t>* curr = p.prev;
	DListNode<t>* newNode = new DListNode<t>(newobj,curr,&p);

	curr->next = newNode;
	p.prev = newNode;


}

// remove the node after the node p
template <typename t>
t DoublyLinkedList<t>::removeAfter(DListNode<t> &p)
{
	DListNode<t>* curr = p.next;

	p.next = p.next->next;
	p.next->prev = &p;

	t obj = curr->obj;

	delete curr;
	
	return obj;
}

// remove the node before the node p
template <typename t>
t DoublyLinkedList<t>::removeBefore(DListNode<t> &p)
{
	DListNode<t>* curr = p.prev;

	p.prev = p.prev->prev;
	p.prev->next = &p;

	
	t obj = curr->obj;

	delete curr;
	
	return obj;

}

// return the list length
template <typename t>
int DoublyLinkedListLength(DoublyLinkedList<t>& dll)
{
	//check if empty
	if (dll.isEmpty()) {
		return 0;
	}

	//traverse through the list
	int count = 0;
	DListNode<t>* curr = dll.getFirst();

	while (curr != dll.getAfterLast()) {
		curr = curr->next;
		count++;
	}

	return count;
}

// output operator
template <typename t>
ostream& operator<<(ostream& out, const DoublyLinkedList<t>& dll)
{
	DListNode<t>* curr = dll.getFirst();
	int count = 0;

	//check 4 empty list
	if (dll.getFirst() == dll.getAfterLast()) {
		out << "Empty List";
	}
	else {
		cout << endl;
		while (curr != dll.getAfterLast()) {

			out << curr->obj << endl;
			curr = curr->next;

		}
	}

	return out;
}
