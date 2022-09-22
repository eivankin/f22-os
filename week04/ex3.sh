#!/bin/bash

# !!!IMPORTANT!!!: does not work with sh, run this script with bash

pstree_and_wait() {
  rm $OUT
  ./ex3 $N &
  export APP_PID=$!

  for (( i = 0; i<=$N; i++ ));
  do
    if [[ "$i" != '0' ]]; then
      sleep 5
    fi
    pstree $APP_PID >> $OUT
  done

  cat $OUT >> ex3.txt
}

rm ex3.txt
gcc ex3.c -o ex3
echo "// The results of the first run for 3 fork calls" >> ex3.txt
export N=3
export OUT=run_1.txt
pstree_and_wait

echo "// The results of the first run for 5 fork calls" >> ex3.txt
export N=5
export OUT=run_2.txt
pstree_and_wait

echo "// The difference" >> ex3.txt
diff run_1.txt run_2.txt >> ex3.txt
rm run_1.txt run_2.txt

echo "As we can see, the program generates binomial tree of processes. \
First three stages of growth is the same, but if number of fork iterations equals 5, the tree continues to grow." >> ex3.txt
cat ex3.txt
rm ex3