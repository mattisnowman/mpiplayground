#!/bin/bash

# Name of your job.
#SBATCH --job-name=pi128

# Start an MPI job with 128 single threaded tasks
#SBATCH --ntasks=128
#SBATCH --cpus-per-task=1

# Specify the amount of memory given to each MPI process
# in the job.
#SBATCH --mem-per-cpu=1G

module purge
module load openmpi

mpicxx -o mpi_pi mpi_pi.cpp -lm -Wall -std=c++11
mpirun --mca btl_openib_allow_ib true -np 128 mpi_pi
