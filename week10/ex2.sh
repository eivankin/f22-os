#!/bin/bash
mkdir -p ../week01
echo Evgenij > ../week01/file.txt
# do not create week10 folder since we already in it
link ../week01/file.txt _ex2.txt
inode=$(stat -c "%i" ../week01/file.txt)
find .. -inum $inode > ex2.txt
find .. -inum $inode -exec rm {} \; >> ex2.txt # does not output anything