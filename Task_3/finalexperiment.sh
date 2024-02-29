#!/bin/zsh

# Function to compile and run a C++ program and capture the execution time
run_program() {
	local program_name=$1
	local result=$(./$program_name)
	local time_taken=$(echo "$result" | grep "Time taken:" | awk '{print $3}')
	echo "$time_taken"
}

# Function to calculate the average time
calculate_average_time() {
	local program_name=$1
	local total_time=$2
	local average_time=$((total_time / 10))
	echo "$average_time"
}

# Compile and run the task3thread.cpp program
echo "Running task3thread.cpp program..."
g++ task3thread.cpp -o task3thread -lpthread

total_time_thread=0
for ((i = 1; i <= 10; i++)); do
	echo "Running iteration $i"
	time=$(run_program "task3thread")
	total_time_thread=$((total_time_thread + time))
	echo "Time taken: $time nanoseconds"
done

average_time_thread=$(calculate_average_time "task3thread.cpp" $total_time_thread)
echo "Average time taken for task3thread.cpp: $average_time_thread nanoseconds"

# Compile and run the task3fork.cpp program
echo "Running task3fork.cpp program..."
g++ task3fork.cpp -o task3fork

total_time_fork=0
for ((i = 1; i <= 10; i++)); do
	echo "Running iteration $i"
	time=$(run_program "task3fork")
	total_time_fork=$((total_time_fork + time))
	echo "Time taken: $time nanoseconds"
done

average_time_fork=$(calculate_average_time "task3fork.cpp" $total_time_fork)
echo "Average time taken for task3fork.cpp: $average_time_fork nanoseconds"

# Calculate the difference between average times
difference=$((average_time_thread - average_time_fork))
echo "Difference in average times: $difference nanoseconds"

# Determine which file is faster based on the experiment run
if [ $difference -gt 0 ]; then
	echo "task3fork.cpp is faster than task3thread.cpp by $difference nanoseconds"
elif [ $difference -lt 0 ]; then
	echo "task3thread.cpp is faster than task3fork.cpp by $((difference * -1)) nanoseconds"
else
	echo "Both files have the same average execution time"
fi
