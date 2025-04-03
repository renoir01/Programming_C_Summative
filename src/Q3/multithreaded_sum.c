#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

// Structure to pass data to threads
typedef struct {
    int thread_id;
    int *array;
    int start_index;
    int end_index;
    long long partial_sum;
} ThreadData;

// Global array and mutex
int *numbers;
int n;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long total_sum = 0;

// Thread function to calculate partial sum
void *calculate_partial_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->partial_sum = 0;
    
    // Calculate sum for this thread's portion of the array
    for (int i = data->start_index; i < data->end_index; i++) {
        data->partial_sum += numbers[i];
    }
    
    // Print thread results for debugging
    printf("Thread %d: Calculated sum from index %d to %d = %lld\n", 
           data->thread_id, data->start_index, data->end_index - 1, data->partial_sum);
    
    // Add this thread's sum to the total (using mutex for thread safety)
    pthread_mutex_lock(&mutex);
    total_sum += data->partial_sum;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main() {
    // Get the value of n from the user
    printf("Enter the number of elements (n > 1000): ");
    scanf("%d", &n);
    
    // Validate input
    if (n <= 1000) {
        printf("Error: n must be greater than 1000\n");
        return 1;
    }
    
    // Allocate memory for the array
    numbers = (int *)malloc(n * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Initialize array with random values (1-100 for simplicity)
    printf("Initializing array with random values...\n");
    for (int i = 0; i < n; i++) {
        numbers[i] = rand() % 100 + 1;
    }
    
    // Create threads and thread data
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    
    // Calculate elements per thread
    int elements_per_thread = n / NUM_THREADS;
    int remaining_elements = n % NUM_THREADS;
    
    // Create and start threads
    int start_index = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].array = numbers;
        thread_data[i].start_index = start_index;
        
        // Distribute remaining elements among first 'remaining_elements' threads
        int extra = (i < remaining_elements) ? 1 : 0;
        thread_data[i].end_index = start_index + elements_per_thread + extra;
        
        start_index = thread_data[i].end_index;
        
        printf("Creating thread %d to process elements from index %d to %d\n", 
               i, thread_data[i].start_index, thread_data[i].end_index - 1);
        
        if (pthread_create(&threads[i], NULL, calculate_partial_sum, (void *)&thread_data[i]) != 0) {
            perror("Failed to create thread");
            free(numbers);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Print the final result
    printf("\nResults:\n");
    printf("Number of elements (n): %d\n", n);
    printf("Number of threads: %d\n", NUM_THREADS);
    printf("Total sum: %lld\n", total_sum);
    
    // Verify result with a single-threaded calculation
    long long verification_sum = 0;
    for (int i = 0; i < n; i++) {
        verification_sum += numbers[i];
    }
    printf("Verification sum (single thread): %lld\n", verification_sum);
    
    if (total_sum == verification_sum) {
        printf("Verification successful: Multithreaded and single-threaded sums match.\n");
    } else {
        printf("Verification failed: Sums do not match!\n");
    }
    
    // Clean up
    free(numbers);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
