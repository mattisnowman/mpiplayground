
#include <iostream>
#include <mpi.h>
#include <vector>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    constexpr int dest_ID = 0;
 
    int sum;
    int value;

    srand(rank);
    value = std::rand() % 100;        
    std::cout << "proc " << rank << ": sending " <<  value << std::endl;
    
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, dest_ID, MPI_COMM_WORLD);

    if (rank == dest_ID)
        std::cout << "proc " << rank << ": sum recevied " << sum << std::endl;

    MPI_Finalize();
    return 0;
}
