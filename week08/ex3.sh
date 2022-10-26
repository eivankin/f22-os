#!/bin/bash
gcc -o ex2 ex2.c
./ex2 &
top -d 1 -n 11 -p $!