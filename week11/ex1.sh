#!/bin/bash
FILE="lofs.img"
MOUNT_POINT="./lofsdisk/"
FILE_SIZE="50M"

function get_dev() {
    losetup --list -a -n | grep $FILE | awk '{print $1}'
}

if [[ -d $MOUNT_POINT ]]
then
  sudo umount $MOUNT_POINT
  sudo rm -rf $MOUNT_POINT
  old_device=$(get_dev)
  [ -e $FILE ] && rm $FILE
  [ ! -z "$old_device" ] && sudo losetup --detach $old_device
fi

fallocate -l $FILE_SIZE $FILE
sudo losetup -f $FILE

device=$(get_dev)
sudo mkfs.ext4 $device
[ -d $MOUNT_POINT ] || mkdir $MOUNT_POINT