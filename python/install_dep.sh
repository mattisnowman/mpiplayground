#!/bin/bash

sudo apt-get update
pkgs=(openmpi-bin python3-mpi4py python3-numpy)
sudo apt-get -y install "${pkgs[@]}" 
