#!/bin/bash
#SBATCH --job-name=pi_scaling
#SBATCH --output=pi_scaling-%j.out
#SBATCH --error=pi_scaling-%j.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8
#SBATCH --mem-per-cpu=1024
#SBATCH --time=00:30:00

module load gcc
module list

make clean
make

# Fixed N for π approximation
N=10000000000

# Loop over thread counts
for i in 1 2 4 8
do
  export OMP_NUM_THREADS=$i
  echo "Running with N=$N and OMP_NUM_THREADS=$OMP_NUM_THREADS"
  ./pi
done