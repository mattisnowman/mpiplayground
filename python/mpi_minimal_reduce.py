from mpi4py import MPI
import random

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

dest_ID = 0

random.seed(rank) 
value = random.randint(0, 99)
print(f"proc {rank}: sending {value}")

sum_value = comm.reduce(value, op=MPI.SUM, root=dest_ID)

if rank == dest_ID:
    print(f"proc {rank}: sum received {sum_value}")