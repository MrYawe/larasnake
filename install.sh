#!/bin/bash

# Installer SDL 1.2s :
sudo apt-get install libsdl1.2debian -y --force-yes
sudo apt-get install libsdl1.2-dev -y --force-yes
sudo apt-get install libsdl-image1.2 -y --force-yes
sudo apt-get install libsdl-image1.2-dev -y --force-yes
sudo apt-get update

# gcc -o prog main.c `sdl-config --cflags --libs`