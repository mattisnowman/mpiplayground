#!/bin/sh

g++ -o pi_pthread pi_pthread.cpp -O3 -lpthread -std=c++11
./pi_pthread