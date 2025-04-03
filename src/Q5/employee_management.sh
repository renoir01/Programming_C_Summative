#!/bin/bash
# Agricultural Technology Employee Management System
# Bash script wrapper for agricultural technology employee management program

# Compile the C program if needed
if [ ! -f "./employee_management" ] || [ "employee_management.c" -nt "employee_management" ]; then
    echo "Compiling agricultural technology employee management program..."
    gcc -o employee_management employee_management.c
    if [ $? -ne 0 ]; then
        echo "Compilation failed. Please check your C code."
        exit 1
    fi
    echo "Compilation successful."
fi

# Function to display the menu
display_menu() {
    clear
    echo "===== Agricultural Technology Employee Management System ====="
    echo "1. Store agricultural employee data"
    echo "2. Retrieve agricultural employee data"
    echo "3. Generate agricultural technology workforce report"
    echo "4. Exit"
    echo "========================================================"
    echo -n "Enter your choice (1-4): "
}

# Main loop
while true; do
    display_menu
    read choice
    
    case $choice in
        1)
            echo "Starting agricultural technology employee data entry process..."
            ./employee_management store
            echo "Press Enter to continue..."
            read
            ;;
        2)
            echo "Retrieving agricultural technology employee data..."
            ./employee_management retrieve
            echo "Press Enter to continue..."
            read
            ;;
        3)
            echo "Generating agricultural technology workforce report..."
            ./employee_management report
            echo "Press Enter to continue..."
            read
            ;;
        4)
            echo "Exiting agricultural technology employee management system. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter 1, 2, 3, or 4."
            echo "Press Enter to continue..."
            read
            ;;
    esac
done
