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

// Struct to hold arguments for the thread function
struct ThreadArgs {
  const vector<vector<int>> *MAT_A;
  const vector<vector<int>> *MAT_B;
  vector<vector<int>> *RESULT_MAT;
  int startRow;
  int endRow;
  int col_B;
};

// Function to perform matrix multiplication for a portion of the result matrix
// Uses pass by reference for the matrices to avoid copying
// Has O(n^3) time complexity
void *multiply(void *arg) {
  ThreadArgs *args = reinterpret_cast<ThreadArgs *>(arg);
  const vector<vector<int>> &MAT_A = *(args->MAT_A);
  const vector<vector<int>> &MAT_B = *(args->MAT_B);
  vector<vector<int>> &RESULT_MAT = *(args->RESULT_MAT);
  int startRow = args->startRow;
  int endRow = args->endRow;
  int col_B = args->col_B;

  for (int i = startRow; i < endRow; ++i) {
    for (int j = 0; j < col_B; ++j) {
      int sum = 0;
      for (size_t k = 0; k < MAT_B.size(); ++k) {
        sum += MAT_A[i][k] * MAT_B[k][j];
      }
      RESULT_MAT[i][j] = sum;
    }
  }
  pthread_exit(NULL);
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
  vector<pthread_t> threads(numThreads);
  vector<ThreadArgs> args(numThreads);

  // Calculate the number of rows each thread will process
  int rowsPerThread = row_A / numThreads;
  for (int i = 0; i < numThreads; ++i) {
    args[i] = {&MAT_A,
               &MAT_B,
               &RESULT_MAT,
               i * rowsPerThread,
               (i == numThreads - 1) ? row_A : (i + 1) * rowsPerThread,
               col_B};
    pthread_create(&threads[i], NULL, multiply, &args[i]);
  }

  // Wait for all threads to finish
  for (int i = 0; i < numThreads; ++i) {
    pthread_join(threads[i], NULL);
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
