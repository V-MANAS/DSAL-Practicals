#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory allocation error!\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data <= root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

int findHeight(Node* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int findMin(Node* root) {
    if (root == NULL) {
        cout << "Error: Tree is empty!\n";
        return -1; // Return a sentinel value indicating error
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

Node* mirrorTree(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirrorTree(root->left);
    mirrorTree(root->right);
    return root;
}

bool searchValue(Node* root, int value) {
    if (root == NULL) {
        return false;
    }
    if (root->data == value) {
        return true;
    }
    if (value < root->data) {
        return searchValue(root->left, value);
    } else {
        return searchValue(root->right, value);
    }
}

void preOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}

void postOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data << " ";
}

void displayTree(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return;
    }
    cout << "\nPre-order traversal: ";
    preOrderTraversal(root);
    cout << "\nIn-order traversal: ";
    inOrderTraversal(root);
    cout << "\nPost-order traversal: ";
    postOrderTraversal(root);
    cout << endl;
}

int main() {
    Node* root = NULL;
    int n, choice;

    cout << "Enter the number of nodes: ";
    cin >> n;

    if (n <= 0) {
        cout << "Tree must have at least one node!\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> value;
        root = insertNode(root, value);
    }

    while (true) {
        cout << "\nBinary Search Tree Menu\n";
        cout << "1. Insert new node\n";
        cout << "2. Find height of the tree\n";
        cout << "3. Find minimum data value\n";
        cout << "4. Mirror the tree\n";
        cout << "5. Search for a value\n";
        cout << "6. Display tree\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            root = insertNode(root, value);
            break;
        }
        case 2: {
            int height = findHeight(root);
            cout << "Height of the tree: " << height << endl;
            break;
        }
        case 3: {
            int min = findMin(root);
            if (min != -1) {
                cout << "Minimum data value: " << min << endl;
            }
            break;
        }
        case 4: {
            root = mirrorTree(root);
            cout << "Tree mirrored successfully.\n";
            break;
        }
        case 5: {
            int value;
            cout << "Enter value to search: ";
            cin >> value;
            bool found = searchValue(root, value);
            cout << (found ? "Value found in the tree.\n" : "Value not found in the tree.\n");
            break;
        }
        case 6:
            displayTree(root);
            break;
        case 7:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
