#include <iostream>
#include <vector>
using namespace std;

// Function to heapify a subtree rooted at index
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if left child is larger
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child is larger
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not the root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to implement Heap Sort
void heapSort(vector<int>& arr, int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);  // Move current root to end
        heapify(arr, i, 0);    // Call max heapify on the reduced heap
    }
}

// Function to print an array in ascending order
void printAscending(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// Function to print an array in descending order
void printDescending(const vector<int>& arr) {
    for (auto it = arr.rbegin(); it != arr.rend(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    int n, choice;

    // Input the number of elements
    cout << "Enter the number of elements: ";
    cin >> n;
    if (n <= 0) {
        cout << "Invalid number of elements!" << endl;
        return 0;
    }

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // Sort the array using heap sort
    heapSort(arr, n);

    // Menu-driven interaction
    while (true) {
        cout << "\n<------------------->" << endl;
        cout << "Heap Sorting Options" << endl;
        cout << "1. Ascending Order" << endl;
        cout << "2. Descending Order" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Sorted array in ascending order: ";
            printAscending(arr);
            break;

        case 2:
            cout << "Sorted array in descending order: ";
            printDescending(arr);
            break;

        case 3:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
