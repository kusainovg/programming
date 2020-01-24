#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"

struct Purchase
{
	std::string Name;
	float weight;
	float price;
	Purchase()
	{
		Name = "none";
		weight = 0;
		price = 0;
	}
	Purchase(std::string _Name, float _weight, float _price)
	{
		Name = _Name;
		weight = _weight;
		price = _price;
	}
	friend std::ostream& operator<<(std::ostream& out, const Purchase& purchase)
	{
		out << "Name: " << purchase.Name << " Weight: " << purchase.weight << " Price: " << purchase.price << '\n';
		return out;
	}
};

template<class T>
class stack
{
private:
	AbstractList<T>* list;
public:
	stack(AbstractList<T>* list_temp)
	{
		list = list_temp;
	}
	stack(std::string str)
	{
		if (str == "list")
		{
			LinkedList<Purchase>* lst = new LinkedList<Purchase>();
			list = lst;
		}
		if (str == "list2")
		{
			LinkedList<Purchase>* lst = new LinkedList<Purchase>();
			list = lst;
		}
	}
	void push(const T& temp)
	{
		list->push_back(temp);
	}
	T pop(std::ostream& out)
	{
		T temp = list->pop();
		out << list->pop_back() << '\n';
		return temp;
	}
	bool isEmpty() const
	{
		return list->isEmpty();
	}
	T top()
	{
		return list->pop();
	}
	int size() const
	{
		return list->size();
	}
};
int main()
{
	setlocale(LC_ALL, "rus");

	LinkedList<Purchase>* linked_list = new LinkedList<Purchase>();
	LinkedList2<Purchase>* linked_list_2 = new LinkedList2<Purchase>();

	stack<Purchase>* st = new stack<Purchase>("list");

	std::ofstream out("text.txt");

	int choice;

	std::cout << "1)Купить товар" << std::endl;
	std::cout << "2)Количество товаров в корзине" << std::endl;
	std::cout << "3)Вывести товары на экран" << std::endl;
	std::cout << "4)Вывести товары в файл" << std::endl;

	std::cout << "Выбор: "; std::cin >> choice;

	while (choice != 5)
	{
		std::cout << "1)Купить товар" << std::endl;
		std::cout << "2)Количество товаров в корзине" << std::endl;
		std::cout << "3)Вывести последний товар на экран" << std::endl;
		std::cout << "4)Вывести последний товар в файл" << std::endl;
		std::cout << "5)Выход" << std::endl;

		std::cout << "Выбор: "; std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			Purchase purch;
			std::cout << "Введите название товара: "; std::cin >> purch.Name;
			std::cout << "Введите вес: "; std::cin >> purch.weight;
			std::cout << "Введите цену: "; std::cin >> purch.price;

			st->push(purch);

			break;
		}
		case 2:
		{
			std::cout << "Количество товаров в корзине: " << st->size() << std::endl;
			break;
		}
		case 3:
		{
			st->pop(std::cout);
			break;
		}
		case 4:
		{
			st->pop(out);
			break;
		}
		default:
			std::cout << "Неправильный ввод!" << std::endl;
			break;
		}
	}

	out.close();
	
	system("pause");
	return 0;
}