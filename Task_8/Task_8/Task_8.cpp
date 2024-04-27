#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

// Structure to hold matrix data and its dimensions
struct Matrix {
    vector<vector<int>> data;
    int rows;
    int cols;
};

// Structure to pass data to pthread functions
struct ThreadData {
    const Matrix* A;
    const Matrix* B;
    Matrix* result;
    int startRow;
    int endRow;
};

// Function to perform matrix multiplication for a range of rows
void* multiplyRows(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    const Matrix* A = data->A;
    const Matrix* B = data->B;
    Matrix* result = data->result;

    for (int i = data->startRow; i < data->endRow; ++i) {
        for (int j = 0; j < B->cols; ++j) {
            result->data[i][j] = 0;
            for (int k = 0; k < A->cols; ++k) {
                result->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

// Function to perform matrix multiplication using pthreads
Matrix multiplyMatrices(const Matrix& A, const Matrix& B, int numThreads) {
    if (A.cols != B.rows) {
        cerr << "Error: Matrices dimensions mismatch for multiplication." << endl;
        exit(1);
    }

    Matrix result;
    result.rows = A.rows;
    result.cols = B.cols;
    result.data.resize(A.rows, vector<int>(B.cols, 0));

    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];
    int rowsPerThread = A.rows / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        threadData[i].A = &A;
        threadData[i].B = &B;
        threadData[i].result = &result;
        threadData[i].startRow = i * rowsPerThread;
        threadData[i].endRow = (i == numThreads - 1) ? A.rows : (i + 1) * rowsPerThread;
        pthread_create(&threads[i], NULL, multiplyRows, (void*)&threadData[i]);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return result;
}

// Function to print matrix
void printMatrix(const Matrix& mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            cout << mat.data[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix A, B;
    // Example matrices A and B
    A.rows = 3; A.cols = 2;
    A.data = { {1, 2}, {3, 4}, {5, 6} };
    B.rows = 2; B.cols = 3;
    B.data = { {7, 8, 9}, {10, 11, 12} };

    int numThreads = 2; // Number of threads for parallel computation
    Matrix result = multiplyMatrices(A, B, numThreads);

    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << endl << "Matrix B:" << endl;
    printMatrix(B);
    cout << endl << "Result Matrix:" << endl;
    printMatrix(result);

    return 0;
}
