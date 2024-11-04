
#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    constexpr int source_ID = 0;
    
    int value;
    if (rank == source_ID)
        value = std::rand();
    
    MPI_Bcast(&value, 1, MPI_INT, source_ID, MPI_COMM_WORLD);
    
    if (rank != source_ID) 
        std::cout << "proc " << rank << ": recevied " << value << " from proc " << source_ID << std::endl;
    
    MPI_Finalize();
    return 0;
}
