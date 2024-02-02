#!/bin/bash

# Function to extract PPIDs and print them
extract_and_print_ppids() {
    ppids=($(ps -e -o ppid= | sort -u))
    printf "%s," "${ppids[@]}"
}

# Call the function
extract_and_print_ppids
