# Parallel Prime Number Calculator

A high-performance multithreaded application written in C that calculates prime numbers within a specified range. This program demonstrates data parallelism by splitting the workload across multiple threads, each tasked with finding and summing prime numbers within a unique sub-range.

## 📜 Overview
This project utilizes pthreads to implement a multithreaded approach for prime number calculation. By distributing the workload, it maximizes efficiency, especially for large ranges, showcasing the power of parallel computation in C.

## 🚀 Features
- **Multithreading**: Distributes the workload among multiple threads for faster computation.
- **Dynamic Range Allocation**: Each thread is assigned a specific range of numbers, avoiding overlap and improving performance.
- **Prime Summation and Counting**: Each thread calculates both the sum and count of primes in its range, with results combined for a grand total.

## 📂 Structure

- **Main Function**: Manages thread creation, argument parsing, and final result calculation.
- **`isPrime` Function**: Efficiently checks if a number is prime.
- **`findPrimes` Function**: The function executed by each thread, calculating primes in its assigned range.

## ⚙️ Getting Started

### Prerequisites
- GCC compiler (or any C compiler that supports pthreads)
- Git for cloning the repository

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Khushal-Me/Parallel-Prime-Calculator.git
   
   cd parallel-prime-calculator
   ```

2. Compile the program:
   ```bash
   gcc -o prime_calculator prime_calculator.c -pthread
   ```

### Usage
Run the program with the following command:
```natural
./prime_calculator <num_1> <num_2>
```

**Example:**
```bash
./prime_calculator 25 100
```

### Output Example
```
Thread # 1 is finding primes from low = 4 to high = 8
Thread # 0 is finding primes from low = 0 to high = 4
Thread # 4 is finding primes from low = 16 to high = 20
...
Thread #23 Sum is 0, Count is 0
Thread #24 Sum is 97, Count is 1
Thread #22 Sum is 89, Count is 1

        GRAND SUM IS 1060, COUNT IS 25
```

## 🧠 How the Code Works

### Code Walkthrough

- **`isPrime(int num)`**: Checks if `num` is a prime number by testing divisibility up to `sqrt(num)`.
- **`findPrimes(void* arg)`**: Main function for each thread. Iterates through the range `[low, high)` and sums/counts the prime numbers.
- **`main`**: Initializes thread data, divides the range, creates threads, and aggregates results after joining all threads.

## 📄 License
This project is licensed under the MIT License. See `LICENSE` for more information.
