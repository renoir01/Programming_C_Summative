#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100

// Function prototypes
void sortNames(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count, int (*compare)(const char*, const char*));
int countNames(char names[MAX_STUDENTS][MAX_NAME_LENGTH]);
int ascendingCompare(const char* a, const char* b);
int descendingCompare(const char* a, const char* b);
void displayNames(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count);

// Array of function pointers
typedef void (*FunctionPtr)(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count);

// Function to sort names in ascending or descending order using callback
void sortNames(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count, int (*compare)(const char*, const char*)) {
    char temp[MAX_NAME_LENGTH];
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compare(names[j], names[j + 1]) > 0) {
                // Swap names
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
            }
        }
    }
    
    // Display the sorted names
    printf("\nSorted Names:\n");
    displayNames(names, count);
}

// Function to count the number of names in the array
int countNames(char names[MAX_STUDENTS][MAX_NAME_LENGTH]) {
    int count = 0;
    
    while (count < MAX_STUDENTS && names[count][0] != '\0') {
        count++;
    }
    
    printf("\nTotal number of students: %d\n", count);
    return count;
}

// Comparison function for ascending order
int ascendingCompare(const char* a, const char* b) {
    return strcmp(a, b);
}

// Comparison function for descending order
int descendingCompare(const char* a, const char* b) {
    return strcmp(b, a);
}

// Function to display names
void displayNames(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }
}

// Function to sort names (for function pointer array)
void sortNamesWrapper(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count) {
    char order[5];
    printf("Enter sorting order ('asc' for ascending, 'desc' for descending): ");
    scanf("%4s", order);
    
    if (strcmp(order, "asc") == 0) {
        sortNames(names, count, ascendingCompare);
    } else if (strcmp(order, "desc") == 0) {
        sortNames(names, count, descendingCompare);
    } else {
        printf("Invalid sorting order. Please enter 'asc' or 'desc'.\n");
    }
}

// Function to count names (for function pointer array)
void countNamesWrapper(char names[MAX_STUDENTS][MAX_NAME_LENGTH], int count) {
    countNames(names);
}

int main() {
    char studentNames[MAX_STUDENTS][MAX_NAME_LENGTH] = {
        "John Smith", "Jane Doe", "Michael Johnson", "Emily Williams", "David Brown",
        "Sarah Davis", "Robert Miller", "Jennifer Wilson", "William Moore", "Linda Taylor",
        "James Anderson", "Patricia Thomas", "Charles Jackson", "Barbara White", "Joseph Harris",
        "Susan Martin", "Richard Thompson", "Margaret Garcia", "Daniel Martinez", "Nancy Robinson",
        "Paul Clark", "Karen Rodriguez", "Mark Lewis", "Betty Walker", "Donald Hall",
        "Dorothy Allen", "George Young", "Sandra Hernandez", "Kenneth King", "Carol Wright",
        "Steven Lopez", "Ashley Hill", "Edward Scott", "Donna Green", "Brian Adams",
        "Michelle Baker", "Ronald Nelson", "Carol Mitchell", "Anthony Perez", "Lisa Roberts",
        "Kevin Carter", "Melissa Phillips", "Jason Evans", "Kimberly Turner", "Jeffrey Torres",
        "Deborah Parker", "Ryan Collins", "Stephanie Edwards", "Gary Stewart", "Rebecca Flores",
        "Nicholas Morris", "Cynthia Nguyen", "Eric Murphy", "Kathleen Rivera", "Stephen Cook",
        "Helen Rogers", "Jonathan Reed", "Diane Bell", "Adam Bailey", "Virginia Cox",
        "Henry Howard", "Julie Richardson", "Arthur Wood", "Heather Watson", "Philip Brooks",
        "Frances Price", "Lawrence Bennett", "Alice Ross", "Gregory Hughes", "Evelyn Foster",
        "Wayne Long", "Cheryl Sanders", "Peter Gray", "Lori James", "Roger Jenkins",
        "Janice Perry", "Gerald Powell", "Beverly Coleman", "Terry Patterson", "Christina Washington",
        "Sean Butler", "Gloria Simmons", "Keith Barnes", "Theresa Henderson", "Christian Perry",
        "Joan Gonzalez", "Terry Hayes", "Judith Bryant", "Harold Alexander", "Brenda Russell",
        "Carl Griffin", "Kelly Hayes", "Samuel Diaz", "Christine Myers", "Willie Ford",
        "Tammy Hamilton", "Ralph Graham", "Martha Sullivan", "Lawrence West", "Shirley Gibson"
    };
    
    // Determine the actual count of names
    int count = countNames(studentNames);
    
    // Array of function pointers
    FunctionPtr functions[2] = {sortNamesWrapper, countNamesWrapper};
    
    int choice;
    do {
        printf("\nChoose an option:\n");
        printf("1. Sort names\n");
        printf("2. Count names\n");
        printf("0. Exit\n");
        printf("Enter your choice (0-2): ");
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 2) {
            functions[choice - 1](studentNames, count);
        } else if (choice != 0) {
            printf("Invalid choice. Please enter a number between 0 and 2.\n");
        }
    } while (choice != 0);
    
    printf("Program terminated.\n");
    
    return 0;
}
