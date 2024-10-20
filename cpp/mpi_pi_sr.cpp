// This program is to caculate PI using MPI and numerical integration
// If f(x) = 4 * sqrt(1 - x^2), then PI is the intergral of f(x) from 0 to 1

#include <cmath>
#include <mpi.h>

constexpr double f(double x)
{
    return sqrt(1 - x * x);
}
 
int main(int argc, char* argv[])
{
    constexpr int64_t N = 1e7;

    constexpr double from = 0.;
    constexpr double to = 1.;
    
    constexpr double d = (to - from) / static_cast<double>(N);

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get process id and total number of processes size
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Wait until all processes arrive here, then continue
    MPI_Barrier(MPI_COMM_WORLD);
    const double begin = MPI_Wtime();
    
    //Each process caculates a part of the sum. 
    double subsum = 0;
    for (int64_t i = rank; i < N; i += size)
    {
        const double x = from + i * d;
        const double fx = f(x);
        subsum += fx * d;
    }
    
    double sum = subsum;
    //Sum up all sub sums
    if (rank)
        MPI_Send(&subsum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    else {
        for (int i = 1; i < size; i++) {
            double subsum2;
            MPI_Recv(&subsum2, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, 0);
            sum += subsum2;
        }
    }
    
    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);
    const double end = MPI_Wtime();
    
     //Caculate and print PI
    if (!rank)
        std::cout << "Processes = " << size << ", Exec. duration = " << end - begin << "s, PI = " << 4 * sum << ", error = "  << 4 * sum - M_PI << std::endl;
    
    MPI_Finalize();
    
    return 0;
}
