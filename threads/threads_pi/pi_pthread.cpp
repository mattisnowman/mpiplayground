#include <iostream>
#include <pthread.h>
#include <cmath>
#include <chrono>  // For measuring time

constexpr static int N = 1e7;

constexpr double from = 0.;
constexpr double to = 1.;
constexpr double dx = (to - from) / static_cast<double>(N);

constexpr double f(double x) {
    return sqrt(1 - x * x);
}

// Structure to hold thread arguments
struct ThreadData {
    int rank;
    int size;
    double result;
};

// Function to be executed by each thread
void* calculate_pi(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    data->result = 0;
    for (int i = data->rank; i < N; i += data->size) {
        const double x = from + i * dx;
        const double fx = f(x);
        data->result += fx * dx;
    }
    return nullptr;
}

int main() {
    constexpr int n = 4;
    pthread_t threads[n];
    ThreadData thread_data[n];

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // Create threads
    for (int i = 0; i < n; i++) {
        thread_data[i].rank = i;
        thread_data[i].size = n;
        pthread_create(&threads[i], nullptr, calculate_pi, &thread_data[i]);
    }

    // Join threads and accumulate results
    double sum = 0;
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], nullptr);
        sum += thread_data[i].result;
    }

    // Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();

    // Output the result and the execution time
    std::cout << "Processes = " << n << ", Exec. duration = " 
              << std::chrono::duration<double>(end - begin).count() 
              << "s, PI = " << 4 * sum << ", error = "  << 4 * sum - M_PI << std::endl;

    return 0;
}
