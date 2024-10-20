#!/usr/bin/env python 

# Caculate PI using MPI and numerical integration
# of a quarter circle

from mpi4py import MPI
import math

def f(x: float) -> float:
	return math.sqrt(1 - x ** 2)

N: int = int(1e6)

fromV: float = 0.
toV: float = 1.

d: float = (toV - fromV) / N

# Initialize MPI
comm = MPI.COMM_WORLD
size: int = comm.Get_size()
rank: int = comm.Get_rank()

# Wait until all processes arrive here, then continue
comm.Barrier()
begin: float = MPI.Wtime()

sum: float = 0
# Each process caculates a part of the sum. 
for i in range(rank, N, size):
    x: float = fromV + i * d
    fx: float = f(x)
    subsum: float = fx * d
    reduced = comm.reduce(subsum, op = MPI.SUM, root=0)
    if rank == 0:
        sum += reduced

# Sum up all sub sums

# Synchronize all processes and get the end time
comm.Barrier()
end: float = MPI.Wtime()

# Caculate and print PI
if rank == 0:
	print("Processes = ", size, ", Exec. duration = ", end - begin, "s, PI = ", 4 * sum, ", error = ", 4 * sum - math.pi)


MPI.Finalize()