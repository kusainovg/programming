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
	LinkedList<T> list;
public:
	void push(const T& temp)
	{
		list.push_back(temp);
	}
	T pop(std::ostream& out)
	{
		T temp = list.pop();
		out << list.pop_back() << '\n';
		return temp;
	}
	bool isEmpty() const
	{
		return list.isEmpty();
	}
	T top()
	{
		return list.pop();
	}
	int size() const
	{
		return list.size();
	}
};
int main()
{
	setlocale(LC_ALL, "rus");

	stack<Purchase> st;

	std::ofstream out("text.txt");

	int choice;

	std::cout << "1)������ �����" << std::endl;
	std::cout << "2)���������� ������� � �������" << std::endl;
	std::cout << "3)������� ������ �� �����" << std::endl;
	std::cout << "4)������� ������ � ����" << std::endl;

	std::cout << "�����: "; std::cin >> choice;

	while (choice >= 1 || choice <= 5)
	{
		std::cout << "1)������ �����" << std::endl;
		std::cout << "2)���������� ������� � �������" << std::endl;
		std::cout << "3)������� ������ �� �����" << std::endl;
		std::cout << "4)������� ������ � ����" << std::endl;

		std::cout << "�����: "; std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			Purchase purch;
			std::cout << "������� �������� ������: "; std::cin >> purch.Name;
			std::cout << "������� ���: "; std::cin >> purch.weight;
			std::cout << "������� ����: "; std::cin >> purch.price;

			st.push(purch);

			break;
		}
		case 2:
		{
			std::cout << "���������� ������� � �������: " << st.size() << std::endl;
			break;
		}
		case 3:
		{
			st.pop(std::cout);
			break;
		}
		case 4:
		{
			st.pop(out);
			break;
		}
		default:
			std::cout << "������������ ����!" << std::endl;
			break;
		}
	}

	
	system("pause");
	return 0;
}