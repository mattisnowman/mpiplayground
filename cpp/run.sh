#!/bin/sh

mpicxx -o mpi_pi mpi_pi.c -lm -Wall -std=c++11

for i in 1 2 4 8
do
 mpirun -np $i --oversubscribe ./mpi_pi
done