#!/bin/bash

function run_in_separate_window() {
    xterm -e $1
}

NUM_OF_SUBSCRIBERS=${1:-1} # default value: 1
PIPE="/tmp/ex1"

# 0 < n < 4
if (( $NUM_OF_SUBSCRIBERS < 1 || $NUM_OF_SUBSCRIBERS > 3 ))
then
  echo 'Invalid number of subscribers'
  exit
fi

# recompile publisher & subscriber
gcc publisher.c -o publisher && gcc subscriber.c -o subscriber

run_in_separate_window "./publisher $NUM_OF_SUBSCRIBERS" &

for (( i = 0; i < $NUM_OF_SUBSCRIBERS; i++ ));
do
  run_in_separate_window ./subscriber &
done

