#include <iostream>
#include <stack>
#include <string>

struct Student
{
	std::string date_of_birth;
	float average_score;
	std::string FIO;

	Student(std::string _date_of_birth, float _average_score, std::string _FIO)
	{
		date_of_birth = _date_of_birth;
		average_score = _average_score;
		FIO = _FIO;
	}
	bool operator<(const Student& stud)
	{
		return this->average_score < stud.average_score;
	}
	bool operator>(const Student& stud)
	{
		return this->average_score > stud.average_score;
	}
	bool operator!=(const Student& stud)
	{
		return this->average_score != stud.average_score;
	}
	/*
	friend std::ostream& operator<<(std::ostream& out, const Student& stud)
	{
		std::cout << "Date of birth: " << stud.date_of_birth << std::endl;
		std::cout << "Average score: " << stud.average_score << std::endl;
		std::cout << "FIO: " << stud.FIO << std::endl;

		return out;
	}*/
};

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
		Node(const T& _value, Node* _parent) : value(_value), parent(_parent), left(nullptr), right(nullptr) {}
	};
	Node* root;

	// Helper methods
	// Method insert
	void insert(T& value, Node* parent)
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

	void insert(T& value)
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
		// Ïåðåãðóçêà îïåðàöèè ðàçûìåíîâûâàíèÿ äëÿ èòåðàòîðà
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
			findNode_Minus();

			return *this;
		}

		Iterator& operator ++(int)
		{
			findNode_Minus();

			return *this;
		}

		Iterator& operator --()
		{
			findNode();

			return *this;
		}

		Iterator& operator --(int)
		{
			findNode();

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
	Iterator rbegin()
	{
		return Iterator(BinaryTree::FindRight(root));
	}
	Iterator rend()
	{
		return Iterator(nullptr);
	}
};

int main()
{
	BinaryTree<Student> bst;

	Student stud1("02.02.2000", 5, "NONe");
	Student stud2("03.02.2001", 4.5, "NONE");

	bst.insert(stud1);
	bst.insert(stud2);
	for (BinaryTree<Student>::Iterator it = bst.rbegin(); it != bst.rend(); it++)
	{
		Student stud = *it;
		std::cout <<  stud.average_score << std::endl;
	}



	//bst.inorder_print();

	system("pause");
	return 0;
}