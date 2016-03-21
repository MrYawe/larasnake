#!/bin/bash

#install used package
sudo apt-get install wget
sudo apt-get install cmake

#install cmocka
wget https://open.cryptomilk.org/attachments/download/54/cmocka-1.0.0.tar.xz
xz -d cmocka-1.0.0.tar.xz
tar vxf cmocka-1.0.0.tar
cd cmocka-1.0.0
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
rm cmocka-1.0.0.tar
rm cmocka-1.0.0
