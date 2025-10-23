#!/bin/bash
#SBATCH --job-name=mandel_scaling
#SBATCH --output=mandel_scaling-%j.out
#SBATCH --error=mandel_scaling-%j.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --mem-per-cpu=1024
#SBATCH --time=00:20:00

module load gcc
module list

make clean
make mandel_parallel


for t in 1 2 4 8 16; do
    export OMP_NUM_THREADS=$t
    echo "Running with OMP_NUM_THREADS=$t"
    ./mandel_parallel > mandel_parallel_output/output_${t}threads.txt
done
