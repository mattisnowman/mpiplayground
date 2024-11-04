// Caculate PI using MPI and numerical integration
// of a quarter circle

#include <cmath>
#include <iostream>
#include <mpi.h>

constexpr double f(double x)
{
    return sqrt(1 - x * x);
}
 
int main(int argc, char* argv[])
{
    constexpr int64_t N = 1e12;

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
    double subsum = 0, sum = 0;
    for (int64_t i = rank; i <= N; i += size)
    {
        const double x = from + i * d;
        const double fx = f(x);
        subsum += fx * d;
        if (i % (N/100) == 0) {
            std::cout << MPI_Wtime() - begin << "s: Step " << i << "/" << N << std::endl;
        }

    }
    
    //Sum up all sub sums
    MPI_Reduce(&subsum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);
    const double end = MPI_Wtime();
    
     //Caculate and print PI
    if (!rank)
        std::cout << "Processes = " << size << ", Exec. duration = " << end - begin << "s, PI = " << 4 * sum << ", error = "  << 4 * sum - M_PI << std::endl;
    
    MPI_Finalize();
    
    return 0;
}
