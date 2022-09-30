#!/bin/bash
gcc -pthread ex3.c -o ex3 -lm

N=10000000

function run_with_time() {
  time ./ex3 $N $1 >/dev/null
}

for M in 1 2 4 10 100
do
  echo "

Measurements for M=$M"
  run_with_time $M
done

rm ex3