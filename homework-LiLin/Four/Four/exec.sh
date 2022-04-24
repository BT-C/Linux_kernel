#!/bin/bash
sudo dmesg -C
path=$(pwd)
cd $path/PrintingDriver
make
sudo insmod PrintModule.ko
cd $path/UserApp
g++ main.cpp -o a.out -lpthread
sudo ./a.out
sudo rmmod PrintModule.ko
dmesg
#make 
