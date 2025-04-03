# Agricultural Technology Programming Assessment

This repository contains solutions for the Agricultural Technology Programming Assessment, covering various aspects of C programming tailored for agricultural applications including sensor data processing, automation systems, multithreading for field data analysis, and agricultural data management.

## Project Structure

```markdown
C_Programming_Assessment/
├── src/
│   ├── Q1/  # Student Management for Agricultural Programs
│   ├── Q2/  # Agricultural IoT Automation System
│   ├── Q3/  # Multithreaded Agricultural Sensor Data Processing
│   ├── Q4/  # Agricultural Data Storage and Computation
│   └── Q5/  # Agricultural Record Management System
└── README.md
```

## Question 1: Student Management for Agricultural Programs

This solution demonstrates the use of function pointers and callback functions to sort an array of agricultural technology student names in either ascending or descending order, with department-based statistics.

### Q1 Features

- Sorting function with callback for flexible sorting order
- Department-based student counting and statistics
- Array of function pointers for user to choose operations
- Support for agricultural technology student management

### Q1 Compilation and Execution

```bash
cd src/Q1
gcc -o student_sorting student_sorting.c
./student_sorting
```

## Question 2: Agricultural IoT Automation System

This solution implements an agricultural automation system for controlling irrigation, ventilation, and heating based on environmental sensors. It includes a circuit design and Arduino code for smart farming applications.

### Q2 Components

- Arduino board
- Soil moisture sensors
- Temperature and humidity sensors
- Relay modules for irrigation, fans, and heaters
- LCD display for real-time monitoring
- IR Remote control for manual override
- Resistors and wiring

### Q2 Usage Instructions

1. Set up the circuit as described in the code comments
2. Upload the `.ino` file to your Arduino board using the Arduino IDE
3. Use the remote control to toggle between automatic and manual modes

## Question 3: Multithreaded Agricultural Sensor Data Processing

This solution demonstrates multithreaded programming in C by processing large agricultural sensor datasets using 10 threads, showing how parallel computing can accelerate data analysis for time-sensitive agricultural decisions.

### Q3 Features

- Processes various agricultural sensor types (soil moisture, temperature, humidity, etc.)
- Divides work equally among 10 threads for efficient processing
- Uses mutex for thread-safe operations
- Compares performance between multithreaded and single-threaded approaches
- Provides agricultural insights based on sensor data analysis

### Q3 Compilation and Execution

```bash
cd src/Q3
gcc -o multithreaded_sum multithreaded_sum.c -lpthread
./multithreaded_sum
```

## Question 4: Agricultural Data Storage and Computation

This solution uses structures to represent agricultural students and their grades for 5 courses related to agricultural technology, with functionality to input data, calculate averages, and store the information in a file.

### Q4 Features

- Structures for agricultural students and courses
- User input validation
- File storage and retrieval
- Average grade calculation for agricultural technology courses

### Q4 Compilation and Execution

```bash
cd src/Q4
gcc -o student_records student_records.c
./student_records
```

## Question 5: Agricultural Record Management System

This solution implements a C program with bash script integration to manage agricultural employee and crop records, allowing for storing and retrieving details relevant to farm management.

### Q5 Features

- Agricultural data structures (crop yields, field conditions, employee details)
- Input validation
- File-based storage
- Bash script wrapper for better user experience

### Q5 Compilation and Execution

```bash
cd src/Q5
gcc -o agricultural_management agricultural_management.c
# To run directly:
./agricultural_management store    # To store agricultural data
./agricultural_management retrieve # To retrieve agricultural data
```

## Agricultural Technology Applications

These programs demonstrate various applications of computer programming in agricultural technology:

1. **Student Management**: For educational institutions focusing on agricultural technology
2. **IoT Automation**: For smart farming and precision agriculture
3. **Sensor Data Processing**: For analyzing field conditions and making data-driven decisions
4. **Data Storage**: For maintaining agricultural research and student records
5. **Record Management**: For efficient farm operations and crop management

## Future Enhancements

- Integration with cloud-based agricultural data platforms
- Mobile application interfaces for remote monitoring
- Machine learning components for predictive agricultural analytics
- Support for additional sensor types and agricultural equipment
- Enhanced visualization of agricultural data

## Requirements

- GCC compiler
- POSIX-compliant system (for pthread support)
- Arduino IDE (for Q2)
- Bash shell (for Q5)

## Notes

- Each solution is independent and can be compiled and run separately
- The solutions include input validation and error handling
- Comments are included throughout the code to explain the implementation details
