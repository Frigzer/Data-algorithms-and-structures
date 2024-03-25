#include <iostream>
#include <cstdlib>

using namespace std;

struct node
{
	string name;
	node* next;
};

//funkcja hashujaca (jest dostosowana do pobierania imion tj. pierwsza litera jest wielka)
int H(string name)
{
	int p = 0;
	p += int(name[0]) - 64;
	for (int i = 1; i < name.size(); i++)
	{
		p += int(name[i]) - 96;
	}
	return p % 13;
}

//dodawanie imion do wezla
void add(node*& head, string name)
{
	if (!head)
	{
		head = new node;
		head->name = name;
		head->next = NULL;
	}
	else
		add(head->next, name);
}

//wyswietlanie imion w poszczegolnych wezlach
void select(node* head)
{
	if (head)
	{
		cout << head->name << ", ";
		select(head->next);
	}
}

//funkcja ktora wyswietla zawartosci wszystkich tabel w tablicy o ile nie sa puste
void show(node** L)
{
	for (int i = 0; i < 13; i++)
	{
		if (L[i])
		{
			cout << i << ": ";
			select(L[i]);
			cout << endl;
		}
		else
			continue;
	}
}

//funkcja usuwajaca imiona z ciagu
void remove(node*& head, string name)
{
	if (head)
	{
		if (head->name == name)
		{
			if (!head->next)
			{
				free(head);
				head = NULL;
			}
			else
			{
				node* tmp = head;
				head = head->next;
				delete(tmp);
			}
		}
		else
			remove(head->next, name);
	}
}

//funkcja sprawdzajaca czy w tekscie wystepuje zworzec (metoda naiwna)
void naive(string text, string pattern)
{
	int position = 0;
	for (int i = 0; i < pattern.size(); i++)
	{
		//cout << text[i + position];
		if (pattern[i] == text[i + position])
		{
			if (pattern.size() - 1 == i)
			{
				//cout << pattern.size() - 1 << position << endl;
				cout << "Znaleziono wzorzec w tekscie na pozycji: " << position << endl;
				i = -1;
				position += pattern.size();
				//return 1;
			}
			else
				continue;
		}
		else
		{
			i = -1;
			position++;
		}
		if (position >= text.size())
			break;
	}
	//cout << "Nie znaleziono wzorca w tekscie" << endl;
	//return 0;
}

//funkcja sprawdzajaca czy w tekscie wystepuje wzorzec (metoda Rabina Karpa)
void rabin(string text, string pattern)
{
	int p = 0;
	for (int i = 0; i < pattern.size(); i++)
	{
		p += (int(pattern[pattern.size() - 1 - i]) - 48) * pow(10, i);
	}
	p = p % 13;

	int t = 0;
	int position = 0;
	//cout << "Podejrzane pola na pozycjach: ";
	for (int i = 0; i <= text.size() - pattern.size(); i++)
	{
		t=0;
		for (int j = 0; j < pattern.size(); j++)
		{
			t += (int(text[pattern.size() - 1 - j + i]) - 48) * pow(10, j);
		}
		t = t % 13;

		if (t == p)
		{
			//naiwny
			//cout << text[i];
			for (int j = 0; j < pattern.size(); j++)
			{
				if (text[j + i] == pattern[j])
				{
					if (pattern.size() - 1 == j)
						cout << "Znaleziono wzorzec w tekscie na pozycji: " << i << endl;
				}
				else
					break;
			}
			//cout << i << " ";
		}
	}
}

int main()
{
	node** L = new node * [13];
	for (int i = 0; i < 13; i++)
		L[i] = NULL;

	add(L[H("Piotr")], "Piotr");
	add(L[H("Antek")], "Antek");
	add(L[H("Ola")], "Ola");
	add(L[H("Andrzej")], "Andrzej");
	add(L[H("Jan")], "Jan");
	add(L[H("Kasia")], "Kasia");
	add(L[H("Kuba")], "Kuba");
	add(L[H("Wojtek")], "Wojtek");
	add(L[H("Filip")], "Filip");

	show(L);

	remove(L[H("Kasia")], "Kasia");
	remove(L[H("Wojtek")], "Wojtek");
	remove(L[H("Antek")], "Antek");

	show(L);

	string text = "abaaabcabaabcabac";
	string pattern = "abaa";

	naive(text, pattern);

	rabin("23590231415267399", "31415");

}