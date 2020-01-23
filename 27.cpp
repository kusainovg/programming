#include <fstream>
#include <iostream>
#include "LinkedList.h"



struct User
{
	char* Name;
	char* Password;
	User()
	{
		Name = new char[32];
		Password = new char[32];
	}
	
};

class UserSingleton
{
private:
	User user;
	static UserSingleton* instance;
	UserSingleton()
	{
		strcpy_s(user.Name, sizeof("none"), "none");
		strcpy_s(user.Password, sizeof("none"), "none");
	}
	
public:
	~UserSingleton()
	{
		user.~User();
		delete instance;
	}
	static UserSingleton* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new UserSingleton();
		}
		return instance;
	}
	void SetUser(const User& temp)
	{
		if (instance != nullptr)
		{
			UserSingleton* user_singleton = UserSingleton::GetInstance();
			strcpy_s(user_singleton->user.Name, sizeof(temp.Name), temp.Name);
			strcpy_s(user_singleton->user.Password, sizeof(temp.Password), temp.Password);
		}
	}
	void ShowUserCredentials() const
	{
		std::cout << "User: " << user.Name << " Password: " << user.Password << std::endl;
	}
	const char* GetName() const
	{
		return user.Name;
	}
	const char* GetPassword() const
	{
		return user.Password;
	}
};

UserSingleton* UserSingleton::instance;

class Program
{
private:
	UserSingleton* CurrentUser;
	LinkedList<User> list;
	void GetListFromFile(std::ifstream& in)
	{
		while (!in.eof())
		{
			User temp;
			in >> temp.Name >> temp.Password;
			list.push_back(temp);
		}

		Show();
	}
	void FlushOut(std::ofstream& out)
	{
		if (!list.isEmpty())
		{
			for (auto it = list.begin(); it <= list.end(); it++)
			{
				User temp = *it;
				out << temp.Name << ' ' << temp.Password << ' ';
			}
		}
	}
	User* FindUserByNameAndPassword(const char* name, const char* password)
	{
		for (auto it = list.begin(); it <= list.end(); ++it)
		{
			User* temp = &(*it);
			if (!strcmp(temp->Name, name) && !strcmp(temp->Password, password))
			{
				return temp;
			}
		}
		return nullptr;
	}
public:
	void Show()
	{
		for (auto it = list.begin(); it <= list.end(); it++)
		{
			User temp = *it;
			std::cout << "Name: " << temp.Name << " Password: " << temp.Password << std::endl;
		}
	}
	Program()
	{
		CurrentUser = nullptr;
	}
	Program(std::ifstream& in)
	{
		CurrentUser = nullptr;
		GetListFromFile(in);
	}
	bool EnterProgram(const User& user)
	{
		CurrentUser = UserSingleton::GetInstance();
		for (auto it = list.begin(); it <= list.end(); it++)
		{
			User temp = *it;
			if (!strcmp(temp.Name, user.Name) && !strcmp(temp.Password, user.Password))
			{
				CurrentUser->SetUser(temp);
				std::cout << "Success login!" << std::endl;

				CurrentUser->ShowUserCredentials();

				return true;
			}
		}
		return false;
	}
	bool ChangePassword(std::ofstream& out, const char* password)
	{
		if (CurrentUser != nullptr)
		{
			std::cout << "Before changing password!" << std::endl;
			Show();

			User* temp = FindUserByNameAndPassword(CurrentUser->GetName(), CurrentUser->GetPassword());
			strcpy_s(temp->Password, sizeof(password), password);

			std::cout << "After changing password!" << std::endl;
			Show();
			//temp->Password = password;
		}
		return false;
	}
	bool ChangeName(std::ofstream& out, const char* name)
	{

	}
};

int main()
{
	std::ifstream in("text.txt");

	if (in.is_open())
	{
		std::cout << "Open!" << std::endl;
	}
	Program prog(in);

	UserSingleton::GetInstance();
	
	User temp;

	temp.Name = new char[32];
	temp.Password = new char[32];

	char* ch = new char[32];
	std::cout << "Enter Name: "; std::cin >> ch;
	strcpy_s(temp.Name, sizeof(ch), ch);

	delete ch;
	ch = new char[32];

	std::cout << "Enter Password: "; std::cin >> ch;
	strcpy_s(temp.Password, sizeof(ch), ch);

	prog.EnterProgram(temp);
	in.close();

	std::ofstream out("text.txt");
	prog.ChangePassword(out, "LULLUL");


	system("pause");
	return 0;
}