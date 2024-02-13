/*
Task 2 – Processes and Threads
Write a C++ multithreaded program that does the following:
1. Ask the user to key in the dimension of TWO (2) 2-d arrays.
2. Use a random number generator to populate BOTH arrays.
3. Use multi-threading to implement matrix multiplication.
4. Print the results.
*/

#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using namespace std;

// Function to generate random numbers
int randomNum() { return rand() % 10; }

// Function to multiply the matrices

void multiplyMatrices(vector<vector<int>> &matrix1,
                      vector<vector<int>> &matrix2, vector<vector<int>> &result,
                      int start, int end) {
  for (int i = start; i < end; i++) {
    for (int j = 0; j < matrix2[0].size(); j++) {
      for (int k = 0; k < matrix2.size(); k++) {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
}

int main() {
  int row1, col1, row2, col2;

  cout << "Enter the number of rows for the first matrix: ";
  cin >> row1;
  cout << "Enter the number of columns for the first matrix: ";
  cin >> col1;
  cout << "Enter the number of rows for the second matrix: ";
  cin >> row2;
  cout << "Enter the number of columns for the second matrix: ";
  cin >> col2;

  if (col1 != row2) {
    cout << "The number of columns in the first matrix must be equal to the "
            "number of rows in the second matrix."
         << endl;
    return 1;
  }

  vector<vector<int>> matrix1(row1, vector<int>(col1));
  vector<vector<int>> matrix2(row2, vector<int>(col2));
  vector<vector<int>> result(row1, vector<int>(col2));

  srand(time(0));

  for (int i = 0; i < row1; i++) {
    for (int j = 0; j < col1; j++) {
      matrix1[i][j] = randomNum();
    }
  }

  for (int i = 0; i < row2; i++) {
    for (int j = 0; j < col2; j++) {
      matrix2[i][j] = randomNum();
    }
  }

  vector<thread> threads;
  int numThreads = 4;
  int step = row1 / numThreads;

  for (int i = 0; i < numThreads; i++) {
    threads.push_back(thread(multiplyMatrices, ref(matrix1), ref(matrix2),
                             ref(result), i * step, (i + 1) * step));
  }

  for (int i = 0; i < numThreads; i++) {
    threads[i].join();
  }

  cout << "Matrix 1: " << endl;
  for (int i = 0; i < row1; i++) {
    for (int j = 0; j < col1; j++) {
      cout << matrix1[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Matrix 2: " << endl;
  for (int i = 0; i < row2; i++) {
    for

        (int j = 0; j < col2; j++) {
      cout << matrix2[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Result: " << endl;

  for (int i = 0; i < row1; i++) {
    for (int j = 0; j < col2; j++) {
      cout << result[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}