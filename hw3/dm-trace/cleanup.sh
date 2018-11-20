#!/bin/bash

# unmounts the dm-trace device and deletes the device.

sudo umount -l /mnt 2> /dev/null
sudo dmsetup remove dmtarget 2> /dev/null
sudo rmmod dm-trace
