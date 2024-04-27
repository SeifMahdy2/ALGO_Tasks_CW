#include <iostream>
#include <unordered_set>

using namespace std;

void removeDuplicates(char arr[], int& length)
{
    unordered_set<char> setCh;

    int index = 0;
    for (int i = 0; i < length; i++) {
        if (setCh.insert(arr[i]).second) {
            // If insertion is successful
            arr[index++] = arr[i]; // Move unique character to the beginning of the array
        }
    }
    // Update the length of the array to the number of unique characters
    length = index;
}

int main()
{
    char arr[] = { 'a', 'b', 'c', 'a', 'd', 'e', 'b', 'f' };
    int length = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Function call to remove duplicates
    removeDuplicates(arr, length);

    cout << "Array after removing duplicates: ";
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}