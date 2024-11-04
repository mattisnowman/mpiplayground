#!/bin/bash

# Name of your job.
#SBATCH --job-name=pi16

# Start an MPI job with 16 single threaded tasks
#SBATCH --ntasks=16
#SBATCH --cpus-per-task=1

# Specify the amount of memory given to each MPI process
# in the job.
#SBATCH --mem-per-cpu=1G

module purge
module load openmpi

mpicxx -o mpi_pi mpi_pi.cpp -lm -Wall -std=c++11
mpirun --mca btl_openib_allow_ib true -np 16 mpi_pi
