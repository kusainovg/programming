#include <iostream>
#include "IteratorList.cpp"

template<class T>
class KekVector
{
private:
	int difference;         // На сколько увеличивать каждый раз массив
	T* _Array;              // Сам массив
	int _size;              // Размер
	int _capacity;          // Capacity
public:
	KekVector()
	{
		difference = 1;
		_size = 0;
		_capacity = 1;
		_Array = new T[_capacity];
	}
	~KekVector()
	{
		// Освобождаю память
		delete[] _Array;
	}
	void push_back(T value)
	{
		if (_size == _capacity)
		{
			_capacity += difference;
			T* temp = new T[_capacity];

			memcpy(temp, _Array, sizeof(T) * _size);

			delete[] _Array;
			_Array = temp;
		}
		_Array[_size] = value;
		_size++;
	}
	bool isEmpty()
	{
		return _size == 0;
	}
	int get_size()
	{
		return _size;
	}
	void Show()
	{
		for (int i = 0; i < _size; i++)
			std::cout << i << " elem: " << _Array[i] << std::endl;
	}

	class Iterator
	{
	private:
		T* current;
	public:
		Iterator(T* temp)
		{
			current = temp;
		}
		// Перегружаю операторы для работы с итераторами
		bool operator>=(const Iterator& temp)
		{
			return current >= temp.current;
		}

		bool operator<=(const Iterator& temp)
		{
			return current <= temp.current;
		}

		bool operator==(const Iterator& temp)
		{
			return current == temp.current;
		}

		Iterator& operator++()
		{
			return Iterator(current++);
		}

		Iterator operator++(int)
		{
			return Iterator(current++);
		}

		Iterator& operator--()
		{
			return Iterator(current--);
		}

		Iterator operator--(int)
		{
			return Iterator(current--);
		}


		// Оператор разыменование для получения значения
		T& operator*()
		{
			return *current;
		}
	};
	Iterator begin()
	{
		return Iterator(_Array);
	}
	Iterator end()
	{
		return Iterator(_Array + _size - 1);
	}
};

int main()
{
	KekVector<int> k_vec;

	k_vec.push_back(2);
	k_vec.push_back(2);
	k_vec.push_back(2);

	k_vec.Show();

	// Как должно выглядеть и работать
	
	std::cout << "Iterator:" << std::endl;



	for (KekVector<int>::Iterator it = k_vec.begin(); it <= k_vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	
	system("pause");
	return 0;
}