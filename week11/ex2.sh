#!/bin/bash
MOUNT_POINT="./lofsdisk"
OUT_FILE="ex2.out"
OUTPUT="ex2.txt"

./ex1.sh 2>/dev/null 1>&2

echo Evgenij > $MOUNT_POINT/file1
echo Ivankin > $MOUNT_POINT/file2

mkdir -p $MOUNT_POINT/{bin,lib64,lib}
mkdir -p $MOUNT_POINT/lib/x86_64-linux-gnu
binaries=( bash cat echo ls )
for binary in "${binaries[@]}"
do
  cp "/bin/$binary" "$MOUNT_POINT/bin/$binary"
  libs=$(ldd "/bin/$binary" | egrep -o '/lib.*\s')
  for lib in $libs
  do
    cp $lib "$MOUNT_POINT$lib"
  done
done


gcc ex2.c -o $OUT_FILE
cp $OUT_FILE $MOUNT_POINT


echo "With chroot:" > $OUTPUT
sudo chroot $MOUNT_POINT "./$OUT_FILE" >> $OUTPUT

echo "
Without chroot:" >> $OUTPUT
"./$OUT_FILE" >> $OUTPUT