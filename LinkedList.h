#pragma once
template<class T>
class LinkedList
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}
	// Destructor
	~LinkedList()
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			Node * t = temp;
			temp = temp->next;
			delete t;
		}
	}

	bool isEmpty() const
	{
		return head == nullptr;
	}

	void push_back(const T& _value)
	{
		Node* temp = new Node();

		temp->value = _value;
		temp->next = nullptr;


		if (isEmpty())
		{
			temp->prev = nullptr;

			head = temp;
			tail = temp;
		}
		else
		{
			temp->prev = tail;

			tail->next = temp;

			tail = temp;
		}
	}
	// Traversing and showing DoubleLinkedList
	void Show() const
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			std::cout << temp->value << ' ';
			temp = temp->next;
		}
	}

	class Iterator
	{
	private:
		Node* current;
	public:
		Iterator(Node* temp)
		{
			current = temp;
		}
		bool operator==(const Iterator& it)
		{
			return this->current == it.current;
		}
		bool operator<=(const Iterator& it)
		{
			bool isLessOrEqual = false;

			Node* temp = current;

			while (temp != nullptr && isLessOrEqual == false)
			{
				if (temp == it.current)
					isLessOrEqual = true;
				else
					temp = temp->next;
			}

			return isLessOrEqual;
		}
		// Overloading operators of incrementing and decrementing
		Iterator& operator++()
		{
			if (current == nullptr)
				return *this;
			else
			{
				current = current->next;
				return *this;
			}
		}
		Iterator& operator++(int)
		{
			if (current == nullptr)
				return *this;
			else
			{
				current = current->next;
				return *this;
			}

		}
		Iterator& operator--()
		{
			if (current == nullptr)
				return *this;
			else
			{
				current = current->prev;
				return Iterator(current);
			}
		}
		Iterator& operator--(int)
		{
			if (current == nullptr)
				return *this;
			else
			{
				current = current->prev;
				return Iterator(current);
			}
		}
		// Перегрузка операции разыменования
		T& operator*()
		{
			return current->value;
		}
	};
	Iterator begin()
	{
		return Iterator(head);
	}
	Iterator end()
	{
		return Iterator(tail);
	}
};

