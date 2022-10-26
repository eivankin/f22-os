#!/bin/bash
gcc -o ex2 ex2.c && ./ex2 & vmstat 1 11 > ex2.txt