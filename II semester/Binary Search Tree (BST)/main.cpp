#include <iostream>
#include <string>

using namespace std;

struct Product {
    string nazwa;
    int ilosc;
    int zakupione;
    int czestosc;
};

struct Node {
    Product produkt;
    Node* left;
    Node* right;
};

class BST {
private:
    Node* root;

    // Funkcja pomocnicza do dodawania nowego wêz³a do drzewa
    Node* add(Node* node, Product produkt) {
        if (node == NULL) {
            Node* newNode = new Node;
            newNode->produkt = produkt;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }

        if (produkt.nazwa < node->produkt.nazwa) {
            node->left = add(node->left, produkt);
        }
        else if (produkt.nazwa > node->produkt.nazwa) {
            node->right = add(node->right, produkt);
        }
        else {
            node->produkt.ilosc += produkt.ilosc;
        }

        return node;
    }

    // Funkcja pomocnicza do wyszukiwania wêz³a o podanej nazwie produktu
    Node* find(Node* node, string nazwa) {
        if (node == NULL) {
            return NULL;
        }

        if (nazwa < node->produkt.nazwa) {
            return find(node->left, nazwa);
        }
        else if (nazwa > node->produkt.nazwa) {
            return find(node->right, nazwa);
        }
        else {
            node->produkt.czestosc++;
            return node;
        }
    }

    // Funkcja pomocnicza do usuwania wêz³ów o iloci mniejszej od 1 oraz wyszukiwanych rzadziej ni¿ N razy
    Node* remove(Node* node, int n) {
        if (node == NULL) {
            return NULL;
        }

        node->left = remove(node->left, n);
        node->right = remove(node->right, n);

        if (node->produkt.ilosc < 1 || node->produkt.czestosc < n) {
            Node* temp = node;
            if (node->left == NULL) {
                node = node->right;
            }
            else if (node->right == NULL) {
                node = node->left;
            }
            else {
                Node* min = findMin(node->right);
                node->produkt = min->produkt;
                node->right = remove(node->right, n);
            }
            delete temp;
        }

        return node;
    }

    // Funkcja pomocnicza do wyszukiwania wêz³a o najmniejszej wartoci w poddrzewie
    Node* findMin(Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

public:
    BST() {
        root = NULL;
    }

    void addProduct(Product produkt) {
        root = add(root, produkt);
    }

    Node* findProduct(string nazwa) {
        return find(root, nazwa);
    }

    void purchaseProduct(string nazwa, int ilosc) {
        Node* node = find(root, nazwa);
        if (node != NULL) {
            node->produkt.ilosc -= ilosc;
        }
    }

    void updateTree(int n) {
        root = remove(root, n);
    }
};

int main() {
    BST bst;

    // Dodawanie produktów
    Product p1 = { "Myszka", 10, 0, 0 };
    Product p2 = { "Klawiatura", 5, 0, 0 };
    Product p3 = { "Monitor", 2, 0, 0 };
    bst.addProduct(p1);
    bst.addProduct(p2);
    bst.addProduct(p3);

    // Wyszukiwanie produktu po nazwie
    Node* node1 = bst.findProduct("Myszka");
    if (node1 != NULL) {
        cout << "Znaleziono produkt " << node1->produkt.nazwa << endl;
    }
    else {
        cout << "Nie znaleziono produktu" << endl;
    }

    // Zakup produktu
    bst.purchaseProduct("Myszka", 5);

    // Aktualizacja drzewa
    bst.updateTree(1);

    return 0;
}
