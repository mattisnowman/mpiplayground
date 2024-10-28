
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

    constexpr int source_ID = 0;
    constexpr int N = 60;

    std::vector<int> global_data;
    std::vector<int> local_data;

    if (rank == source_ID) {
        global_data.resize(N);
        for (int i = 0; i < N; i++)
            global_data[i] = std::rand();        
        std::cout << "proc " << rank << ": sending " <<  global_data << std::endl;
    }

    local_data.resize(N/size);

    MPI_Scatter(global_data.data(), N/size, MPI_INT, 
                local_data.data(), N/size, MPI_INT, 0, MPI_COMM_WORLD);

    std::cout << "proc " << rank << ": recevied " << local_data << std::endl;

    MPI_Finalize();
    return 0;
}
