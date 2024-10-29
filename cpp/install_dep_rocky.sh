#!/bin/sh

sudo dnf install -y openmpi openmpi-devel

export PATH=/usr/lib64/openmpi/bin:$PATH
export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib/:$LD_LIBRARY_PATH
export PSM3_DEVICES='self,shm' 