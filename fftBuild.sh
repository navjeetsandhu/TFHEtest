#!/bin/bash

OS=$(uname -s)
if [ "$OS" == "Darwin" ]; then
  echo "This is macOS"
  export LDFLAGS="-L/usr/local/opt/libomp/lib"
  export CPPFLAGS="-I/usr/local/opt/libomp/include"
else
    echo "This is not macOS"
fi

if [ -d "build" ]; then
    echo "Directory 'build' exists."
    rm -rf build
else
    echo "Directory 'build' does not exist."
fi

mkdir build
cd build
if [ $# -ge 1 ]; then
  echo "Input provided is: " $1
  if [ $1 -eq 1 ]; then
    echo "Input 1 mean disabling FPGA in build"
    cmake .. -DUSE_FPGA=OFF
  else
    echo "Any input except 1 mean disabling FPGA and FFTW3"
    cmake .. -DUSE_FPGA=OFF -DUSE_FFTW3=OFF
  fi
else
    cmake ..
fi

make