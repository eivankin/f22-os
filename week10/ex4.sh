#!/bin/bash

rm -rf tmp
mkdir tmp
cd tmp
touch file1 file2
ln file1 link1
cd ..

gcc -o ex4 ex4.c
./ex4 > ex4.txt
rm ex4