#!/bin/bash
gcc ex1.c -o ex1
page_nums=(10 50 100)
for i in "${page_nums[@]}"; do
  echo $i
  ./ex1 $i
done
rm ex1