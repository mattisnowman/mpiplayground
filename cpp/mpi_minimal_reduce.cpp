
#include <mpi.h>
#include <vector>

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "(" << v.size() << ")[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

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
