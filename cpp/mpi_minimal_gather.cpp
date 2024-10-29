
#include <mpi.h>
#include <vector>

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "(" << v.size() << ")[";
    for (auto i : v)
        os << " " << i;
    return os << "]";
}

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    constexpr int dest_ID = 0;
    constexpr int N = 5;

    std::vector<int> global_data;
    std::vector<int> local_data;

    srand(rank);
    
    local_data.resize(N);
    for (int i = 0; i < N; i++)
        local_data[i] = std::rand();        
    std::cout << "proc " << rank << ": sending " <<  local_data << std::endl;
    
    if (rank == dest_ID)
        global_data.resize(N * size);

    MPI_Gather(local_data.data(), N, MPI_INT, 
               global_data.data(), N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == dest_ID)
        std::cout << "proc " << rank << ": recevied " << global_data << std::endl;

    MPI_Finalize();
    return 0;
}
