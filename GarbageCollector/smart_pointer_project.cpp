#include <memory>
#include "gc_pointer.h"

namespace custom{
	template<typename T> class list{
		private:
			struct Node{
				T val;
        Pointer<Node> prev;
        Pointer<Node> next;
				Node(T _val, Node* _prev, Node* _next) 
					: val(_val), prev(_prev), next(_next){}
			  };
				Node* head;
				Node* tail;
		public:
				// Constructor
				list(): head(NULL), tail(NULL){}
				void push_back(T);
				bool empty() const { return ( !head || !tail);}
				void print();
	};

	template <typename T>
		void list<T>::push_back(T val){
			list::tail = new Node(val, tail, NULL);
			if(tail->prev){
				tail->prev->next = list::tail;
			}
			if(list::empty()){
				list::head = list::tail;
			}
		}

	template <typename T>
		void list<T>::print(){
			Node* ptr = list::head;
			while(ptr != NULL){
				std::cout << ptr->val << std::endl;
				ptr = ptr->next;
			}
			std::cout << std::endl;
		}
}




int main() {
custom::list< int > list;

std::cout << "Add 5 numbers: " << std::endl;
for(int i = 0; i < 5; i++) {
    int temp;
    std::cout<<"Add "<< i+1<< ". element:"<< std::endl;
    std::cin >>temp;
    list.push_back(temp);
}

list.print();
return 0;
}
