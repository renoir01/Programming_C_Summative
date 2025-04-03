/*
 * Agricultural Technology Student Management System
 * 
 * This program manages a list of agricultural technology students,
 * providing functionality to sort names and count entries.
 * It demonstrates the use of function pointers and callback functions
 * for flexible sorting operations critical in agricultural data management.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100
#define MAX_DEPARTMENT_LENGTH 50

// Enhanced student structure for agricultural technology focus
typedef struct {
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPARTMENT_LENGTH]; // Agricultural department
} Student;

// Function prototypes
void sortNames(Student students[], int count, int (*compare)(const Student*, const Student*));
int countNames(Student students[]);
int ascendingCompare(const Student* a, const Student* b);
int descendingCompare(const Student* a, const Student* b);
void displayNames(Student students[], int count);
void clearInputBuffer();
void addNewStudent(Student students[], int *count);

// Array of function pointers
typedef void (*FunctionPtr)(Student students[], int count);

/**
 * Function to sort student names using callback function for comparison
 * This demonstrates the use of function pointers for flexible sorting algorithms
 * 
 * @param students Array of Student structures
 * @param count Number of students in the array
 * @param compare Function pointer to comparison function
 */
void sortNames(Student students[], int count, int (*compare)(const Student*, const Student*)) {
    Student temp;
    
    // Bubble sort implementation with callback function
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compare(&students[j], &students[j + 1]) > 0) {
                // Swap students
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    // Display the sorted names
    printf("\n===== Sorted Agricultural Technology Students =====\n");
    displayNames(students, count);
}

/**
 * Function to count the number of students in the array
 * 
 * @param students Array of Student structures
 * @return Number of students in the array
 */
int countNames(Student students[]) {
    int count = 0;
    
    while (count < MAX_STUDENTS && students[count].name[0] != '\0') {
        count++;
    }
    
    printf("\nTotal number of agricultural technology students: %d\n", count);
    
    // Display department statistics
    printf("\n===== Department Distribution =====\n");
    
    // Define key agricultural technology departments
    const char *agDepts[] = {"Crop Science", "Soil Science", "IoT Systems", "Data Analytics", "Field Operations"};
    const int numDepts = 5;
    int deptCounts[5] = {0};
    
    // Count students in each department
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < numDepts; j++) {
            if (strstr(students[i].department, agDepts[j]) != NULL) {
                deptCounts[j]++;
                break;
            }
        }
    }
    
    // Display department counts
    for (int i = 0; i < numDepts; i++) {
        printf("%s: %d students\n", agDepts[i], deptCounts[i]);
    }
    
    return count;
}

/**
 * Comparison function for ascending order
 * 
 * @param a Pointer to first Student
 * @param b Pointer to second Student
 * @return Comparison result
 */
int ascendingCompare(const Student* a, const Student* b) {
    return strcmp(a->name, b->name);
}

/**
 * Comparison function for descending order
 * 
 * @param a Pointer to first Student
 * @param b Pointer to second Student
 * @return Comparison result
 */
int descendingCompare(const Student* a, const Student* b) {
    return strcmp(b->name, a->name);
}

/**
 * Function to display student names and departments
 * 
 * @param students Array of Student structures
 * @param count Number of students in the array
 */
void displayNames(Student students[], int count) {
    printf("%-5s %-30s %-20s\n", "ID", "Name", "Department");
    printf("%-5s %-30s %-20s\n", "--", "----", "----------");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-30s %-20s\n", i + 1, students[i].name, students[i].department);
    }
}

/**
 * Function to clear input buffer
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Function to add a new student to the array
 * 
 * @param students Array of Student structures
 * @param count Pointer to the current count of students
 */
void addNewStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Error: Maximum number of students reached.\n");
        return;
    }
    
    printf("\n===== Add New Agricultural Technology Student =====\n");
    
    printf("Enter student name: ");
    fgets(students[*count].name, MAX_NAME_LENGTH, stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';
    
    printf("Enter department (Crop Science/Soil Science/IoT Systems/Data Analytics/Field Operations): ");
    fgets(students[*count].department, MAX_DEPARTMENT_LENGTH, stdin);
    students[*count].department[strcspn(students[*count].department, "\n")] = '\0';
    
    (*count)++;
    printf("Student added successfully.\n");
}

/**
 * Function to sort names (for function pointer array)
 * 
 * @param students Array of Student structures
 * @param count Number of students in the array
 */
void sortNamesWrapper(Student students[], int count) {
    char order[5];
    printf("Enter sorting order ('asc' for ascending, 'desc' for descending): ");
    scanf("%4s", order);
    clearInputBuffer();
    
    if (strcmp(order, "asc") == 0) {
        sortNames(students, count, ascendingCompare);
    } else if (strcmp(order, "desc") == 0) {
        sortNames(students, count, descendingCompare);
    } else {
        printf("Invalid sorting order. Please enter 'asc' or 'desc'.\n");
    }
}

/**
 * Function to count names (for function pointer array)
 * 
 * @param students Array of Student structures
 * @param count Number of students in the array
 */
void countNamesWrapper(Student students[], int count) {
    countNames(students);
}

/**
 * Function to add student (for function pointer array)
 * 
 * @param students Array of Student structures
 * @param count Number of students in the array
 */
void addStudentWrapper(Student students[], int *count) {
    addNewStudent(students, count);
}

/**
 * Main function
 */
int main() {
    // Initialize student array with agricultural technology focus
    Student students[MAX_STUDENTS] = {
        {"John Smith", "Crop Science"},
        {"Jane Doe", "Soil Science"},
        {"Michael Johnson", "IoT Systems"},
        {"Emily Williams", "Data Analytics"},
        {"David Brown", "Field Operations"},
        {"Sarah Davis", "Crop Science"},
        {"Robert Miller", "Soil Science"},
        {"Jennifer Wilson", "IoT Systems"},
        {"William Moore", "Data Analytics"},
        {"Linda Taylor", "Field Operations"},
        {"James Anderson", "Crop Science"},
        {"Patricia Thomas", "Soil Science"},
        {"Charles Jackson", "IoT Systems"},
        {"Barbara White", "Data Analytics"},
        {"Joseph Harris", "Field Operations"},
        {"Susan Martin", "Crop Science"},
        {"Richard Thompson", "Soil Science"},
        {"Margaret Garcia", "IoT Systems"},
        {"Daniel Martinez", "Data Analytics"},
        {"Nancy Robinson", "Field Operations"},
        {"Paul Clark", "Crop Science"},
        {"Karen Rodriguez", "Soil Science"},
        {"Mark Lewis", "IoT Systems"},
        {"Betty Walker", "Data Analytics"},
        {"Donald Hall", "Field Operations"},
        {"Dorothy Allen", "Crop Science"},
        {"George Young", "Soil Science"},
        {"Sandra Hernandez", "IoT Systems"},
        {"Kenneth King", "Data Analytics"},
        {"Carol Wright", "Field Operations"},
        {"Steven Lopez", "Crop Science"},
        {"Ashley Hill", "Soil Science"},
        {"Edward Scott", "IoT Systems"},
        {"Donna Green", "Data Analytics"},
        {"Brian Adams", "Field Operations"},
        {"Michelle Baker", "Crop Science"},
        {"Ronald Nelson", "Soil Science"},
        {"Carol Mitchell", "IoT Systems"},
        {"Anthony Perez", "Data Analytics"},
        {"Lisa Roberts", "Field Operations"},
        {"Kevin Carter", "Crop Science"},
        {"Melissa Phillips", "Soil Science"},
        {"Jason Evans", "IoT Systems"},
        {"Kimberly Turner", "Data Analytics"},
        {"Jeffrey Torres", "Field Operations"},
        {"Deborah Parker", "Crop Science"},
        {"Ryan Collins", "Soil Science"},
        {"Stephanie Edwards", "IoT Systems"},
        {"Gary Stewart", "Data Analytics"},
        {"Rebecca Flores", "Field Operations"},
        {"Nicholas Morris", "Crop Science"},
        {"Cynthia Nguyen", "Soil Science"},
        {"Eric Murphy", "IoT Systems"},
        {"Kathleen Rivera", "Data Analytics"},
        {"Stephen Cook", "Field Operations"},
        {"Helen Rogers", "Crop Science"},
        {"Jonathan Reed", "Soil Science"},
        {"Diane Bell", "IoT Systems"},
        {"Adam Bailey", "Data Analytics"},
        {"Virginia Cox", "Field Operations"},
        {"Henry Howard", "Crop Science"},
        {"Julie Richardson", "Soil Science"},
        {"Arthur Wood", "IoT Systems"},
        {"Heather Watson", "Data Analytics"},
        {"Philip Brooks", "Field Operations"},
        {"Frances Price", "Crop Science"},
        {"Lawrence Bennett", "Soil Science"},
        {"Alice Ross", "IoT Systems"},
        {"Gregory Hughes", "Data Analytics"},
        {"Evelyn Foster", "Field Operations"},
        {"Wayne Long", "Crop Science"},
        {"Cheryl Sanders", "Soil Science"},
        {"Peter Gray", "IoT Systems"},
        {"Lori James", "Data Analytics"},
        {"Roger Jenkins", "Field Operations"},
        {"Janice Perry", "Crop Science"},
        {"Gerald Powell", "Soil Science"},
        {"Beverly Coleman", "IoT Systems"},
        {"Terry Patterson", "Data Analytics"},
        {"Christina Washington", "Field Operations"},
        {"Sean Butler", "Crop Science"},
        {"Gloria Simmons", "Soil Science"},
        {"Keith Barnes", "IoT Systems"},
        {"Theresa Henderson", "Data Analytics"},
        {"Christian Perry", "Field Operations"},
        {"Joan Gonzalez", "Crop Science"},
        {"Terry Hayes", "Soil Science"},
        {"Judith Bryant", "IoT Systems"},
        {"Harold Alexander", "Data Analytics"},
        {"Brenda Russell", "Field Operations"},
        {"Carl Griffin", "Crop Science"},
        {"Kelly Hayes", "Soil Science"},
        {"Samuel Diaz", "IoT Systems"},
        {"Christine Myers", "Data Analytics"},
        {"Willie Ford", "Field Operations"},
        {"Tammy Hamilton", "Crop Science"},
        {"Ralph Graham", "Soil Science"},
        {"Martha Sullivan", "IoT Systems"},
        {"Lawrence West", "Data Analytics"},
        {"Shirley Gibson", "Field Operations"}
    };
    
    // Determine the actual count of names
    int count = countNames(students);
    
    // Array of function pointers with added functionality
    FunctionPtr functions[3] = {sortNamesWrapper, countNamesWrapper, addStudentWrapper};
    
    printf("\n===== Agricultural Technology Student Management System =====\n");
    printf("This system demonstrates the use of function pointers and callbacks\n");
    printf("for efficient management of agricultural technology student data.\n\n");
    
    int choice;
    do {
        printf("\nChoose an option:\n");
        printf("1. Sort students by name\n");
        printf("2. Count students and show department statistics\n");
        printf("3. Add new student\n");
        printf("0. Exit\n");
        printf("Enter your choice (0-3): ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        if (choice == 1 || choice == 2) {
            functions[choice - 1](students, count);
        } else if (choice == 3) {
            functions[2](students, &count);
        } else if (choice != 0) {
            printf("Invalid choice. Please enter a number between 0 and 3.\n");
        }
    } while (choice != 0);
    
    printf("Program terminated.\n");
    
    return 0;
}
