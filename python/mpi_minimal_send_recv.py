from mpi4py import MPI
import random

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

source_ID = 0
dest_ID = 2

if rank == source_ID:
    value = random.randint(0, 100)
    print(f"proc {rank}: sending {value} to proc {dest_ID}")
    comm.send(value, dest=dest_ID, tag=0)

elif rank == dest_ID:
    value = comm.recv(source=source_ID, tag=0)
    print(f"proc {rank}: received {value} from proc {source_ID}")
