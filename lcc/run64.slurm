#!/bin/bash

# Name of your job.
#SBATCH --job-name=pi64

# Start an MPI job with 64 single threaded tasks
#SBATCH --ntasks=64
#SBATCH --cpus-per-task=1

# Specify the amount of memory given to each MPI process
# in the job.
#SBATCH --mem-per-cpu=1G

module purge
module load openmpi

mpicxx -o mpi_pi mpi_pi.cpp -lm -Wall -std=c++11
mpirun --mca btl_openib_allow_ib true -np 64 mpi_pi
