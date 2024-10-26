#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    MPI_Barrier(MPI_COMM_WORLD);
    const double begin = MPI_Wtime();

    //code
    //code
    //code...

    MPI_Barrier(MPI_COMM_WORLD);
    const double end = MPI_Wtime();

    MPI_Finalize();
    
    return 0;
}
