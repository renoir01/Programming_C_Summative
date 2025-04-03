/*
 * Agricultural Technology Employee Management System
 * 
 * This program manages employee records for an agricultural technology company,
 * allowing for the storage and retrieval of employee information including
 * specialized agricultural technology roles and departments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_ROLE_LENGTH 50
#define MAX_DEPARTMENT_LENGTH 50
#define MAX_LINE_LENGTH 256
#define NUM_EMPLOYEES 5
#define EMPLOYEE_FILE "employees.txt"

// Structure to represent an agricultural technology employee
typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int age;
    double salary;
    char role[MAX_ROLE_LENGTH];           // Agricultural technology role
    char department[MAX_DEPARTMENT_LENGTH]; // Agricultural department
} Employee;

// Function prototypes
void clearInputBuffer();
int validateEmail(const char *email);
int validateAge(int age);
int validateSalary(double salary);
void storeEmployeeData(Employee employees[], int count);
void retrieveEmployeeData();
void generateAgriTechReport();

int main(int argc, char *argv[]) {
    printf("===== Agricultural Technology Employee Management System =====\n\n");
    
    // Check if we're storing, retrieving data, or generating a report
    if (argc < 2) {
        printf("Usage: %s [store|retrieve|report]\n", argv[0]);
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
    } else if (strcmp(command, "report") == 0) {
        // Generate agricultural technology report
        generateAgriTechReport();
    } else {
        printf("Invalid command. Use 'store', 'retrieve', or 'report'.\n");
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
    printf("===== Agricultural Technology Employee Data Entry =====\n");
    printf("Please enter details for %d agricultural technology employees:\n\n", count);
    
    // Define available agricultural roles and departments for selection
    const char *agriRoles[] = {
        "Field Sensor Technician",
        "IoT Systems Engineer",
        "Agricultural Data Analyst",
        "Drone Operator",
        "Supply Chain Specialist"
    };
    
    const char *agriDepartments[] = {
        "Smart Farming",
        "Precision Agriculture",
        "Agricultural IoT",
        "Farm Automation",
        "Supply Chain Technology"
    };
    
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
        
        // Display available roles
        printf("\nAvailable Agricultural Technology Roles:\n");
        for (int j = 0; j < 5; j++) {
            printf("%d. %s\n", j + 1, agriRoles[j]);
        }
        
        // Get role selection
        int roleChoice;
        do {
            printf("Select role (1-5): ");
            if (scanf("%d", &roleChoice) != 1 || roleChoice < 1 || roleChoice > 5) {
                printf("Invalid selection. Please enter a number between 1 and 5.\n");
                clearInputBuffer();
                roleChoice = 0;
                continue;
            }
            clearInputBuffer();
        } while (roleChoice < 1 || roleChoice > 5);
        
        strcpy(employees[i].role, agriRoles[roleChoice - 1]);
        
        // Display available departments
        printf("\nAvailable Agricultural Technology Departments:\n");
        for (int j = 0; j < 5; j++) {
            printf("%d. %s\n", j + 1, agriDepartments[j]);
        }
        
        // Get department selection
        int deptChoice;
        do {
            printf("Select department (1-5): ");
            if (scanf("%d", &deptChoice) != 1 || deptChoice < 1 || deptChoice > 5) {
                printf("Invalid selection. Please enter a number between 1 and 5.\n");
                clearInputBuffer();
                deptChoice = 0;
                continue;
            }
            clearInputBuffer();
        } while (deptChoice < 1 || deptChoice > 5);
        
        strcpy(employees[i].department, agriDepartments[deptChoice - 1]);
        
        printf("\n");
    }
    
    // Save data to file
    FILE *file = fopen(EMPLOYEE_FILE, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    // Write header
    fprintf(file, "%-40s %-10s %-15s %-30s %-30s\n", 
            "Email", "Age", "Salary", "Role", "Department");
    fprintf(file, "%-40s %-10s %-15s %-30s %-30s\n", 
            "-----", "---", "------", "----", "----------");
    
    // Write employee data
    for (int i = 0; i < count; i++) {
        fprintf(file, "%-40s %-10d %-15.2f %-30s %-30s\n", 
                employees[i].email, 
                employees[i].age, 
                employees[i].salary,
                employees[i].role,
                employees[i].department);
    }
    
    fclose(file);
    printf("Agricultural technology employee data has been successfully stored in %s\n", EMPLOYEE_FILE);
}

// Function to retrieve employee data
void retrieveEmployeeData() {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    printf("===== Agricultural Technology Employee Records =====\n\n");
    
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    
    // Read and display file contents
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        lineCount++;
    }
    
    if (lineCount <= 2) { // Only header lines
        printf("No agricultural technology employee records found.\n");
    }
    
    fclose(file);
}

// Function to generate an agricultural technology report
void generateAgriTechReport() {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    
    printf("===== Agricultural Technology Workforce Analysis =====\n\n");
    
    char line[MAX_LINE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int age;
    double salary;
    char role[MAX_ROLE_LENGTH];
    char department[MAX_DEPARTMENT_LENGTH];
    
    // Skip header lines
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    
    // Initialize counters
    int totalEmployees = 0;
    int departmentCount[5] = {0};
    int roleCount[5] = {0};
    double totalSalary = 0.0;
    int totalAge = 0;
    
    // Define department and role names for reporting
    const char *departments[] = {
        "Smart Farming",
        "Precision Agriculture",
        "Agricultural IoT",
        "Farm Automation",
        "Supply Chain Technology"
    };
    
    const char *roles[] = {
        "Field Sensor Technician",
        "IoT Systems Engineer",
        "Agricultural Data Analyst",
        "Drone Operator",
        "Supply Chain Specialist"
    };
    
    // Process each employee
    while (fscanf(file, "%s %d %lf %[^,], %[^\n]", 
                 email, &age, &salary, role, department) == 5) {
        totalEmployees++;
        totalSalary += salary;
        totalAge += age;
        
        // Count departments
        for (int i = 0; i < 5; i++) {
            if (strstr(department, departments[i]) != NULL) {
                departmentCount[i]++;
                break;
            }
        }
        
        // Count roles
        for (int i = 0; i < 5; i++) {
            if (strstr(role, roles[i]) != NULL) {
                roleCount[i]++;
                break;
            }
        }
    }
    
    // Display report
    if (totalEmployees > 0) {
        printf("Total Agricultural Technology Employees: %d\n", totalEmployees);
        printf("Average Age: %.1f years\n", (double)totalAge / totalEmployees);
        printf("Average Salary: $%.2f\n\n", totalSalary / totalEmployees);
        
        printf("Department Distribution:\n");
        for (int i = 0; i < 5; i++) {
            printf("- %s: %d employee(s)\n", departments[i], departmentCount[i]);
        }
        
        printf("\nRole Distribution:\n");
        for (int i = 0; i < 5; i++) {
            printf("- %s: %d employee(s)\n", roles[i], roleCount[i]);
        }
        
        printf("\nThis report provides insights into the agricultural technology\n");
        printf("workforce composition and can help with resource allocation\n");
        printf("and strategic planning for agricultural technology initiatives.\n");
    } else {
        printf("No employee data available for analysis.\n");
    }
    
    fclose(file);
}
