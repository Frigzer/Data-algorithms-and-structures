#include <iostream>
#include <iomanip>

using namespace std;

struct node
{
	node* parent;
	node* left;
	node* right;
	int value;
	int bf = 0;
	int height = 1;
};

void balanceTree(node*& root);
void resetBalanceFactor(node*& root);
void updateBalanceFactor(node*& root);
void preBalance(node*& root);

//wstawianie do drzewa
void insert(node*& root, int val, node* p = NULL)
{
	if (!root)
	{
		root = new node;
		root->value = val;
		root->left = NULL;
		root->right = NULL;
		root->parent = p;

		if (root->parent)//ustawienie balansu przy dodawaniu
		{
			node* temp = root;
			while (temp->parent)
			{
				if (temp == temp->parent->left)
				{
					temp->parent->bf++;
					if (temp->parent->right && temp->height <= temp->parent->right->height)
						break;
				}
				else if (temp == temp->parent->right)
				{
					temp->parent->bf--;
					if (temp->parent->left && temp->height <= temp->parent->left->height)
						break;
				}

				temp->parent->height++;

				temp = temp->parent;
			}

		}
	}
	else if (val >= root->value)
		insert(root->right, val, root);
	else
		insert(root->left, val, root);

	node* e = root;
	while (e->parent)
	{

		e = e->parent;
	}

	balanceTree(root); //rotacja drzewa

	//balansowanie po rotacji
	resetBalanceFactor(e);
	updateBalanceFactor(e);

}

void inorder(node* root)
{
	if (root)
	{
		inorder(root->left);
		cout << root->value << " ";
		inorder(root->right);
	}
}

void postorder(node* root)
{
	if (root)
	{
		postorder(root->left);
		postorder(root->right);
		cout << root->value << " ";
	}
}

void preorder(node* root)
{
	if (root)
	{
		cout << root->value << " ";
		preorder(root->left);
		preorder(root->right);
	}
}

//minimum
void getMin(node* root)
{
	if (root)
	{
		if (!root->left)
			cout << root->value;
		else
			getMin(root->left);
	}
}

//naksimum
void getMax(node* root)
{
	if (root)
	{
		if (!root->right)
			cout << root->value;
		else
			getMax(root->right);
	}
}

//poprzednik
void prev(node* root, int val)
{
	if (root)
	{
		if (root->value == val)
		{
			node* e = root;

			if (e->left)
			{
				getMax(e->left);
			}
			else if (e->parent->right == e)
			{
				cout << e->parent->value;
			}
			else
			{
				while (e->parent->left && e->parent->parent)
				{
					e = e->parent;
				}
				if (val > e->parent->value)
					cout << e->parent->value;
			}
		}
		else if (val > root->value)
			prev(root->right, val);
		else
			prev(root->left, val);
	}
}

//nastepnik
void next(node* root, int val)
{
	if (root)
	{
		if (root->value == val)
		{
			node* e = root;

			if (e->right)
			{
				getMin(e->right);
			}
			else if (e->parent->left == e)
			{
				cout << e->parent->value;
			}
			else
			{
				while (e->parent->right && e->parent->parent)
				{
					e = e->parent;
				}
				if (val < e->parent->value)
					cout << e->parent->value;
			}
		}
		else if (val > root->value)
			next(root->right, val);
		else
			next(root->left, val);
	}
}

//usuwanie
void remove(node*& root, int val)
{
	if (root)
	{
		if (val > root->value)
			remove(root->right, val);
		else if (val < root->value)
			remove(root->left, val);
		else
		{
			if (!root->left)
			{
				if (root->right)
					root->right->parent = root->parent;
				root = root->right;
			}
			else if (!root->right)
			{
				if (root->left)
					root->left->parent = root->parent;
				root = root->left;
			}
			else
			{
				node* e = root->right;
				while (e->left)
				{
					e = e->left;
				}
				if (e->parent->left == e)
				{
					e->parent->left = e->right;
					if (e->right)
						e->right->parent = e->parent;
				}
				else
				{
					e->parent->right = e->right;
					if (e->right)
						e->right->parent = e->parent;
				}
				e->parent = root->parent;
				e->left = root->left;
				e->right = root->right;
				if (e->left)
					e->left->parent = e;
				if (e->right)
					e->right->parent = e;
				delete root;
				root = e;
			}
		}
		//ustawienie balans factor po usunieciu
		resetBalanceFactor(root);
		updateBalanceFactor(root);

		//balansowanie drzewa
		preBalance(root);

		//ustawienie balans factor po rotacji
		resetBalanceFactor(root);
		updateBalanceFactor(root);
	}

}

//resetowanie balance factor i wysokosci dla wszystkich lisci
void resetBalanceFactor(node*& root)
{
	if (root)
	{
		root->bf = 0;
		root->height = 1;
		resetBalanceFactor(root->left);

		resetBalanceFactor(root->right);

	}
}

//aktualizacja balance factor i wysokosci
void updateBalanceFactor(node*& root)
{
	if (root)
	{
		if (root->parent)
		{
			node* temp = root;
			while (temp->parent)
			{

				if (temp == temp->parent->left)
				{
					temp->parent->bf++;
					if (temp->parent->right && temp->height < temp->parent->right->height)
						break;
				}
				else if (temp == temp->parent->right)
				{
					temp->parent->bf--;
					if (temp->parent->left && temp->height <= temp->parent->left->height)
						break;
				}
				temp->parent->height++;

				temp = temp->parent;
			}
		}
		updateBalanceFactor(root->left);
		updateBalanceFactor(root->right);
	}
}

//rotacja w lewo
void rotateLeft(node*& root)
{
	if (root && root->right)
	{
		node* temp = root->right;
		root->right = NULL;
		temp->parent = root->parent;
		root->parent = temp;
		if (!temp->left)
		{
			temp->left = root;
		}
		else if (temp->left->value > root->value)
		{
			root->right = temp->left;
			temp->left->parent = root;
			temp->left = root;
		}
		root = temp;
	}
}

//rotacja w prawo
void rotateRight(node*& root)
{
	if (root && root->left)
	{
		node* temp = root->left;
		root->left = NULL;
		temp->parent = root->parent;
		root->parent = temp;
		if (!temp->right)
		{
			temp->right = root;
		}
		else if (temp->right->value < root->value)
		{
			root->left = temp->right;
			temp->right->parent = root;
			temp->right = root;
		}
		root = temp;
	}
}

//funkcja sprawdza jaka rotacje trzeba wykonac
void balanceTree(node*& root)
{
	if (root)
	{
		if (root->bf >= 2)
		{
			if (root->left && root->left->bf <= -1)
			{
				rotateLeft(root->left);
				rotateRight(root);
			}
			else
				rotateRight(root);
		}
		else if (root->bf <= -2)
		{
			if (root->right && root->right->bf >= 1)
			{
				rotateRight(root->right);
				rotateLeft(root);
			}
			else
				rotateLeft(root);
		}
	}
}

//funkcja przechodzi drzewo inorder i balansuje drzewo
void preBalance(node*& root)
{
	if (root)
	{
		balanceTree(root);
		preBalance(root->left);
		preBalance(root->right);
	}
}

//funkcja z gpt, ktora wyswietla drzewo aby sprawdzic poprawnosc
void printTree(node* root, int indent = 0, bool isLeft = false) {
	if (root != nullptr) {
		if (root->right) {
			printTree(root->right, indent + 4, false);
		}
		if (indent > 0) {
			cout << setw(indent) << " ";
		}
		cout << (isLeft ? "/ " : "\\ ") << root->value << "\n";
		if (root->left) {
			printTree(root->left, indent + 4, true);
		}
	}
}

int main()
{

	node* root = NULL;

	insert(root, 20);
	insert(root, 3);
	insert(root, 10);
	insert(root, 40);
	insert(root, 30);
	insert(root, 25);
	insert(root, 5);
	insert(root, 8);
	insert(root, 50);
	insert(root, 60);
	insert(root, 9);

	//insert(root, 5);
	//insert(root, 10);
	//insert(root, 7);
	//insert(root, 4);
	//insert(root, 6);



	//insert(root, 7);
	//insert(root, 5);
	//insert(root, 4);
	//insert(root, 10);
	//insert(root, 6);

	//balanceTree(root);
	//rotateRight(root->right);
	//balanceTree(root);

	//resetBalanceFactor(root);
	//updateBalanceFactor(root);

	remove(root, 40);
	remove(root, 9);
	remove(root, 3);
	remove(root, 20);
	remove(root, 25);
	remove(root, 50);
	remove(root, 30);
	remove(root, 10);
	remove(root, 8);


	printTree(root);
	cout << root->bf;

}