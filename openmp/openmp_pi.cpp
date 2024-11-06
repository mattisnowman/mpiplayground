// Caculate PI using MPI and numerical integration
// of a quarter circle

#include <cmath>
#include <iostream>
#include <chrono> 

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

    auto begin = std::chrono::high_resolution_clock::now();
    
    double subsum = 0, sum = 0;

    // Parallelize the loop with OpenMP
    #pragma omp parallel for reduction(+:sum)
    for (int64_t i = 0; i <= N; i += 1)
    {
        const double x = from + i * d;
        const double fx = f(x);
        subsum += fx * d;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Exec. duration = " << std::chrono::duration<double>(end - begin).count()
              << "s, PI = " << 4 * sum << ", error = "  << 4 * sum - M_PI << std::endl;
        
    return 0;
}
