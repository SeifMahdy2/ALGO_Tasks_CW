#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Doubly linked list class
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Function to append a node to the end of the list
    void append(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Function to print the list
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Function to swap two nodes
    void swap(Node* a, Node* b) {
        int temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    // Function to partition the list and return the pivot node
    Node* partition(Node* low, Node* high) {
        int pivot = high->data;
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) {
            if (j->data <= pivot) {
                i = (i == nullptr) ? low : i->next;
                swap(i, j);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i, high);
        return i;
    }

    // Recursive function to perform Quick Sort
    void quickSort(Node* low, Node* high) {
        if (high != nullptr && low != high && low != high->next) {
            Node* pivot = partition(low, high);
            quickSort(low, pivot->prev);
            quickSort(pivot->next, high);
        }
    }

    // Function to initiate Quick Sort
    void quickSort() {
        quickSort(head, tail);
    }
};

// Main function
int main() {
    DoublyLinkedList dll;
    dll.append(5);
    dll.append(9);
    dll.append(3);
    dll.append(7);
    dll.append(2);
    dll.append(8);
    dll.append(1);

    cout << "Original list:" << endl;
    dll.printList();

    dll.quickSort();

    cout << "Sorted list:" << endl;
    dll.printList();

    return 0;
}
