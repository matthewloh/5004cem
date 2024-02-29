#include <chrono>
#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

// Fork-based version
int randomNum() { return rand() % 100; }

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

  auto start = chrono::steady_clock::now();

  int addResultChild = 0;
  int subtractResultChild = 0;

  pid_t pid = fork();

  cout << "Process id = " << pid << "\n";

  if (pid == 0) {
    /* This is executed by the child process
     * */
    cout << "Child process\n";
    for (int i = 0; i < 100; i++) {
      addResultChild += numbers[i];
    }
    cout << "The sum of the numbers is: " << addResultChild << endl;
    exit(0);
  } else {
    /* This is executed by the parent process
     * */
    cout << "Parent process\n";
    for (int i = 0; i < 100; i++) {
      subtractResultChild -= numbers[i];
    }
    cout << "The difference of the numbers is: " << subtractResultChild << endl;
    wait(NULL);
  }
  auto end = chrono::steady_clock::now();
  auto duration = end - start;
  cout << "Time taken: "
       << chrono::duration_cast<chrono::nanoseconds>(duration).count()
       << " nanoseconds" << endl;
  return 0;
}
