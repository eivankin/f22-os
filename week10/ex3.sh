#!/bin/bash

[ ! -e _ex3.txt ] || rm _ex3.txt
echo Evgenij > _ex3.txt
chmod -x _ex3.txt
stat -c "%A %a" _ex3.txt > ex3.txt
chmod ou+rwx _ex3.txt
stat -c "%A %a" _ex3.txt >> ex3.txt
chmod g=u _ex3.txt
stat -c "%A %a" _ex3.txt >> ex3.txt

echo "
660 means
read and write rights to owner (110),
read and write rights to group (110),
no rights to others (000)
" >> ex3.txt
echo "775 means
read, write and execute rights to owner (111),
read, write and execute rights to group (111),
read and execute rights to others (101)
" >> ex3.txt
echo "777 means
read, write and execute rights to for owner, group and others (111)
" >> ex3.txt