/*
 * Parallel Prime Number Calculator
 *
 * This program uses multiple threads to count and sum prime numbers within a specified range.
 * It demonstrates the concept of data parallelism by dividing the workload among multiple threads,
 * where each thread processes its own range of numbers to find primes.
 * Author: Khushal Mehta
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define a structure to hold data specific to each thread
typedef struct {
    int thread_id; // Unique ID of the thread
    int low;       // Starting number for the range
    int high;      // Ending number for the range
    long long sum; // Sum of primes found by this thread
    int count;     // Count of primes found by this thread
} ThreadData;

// Mutex for synchronizing output (not currently used in this version)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) return 0;       // Numbers less than or equal to 1 are not prime
    if (num == 2) return 1;       // 2 is prime
    if (num % 2 == 0) return 0;   // Even numbers greater than 2 are not prime

    // Check odd numbers from 3 to sqrt(num) for factors
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1; // If no factors found, the number is prime
}

// Function for each thread to find primes in its assigned range
void* findPrimes(void* arg) {
    ThreadData* data = (ThreadData*)arg; // Cast the argument to ThreadData pointer
    data->sum = 0;                       // Initialize sum for this thread
    data->count = 0;                     // Initialize count for this thread

    // Print the range of numbers that this thread is working on
    printf("Thread # %d is finding primes from low = %d to high = %d\n",
           data->thread_id, data->low, data->high);

    // Loop through the assigned range and check for prime numbers
    for (int i = data->low; i < data->high; i++) {
        if (isPrime(i)) {       // If i is prime
            data->sum += i;     // Add it to the sum
            data->count++;      // Increment the count of primes
        }
    }

    // Print the results for this thread
    printf("Thread # %d Sum is %lld, Count is %d\n",
           data->thread_id, data->sum, data->count);

    return NULL; // Exit the thread
}

// Main function
int main(int argc, char* argv[]) {
    // Check if the number of arguments is correct
    if (argc != 3) {
        printf("Usage: %s <num_threads> <max_number>\n", argv[0]);
        return 1; // Exit if the correct arguments are not provided
    }

    // Parse command-line arguments
    int num_threads = atoi(argv[1]); // Number of threads
    int max_number = atoi(argv[2]);  // Upper limit for prime search

    // Check if inputs are valid
    if (num_threads < 1 || max_number < 1) {
        printf("Both arguments must be positive integers\n");
        return 1; // Exit if inputs are invalid
    }

    // Allocate memory for threads and thread data
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData* thread_data = malloc(num_threads * sizeof(ThreadData));

    // Check if memory allocation was successful
    if (!threads || !thread_data) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Calculate the chunk size for each thread
    double chunk_size = (double)max_number / num_threads;
    int current_low = 0; // Initialize the starting point of the range

    // Create and launch threads
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;        // Assign a thread ID
        thread_data[i].low = current_low;    // Set the starting point for this thread

        // Calculate the end of the range for the current thread
        if (i == num_threads - 1) {
            thread_data[i].high = max_number; // Last thread takes the remaining range
        } else {
            thread_data[i].high = (int)((i + 1) * chunk_size); // Assign range based on chunk size
        }

        current_low = thread_data[i].high; // Update the starting point for the next thread

        // Create a new thread to execute findPrimes function
        pthread_create(&threads[i], NULL, findPrimes, &thread_data[i]);
    }

    // Wait for all threads to finish and collect results
    long long grand_sum = 0; // Total sum of all primes found
    int total_count = 0;     // Total count of all primes found

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL); // Wait for each thread to complete
        grand_sum += thread_data[i].sum; // Add this thread's sum to the grand total
        total_count += thread_data[i].count; // Add this thread's count to the total count
    }

    // Display the final results
    printf("\n\tGRAND SUM IS %lld, COUNT IS %d\n", grand_sum, total_count);

    // Clean up allocated memory and destroy mutex
    free(threads);
    free(thread_data);
    pthread_mutex_destroy(&mutex);

    return 0; // End of the program
}
