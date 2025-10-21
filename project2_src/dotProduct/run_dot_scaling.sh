#!/bin/bash

#SBATCH --job-name=dot_product_scaling       # Job name
#SBATCH --output=dot_product_scaling-%j.out  # Output file
#SBATCH --error=dot_product_scaling-%j.err   # Error file
#SBATCH --ntasks=1                           # One task
#SBATCH --cpus-per-task=20                   # Max threads to test
#SBATCH --mem-per-cpu=1024                   # Memory per CPU
#SBATCH --time=00:10:00                      # Time limit
# Load compiler
module load gcc
module list

# Compile the program
make clean
make

# Run with different thread counts
for i in 1 2 4 8 16 20
do
  export OMP_NUM_THREADS=$i
  echo "Running with OMP_NUM_THREADS=$OMP_NUM_THREADS"
  ./dotProduct
done