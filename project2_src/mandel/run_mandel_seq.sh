#!/bin/bash
#SBATCH --job-name=mandel_seq          # Job name
#SBATCH --output=mandel_seq-%j.out     # Standard output
#SBATCH --error=mandel_seq-%j.err      # Standard error
#SBATCH --ntasks=1                     # Run a single task
#SBATCH --cpus-per-task=1              # Use 1 CPU core (sequential)
#SBATCH --mem-per-cpu=1024             # Memory per core (MB)
#SBATCH --time=00:05:00                # Max runtime

# Load compiler module
module load gcc
module list

# Clean and compile using Makefile
make clean
make mandel_seq

# Run the program
./mandel_seq