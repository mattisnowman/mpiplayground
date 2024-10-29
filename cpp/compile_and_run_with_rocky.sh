#!/bin/sh

#export PATH=/usr/lib64/openmpi/bin:$PATH
#export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib/:$LD_LIBRARY_PATH
#export PSM3_DEVICES='self,shm' 

if [ "$#" -ne 0 ]; then
	if [ "$1" = "-help" ]; then
        echo "Usage: $0 filename N"
        echo
        echo "Arguments:"
        echo "  filename   The C++ file to be compiled."
        echo "  N          The number of cores to run the compiled program on."
        echo
        echo "Options:"
        echo "  -help Display this help message and exit."
		exit 1
	fi
fi

# Compile the selected source file
mpicxx -o mpi_exec $1 -lm -Wall -std=c++11
mpirun -np $2 --oversubscribe ./mpi_exec
