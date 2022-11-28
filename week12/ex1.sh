#!/bin/bash
sudo cat /proc/ioports > ex1.txt
echo "
dma1 is a direct memory access port. It allows to write directly to memory, bypassing CPU." >> ex1.txt
echo "pic1 is the first peripheral interface controller. It allows to communicate with peripheral devices." >> ex1.txt
echo "timer1 is a timer port. It allows to access clocks with different frequencies." >> ex1.txt