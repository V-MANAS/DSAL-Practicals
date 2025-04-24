#include <iostream>
#include <climits>
#include <queue>
#include <utility>
using namespace std;

const int SIZE = 10; // Maximum number of nodes

class OBST {
private:
    int p[SIZE + 1]; // Probabilities of successful searches
    int q[SIZE + 1]; // Probabilities of unsuccessful searches
    int a[SIZE + 1]; // Keys
    int w[SIZE + 1][SIZE + 1]; // Weight matrix
    int c[SIZE + 1][SIZE + 1]; // Cost matrix
    int r[SIZE + 1][SIZE + 1]; // Root matrix
    int n; // Number of nodes
    bool dataEntered;
    bool treeBuilt;

public:
    OBST() : n(0), dataEntered(false), treeBuilt(false) {
        for (int i = 0; i <= SIZE; i++) {
            p[i] = q[i] = a[i] = 0;
            for (int j = 0; j <= SIZE; j++) {
                w[i][j] = c[i][j] = r[i][j] = 0;
            }
        }
    }

    void getInput() {
        cout << "Enter number of nodes (max " << SIZE << "): ";
        cin >> n;
        if (n <= 0 || n > SIZE) {
            cout << "Invalid number of nodes!\n";
            return;
        }

        cout << "Enter elements (keys):\n";
        for (int i = 1; i <= n; i++) {
            cout << "a[" << i << "]: ";
            cin >> a[i];
        }

        cout << "Enter search probabilities (p):\n";
        for (int i = 1; i <= n; i++) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }

        cout << "Enter miss probabilities (q):\n";
        for (int i = 0; i <= n; i++) {
            cout << "q[" << i << "]: ";
            cin >> q[i];
        }

        dataEntered = true;
        treeBuilt = false;
    }

    void buildOBST() {
        if (!dataEntered) {
            cout << "Error: Enter data first!\n";
            return;
        }

        for (int i = 0; i <= n; i++) {
            w[i][i] = q[i];
            c[i][i] = 0;
            r[i][i] = 0;
        }

        for (int length = 1; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length;
                w[i][j] = w[i][j - 1] + p[j] + q[j];
                int min = INT_MAX;

                for (int k = i + 1; k <= j; k++) {
                    int cost = c[i][k - 1] + c[k][j];
                    if (cost < min) {
                        min = cost;
                        r[i][j] = k;
                    }
                }
                c[i][j] = w[i][j] + min;
            }
        }

        treeBuilt = true;
        cout << "OBST built successfully. Cost: " << c[0][n] << endl;
    }

    void displayOBST() {
        if (!treeBuilt) {
            cout << "Error: Build tree first!\n";
            return;
        }

        cout << "\nOptimal BST Structure:\n";
        cout << "Root: " << a[r[0][n]] << " (Node " << r[0][n] << ")\n";
        cout << "Total cost: " << c[0][n] << "\n\n";

        queue<pair<int, int>> nodes;
        nodes.push(make_pair(0, n));
        cout << "Node\tLeft\tRight\n";
        cout << "-------------------\n";

        while (!nodes.empty()) {
            pair<int, int> range = nodes.front();
            nodes.pop();
            int i = range.first;
            int j = range.second;
            int root = r[i][j];
            cout << a[root] << "\t";

            if (r[i][root - 1] != 0) {
                cout << a[r[i][root - 1]];
                nodes.push(make_pair(i, root - 1));
            } else {
                cout << "-";
            }

            cout << "\t";

            if (r[root][j] != 0) {
                cout << a[r[root][j]];
                nodes.push(make_pair(root, j));
            } else {
                cout << "-";
            }

            cout << "\n";
        }
    }
};

int main() {
    OBST tree;
    int choice;

    do {
        cout << "\nOptimal BST Menu\n";
        cout << "1. Enter data\n";
        cout << "2. Build tree\n";
        cout << "3. Display tree\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tree.getInput();
            break;
        case 2:
            tree.buildOBST();
            break;
        case 3:
            tree.displayOBST();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
