from mpi4py import MPI
import random

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

source_ID = 0

if rank == source_ID:
    value = random.randint(0, 100) 
else:
    value = None

value = comm.bcast(value, root=source_ID)

if rank != source_ID:
    print(f"proc {rank}: received {value} from proc {source_ID}")
