#include <assert.h>

template <class T>
class List {
	private:
		struct Node{
	    T value;
			Node *previous;
			Node *next;
			Node(T val, Node *previous, Node *next) 
				: value(val), previous(previous), next(next){}
		};
		Node* head_;
		Node* tail_;

	public: 
		List() : head_(nullptr), tail_(nullptr) {}
    ~List();
		void PushFront(T);
		void PushBack(T);
		T PopFront();
		T PopBack();
    int Size() const;
		bool Empty() const { return (head_ == nullptr); }
};


template <class T> List<T>::~List() {
  while (head_){
    Node *tmp(head_); // This is copy constructor. We use it to create a new pointer. 
		// But I really don't know what a copy constructor is. 
		// Check this: https://www.geeksforgeeks.org/copy-constructor-in-cpp/
	  head_ = head_->next;	
		delete tmp;
	}
}


template <class T> void List<T>::PushFront(T value) {
  head_ = new Node(value, nullptr, head_);
	if (tail_ == nullptr)
		tail_ = head_;
	else
		// The first one is the recent head 
		// We have to do this because the previous head was pointing 
		// backwards to nullptr.
		// Sólo que no entiendo pq al final poner = head_;
		head_->next->previous = head_;
}


template <class T> void List<T>::PushBack(T value){
	tail_ = new Node(value, tail_, nullptr);
  if (head_ == nullptr)
		head_ = tail_;
	else 
		tail_->previous->next = tail_;
}


template <class T> T List<T>::PopFront(){
	if (List::Empty()){
		throw("Cannot List::PopFront() when List::Empty()");
	}
	Node *tmp(head_);
	T value = (head_->value);
	head_ = head_->next;
	if (head_){
    head_->previous = nullptr;
	} else {
		// This is for when we got into an empty list.
		// So, if the new head is null, then the tail
		// should also be null. 
    tail_ = nullptr;
	}
	delete tmp;
	return value;
}


template <class T> T List<T>::PopBack(){
	if (List::Empty()){
		throw("Cannot List::PopBack() when List::Empty()");
	}
	Node *tmp(tail_);
	T value = (tail_->value);
  tail_ = tail_->previous;
	if (tail_){
   tail_->next = nullptr;
	} else {
		// case of empty list.
    head_ = nullptr;
	}
	delete tmp;
	return value;
}


template <class T> int List<T>::Size() const {
  int size = 0;
	Node *ptr(head_);
	while (ptr != nullptr){
    ptr = ptr->next;
		size++;
	}
	return size;
}


int main(){

	List<int> list1;
  list1.PushBack(9);
  assert(list1.Size() == 1);

  // Deeper test
  List<int> list2;
  list2.PushFront(9);
  list2.PushBack(10);
  assert(list2.Size() == 2);
  assert(list2.PopBack() == 10);
  assert(list2.PopFront() == 9);
  assert(list2.Size() == 0);



}
