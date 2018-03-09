#include "TemplateDoublyLinkedList.h"

template <typename t>
class Que {
private:
	DoublyLinkedList<t> ll;
	
public:
	Que() : ll() {};
	
	
	void enqueue(t x);
	t dequeue();
	bool isEmpty() const;
	int size();
	t min();

	friend ostream& operator<<(ostream& out, const Que<t>& q) {

		out << q.ll;
		return out;
	};
};


template <typename t>
void Que<t>::enqueue(t x) {
	ll.insertLast(x);
}

template <typename t>
t Que<t>::dequeue() {
	return ll.removeFirst();
}

template <typename t>
bool Que<t>::isEmpty() const {

	return ll.isEmpty();
}

template <typename t>
int Que<t>::size() {

	return DoublyLinkedListLength(ll);
}

template <typename t>
t Que<t>::min() {
	
	DListNode<t>* curr = ll.getFirst();
	t min = curr->obj;
	if (ll.isEmpty()) {
		return t();
	
	}

	while (curr != ll.getAfterLast()) {

		if (min > curr->obj)
			min = curr -> obj;
		
		curr = curr->next;

	}	
	return min;
}

