#include <iostream>
#include <string>
using namespace std;

struct Node {
    string label;
    int childCount;
    Node* children[10];

    Node() : childCount(0) {
        for (int i = 0; i < 10; i++) {
            children[i] = nullptr;
        }
    }

    ~Node() {
        for (int i = 0; i < childCount; i++) {
            delete children[i];
        }
    }
};

class BookTree {
public:
    BookTree() : root(nullptr) {}
    ~BookTree() {
        delete root;
    }

    void createTree() {
        if (root) {
            cout << "Book tree already exists. Replace it? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'n' || choice == 'N') {
                return;
            }
            delete root; // Clear the existing tree
        }

        root = new Node();
        cout << "Enter name of the book: ";
        getline(cin, root->label);

        int chapterCount;
        cout << "Enter number of chapters in the book: ";
        cin >> chapterCount;
        cin.ignore();

        for (int i = 0; i < chapterCount; i++) {
            createChapter(root);
        }
    }

    void displayTree() const {
        if (!root) {
            cout << "Book tree does not exist." << endl;
            return;
        }
        cout << "\n----- Book Hierarchy -----\n";
        displayNode(root, "");
    }

private:
    Node* root;

    void createChapter(Node* parent) {
        Node* chapter = new Node();
        cout << "Enter name of Chapter " << parent->childCount + 1 << ": ";
        getline(cin, chapter->label);

        int sectionCount;
        cout << "Enter number of sections in Chapter " << chapter->label << ": ";
        cin >> sectionCount;
        cin.ignore();

        for (int i = 0; i < sectionCount; i++) {
            createSection(chapter);
        }
        parent->children[parent->childCount++] = chapter;
    }

    void createSection(Node* parent) {
        Node* section = new Node();
        cout << "Enter name of Section " << parent->childCount + 1 << ": ";
        getline(cin, section->label);

        int subsectionCount;
        cout << "Enter number of subsections in Section " << section->label << ": ";
        cin >> subsectionCount;
        cin.ignore();

        for (int i = 0; i < subsectionCount; i++) {
            createSubsection(section);
        }
        parent->children[parent->childCount++] = section;
    }

    void createSubsection(Node* parent) {
        Node* subsection = new Node();
        cout << "Enter name of Subsection " << parent->childCount + 1 << ": ";
        getline(cin, subsection->label);

        parent->children[parent->childCount++] = subsection;
    }

    void displayNode(Node* node, const string& indent) const {
        cout << indent << node->label << endl;
        for (int i = 0; i < node->childCount; i++) {
            displayNode(node->children[i], indent + "  ");
        }
    }
};

int main() {
    BookTree bookTree;
    int choice;

    while (true) {
        cout << "\n-----------------\n";
        cout << "Book Tree Menu\n";
        cout << "-----------------\n";
        cout << "1. Create Book Tree\n";
        cout << "2. Display Book Tree\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            bookTree.createTree();
            break;
        case 2:
            bookTree.displayTree();
            break;
        case 3:
            cout << "Thanks for using this program!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
