#!/bin/bash
#SBATCH --job-name=recur_seq
#SBATCH --output=recur_seq.out
#SBATCH --error=recur_seq.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=1024MB
#SBATCH --time=00:05:00

module load gcc
make clean
make recur_seq

./recur_seq