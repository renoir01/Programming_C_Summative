/*
 * Agricultural Sensor Data Processing System
 * 
 * This program demonstrates multithreaded processing of large agricultural sensor datasets
 * using POSIX threads. It simulates processing field sensor data collected from IoT devices
 * in agricultural settings, showing how parallel computing can accelerate data analysis
 * for time-sensitive agricultural decisions.
 * 
 * Key features:
 * - Parallel processing using multiple threads
 * - Thread synchronization with mutex locks
 * - Dynamic workload distribution
 * - Performance comparison with single-threaded approach
 * - Simulated agricultural sensor data processing
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define NUM_THREADS 10
#define MIN_ARRAY_SIZE 1000
#define MAX_SENSOR_VALUE 100

// Sensor data types for agricultural applications
typedef enum {
    SOIL_MOISTURE,
    TEMPERATURE,
    HUMIDITY,
    LIGHT_INTENSITY,
    NUTRIENT_LEVEL
} SensorType;

// Structure to represent a sensor reading
typedef struct {
    int value;
    SensorType type;
    int field_sector;
} SensorReading;

// Structure to pass data to threads
typedef struct {
    int thread_id;
    SensorReading *readings;
    int start_index;
    int end_index;
    long long partial_sum;
    double processing_time;
} ThreadData;

// Global variables
SensorReading *sensor_readings;
int n;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long total_sum = 0;

// Function to generate random sensor data
void generate_sensor_data() {
    printf("Generating simulated agricultural sensor data...\n");
    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        // Randomly assign sensor type
        sensor_readings[i].type = rand() % 5;
        
        // Generate value based on sensor type
        switch (sensor_readings[i].type) {
            case SOIL_MOISTURE:
                // Soil moisture (0-100%)
                sensor_readings[i].value = rand() % 101;
                break;
            case TEMPERATURE:
                // Temperature (0-50°C)
                sensor_readings[i].value = rand() % 51;
                break;
            case HUMIDITY:
                // Humidity (0-100%)
                sensor_readings[i].value = rand() % 101;
                break;
            case LIGHT_INTENSITY:
                // Light intensity (0-1000 lux)
                sensor_readings[i].value = rand() % 1001;
                break;
            case NUTRIENT_LEVEL:
                // Nutrient level (0-100 ppm)
                sensor_readings[i].value = rand() % 101;
                break;
        }
        
        // Assign field sector (1-20)
        sensor_readings[i].field_sector = (rand() % 20) + 1;
    }
}

// Function to get sensor type name
const char* get_sensor_type_name(SensorType type) {
    switch (type) {
        case SOIL_MOISTURE: return "Soil Moisture";
        case TEMPERATURE: return "Temperature";
        case HUMIDITY: return "Humidity";
        case LIGHT_INTENSITY: return "Light Intensity";
        case NUTRIENT_LEVEL: return "Nutrient Level";
        default: return "Unknown";
    }
}

// Thread function to calculate partial sum
void *calculate_partial_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->partial_sum = 0;
    
    // Record start time
    clock_t start_time = clock();
    
    // Calculate sum for this thread's portion of the array
    for (int i = data->start_index; i < data->end_index; i++) {
        data->partial_sum += sensor_readings[i].value;
    }
    
    // Record end time and calculate processing time
    clock_t end_time = clock();
    data->processing_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    // Print thread results for debugging
    printf("Thread %d: Processed sensor readings from index %d to %d = %lld (%.4f seconds)\n", 
           data->thread_id, data->start_index, data->end_index - 1, data->partial_sum, data->processing_time);
    
    // Add this thread's sum to the total (using mutex for thread safety)
    pthread_mutex_lock(&mutex);
    total_sum += data->partial_sum;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

// Function to analyze sensor data by type
void analyze_sensor_data_by_type() {
    int type_counts[5] = {0};
    long long type_sums[5] = {0};
    
    for (int i = 0; i < n; i++) {
        SensorType type = sensor_readings[i].type;
        type_counts[type]++;
        type_sums[type] += sensor_readings[i].value;
    }
    
    printf("\n===== Sensor Data Analysis by Type =====\n");
    for (int i = 0; i < 5; i++) {
        if (type_counts[i] > 0) {
            double average = (double)type_sums[i] / type_counts[i];
            printf("%s: %d readings, Sum: %lld, Average: %.2f\n", 
                   get_sensor_type_name((SensorType)i), type_counts[i], type_sums[i], average);
        }
    }
}

// Function to analyze sensor data by field sector
void analyze_sensor_data_by_sector() {
    // We have 20 sectors
    int sector_counts[20] = {0};
    long long sector_sums[20] = {0};
    
    for (int i = 0; i < n; i++) {
        int sector = sensor_readings[i].field_sector - 1; // Convert to 0-based index
        sector_counts[sector]++;
        sector_sums[sector] += sensor_readings[i].value;
    }
    
    printf("\n===== Sensor Data Analysis by Field Sector =====\n");
    for (int i = 0; i < 20; i++) {
        if (sector_counts[i] > 0) {
            double average = (double)sector_sums[i] / sector_counts[i];
            printf("Sector %d: %d readings, Sum: %lld, Average: %.2f\n", 
                   i+1, sector_counts[i], sector_sums[i], average);
        }
    }
}

int main() {
    // Get the value of n from the user
    printf("===== Agricultural Sensor Data Processing System =====\n");
    printf("This system demonstrates multithreaded processing of large sensor datasets\n");
    printf("for agricultural technology applications.\n\n");
    
    printf("Enter the number of sensor readings to process (n > %d): ", MIN_ARRAY_SIZE);
    scanf("%d", &n);
    
    // Validate input
    if (n <= MIN_ARRAY_SIZE) {
        printf("Error: n must be greater than %d\n", MIN_ARRAY_SIZE);
        return 1;
    }
    
    // Allocate memory for the sensor readings array
    sensor_readings = (SensorReading *)malloc(n * sizeof(SensorReading));
    if (sensor_readings == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Generate simulated sensor data
    generate_sensor_data();
    
    // Create threads and thread data
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    
    // Calculate elements per thread
    int elements_per_thread = n / NUM_THREADS;
    int remaining_elements = n % NUM_THREADS;
    
    printf("\nStarting multithreaded processing with %d threads...\n", NUM_THREADS);
    
    // Record start time for multithreaded processing
    clock_t mt_start_time = clock();
    
    // Create and start threads
    int start_index = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].readings = sensor_readings;
        thread_data[i].start_index = start_index;
        
        // Distribute remaining elements among first 'remaining_elements' threads
        int extra = (i < remaining_elements) ? 1 : 0;
        thread_data[i].end_index = start_index + elements_per_thread + extra;
        
        start_index = thread_data[i].end_index;
        
        printf("Creating thread %d to process readings from index %d to %d\n", 
               i, thread_data[i].start_index, thread_data[i].end_index - 1);
        
        if (pthread_create(&threads[i], NULL, calculate_partial_sum, (void *)&thread_data[i]) != 0) {
            perror("Failed to create thread");
            free(sensor_readings);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Record end time for multithreaded processing
    clock_t mt_end_time = clock();
    double mt_processing_time = (double)(mt_end_time - mt_start_time) / CLOCKS_PER_SEC;
    
    // Print the multithreaded result
    printf("\n===== Multithreaded Processing Results =====\n");
    printf("Number of sensor readings (n): %d\n", n);
    printf("Number of threads: %d\n", NUM_THREADS);
    printf("Total sum of sensor values: %lld\n", total_sum);
    printf("Multithreaded processing time: %.4f seconds\n", mt_processing_time);
    
    // Verify result with a single-threaded calculation
    printf("\nVerifying with single-threaded processing...\n");
    
    // Record start time for single-threaded processing
    clock_t st_start_time = clock();
    
    long long verification_sum = 0;
    for (int i = 0; i < n; i++) {
        verification_sum += sensor_readings[i].value;
    }
    
    // Record end time for single-threaded processing
    clock_t st_end_time = clock();
    double st_processing_time = (double)(st_end_time - st_start_time) / CLOCKS_PER_SEC;
    
    printf("Single-threaded sum: %lld\n", verification_sum);
    printf("Single-threaded processing time: %.4f seconds\n", st_processing_time);
    
    // Calculate speedup
    double speedup = st_processing_time / mt_processing_time;
    
    if (total_sum == verification_sum) {
        printf("\nVerification successful: Multithreaded and single-threaded sums match.\n");
        printf("Performance speedup: %.2fx faster with multithreading\n", speedup);
    } else {
        printf("\nVerification failed: Sums do not match!\n");
    }
    
    // Perform additional agricultural data analysis
    analyze_sensor_data_by_type();
    analyze_sensor_data_by_sector();
    
    // Print agricultural technology application insights
    printf("\n===== Agricultural Technology Insights =====\n");
    printf("This multithreaded processing system demonstrates how parallel computing\n");
    printf("can accelerate agricultural data analysis for time-sensitive decisions.\n");
    printf("Applications include:\n");
    printf("1. Real-time irrigation management based on soil moisture sensors\n");
    printf("2. Climate control in greenhouses using temperature and humidity data\n");
    printf("3. Precision agriculture with field-sector specific interventions\n");
    printf("4. Crop health monitoring through nutrient level analysis\n");
    printf("5. Optimized harvesting schedules based on environmental conditions\n");
    
    // Clean up
    free(sensor_readings);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
