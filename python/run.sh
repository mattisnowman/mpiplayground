#!/bin/sh

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
    SOURCE_FILE="mpi_pi.py"
else
    if [ "$1" = "sr" ]; then
        SOURCE_FILE="mpi_pi_sr.py"
    elif [ "$1" = "lowgran" ]; then
        SOURCE_FILE="mpi_pi_lowgran.py"
    else
        echo "Invalid argument. Use 'sr' for mpi_pi_sr.py or 'lowgran' for mpi_pi_lowgran.py."
        echo "No argument for mpi_pi.py."
        exit 1
    fi
fi

SOURCE_DIR="$(dirname "$(realpath "$0")")"
SOURCE_FILE="${SOURCE_DIR}/${SOURCE_FILE}"

echo "Running" $SOURCE_FILE 

# Run the MPI program with different numbers of processes
for i in 1 2 4 8 16 32
do
	mpirun -oversubscribe -n $i python3 $SOURCE_FILE
done