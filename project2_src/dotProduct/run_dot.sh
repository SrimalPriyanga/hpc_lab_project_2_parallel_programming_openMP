#!/bin/bash

#SBATCH --job-name=dot_product       # Name of the job
#SBATCH --output=dot_product-%j.out  # Output file
#SBATCH --error=dot_product-%j.err   # Error file
#SBATCH --ntasks=1                   # Run one task
#SBATCH --cpus-per-task=8            # Use 8 CPU cores
#SBATCH --mem-per-cpu=1024           # Memory per core (MB)
#SBATCH --time=00:05:00              # Max runtime

# Load compiler module
module load gcc
module list

# Compile the dotProduct.cpp file
make clean
make

# Set number of OpenMP threads
export OMP_NUM_THREADS=8

# Run the program
./dotProduct