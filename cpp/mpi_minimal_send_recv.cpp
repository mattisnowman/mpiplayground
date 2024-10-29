
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    constexpr int source_ID = 0;
    constexpr int dest_ID = 2;

    int value;
    if (rank == source_ID) {
        value = std::rand();
        std::cout << "proc " << rank << ": sending " << value << " to proc " << dest_ID << std::endl;
        MPI_Send(&value, 1, MPI_INT, dest_ID, 0, MPI_COMM_WORLD);
    }
    if (rank == dest_ID) {
        MPI_Recv(&value, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, 0);
        std::cout << "proc " << rank << ": recevied " << value << " from proc " << source_ID << std::endl;
    }

    MPI_Finalize();
    return 0;
}
