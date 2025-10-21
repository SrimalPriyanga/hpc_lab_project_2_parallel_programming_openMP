#!/bin/bash
#SBATCH --job-name=dot_product_scaling
#SBATCH --output=dot_product_scaling-%j.out
#SBATCH --error=dot_product_scaling-%j.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=20
#SBATCH --mem-per-cpu=1024
#SBATCH --time=00:30:00

module load gcc
module list

make clean

# Loop over vector sizes
for N in 100000 1000000 10000000 100000000 1000000000
do
  echo "Start: Compiling for N=$N"
  g++ -fopenmp -DN=$N dotProduct.cpp -o dotProduct

  # Loop over thread counts
  for i in 1 2 4 8 16 20
  do
    export OMP_NUM_THREADS=$i
    echo "Running with N=$N and OMP_NUM_THREADS=$OMP_NUM_THREADS"
    ./dotProduct
  done
  echo "End: Compiling for N=$N"
  echo "--------------------------------"
done