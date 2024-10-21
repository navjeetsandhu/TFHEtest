#!/bin/bash


OS=$(uname -s)
if [ "$OS" == "Darwin" ]; then
  echo "This is macOS"
  export LDFLAGS="-L/usr/local/opt/libomp/lib"
  export CPPFLAGS="-I/usr/local/opt/libomp/include"
else
    echo "This is not macOS"
fi

rm -rf build
mkdir build
cd build
cmake ..
make