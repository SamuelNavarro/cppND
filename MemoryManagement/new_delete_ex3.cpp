#include <iostream>

class BinaryTree {
	private:
		struct Node{
			Node(int _data, Node* _left, Node* _right)
				: data(_data), left(_left), right(_right){}
			~Node(){
				if(left)
					delete left;
				if (right)
					delete right;
			}
			int data;
			Node* left;
			Node* right;
		};
		Node* root;

		void Add(int val, Node* ptr){
			if(val > ptr->data){
				// Creo que este es para asegurarnos de que no hay ya info 
				// en ese bloque de memoria.
				if(ptr->left != nullptr)
					// por eso es que queremos hacer
					// recursivamente Add hasta que lleguemos
					// al bloque de memoria que no tiene nada
					Add(val, ptr->left);
				else
					// Hasta que llegamos a un bloque de memoria
					// con nullptr, agregamos el nodo.
					ptr->left = new Node(val, nullptr, nullptr);
			}
			else if(val <= ptr->data){
				if(ptr->right != nullptr)
					Add(val, ptr->right);
				else
					ptr->right = new Node(val, nullptr, nullptr);
			}
		}


		bool Search(int item, Node* ptr){
			if(!ptr->left && !ptr->right){
				if(ptr->data == item){
					return true;
				}
				return false;
			}
			// Si apunta a izquierda y por lo tanto
			// el valor es menor que el item buscado
			// entonces buscamos a la izquierda.
			if(ptr->data < item && ptr->left){
				Search(item, ptr->left);
			}
			// lo mismo aquí, entonces buscamos a la derecha
			else if(ptr->data > item && ptr->right){
				Search(item, ptr->right);
			}
		}

	public:
		BinaryTree(int data){
			BinaryTree::root = new Node(data, nullptr, nullptr);
		};
		~BinaryTree(){
			delete BinaryTree::root;
		}
		void addData(int new_data){
			BinaryTree::Add(new_data, BinaryTree::root);
		}
		bool searchItem(int item){
			return BinaryTree::Search(item, BinaryTree::root);
		}
};



int main(){

	BinaryTree tree(2);
	tree.addData(10);
  tree.addData(1);
  tree.addData(20);
  tree.addData(0);

  std::cout<<tree.searchItem(0)<<std::endl;
  std::cout<<tree.searchItem(9)<<std::endl;

  tree.addData(11);
  std::cout<<tree.searchItem(11)<<std::endl;

	return 0;
}
