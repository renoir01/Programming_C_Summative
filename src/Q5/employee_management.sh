#!/bin/bash
# Bash script wrapper for employee management program

# Compile the C program if needed
if [ ! -f "./employee_management" ] || [ "employee_management.c" -nt "employee_management" ]; then
    echo "Compiling employee_management.c..."
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
    echo "===== Employee Management System ====="
    echo "1. Store employee data"
    echo "2. Retrieve employee data"
    echo "3. Exit"
    echo "====================================="
    echo -n "Enter your choice (1-3): "
}

# Main loop
while true; do
    display_menu
    read choice
    
    case $choice in
        1)
            echo "Starting data entry process..."
            ./employee_management store
            echo "Press Enter to continue..."
            read
            ;;
        2)
            echo "Retrieving employee data..."
            ./employee_management retrieve
            echo "Press Enter to continue..."
            read
            ;;
        3)
            echo "Exiting program. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter 1, 2, or 3."
            echo "Press Enter to continue..."
            read
            ;;
    esac
done
