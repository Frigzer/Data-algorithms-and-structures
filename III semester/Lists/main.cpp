#include <iostream>

using namespace std;

struct node
{
	node* next = NULL;
	int val;
};

//dodawanie na poczatek listy
void push(node*& head, int value)
{
	node* tail = head;
	if (!head)
	{
		head = new node;
		head->val = value;
		head->next = NULL;
	}
	else
	{
		tail = head;
		head = new node;
		head->val = value;
		head->next = tail;
	}
}

//dodawanie na koniec listy
void add(node*& head, int value)
{
	if (!head)
	{
		head = new node;
		head->val = value;
		head->next = NULL;
	}
	else
		add(head->next, value);
}

/*void deleteFirst(node*& head)
{
	node* tmp = head->next;
	delete head;
	head = tmp;
}*/

//wyswietlenie elementow listy
void select(node* head)
{
	if (head)
	{
		cout << head->val << endl;
		select(head->next);
	}
}

//usuniecie co drugiego elementu
void deleteEverySecond(node*& head)
{
	if (head && head->next)
	{
		node* tmp = head->next->next;
		delete head->next;
		head->next = tmp;
		deleteEverySecond(head->next);
	}
}

//zamiana x wartosci z nastepnym
void swapXwithNext(node*& head, int x)
{
	if (head)
	{
		if (head->val == x)
		{
			if (head->next)
			{
				node* tmp = head->next;
				head->next = head->next->next;
				tmp->next = head;
				head = tmp;
			}
		}
		else
			swapXwithNext(head->next, x);
	}
}

//usuniecie parzystych
void deleteEveryEven(node*& head)
{
	if (head)
	{
		if (((head->val) % 2) == 0)
		{
			node* tmp = head->next;
			delete head;
			head = tmp;
			deleteEveryEven(head);
		}
		else
			deleteEveryEven(head->next);

	}
}

//kopiowanie wartosci z jednej listy do drugiej
void copyNode(node* from, node*& to)
{
	if (from)
	{
		add(to, from->val);
		copyNode(from->next, to->next);
	}
}

//kopiowanie wartosci z jednej listy do drugiej dodajac wezel dwa razy
void copyTwice(node* from, node*& to)
{
	if (from)
	{
		add(to, from->val);
		add(to->next, from->val);
		copyTwice(from->next, to->next);
	}
}

//kopiowanie wartosci z jednej listy do drugiej wezel wartosc-razy
void copyManyTimes(node* from, node*& to)
{
	if (from)
	{
		for (int i = 0; i < from->val; i++)
		{
			add(to, from->val);
		}
		copyManyTimes(from->next, to->next);
	}
}

//zamiana perwszego z ostatnim
void swapFirsWithLast(node*& head)
{

	if (head)
	{
		if (head->next)
		{
			node* first = head;
			node* prevLast = NULL;
			node* last = head;
			while (last->next)
			{
				prevLast = last;
				last = last->next;
			}
			prevLast->next = first;
			last->next = first->next;
			first->next = NULL;
			head = last;
		}

	}
}

//dzielenie listy
void split(node*& head, node*& h1, node*& h2)
{
	node* p1 = NULL;
	node* p2 = NULL;
	while (head)
	{
		if (head->next)
		{
			p1 = head;
			head = head->next;
			p1->next = h1;
			h1 = p1;

			p2 = head;
			head = head->next;
			p2->next = h2;
			h2 = p2;
		}
		else
		{
			p1 = head;
			head = NULL;
			p1->next = h1;
			h1 = p1;

		}
	}

	head = NULL;
}

//dzielenie 2 metoda
void split2(node*& head, node*& h1, node*& h2)
{
	int i = 1;
	node* p1 = h1;
	node* p2 = h2;
	node* p = head;
	while (p->next)
	{
		i++;
		p = p->next;
	}

}

//cwiczenie listy
void merge(node*& head, node*& h1, node*& h2)
{
	node* tail = head;
	node* p1 = h1;
	node* p2 = h2;
	while (h1 != NULL && h2 != NULL)
	{
		if (h1->val > h2->val)
		{
			if (!head)
				head = p2;
			else
				tail->next = p2;
			tail = p2;
			h2 = p2->next;
			p2 = h2;
		}
		else
		{
			if (!head)
				head = p1;
			else
				tail->next = p1;
			tail = p1;
			h1 = p1->next;
			p1 = h1;

		}
	}

	if (h1)
	{
		tail->next = h1;
		h1 = NULL;
	}
	else
	{
		tail->next = h2;
		h2 = NULL;
	}
}

//algorytm merge sort
void mergeSort(node*& head)
{
	if (head && head->next)

	{
		node* h1 = NULL;
		node* h2 = NULL;

		split(head, h1, h2);

		mergeSort(h1);
		mergeSort(h2);

		merge(head, h1, h2);
	}
}

void swapFirstTwo(node*& head)
{
	if (head && head->next && head->next->next && head->next->next->next)
	{
		node* tmp = head;
		head = head->next->next;
		tmp->next->next = head->next->next;
		head->next->next = tmp;
	}
}

void reverseBetween(node*& head, int x, int y)
{
	node* p = head;
	node* p1 = NULL;
	node* p2 = NULL;
	node* temp = NULL;
	node* tail = NULL;
	while (p->next)
	{
		if (p->val == x)
		{
			p1 = p;
		}

		if (p->next->val == y)
		{
			p2 = p->next;
		}

		p = p->next;
	}
	p = p1;
	p1 = p1->next;
	while (p1->next)
	{
		tail = temp;
		temp = p1;
		p1 = p1->next;
		temp->next = tail;
		if (p1->val == p2->val)
		{
			break;
		}
	}
	p->next->next = p2;
	p->next = temp;
	//tail->next->next = p2;

}


int main()
{
	node* head = NULL;
	add(head, 1);
	add(head, 2);
	add(head, -3);
	add(head, 4);
	add(head, 5);
	add(head, 16);
	add(head, 7);
	add(head, 8);

	//swapFirstTwo(head);
	//mergeSort(head);

	reverseBetween(head, 1, 8);
	select(head);

}