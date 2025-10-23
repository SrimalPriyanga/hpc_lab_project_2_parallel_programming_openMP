#!/bin/bash
#SBATCH --job-name=recur_omp_scaling
#SBATCH --output=recur_omp_scaling.out
#SBATCH --error=recur_omp_scaling.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --mem-per-cpu=1024MB
#SBATCH --time=00:05:00

# Load the gcc module
module load gcc

# Clean and compile using make
make clean
make

# Run recur_omp with different thread counts
for threads in 1 2 4 8 16
do
    echo "Running with OMP_NUM_THREADS=$threads"
    export OMP_NUM_THREADS=$threads
    ./recur_omp
    echo ""
done
