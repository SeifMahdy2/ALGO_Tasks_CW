#include <iostream>
using namespace std;

// Recursive function that earranges the elements of an array so that all elements less than or equal to k come before any elements larger than k
void rearrange(int arr[], int k, int n, int index = 0, int left = 0) {
    // if the index reaches the end of the array return
    if (index == n)
        return;

    // If current element is less than or equal to k, swap it with the leftmost element greater than k
    if (arr[index] <= k) {
        swap(arr[index], arr[left]); // swap current element with the left pointer
        ++left; // increment left pointer
    }

    // Recursively rearrange the rest of the array
    rearrange(arr, k, n, index + 1, left); // move to the next index and update left pointer
}

int main() {
    int unsortedArray[] = { 3, 1, 12, 9, 4, 10, 54, 34, 12, 89 };
    int key;
    cout << "Enter the key that you want: ";
    cin >> key;

    int n = size(unsortedArray);
    

    // Rearrange the array such that all elements less than or equal to the key come before any elements larger than the key
    rearrange(unsortedArray, key, n);

    // Rearrange again, but only for elements less than the key - 1
    rearrange(unsortedArray, key - 1, n);

    cout << "Output: [";
    for (int i = 0; i < n; ++i) {
        cout << unsortedArray[i];
        if (i < n - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
