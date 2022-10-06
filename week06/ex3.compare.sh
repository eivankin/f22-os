#!/bin/bash
Q=${1:-1}

echo "FCFS vs RR with quantum=$Q" > ex3.txt
diff <(cat input_sample_2.txt | ./ex1.sh) <( echo "$Q
$(cat input_sample_2.txt)"  | ./ex3.sh) >> ex3.txt

echo "

SJF vs RR with quantum=$Q" >> ex3.txt
diff <(cat input_sample_2.txt | ./ex2.sh) <( echo "$Q
$(cat input_sample_2.txt)"  | ./ex3.sh) >> ex3.txt

echo "

As we can see from the difference, RR algorithm has the best results (average TAT & WT) in theory,
but it takes time to switch between processes in practice." >> ex3.txt