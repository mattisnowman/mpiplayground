#!/bin/bash

sudo apt-get update
pkgs=(openmpi-bin libopenmpi-dev g++)
sudo apt-get -y install "${pkgs[@]}" 
