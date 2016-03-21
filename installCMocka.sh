#!/bin/bash

#install used package
sudo apt-get install cmake -y --force-yes

#install cmocka
cd lib/cmocka-1.0.0/build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
cd ../../..
