/*
 * Student Records System
 * 
 * This program manages records for students, storing their grades for
 * five specified courses. It demonstrates the use of structures, file I/O,
 * and data management techniques.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define NUM_COURSES 5

// Structure to represent a course
typedef struct {
    char name[50];
    float grade;
} Course;

// Structure to represent a student
typedef struct {
    char fullName[MAX_NAME_LENGTH];
    Course courses[NUM_COURSES];
    float average;
} Student;

// Function prototypes
void inputStudentData(Student *students, int n);
void calculateAverages(Student *students, int n);
void saveToFile(Student *students, int n, const char *filename);
void displayStudentData(Student *students, int n);

int main() {
    int n;
    
    printf("===== Student Records System =====\n");
    printf("This system manages grades and performance data for students.\n\n");
    
    // Get the number of students
    do {
        printf("Enter the number of students (between 6 and 99): ");
        scanf("%d", &n);
        
        // Clear input buffer
        while (getchar() != '\n');
        
        if (n <= 5 || n >= 100) {
            printf("Invalid number of students. Please enter a value between 6 and 99.\n");
        }
    } while (n <= 5 || n >= 100);
    
    // Allocate memory for students
    Student *students = (Student *)malloc(n * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    // Initialize course names
    const char *courseNames[NUM_COURSES] = {
        "Data Structures in C",
        "Mobile Application Development",
        "Programming in C#",
        "Machine Learning Techniques",
        "Introduction to Blockchain Development"
    };
    
    // Initialize course names for each student
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < NUM_COURSES; j++) {
            strcpy(students[i].courses[j].name, courseNames[j]);
        }
    }
    
    // Input student data
    inputStudentData(students, n);
    
    // Calculate average grades
    calculateAverages(students, n);
    
    // Save data to file
    saveToFile(students, n, "student_records.txt");
    
    // Display student data
    displayStudentData(students, n);
    
    // Free allocated memory
    free(students);
    
    return 0;
}

void inputStudentData(Student *students, int n) {
    printf("\n===== Enter Student Data =====\n");
    
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        
        // Get student name
        printf("Enter full name: ");
        fgets(students[i].fullName, MAX_NAME_LENGTH, stdin);
        
        // Remove newline character if present
        size_t len = strlen(students[i].fullName);
        if (len > 0 && students[i].fullName[len - 1] == '\n') {
            students[i].fullName[len - 1] = '\0';
        }
        
        // Get course grades
        printf("Enter grades (0-100) for the following courses:\n");
        for (int j = 0; j < NUM_COURSES; j++) {
            float grade;
            do {
                printf("%s: ", students[i].courses[j].name);
                scanf("%f", &grade);
                
                if (grade < 0 || grade > 100) {
                    printf("Invalid grade. Please enter a value between 0 and 100.\n");
                }
            } while (grade < 0 || grade > 100);
            
            students[i].courses[j].grade = grade;
        }
        
        // Clear input buffer
        while (getchar() != '\n');
    }
}

void calculateAverages(Student *students, int n) {
    for (int i = 0; i < n; i++) {
        float sum = 0.0;
        
        for (int j = 0; j < NUM_COURSES; j++) {
            sum += students[i].courses[j].grade;
        }
        
        students[i].average = sum / NUM_COURSES;
    }
}

void saveToFile(Student *students, int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    // Write header
    fprintf(file, "%-30s", "Full Name");
    for (int j = 0; j < NUM_COURSES; j++) {
        fprintf(file, "%-35s", students[0].courses[j].name);
    }
    fprintf(file, "%-10s\n", "Average");
    
    // Write separator line
    for (int i = 0; i < 30 + 35 * NUM_COURSES + 10; i++) {
        fprintf(file, "-");
    }
    fprintf(file, "\n");
    
    // Write student data
    for (int i = 0; i < n; i++) {
        fprintf(file, "%-30s", students[i].fullName);
        
        for (int j = 0; j < NUM_COURSES; j++) {
            fprintf(file, "%-35.2f", students[i].courses[j].grade);
        }
        
        fprintf(file, "%-10.2f\n", students[i].average);
    }
    
    fclose(file);
    printf("\nStudent records have been saved to %s\n", filename);
}

void displayStudentData(Student *students, int n) {
    printf("\n===== Student Records =====\n");
    
    // Display header
    printf("%-30s", "Full Name");
    for (int j = 0; j < NUM_COURSES; j++) {
        printf("%-35s", students[0].courses[j].name);
    }
    printf("%-10s\n", "Average");
    
    // Display separator line
    for (int i = 0; i < 30 + 35 * NUM_COURSES + 10; i++) {
        printf("-");
    }
    printf("\n");
    
    // Display student data
    for (int i = 0; i < n; i++) {
        printf("%-30s", students[i].fullName);
        
        for (int j = 0; j < NUM_COURSES; j++) {
            printf("%-35.2f", students[i].courses[j].grade);
        }
        
        printf("%-10.2f\n", students[i].average);
    }
}
