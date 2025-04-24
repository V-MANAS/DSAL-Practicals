#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(char data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to construct the expression tree from a prefix expression
Node* constructTree(const string& prefix) {
    stack<Node*> stack;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        if (isalpha(prefix[i])) {
            Node* newNode = createNode(prefix[i]);
            stack.push(newNode);
        } else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/') {
            if (stack.size() < 2) {
                cout << "Invalid prefix expression!" << endl;
                return nullptr;
            }
            Node* rightChild = stack.top(); stack.pop();
            Node* leftChild = stack.top(); stack.pop();
            Node* newNode = createNode(prefix[i]);
            newNode->left = leftChild;
            newNode->right = rightChild;
            stack.push(newNode);
        }
    }
    if (stack.size() != 1) {
        cout << "Invalid prefix expression!" << endl;
        return nullptr;
    }
    return stack.top();
}

// Function for post-order traversal of the tree
void postOrderTraversal(Node* root) {
    if (root == nullptr) return;
    stack<Node*> stack1, stack2;
    stack1.push(root);
    while (!stack1.empty()) {
        Node* temp = stack1.top();
        stack1.pop();
        stack2.push(temp);
        if (temp->right != nullptr) {
            stack1.push(temp->right);
        }
        if (temp->left != nullptr) {
            stack1.push(temp->left);
        }
    }
    while (!stack2.empty()) {
        cout << stack2.top()->data << " ";
        stack2.pop();
    }
    cout << endl;
}

// Function to delete the tree and free memory
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    cout << "Deleting Node: " << root->data << endl;
    delete root;
}

// Main function to interact with the user
int main() {
    string prefix;
    int choice;
    Node* root = nullptr;

    while (true) {
        cout << "\nExpression Tree Menu" << endl;
        cout << "1. Construct expression tree" << endl;
        cout << "2. Post-order traversal" << endl;
        cout << "3. Delete tree" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter a prefix expression: ";
            cin >> prefix;
            root = constructTree(prefix);
            break;

        case 2:
            if (root == nullptr) {
                cout << "Tree is empty." << endl;
            } else {
                cout << "Post-order traversal of the expression tree: ";
                postOrderTraversal(root);
            }
            break;

        case 3:
            if (root == nullptr) {
                cout << "Tree is empty." << endl;
            } else {
                deleteTree(root);
                root = nullptr;
                cout << "Expression tree deleted." << endl;
            }
            break;

        case 4:
            cout << "Thanks for using this program!" << endl;
            if (root != nullptr) {
                deleteTree(root);
            }
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
