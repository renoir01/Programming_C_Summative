# C Programming Assessment

This repository contains solutions for the C Programming Assessment, covering various aspects of C programming including string manipulation, function pointers, multithreading, file handling, and embedded systems programming.

## Project Structure

```
C_Programming_Assessment/
├── src/
│   ├── Q1/  # Sorting Names Using Functions
│   ├── Q2/  # Home Automation
│   ├── Q3/  # Multithreads
│   ├── Q4/  # Data Storage and Computation
│   └── Q5/  # File Handling - Using Bash Script
└── README.md
```

## Question 1: Sorting Names Using Functions

This solution demonstrates the use of function pointers and callback functions to sort an array of student names in either ascending or descending order based on user input.

### Features:
- Sorting function with callback for flexible sorting order
- Function to count names in an array
- Array of function pointers for user to choose operations
- Support for 100 student names

### Compilation and Execution:
```bash
cd src/Q1
gcc -o student_sorting student_sorting.c
./student_sorting
```

## Question 2: Home Automation

This solution implements a home automation system for controlling a light bulb using a remote control. It includes a circuit design and Arduino code.

### Components:
- Arduino board
- IR Receiver
- Relay module
- Light bulb with socket
- Power source
- IR Remote control
- Resistors and wiring

### Usage:
1. Set up the circuit as described in the code comments
2. Upload the `.ino` file to your Arduino board using the Arduino IDE
3. Use the remote control to toggle the light

## Question 3: Multithreads

This solution demonstrates multithreaded programming in C by calculating the sum of a large array of numbers using 10 threads.

### Features:
- Divides work equally among 10 threads
- Uses mutex for thread-safe operations
- Verifies results with a single-threaded calculation

### Compilation and Execution:
```bash
cd src/Q3
gcc -o multithreaded_sum multithreaded_sum.c -lpthread
./multithreaded_sum
```

## Question 4: Data Storage and Computation

This solution uses structures to represent students and their grades for 5 courses, with functionality to input data, calculate averages, and store the information in a file.

### Features:
- Structures for students and courses
- User input validation
- File storage and retrieval
- Average grade calculation

### Compilation and Execution:
```bash
cd src/Q4
gcc -o student_records student_records.c
./student_records
```

## Question 5: File Handling - Using Bash Script in C

This solution implements a C program with bash script integration to manage employee records, allowing for storing and retrieving employee details.

### Features:
- Employee data structure (email, age, salary)
- Input validation
- File-based storage
- Bash script wrapper for better user experience

### Compilation and Execution:
```bash
cd src/Q5
gcc -o employee_management employee_management.c
# To run directly:
./employee_management store    # To store employee data
./employee_management retrieve # To retrieve employee data
# Or use the bash wrapper:
bash employee_management.sh
```

## Requirements

- GCC compiler
- POSIX-compliant system (for pthread support)
- Arduino IDE (for Q2)
- Bash shell (for Q5)

## Notes

- Each solution is independent and can be compiled and run separately
- The solutions include input validation and error handling
- Comments are included throughout the code to explain the implementation details
