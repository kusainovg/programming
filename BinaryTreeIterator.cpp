#include <iostream>
#include <stack>

template<class T>
class BinaryTree
{
private:
	struct Node
	{
		T value;
		Node* parent;
		Node* left;
		Node* right;
		Node(const T& _value, Node* _parent) : value(_value), parent(_parent), left(nullptr), right(nullptr){}
	};
	Node* root;

	// Helper methods
	// Method insert
	void insert(const T& value, Node* parent)
	{
		if (value < parent->value)
		{
			if (parent->left == nullptr)
				parent->left = new Node(value, parent);
			else
				insert(value, parent->left);
		}
		else if (value > parent->value)
		{
			if (parent->right == nullptr)
				parent->right = new Node(value, parent);
			else
				insert(value, parent->right);
		}
	}
	// Preorder print
	void inorder_print(Node* parent)
	{
		if (parent != nullptr)
		{
			inorder_print(parent->left);
			std::cout << parent->value << ' ';
			inorder_print(parent->right);
		}
	}
public:
	BinaryTree()
	{
		root = nullptr;
	}
	~BinaryTree()
	{

	}
	
	void insert(const T& value)
	{
		if (root != nullptr)
		{
			insert(value, root);
		}
		else
		{
			root = new Node(value, nullptr);
		}
	}
	void inorder_print()
	{
		inorder_print(root);
		std::cout << std::endl;
	}
	static Node* FindLeft(Node* parent)
	{
		Node* temp = parent;
		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp;
	}
	static Node* FindRight(Node* parent)
	{
		Node* temp = parent;
		while (temp->right != nullptr)
		{
			temp = temp->right;
		}
		return temp;
	}
	class Iterator
	{
	private:
		Node* current;
		std::stack<Node*> stack;
		std::stack<Node*> stack_minus;
	public:
		Iterator(Node* temp) : current(temp) {}
		// Перегрузка операции разыменовывания для итератора
		T& operator*()
		{
			return current->value;
		}
		// 
		bool operator !=(const Iterator& other)
		{
			return current != other.current;
		}

		void findNode()
		{
			if (current->right)
			{
				stack.push(current);

				current = BinaryTree::FindLeft(current->right);
			}
			else
			{
				current = current->parent;

				if (!stack.empty())
				{
					while (current == stack.top())
					{
						current = stack.top()->parent;

						stack.pop();

						if (stack.empty())
						{
							break;
						}
					}
				}
			}
		}

		void findNode_Minus()
		{
			if (current->left)
			{
				stack_minus.push(current);

				current = BinaryTree::FindRight(current->left);
			}
			else
			{
				current = current->parent;

				if (!stack_minus.empty())
				{
					while (current == stack_minus.top())
					{
						current = stack_minus.top()->parent;

						stack_minus.pop();

						if (stack_minus.empty())
						{
							break;
						}
					}
				}
			}
		}

		Iterator& operator ++()
		{
			findNode();

			return *this;
		}

		Iterator& operator ++(int)
		{
			findNode();

			return *this;
		}

		Iterator& operator --()
		{
			findNode_Minus();

			return *this;
		}

		Iterator& operator --(int)
		{
			findNode_Minus();

			return *this;
		}
	};
	Iterator begin()
	{
		return Iterator(BinaryTree::FindLeft(root));
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
};

int main()
{
	BinaryTree<int> bst;

	bst.insert(1);
	bst.insert(5);
	bst.insert(100);
	bst.insert(3);
	bst.insert(-100);

	for (BinaryTree<int>::Iterator it = bst.begin(); it != bst.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	

	//bst.inorder_print();

	system("pause");
	return 0;
}