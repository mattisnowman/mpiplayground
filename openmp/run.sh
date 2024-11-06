#!/bin/sh

g++ -o pi_multi openmp_pi.cpp -fopenmp -lm -Wall -std=c++11
g++ -o pi_single openmp_pi.cpp -lm -Wall -std=c++11

echo "Single core:"
./pi_single
echo "Multiple cores with openmp:"
./pi_multi