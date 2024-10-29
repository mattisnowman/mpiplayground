from mpi4py import MPI
import random

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

dest_ID = 0
N = 5

random.seed(rank)

local_data = [random.randint(0, 100) for _ in range(N)]
print(f"proc {rank}: sending {local_data}")

global_data = comm.gather(local_data, root=dest_ID)

if rank == dest_ID:
    print(f"proc {rank}: received {global_data}")
