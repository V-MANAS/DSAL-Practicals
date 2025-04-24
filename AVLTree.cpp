#include <algorithm>
#include <iostream>
using namespace std;
template <typename T>
class AVLNode {
public:
T key;
AVLNode* left;
AVLNode* right;
int height;
AVLNode(T k) : key(k), left(NULL), right(NULL), height(1) {}
};
template <typename T>
class AVLTree {
private:
AVLNode<T>* root;
int height(AVLNode<T>* node) {
if (node == NULL)
return 0;
return node->height;
}
int balanceFactor(AVLNode<T>* node) {
if (node == NULL)
return 0;
return height(node->left) - height(node->right);
}
AVLNode<T>* rightRotate(AVLNode<T>* y) {
AVLNode<T>* x = y->left;
AVLNode<T>* T2 = x->right;
x->right = y;
y->left = T2;
y->height = max(height(y->left), height(y->right)) + 1;
x->height = max(height(x->left), height(x->right)) + 1;
return x;
}
AVLNode<T>* leftRotate(AVLNode<T>* x) {
AVLNode<T>* y = x->right;
AVLNode<T>* T2 = y->left;
y->left = x;
x->right = T2;
x->height = max(height(x->left), height(x->right)) + 1;
y->height = max(height(y->left), height(y->right)) + 1;
return y;
}
AVLNode<T>* insert(AVLNode<T>* node, T key) {
if (node == NULL)
return new AVLNode<T>(key);
if (key < node->key)
node->left = insert(node->left, key);
else if (key > node->key)
node->right = insert(node->right, key);
else
return node;
node->height = 1 + max(height(node->left), height(node->right));
int balance = balanceFactor(node);
if (balance > 1 && key < node->left->key)
return rightRotate(node);
if (balance < -1 && key > node->right->key)
return leftRotate(node);
if (balance > 1 && key > node->left->key) {
node->left = leftRotate(node->left);
return rightRotate(node);
}
if (balance < -1 && key < node->right->key) {
node->right = rightRotate(node->right);
return leftRotate(node);
}
return node;
}
AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
if (root == NULL)
return root;
if (key < root->key)
root->left = deleteNode(root->left, key);
else if (key > root->key)
root->right = deleteNode(root->right, key);
 else {
 if (root->left == NULL)
 return root->right;
 else if (root->right == NULL)
 return root->left;
 AVLNode<T>* temp = root->right;
 while (temp->left != NULL)
 temp = temp->left;
 root->key = temp->key;
 root->right = deleteNode(root->right, temp->key);
 }
 if (root == NULL)
 return root;
 root->height = 1 + max(height(root->left), height(root->right));
 int balance = balanceFactor(root);
 // Left-left case
 if (balance > 1 && balanceFactor(root->left) >= 0)
 return rightRotate(root);
 // Left-right case
 if (balance > 1 && balanceFactor(root->left) < 0) {
 root->left = leftRotate(root->left);
 return rightRotate(root);
 }
 // Right-right case
 if (balance < -1 && balanceFactor(root->right) <= 0)
 return leftRotate(root);
 // Right-left case
 if (balance < -1 && balanceFactor(root->right) > 0) {
 root->right = rightRotate(root->right);
 return leftRotate(root);
 }
 return root;
 }
 // Print the tree
 void printTree(AVLNode<T>* node) {
 if (node == NULL)
 return;
 printTree(node->left);
 cout << node->key << " ";
 printTree(node->right);
 }
public:
 AVLTree() : root(NULL) {}
 // Insert a new key
 void insert(T key) {
 root = insert(root, key);
 }
 // Delete a key
 void deleteKey(T key) {
 root = deleteNode(root, key);
 }
 // Print the tree
 void print() {
 printTree(root);
 cout << endl;
 }
};
int main() {
 AVLTree<int> tree;
 int choice;
 while (true) {
 cout<<"\n<-------------->"<<endl;
 cout << "AVL Tree Menu" << endl;
 cout << "1. Insert a key" << endl;
 cout << "2. Delete a key" << endl;
 cout << "3. Print the tree" << endl;
 cout << "4. Exit" << endl;
 cout << "Enter your choice: ";
 cin >> choice;
switch (choice) {
 case 1: {
 int key;
 cout << "Enter the key to insert: ";
 cin >> key;
 tree.insert(key);
 break;
 }
 case 2: {
 int key;
 cout << "Enter the key to delete: ";
 cin >> key;
 tree.deleteKey(key);
 break;
 }
 case 3:
 cout << "AVL Tree: ";
 tree.print();
 break;
 case 4:
 return 0;
 default:
 cout << "Invalid choice. Please try again." << endl;
 }
 }
 return 0;
}