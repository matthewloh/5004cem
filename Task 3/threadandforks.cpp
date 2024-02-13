/*
 Task 3 – Threads and Forks
[30 marks]
Write a multi threaded and fork program that does the following:
Both programs must implement the following:
a) Randomly generate a set of 100 numbers and fill up an array with those
numbers.
b) Use a multi threaded program that uses 1 thread to add the numbers and
another thread to minus the numbers.
c) Implement a separate program that does the same but using child process.
d) Design a method to compare both program’s performances. Justify your
comparison method.
e) Use the method in d) above to compare BOTH programs. Analyse and
discuss the results.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <random>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

// Function to generate random numbers
int randomNum() { return rand() % 10; }

// Function to add the numbers
void addNumbers(vector<int> &numbers, int start, int end, int &result) {
  for (int i = start; i < end; i++) {
    result += numbers[i];
  }
}

// Function to subtract the numbers
void subtractNumbers(vector<int> &numbers, int start, int end, int &result) {
  for (int i = start; i < end; i++) {
    result -= numbers[i];
  }
}

int main() {
  vector<int> numbers(100);
  srand(time(0));

  for (int i = 0; i < 100; i++) {
    numbers[i] = randomNum();
  }

  int addResult = 0;
  int subtractResult = 0;

  thread addThread(addNumbers, ref(numbers), 0, 100, ref(addResult));
  thread subtractThread(subtractNumbers, ref(numbers), 0, 100, ref(subtractResult));

  addThread.join();
  subtractThread.join();

  cout << "The sum of the numbers is: " << addResult << endl;
  cout << "The difference of the numbers is: " << subtractResult << endl;

  int addResultChild = 0;
  int subtractResultChild = 0;

  pid_t pid = fork();

  if (pid == 0) {
    addNumbers(numbers, 0, 100, addResultChild);
    exit(0);
  } else {
    wait(NULL);
    subtractNumbers(numbers, 0, 100, subtractResultChild);
  }

  cout << "The sum of the numbers using child process is: " << addResultChild << endl;
  cout << "The difference of the numbers using child process is: " << subtractResultChild << endl;

  return 0;
}