#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class node
{
public:
	node* next = nullptr;

	string lastname;
	string firstname;
	string country;
	int elo;
	int year;

};

void addB(node*& head, string newLast, string newFirst, string newCountry, int newElo, int newYear) // dodawanie na koniec listy
{
	node* newNode = new node;
	newNode->lastname = newLast;
	newNode->firstname = newFirst;
	newNode->country = newCountry;
	newNode->elo = newElo;
	newNode->year = newYear;
	newNode->next = head;
	newNode->next = nullptr;
	if (head)
	{
		node* pom = head;
		while (pom->next)
			pom = pom->next;
		pom->next = newNode;
	}
	else
		head = newNode;
}

void show(node* head)  // wywietlenie elementów listy
{
	node* pom = head;
	while (pom)
	{
		std::cout << pom->lastname << " " << pom->firstname << " " << pom->country << " " << " " << pom->elo << " " << pom->year << endl;
		pom = pom->next;
	}
}

int findAll(node*& head, string target)
{
	node* pom = head;
	int i = 0;
	cout << target << ": ";
	while (pom)
	{
		if (pom->country == target)
		{
			i++;
			pom = pom->next;
		}
		else
		{
			pom = pom->next;

		}
	}
	cout << i;
	return i;
}

void zad1(int target)
{
	node* list1 = nullptr;
	string lastname, firstname, country, temp1, temp2;
	int elo, year;

	ifstream file;
	file.open("Grupa1.txt");
	while (!file.eof())
	{
		file >> lastname;
		file >> firstname;
		file >> country;
		file >> temp1;
		elo = stoi(temp1);
		file >> temp2;
		year = stoi(temp2);

		if (elo > target)
			addB(list1, lastname, firstname, country, elo, year);
	}
	file.close();
	show(list1);

	node* pom = list1;
	while (pom)
	{
		node* next = pom->next;
		delete pom;
		pom = next;
	}
}

void zad2(node* head)
{
	map<string, node*> najlepsiGracze;

	node* pom = head;
	while (pom)
	{
		if (najlepsiGracze.find(pom->country) == najlepsiGracze.end())
		{
			najlepsiGracze[pom->country] = pom;
		}
		else if (pom->elo > najlepsiGracze[pom->country]->elo)
		{
			najlepsiGracze[pom->country] = pom;
		}

		pom = pom->next;
	}
	cout << "Najepsi gracze:\n";
	for (const auto& x : najlepsiGracze)
	{
		cout << x.first << ": " << x.second->firstname << " " << x.second->lastname << " (" << x.second->elo << " ELO)" << endl;
	}
}

void zad3(node*& head) 
{
	node* pom = head;
	node* pom2 = nullptr;
	

	while (pom) 
	{
		int age = 2023 - pom->year;
		if (age > 30) 
		{
			if (!pom2) 
			{
				head = pom->next;
				delete pom;
				pom = head;
			}
			else 
			{
				pom2->next = pom->next;
				delete pom;
				pom = pom2->next;
			}
		}
		else {
			pom2 = pom;
			pom = pom->next;
		}
	}
}


int main()
{
	setlocale(LC_ALL, ".UTF8");

	cout << "Zadanie 1:\n\n";
	zad1(2700); // poza tworzeniem listym te¿ j¹ wywietla na ekran, aby mo¿na by³o sprawdziæ poprawnoæ

	node* list3 = nullptr;
	string lastname, firstname, country, temp1, temp2;
	int elo, year;

	ifstream file;
	file.open("Grupa1.txt");
	while (!file.eof())
	{
		stringstream ss1, ss2;
		file >> lastname;
		file >> firstname;
		file >> country;
		file >> temp1;
		elo = stoi(temp1);
		file >> temp2;
		year = stoi(temp2);
		addB(list3, lastname, firstname, country, elo, year);
	}
	file.close();

	cout << "\nZadanie 2:\n\n";
	zad2(list3);

	cout << "\nZadanie 3:\n\n";
	zad3(list3);
	show(list3);

	node* pom = list3;
	while (pom)
	{
		node* next = pom->next;
		delete pom;
		pom = next;
	}
}