#!/bin/bash

# Get the number of available CPUs
num_cpus=$(nproc)

# Function to stress all CPUs
stress_cpus() {
    echo "Stressing all CPUs. Press Ctrl+C to stop."

    # Run stress with the number of available CPUs
    stress --cpu "$num_cpus"
}

# Call the function to stress all CPUs
stress_cpus