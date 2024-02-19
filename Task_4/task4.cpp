#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
/*
 * A process has a name, CPU cycles, and remaining CPU cycles, represented by a
 * struct in C++.
 * This code simulates the Round Robin CPU scheduling algorithm using a queue.
 * "Processes" are stored in a vector (for C++ dynamic memory allocation) and
 * added to the ready queue.
 * The Round Robin algorithm is simulated by iterating through the ready queue
 * and executing processes.
 * */

struct Process {
  string name;
  int CPU_cycles;
  int remaining_cycles;
};

void simRoundRobin(vector<Process> &processes, int time_quantum) {
  queue<Process> ready_queue;
  vector<Process> completed_processes;

  for (Process &p : processes) {
    ready_queue.push(p);
  }

  int curr_time = 0;

  while (!ready_queue.empty()) {
    Process curr_process = ready_queue.front();
    ready_queue.pop();

    // The min function from <algorithm> is used to
    // avoid executing more cycles than remaining
    // I.E, if remaining cycles are 3 and time quantum is 5, only 3 cycles will
    // be executed

    int executed_cycles = min(time_quantum, curr_process.remaining_cycles);
    curr_process.remaining_cycles -= executed_cycles; // Simulation of execution
    curr_time += executed_cycles;

    cout << "Time Elapsed: " << curr_time
         << ", Current Process: " << curr_process.name
         << ", Remaining CPU Cycles: " << curr_process.remaining_cycles << endl;

    if (curr_process.remaining_cycles > 0) {
      ready_queue.push(curr_process); // Continue to the next cycle
      cout << "Process " << curr_process.name
           << " added back to the ready queue." << endl;
      cout << "Ready queue: ";
      queue<Process> temp = ready_queue;
      while (!temp.empty()) {
        cout << temp.front().name << " ";
        temp.pop();
      }
      cout << endl << endl;

    } else {
      completed_processes.push_back(curr_process); // Add to completed processes
      cout << "Process " << curr_process.name << " completed. \n" << endl;
    }
  }

  // Display completed processes
  cout << "\nCompleted Processes:\n";
  for (Process &proc : completed_processes) {
    cout << "Process: " << proc.name
         << ", Original CPU Cycles: " << proc.CPU_cycles << endl;
  }
}

int main() {
  vector<Process> processes = {{"P1", 20, 20},
                               {"P2", 25, 25},
                               {"P3", 15, 15},
                               {"P4", 30, 30},
                               {"P5", 10, 10}};
  int time_quantum;
  cout << "Enter time quantum value (> 1 and <= largest CPU cycle): ";
  cin >> time_quantum;

  for (Process &proc : processes) {
    if (proc.CPU_cycles < time_quantum) {
      cout << "Time quantum cannot be larger than the largest CPU cycle."
           << endl;
      return 1;
    }
  }

  simRoundRobin(processes, time_quantum);

  return 0;
}
