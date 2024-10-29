#!/bin/sh

export PATH=/usr/lib64/openmpi/bin:$PATH
export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib/:$LD_LIBRARY_PATH
export PSM3_DEVICES='self,shm' 

# Initialize a variable to store the source code file name
SOURCE_FILE=""

if [ "$#" -ne 0 ]; then
	if [ "$1" = "-help" ]; then
		echo "Compile and run the mpi examples with 1 to 16 processes in a row."
		echo "Add parameter 'sr' to run the example with send/receive."
		echo "Add parameter 'lowgran' to run the example with low granularity."
		exit 1
	fi
fi


if [ "$#" -eq 0 ]; then
    SOURCE_FILE="mpi_pi.cpp"
else
    if [ "$1" = "sr" ]; then
        SOURCE_FILE="mpi_pi_sr.cpp"
    elif [ "$1" = "lowgran" ]; then
        SOURCE_FILE="mpi_pi_lowgran.cpp"
    else
        echo "Invalid argument. Use 'sr' for mpi_pi_sr.cpp or 'lowgran' for mpi_pi_lowgran.cpp."
        echo "No argument for mpi_pi.cpp."
        exit 1
    fi
fi

SOURCE_DIR="$(dirname "$(realpath "$0")")"
SOURCE_FILE="${SOURCE_DIR}/${SOURCE_FILE}"

echo "Running" $SOURCE_FILE 

# Compile the selected source file
mpicxx -o mpi_pi $SOURCE_FILE -lm -Wall -std=c++11

# Run the MPI program with different numbers of processes
for i in 1 2 4 8 16 32
do
    mpirun -np $i --oversubscribe ./mpi_pi
done