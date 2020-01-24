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
		Node()
		{
			next = prev = nullptr;
		}
		Node(const T& _value)
		{
			next = prev = nullptr;
			value = _value;
		}
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

		Node* temp = new Node(_value);

		if (tail == nullptr)
			head = tail = temp;
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		/*
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
		*/
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

	T pop_back()
	{
		if (tail != nullptr)
		{
			T t = tail->value;

			Node * temp = tail;

			tail = tail->prev;

			delete temp;

			return t;
		}
	}
	T pop()
	{
		return tail->value;
	}

	int size() const
	{
		
		if (head == nullptr)
			return 0;
		else
		{
			int count = 0;

			Node* temp = head;
			while (temp != nullptr)
			{
				count++;
				temp = temp->next;
			}

			return count;
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
		// Ïåðåãðóçêà îïåðàöèè ðàçûìåíîâàíèÿ
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