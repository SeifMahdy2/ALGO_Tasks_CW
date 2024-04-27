#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

int insertionSort(int arr[], int n);
int bubbleSort(int arr[], int size);
int selectionSort(int arr[], int size);
int heap_sort(int arr[], int n);

// Function to generate random arrays
void generateRandomArrays(vector<vector<int>>& randomArrays) {
    // Seed for random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    // Generate 30 random arrays of varying sizes
    for (int i = 0; i < 30; ++i) {
        vector<int> arr(i + 1);
        iota(arr.begin(), arr.end(), 1); // Fill the array with values from 1 to i+1
        shuffle(arr.begin(), arr.end(), gen); // Shuffle array
        randomArrays.push_back(arr); // Add the shuffled array to the collection
    }
}

// Function to generate sorted arrays
void generateSortedArrays(vector<vector<int>>& sortedArrays) {
    // Generate 30 sorted arrays of varying sizes
    for (int i = 0; i < 30; ++i) {
        vector<int> arr(i + 1);
        iota(arr.begin(), arr.end(), 1); // Fill the array with values from 1 to i+1
        sortedArrays.push_back(arr); // Add the sorted array to the collection
    }
}

// Function to generate inversely sorted arrays
void generateInverselySortedArrays(vector<vector<int>>& inverselySortedArrays) {
    // Generate 30 inversely sorted arrays of varying sizes
    for (int i = 0; i < 30; ++i) {
        vector<int> arr(i + 1);
        iota(arr.rbegin(), arr.rend(), 1); // Fill the array with values from i+1 to 1 in reverse order
        inverselySortedArrays.push_back(arr); // Add the inversely sorted array to the collection
    }
}

// Insertion Sort
int insertionSort(int arr[], int n) {
    int comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        for (int j = 0; j < i; j++) {
            comparisons++;
            if (key < arr[i - j - 1]) {
                swap(arr[i - j], arr[i - j - 1]);
            }
            else {
                break; // Break the loop if the key is in the correct position
            }
        }
    }
    return comparisons;
}

// Bubble Sort
int bubbleSort(int arr[], int size) {
    int comparisons = 0;
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < size - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]); // Swap elements if they are in the wrong order
                swapped = true;
            }
        }
        if (!swapped) {
            // If no swaps were made, the array is already sorted
            break;
        }
    }
    return comparisons; // Return the total number of comparisons made
}

// Selection Sort
int selectionSort(int arr[], int size) {
    int comparisons = 0;
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (arr[j] < arr[min]) {
                min = j; // Find the index of the minimum element
            }
        }
        std::swap(arr[i], arr[min]); // Swap the minimum element with the current element
    }
    return comparisons; // Return the total number of comparisons made
}

// Heapify function for Heap Sort
int heapify(int arr[], int n, int i, int* comparisons) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    (*comparisons)++;

    if (r < n && arr[r] > arr[largest])
        largest = r;
    (*comparisons)++;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        (*comparisons)++;
        return heapify(arr, n, largest, comparisons); // Recursively heapify the affected subtree
    }
    return 1;
}

// Heap Sort
int heap_sort(int arr[], int n) {
    int comparisons = 0;

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        comparisons += heapify(arr, n, i, &comparisons);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        comparisons += heapify(arr, i, 0, &comparisons);
    }
    return comparisons; // Return the total number of comparisons made
}

// Function to test comparisons and execution time
void test_comparisons() {
    vector<vector<int>> randomArrays;
    vector<vector<int>> sortedArrays;
    vector<vector<int>> inverselySortedArrays;

    // Generate random, sorted, and inversely sorted arrays
    generateRandomArrays(randomArrays);
    generateSortedArrays(sortedArrays);
    generateInverselySortedArrays(inverselySortedArrays);

    int max_width = 20;
    cout << setw(max_width) << "Size"
        << setw(max_width) << "Random"
        << setw(max_width) << "Sorted"
        << setw(max_width) << "Inversely Sorted"
        << endl;

    // Insertion Sort
    cout << "Insertion Sort:" << endl;
    for (int i = 0; i < 30; ++i) {
        cout << setw(max_width) << i + 1;

        auto start_random = high_resolution_clock::now();
        int comparisons_random = insertionSort(&randomArrays[i][0], i + 1);
        auto stop_random = high_resolution_clock::now();
        auto duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        long long nanoseconds_random = duration_random.count();

        auto start_sorted = high_resolution_clock::now();
        int comparisons_sorted = insertionSort(&sortedArrays[i][0], i + 1);
        auto stop_sorted = high_resolution_clock::now();
        auto duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        long long nanoseconds_sorted = duration_sorted.count();

        auto start_inversely_sorted = high_resolution_clock::now();
        int comparisons_inversely_sorted = insertionSort(&inverselySortedArrays[i][0], i + 1);
        auto stop_inversely_sorted = high_resolution_clock::now();
        auto duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        long long nanoseconds_inversely_sorted = duration_inversely_sorted.count();

        cout << setw(max_width) << comparisons_random << " " << nanoseconds_random << "us"
            << setw(max_width) << comparisons_sorted << " " << nanoseconds_sorted << "us"
            << setw(max_width) << comparisons_inversely_sorted << " " << nanoseconds_inversely_sorted << "us"
            << endl;
    }

    // Bubble Sort
    cout << "Bubble Sort:" << endl;
    for (int i = 0; i < 30; ++i) {
        cout << setw(max_width) << i + 1;

        auto start_random = high_resolution_clock::now();
        int comparisons_random = bubbleSort(&randomArrays[i][0], i + 1);
        auto stop_random = high_resolution_clock::now();
        auto duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        long long nanoseconds_random = duration_random.count();

        auto start_sorted = high_resolution_clock::now();
        int comparisons_sorted = bubbleSort(&sortedArrays[i][0], i + 1);
        auto stop_sorted = high_resolution_clock::now();
        auto duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        long long nanoseconds_sorted = duration_sorted.count();

        auto start_inversely_sorted = high_resolution_clock::now();
        int comparisons_inversely_sorted = bubbleSort(&inverselySortedArrays[i][0], i + 1);
        auto stop_inversely_sorted = high_resolution_clock::now();
        auto duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        long long nanoseconds_inversely_sorted = duration_inversely_sorted.count();

        cout << setw(max_width) << comparisons_random << " " << nanoseconds_random << "us"
            << setw(max_width) << comparisons_sorted << " " << nanoseconds_sorted << "us"
            << setw(max_width) << comparisons_inversely_sorted << " " << nanoseconds_inversely_sorted << "us"
            << endl;
    }

    // Selection Sort
    cout << "Selection Sort:" << endl;
    for (int i = 0; i < 30; ++i) {
        cout << setw(max_width) << i + 1;

        auto start_random = high_resolution_clock::now();
        int comparisons_random = selectionSort(&randomArrays[i][0], i + 1);
        auto stop_random = high_resolution_clock::now();
        auto duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        long long nanoseconds_random = duration_random.count();

        auto start_sorted = high_resolution_clock::now();
        int comparisons_sorted = selectionSort(&sortedArrays[i][0], i + 1);
        auto stop_sorted = high_resolution_clock::now();
        auto duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        long long nanoseconds_sorted = duration_sorted.count();

        auto start_inversely_sorted = high_resolution_clock::now();
        int comparisons_inversely_sorted = selectionSort(&inverselySortedArrays[i][0], i + 1);
        auto stop_inversely_sorted = high_resolution_clock::now();
        auto duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        long long nanoseconds_inversely_sorted = duration_inversely_sorted.count();

        cout << setw(max_width) << comparisons_random << " " << nanoseconds_random << "us"
            << setw(max_width) << comparisons_sorted << " " << nanoseconds_sorted << "us"
            << setw(max_width) << comparisons_inversely_sorted << " " << nanoseconds_inversely_sorted << "us"
            << endl;
    }

    // Heap Sort
    cout << "Heap Sort:" << endl;
    for (int i = 0; i < 30; ++i) {
        cout << setw(max_width) << i + 1;

        auto start_random = high_resolution_clock::now();
        int comparisons_random = heap_sort(&randomArrays[i][0], i + 1);
        auto stop_random = high_resolution_clock::now();
        auto duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        long long nanoseconds_random = duration_random.count();

        auto start_sorted = high_resolution_clock::now();
        int comparisons_sorted = heap_sort(&sortedArrays[i][0], i + 1);
        auto stop_sorted = high_resolution_clock::now();
        auto duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        long long nanoseconds_sorted = duration_sorted.count();

        auto start_inversely_sorted = high_resolution_clock::now();
        int comparisons_inversely_sorted = heap_sort(&inverselySortedArrays[i][0], i + 1);
        auto stop_inversely_sorted = high_resolution_clock::now();
        auto duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        long long nanoseconds_inversely_sorted = duration_inversely_sorted.count();

        cout << setw(max_width) << comparisons_random << " " << nanoseconds_random << "us"
            << setw(max_width) << comparisons_sorted << " " << nanoseconds_sorted << "us"
            << setw(max_width) << comparisons_inversely_sorted << " " << nanoseconds_inversely_sorted << "us"
            << endl;
    }

    // Write results to CSV files
    ofstream outfile("sorting_comparisons.csv");
    ofstream timefile("sorting_times.csv");
    if (!outfile.is_open() || !timefile.is_open()) {
        cout << "Error: Unable to open the file." << endl;
        return;
    }

    outfile << "Size,Random_InsertionSort,Sorted_InsertionSort,InverselySorted_InsertionSort,"
        << "Random_BubbleSort,Sorted_BubbleSort,InverselySorted_BubbleSort,"
        << "Random_SelectionSort,Sorted_SelectionSort,InverselySorted_SelectionSort,"
        << "Random_HeapSort,Sorted_HeapSort,InverselySorted_HeapSort" << endl;

    timefile << "Size,Random_InsertionSort,Sorted_InsertionSort,InverselySorted_InsertionSort,"
        << "Random_BubbleSort,Sorted_BubbleSort,InverselySorted_BubbleSort,"
        << "Random_SelectionSort,Sorted_SelectionSort,InverselySorted_SelectionSort,"
        << "Random_HeapSort,Sorted_HeapSort,InverselySorted_HeapSort" << endl;

    for (int i = 0; i < 30; ++i) {
        outfile << i + 1;
        timefile << i + 1;

        int comparisons_random, comparisons_sorted, comparisons_inversely_sorted;
        long long nanoseconds_random, nanoseconds_sorted, nanoseconds_inversely_sorted;

        // Insertion Sort
        comparisons_random = insertionSort(&randomArrays[i][0], i + 1);
        auto start_random = high_resolution_clock::now();
        insertionSort(&randomArrays[i][0], i + 1);
        auto stop_random = high_resolution_clock::now();
        auto duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        nanoseconds_random = duration_random.count();
        comparisons_sorted = insertionSort(&sortedArrays[i][0], i + 1);
        auto start_sorted = high_resolution_clock::now();
        insertionSort(&sortedArrays[i][0], i + 1);
        auto stop_sorted = high_resolution_clock::now();
        auto duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        nanoseconds_sorted = duration_sorted.count();
        comparisons_inversely_sorted = insertionSort(&inverselySortedArrays[i][0], i + 1);
        auto start_inversely_sorted = high_resolution_clock::now();
        insertionSort(&inverselySortedArrays[i][0], i + 1);
        auto stop_inversely_sorted = high_resolution_clock::now();
        auto duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        nanoseconds_inversely_sorted = duration_inversely_sorted.count();
        outfile << "," << comparisons_random << "," << comparisons_sorted << "," << comparisons_inversely_sorted;
        timefile << "," << nanoseconds_random << "," << nanoseconds_sorted << "," << nanoseconds_inversely_sorted;

        // Bubble Sort
        comparisons_random = bubbleSort(&randomArrays[i][0], i + 1);
        start_random = high_resolution_clock::now();
        bubbleSort(&randomArrays[i][0], i + 1);
        stop_random = high_resolution_clock::now();
        duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        nanoseconds_random = duration_random.count();
        comparisons_sorted = bubbleSort(&sortedArrays[i][0], i + 1);
        start_sorted = high_resolution_clock::now();
        bubbleSort(&sortedArrays[i][0], i + 1);
        stop_sorted = high_resolution_clock::now();
        duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        nanoseconds_sorted = duration_sorted.count();
        comparisons_inversely_sorted = bubbleSort(&inverselySortedArrays[i][0], i + 1);
        start_inversely_sorted = high_resolution_clock::now();
        bubbleSort(&inverselySortedArrays[i][0], i + 1);
        stop_inversely_sorted = high_resolution_clock::now();
        duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        nanoseconds_inversely_sorted = duration_inversely_sorted.count();
        outfile << "," << comparisons_random << "," << comparisons_sorted << "," << comparisons_inversely_sorted;
        timefile << "," << nanoseconds_random << "," << nanoseconds_sorted << "," << nanoseconds_inversely_sorted;

        // Selection Sort
        comparisons_random = selectionSort(&randomArrays[i][0], i + 1);
        start_random = high_resolution_clock::now();
        selectionSort(&randomArrays[i][0], i + 1);
        stop_random = high_resolution_clock::now();
        duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        nanoseconds_random = duration_random.count();
        comparisons_sorted = selectionSort(&sortedArrays[i][0], i + 1);
        start_sorted = high_resolution_clock::now();
        selectionSort(&sortedArrays[i][0], i + 1);
        stop_sorted = high_resolution_clock::now();
        duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        nanoseconds_sorted = duration_sorted.count();
        comparisons_inversely_sorted = selectionSort(&inverselySortedArrays[i][0], i + 1);
        start_inversely_sorted = high_resolution_clock::now();
        selectionSort(&inverselySortedArrays[i][0], i + 1);
        stop_inversely_sorted = high_resolution_clock::now();
        duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        nanoseconds_inversely_sorted = duration_inversely_sorted.count();
        outfile << "," << comparisons_random << "," << comparisons_sorted << "," << comparisons_inversely_sorted;
        timefile << "," << nanoseconds_random << "," << nanoseconds_sorted << "," << nanoseconds_inversely_sorted;

        // Heap Sort
        comparisons_random = heap_sort(&randomArrays[i][0], i + 1);
        start_random = high_resolution_clock::now();
        heap_sort(&randomArrays[i][0], i + 1);
        stop_random = high_resolution_clock::now();
        duration_random = duration_cast<nanoseconds>(stop_random - start_random);
        nanoseconds_random = duration_random.count();
        comparisons_sorted = heap_sort(&sortedArrays[i][0], i + 1);
        start_sorted = high_resolution_clock::now();
        heap_sort(&sortedArrays[i][0], i + 1);
        stop_sorted = high_resolution_clock::now();
        duration_sorted = duration_cast<nanoseconds>(stop_sorted - start_sorted);
        nanoseconds_sorted = duration_sorted.count();
        comparisons_inversely_sorted = heap_sort(&inverselySortedArrays[i][0], i + 1);
        start_inversely_sorted = high_resolution_clock::now();
        heap_sort(&inverselySortedArrays[i][0], i + 1);
        stop_inversely_sorted = high_resolution_clock::now();
        duration_inversely_sorted = duration_cast<nanoseconds>(stop_inversely_sorted - start_inversely_sorted);
        nanoseconds_inversely_sorted = duration_inversely_sorted.count();
        outfile << "," << comparisons_random << "," << comparisons_sorted << "," << comparisons_inversely_sorted;
        timefile << "," << nanoseconds_random << "," << nanoseconds_sorted << "," << nanoseconds_inversely_sorted;

        outfile << endl;
        timefile << endl;
    }

    // Close the files
    outfile.close();
    timefile.close();
}

// Main function
int main() {
    // Call the test_comparisons function to run the tests
    test_comparisons();
    return 0;
}
