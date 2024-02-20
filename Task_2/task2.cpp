/*
 * Task 2 - Processes and Threads
 * */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>

using namespace std;

// Function to generate random numbers for matrix initialization
// Generating numbers between 0 and 9

int getRandomNumber() { return rand() % 10; }

// Function to perform matrix multiplication for a portion of the result matrix
// Uses pass by reference for the matrices to avoid copying
// Has O(n^3) time complexity
void multiply(const vector<vector<int>> &MAT_A,
              const vector<vector<int>> &MAT_B, vector<vector<int>> &result,
              int startRow, int endRow, int startCol, int endCol) {
  for (int i = startRow; i < endRow; ++i) {
    for (int j = startCol; j < endCol; ++j) {
      int sum = 0;
      for (int k = 0; k < MAT_B.size(); ++k) {
        sum += MAT_A[i][k] * MAT_B[k][j];
      }
      result[i][j] = sum;
      cout << "Thread ID: " << this_thread::get_id() << " calculated element ("
           << i << " , " << j << ") : " << sum << endl;
    }
  }
}

void initialize_matrices(vector<vector<int>> &MAT_A, vector<vector<int>> &MAT_B,
                         int row_a, int col_a_row_b, int col_b) {
  cout << "Initializing matrices with random numbers..." << endl;
  cout << "Matrix A: " << row_a << " x " << col_a_row_b << endl;
  cout << "Matrix B: " << col_a_row_b << " x " << col_b << endl;

  for (int i = 0; i < row_a; ++i) {
    for (int j = 0; j < col_a_row_b; ++j) {
      MAT_A[i][j] = getRandomNumber();
    }
  }

  cout << "Matrix A initialized with elements: " << endl;
  for (int i = 0; i < row_a; ++i) {
    for (int j = 0; j < col_a_row_b; ++j) {
      cout << MAT_A[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < col_a_row_b; ++i) {
    for (int j = 0; j < col_b; ++j) {
      MAT_B[i][j] = getRandomNumber();
    }
  }

  cout << "Matrix B initialized with elements: " << endl;
  for (int i = 0; i < col_a_row_b; ++i) {
    for (int j = 0; j < col_b; ++j) {
      cout << MAT_B[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  srand(time(0)); // Seed for RNG

  int row_A, col_A_row_B, col_B;
  cout << "Enter the number of rows for the first matrix: ";
  cin >> row_A;
  cout << "Enter the number of columns for the first matrix and rows for the "
          "second matrix: ";
  cin >> col_A_row_B;
  cout << "Enter the number of columns for the second matrix: ";
  cin >> col_B;

  // Initialize the result matrix with zeros
  vector<vector<int>> RESULT_MAT(row_A, vector<int>(col_B, 0));

  // Initialize matrices A and B with random numbers
  vector<vector<int>> MAT_A(row_A, vector<int>(col_A_row_B));
  vector<vector<int>> MAT_B(col_A_row_B, vector<int>(col_B));

  initialize_matrices(MAT_A, MAT_B, row_A, col_A_row_B, col_B);

  // Create threads for matrix multiplication
  int numThreads =
      thread::hardware_concurrency(); // Number of available threads
  cout << "The number of threads available: " << numThreads << endl;
  vector<thread> threads;
  /*
   * 1. Calculate the number of rows each thread will process
   *  - For a 2 x 2 matrix and 4 threads, each thread will process 1 element
   *  - i.e | a b |    | 1 2 |     | a*1 + b*3  a*2 + b*4 |
   *        |     | *  |     |  =  |     ...        ...   |
   *        | c d |    | 3 4 |     | c*1 + d*3  c*2 + d*4 |
   * 2. Create threads and assign a portion of the result matrix to each thread
   * 3. Wait for all threads to finish
   * 4. Print the result matrix
   * */

  int rowsPerThread = row_A / numThreads;
  for (int i = 0; i < numThreads; ++i) {
    int startRow = i * rowsPerThread;
    // Ternary operator to handle the case where the number of rows is not
    // evenly divisible by the number of threads
    int endRow = (i == numThreads - 1) ? row_A : startRow + rowsPerThread;
    threads.push_back(thread(multiply, ref(MAT_A), ref(MAT_B), ref(RESULT_MAT),
                             startRow, endRow, 0, col_B));
  }

  // Wait for all threads to finish
  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }

  cout << "Resultant matrix after multiplication:" << endl;
  for (int i = 0; i < row_A; ++i) {
    for (int j = 0; j < col_B; ++j) {
      cout << RESULT_MAT[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
