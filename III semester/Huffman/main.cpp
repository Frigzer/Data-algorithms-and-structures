#include <iostream>

using namespace std;

struct tree
{
	tree* left;
	tree* right;
	char letter = NULL;
};

struct node
{
	node* next;
	node* prev;
	int value;
	tree* root;
};

void add(node*& head, char p, int val, node* x = NULL)
{
	if (!head)
	{
		head = new node;
		head->value = val;
		head->next = NULL;
		head->prev = x;
		tree* root = new tree;
		root->letter = p;
		root->left = NULL;
		root->right = NULL;
		head->root = root;
	}
	else
		add(head->next, p, val, head);

}

//funkcja koduje na podstawie podanego klucza
void code(node*& head)
{
	if (head && head->next)
	{
		node* p1 = head;
		node* p2 = head->next;

		node* p = head->next;
		while (p)
		{
			if (p->value < p1->value)
			{
				p2 = p1;
				p1 = p;
			}
			else if (p->value < p2->value)
			{
				p2 = p;
			}
			p = p->next;
		}

		tree* root = new tree;
		root->left = p1->root;
		root->right = p2->root;
		p1->root = root;
		p1->value += p2->value;

		if (p2->prev)
			p2->prev->next = p2->next;
		if (p2->next)
			p2->next->prev = p2->prev;
		if (p2 == head)
			head = p2->next;

		delete p2;
		code(head);
	}
}

//funkcja wyswietla binarne kody kazdego ze znakow uzytych w kluczu
void printBinaryCodes(tree* root, string strFromNode = "")
{
	if (root)
	{
		if (root->letter)
			cout << root->letter << ": " << strFromNode << endl;

		printBinaryCodes(root->left, strFromNode + "0");
		printBinaryCodes(root->right, strFromNode + "1");
	}
	else
		return;
}

//funkcja ktora wyswitla (istnieje po to aby w mainie nie odwolywac sie do head->root, tylko do samego head)
void displayCode(node* head)
{
	printBinaryCodes(head->root);
}

//funkcja ktora pobiera ciag 0 i 1 ktora zamienia ten ciag na jakis tekst
void decode(node* head, string text)
{
	tree* p = head->root;
	for (int i = 0; i <= text.size(); i++)
	{
		if (text[i] == '0')
		{
			if (p->left)
				p = p->left;
			else
			{
				cout << p->letter;
				p = head->root;
				i--;
			}
		}
		else if (text[i] == '1')
		{
			if (p->right)
				p = p->right;
			else
			{
				cout << p->letter;
				p = head->root;
				i--;
			}
		}
		else
			cout << p->letter;
	}
}

int main()
{
	node* head = NULL;
	//string text = "ASFASFGesfsfdwe?!2w:112DFSDF.,/!@%&*%$^@(*&)6ASDA";
	string text = "DAAFDDGFDSESESFSFDDFADFDAFDAFDDFSFDSFDSFDSDXFDDFSFDFFDAFDFDXFDFDGFDGFDSDAAAASAADSASASASASASASASAAAAAAAAASASSAWASAAAAAASASASDADDSADSADSSAASAAAADSADSSDAAAAADSASADSAAAAAAAASDADSADSADSASASASSSAAAAASSADSASADSAAAAFDFESDSADSADDSADADSFFFDSDSDAAAAAA";
	int table[126 - 33] = { 0 };
	for (int i = 0; i < (126 - 33); i++)
	{
		for (int j = 0; j < text.size(); j++)
		{
			if (text[j] == i + 33)
				table[i] += 1;
		}
		if (table[i])
			add(head, char(i + 33), table[i]);
	}
	code(head);

	displayCode(head);
	//cout << head->root->right->left->letter;
	decode(head, "110000100111");
	//decode(head, "111");
	return 0;
}