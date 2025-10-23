#!/bin/bash
#SBATCH --job-name=mandel_img_sizes
#SBATCH --output=mandel_img_sizes-%j.out
#SBATCH --error=mandel_img_sizes-%j.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=2048
#SBATCH --time=01:00:00

module load gcc
module list

for size in 512 1024 2048 4096 8192; do
  echo "Running with IMAGE_WIDTH=IMAGE_HEIGHT=$size"
  sed -i "s/^#define IMAGE_WIDTH.*/#define IMAGE_WIDTH $size/" consts.h
  sed -i "s/^#define IMAGE_HEIGHT.*/#define IMAGE_HEIGHT $size/" consts.h
  make clean
  make mandel_seq
  ./mandel_seq > img_outputs/output_${size}.txt
done