from mpi4py import MPI
import random

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

source_ID = 0
N = 60

local_data = None

if rank == source_ID:
    global_data = [[random.randint(0, 100) for _ in range(N//size)] for p in range(size)]
    print(f"proc {rank}: sending {global_data}")
else:
    global_data = None

local_data = comm.scatter(global_data, root=source_ID)

print(f"proc {rank}: received {local_data}")