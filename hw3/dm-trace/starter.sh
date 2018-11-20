#!/bin/bash

if [[ "$#" -lt 3 ]]; then
        echo "
./starter.sh <dev> <fsType> <devSize>

        dev - underlying device. eg. /dev/sdb
        fsType - file system type. eg.  ext4, btrfs, f2fs
        devSize: - size of the device in GBs
	"
        exit
fi

dev=$1
fsType=$2
# number of sectors
devSize=$3
numSectors=$(($devSize * 2 * 1024 * 1024))

echo " make sure the device is unmounted and removed"

sudo umount -l /mnt 2> /dev/null
sudo dmsetup remove dmtarget 2> /dev/null
sudo rmmod dm-trace
sudo insmod dm-trace.ko

echo " Format file system"

if [[ "$fsType" == "ext4" ]]; then
	yes | sudo mkfs.$fsType $dev
elif [[ "$fsType" == "btrfs" ]]; then
	sudo mkfs.$fsType -f $dev
else
	echo "unrecognized fs type"
	exit
fi

echo " Create dm-trace device"

sudo dmsetup create dmtarget --table "0 $numSectors trace $dev 0" --readahead none

echo " Mount dm-trace device."

sudo mount -t $fsType /dev/mapper/dmtarget /mnt
