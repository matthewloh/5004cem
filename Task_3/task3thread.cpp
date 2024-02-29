#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

// Threaded version
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

  int addResult = 0;
  int subtractResult = 0;

  thread addThread(addNumbers, ref(numbers), 0, 100, ref(addResult));
  thread subtractThread(subtractNumbers, ref(numbers), 0, 100,
                        ref(subtractResult));

  addThread.join();
  subtractThread.join();

  cout << "The sum of the numbers is: " << addResult << endl;
  cout << "The difference of the numbers is: " << subtractResult << endl;

  auto end = chrono::steady_clock::now();
  auto duration = end - start;
  cout << "Time taken: "
       << chrono::duration_cast<chrono::nanoseconds>(duration).count()
       << " nanoseconds" << endl;
  return 0;
}
