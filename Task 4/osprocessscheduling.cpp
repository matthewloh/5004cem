/*
Task 4 - OS Process Scheduling
[20 marks]
Write a C/C++/java/python program that does the following:
a) Derive a method to keep information about 5 processes. The information
shows the process name and CPU burst cycle of each process.
b) Ask the user to input time quantum value. The time quantum cannot be <=
1 and cannot be larger than the biggest CPU cycle of your processes.
c) Based on the time quantum value supplied by the user, simulate Round
Robin Scheduler.
d) Print out the remaining CPU cycles for each process after every time step.
*/

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Process {
  string name;
  int cpuBurst;
};

int main() {
  vector<Process> processes = {{"P1", 10}, {"P2", 5}, {"P3", 8}, {"P4", 6}, {"P5", 7}};
  queue<Process> readyQueue;
  int timeQuantum;

  cout << "Enter the time quantum: ";
  cin >> timeQuantum;

  for (auto process : processes) {
    readyQueue.push(process);
  }

  while (!readyQueue.empty()) {
    Process currentProcess = readyQueue.front();
    readyQueue.pop();

    if (currentProcess.cpuBurst > timeQuantum) {
      currentProcess.cpuBurst -= timeQuantum;
      readyQueue.push(currentProcess);
    } else {
      currentProcess.cpuBurst = 0;
    }

    cout << "Remaining CPU cycles for each process: ";
    for (auto process : processes) {
      cout << process.name << ": " << process.cpuBurst << " ";
    }
    cout << endl;
  }

  return 0;
}
