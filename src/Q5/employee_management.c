#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_LINE_LENGTH 256
#define NUM_EMPLOYEES 5
#define EMPLOYEE_FILE "employees.txt"

// Structure to represent an employee
typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int age;
    double salary;
} Employee;

// Function prototypes
void clearInputBuffer();
int validateEmail(const char *email);
int validateAge(int age);
int validateSalary(double salary);
void storeEmployeeData(Employee employees[], int count);
void retrieveEmployeeData();

int main(int argc, char *argv[]) {
    // Check if we're storing or retrieving data
    if (argc < 2) {
        printf("Usage: %s [store|retrieve]\n", argv[0]);
        return 1;
    }

    // Convert the command to lowercase for case-insensitive comparison
    char command[10];
    strncpy(command, argv[1], 9);
    command[9] = '\0';
    
    for (int i = 0; command[i]; i++) {
        command[i] = tolower(command[i]);
    }

    if (strcmp(command, "store") == 0) {
        // Store employee data
        Employee employees[NUM_EMPLOYEES];
        storeEmployeeData(employees, NUM_EMPLOYEES);
    } else if (strcmp(command, "retrieve") == 0) {
        // Retrieve employee data
        retrieveEmployeeData();
    } else {
        printf("Invalid command. Use 'store' or 'retrieve'.\n");
        return 1;
    }

    return 0;
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to validate email format
int validateEmail(const char *email) {
    // Basic validation: check for @ symbol and at least one . after @
    const char *at = strchr(email, '@');
    if (!at) return 0;
    
    const char *dot = strchr(at, '.');
    if (!dot) return 0;
    
    // Check that there's at least one character before @, between @ and ., and after .
    if (at == email || dot == at + 1 || dot[1] == '\0') return 0;
    
    return 1;
}

// Function to validate age
int validateAge(int age) {
    return (age >= 18 && age <= 65);
}

// Function to validate salary
int validateSalary(double salary) {
    return (salary > 0);
}

// Function to store employee data
void storeEmployeeData(Employee employees[], int count) {
    printf("===== Employee Data Entry =====\n");
    printf("Please enter details for %d employees:\n\n", count);
    
    for (int i = 0; i < count; i++) {
        printf("Employee %d:\n", i + 1);
        
        // Get and validate email
        do {
            printf("Email: ");
            scanf("%99s", employees[i].email);
            clearInputBuffer();
            
            if (!validateEmail(employees[i].email)) {
                printf("Invalid email format. Please enter a valid email address.\n");
            }
        } while (!validateEmail(employees[i].email));
        
        // Get and validate age
        do {
            printf("Age (18-65): ");
            if (scanf("%d", &employees[i].age) != 1) {
                printf("Invalid input. Please enter a number.\n");
                clearInputBuffer();
                employees[i].age = 0; // Reset to invalid value
                continue;
            }
            clearInputBuffer();
            
            if (!validateAge(employees[i].age)) {
                printf("Invalid age. Please enter an age between 18 and 65.\n");
            }
        } while (!validateAge(employees[i].age));
        
        // Get and validate salary
        do {
            printf("Salary: ");
            if (scanf("%lf", &employees[i].salary) != 1) {
                printf("Invalid input. Please enter a number.\n");
                clearInputBuffer();
                employees[i].salary = 0; // Reset to invalid value
                continue;
            }
            clearInputBuffer();
            
            if (!validateSalary(employees[i].salary)) {
                printf("Invalid salary. Please enter a positive number.\n");
            }
        } while (!validateSalary(employees[i].salary));
        
        printf("\n");
    }
    
    // Save data to file
    FILE *file = fopen(EMPLOYEE_FILE, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    // Write header
    fprintf(file, "%-40s %-10s %-15s\n", "Email", "Age", "Salary");
    fprintf(file, "%-40s %-10s %-15s\n", "-----", "---", "------");
    
    // Write employee data
    for (int i = 0; i < count; i++) {
        fprintf(file, "%-40s %-10d %-15.2f\n", 
                employees[i].email, 
                employees[i].age, 
                employees[i].salary);
    }
    
    fclose(file);
    printf("Employee data has been successfully stored in %s\n", EMPLOYEE_FILE);
}

// Function to retrieve employee data
void retrieveEmployeeData() {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    printf("===== Employee Records =====\n\n");
    
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    
    // Read and display file contents
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        lineCount++;
    }
    
    if (lineCount <= 2) { // Only header lines
        printf("No employee records found.\n");
    }
    
    fclose(file);
}
