#!/bin/bash

#install used package
sudo apt-get install cmake -y --force-yes
sudo apt-get install wget -y --force-yes

#install cmocka
mkdir lib

wget https://cmocka.org/files/1.0/cmocka-1.0.1.tar.xz
xz -d cmocka-1.0.1.tar.xz
tar vxf cmocka-1.0.1.tar
rm cmocka-1.0.1.tar
mv cmocka-1.0.1 lib/

cd lib/cmocka-1.0.1
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
cd ../../..
