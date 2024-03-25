#include <iostream>
#include <fstream>

using namespace std;


struct node {
	node* next;
	int to;
	int dist;
};

void Add(node*& head, int to, int value)
{
	if (!head)
	{
		head = new node;
		head->to = to;
		head->dist = value;
		head->next = NULL;
	}
	else
		Add(head->next, to, value);
}

void show(node* head)
{
	if (head)
	{
		cout << head->to << "/" << head->dist << "->";
		show(head->next);
	}
	else
		cout << "NULL";
}

struct node2 {
	node2* next;
	int from;
	int to;
	int dist;

};

void add2(node2*& head, int from, int to, int dist)
{
	if (!head)
	{
		head = new node2;
		head->from = from;
		head->to = to;
		head->dist = dist;
		head->next = NULL;
	}
	else
		add2(head->next, from, to, dist);

}

void display(node2*& head)
{
	if (head)
	{
		cout << head->from << "->" << head->to << ": " << head->dist << endl;
		display(head->next);
	}

}

int main()
{
	fstream file;
	file.open("graf.txt");
	int size = 0;
	file >> size;

	int** M = new int* [size];
	for (int i = 0; i < size; i++)
		M[i] = new int[size];

	//Macierz sasiedztwa
	cout << "Macierz sasiedztwa" << endl;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			file >> M[i][j];

	file.close();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << M[i][j] << " ";
		cout << endl;
	}
	cout << endl;


	//Lista sasiedztwa grafu w oparciu o macierz
	cout << "Lista sasiedztwa grafu w oparciu o macierz" << endl;
	node** LN = new node * [size];
	for (int i = 0; i < size; i++)
		LN[i] = NULL;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (M[i][j] != 0)
				Add(LN[i], j, M[i][j]);
	for (int i = 0; i < size; i++)
	{
		cout << "LN[" << i << "]->";
		show(LN[i]);
		cout << endl;
	}

	//Lista krawedzi grafu w oparciu o macierz
	cout << "\nLista krawedzi grafu w oparciu o macierz";
	node2* LE = NULL;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (M[i][j] != 0)
				add2(LE, i, j, M[i][j]);
	cout << endl;
	display(LE);

	//Lista krawedzi grafu w oparciu o liste sasiedztwa
	cout << "\nLista krawedzi grafu w oparciu o liste sasiedztwa" ;
	LE = NULL;

	for (int i = 0; i < size; i++)
	{
		node* temp = LN[i];
		while (temp)
		{
			add2(LE, i, temp->to, temp->dist);
			temp = temp->next;
		}
	}

	cout << endl;
	display(LE);
	cout << endl;

	// lista sasiedztwa grafu w oparciu o liste krawedzi
	cout << "Lista sasiedztwa grafu w oparciu o liste krawedzi" << endl;
	LN = new node * [size];
	for (int i = 0; i < size; i++)
		LN[i] = NULL;

	node2* temp = LE;
	for (int i = 0; i < size; i++)
	{
		while (temp)
		{
			Add(LN[i], temp->to, temp->dist);
			if (temp->next && (temp->from != temp->next->from))
			{
				temp = temp->next;
				break;
			}
			temp = temp->next;
		}
	}
	for (int i = 0; i < size; i++)
	{
		cout << "LN[" << i << "]->";
		show(LN[i]);
		cout << endl;
	}
}