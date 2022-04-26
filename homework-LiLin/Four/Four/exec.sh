#!/bin/bash
sudo dmesg -C
path=$(pwd)
#cd $path/PrintingDriver
cd $path/PrintingDriverSchedule
#cd $path/PrintingDriverMutex
make
sudo insmod PrintModule.ko
cd $path/UserApp
g++ main.cpp -o a.out -lpthread
sudo time ./a.out
sudo rmmod PrintModule.ko
dmesg
#make 
