#!/bin/bash
outputDevice=/dev/spidev0.0
cat ./testImages/allBlack.pix > $outputDevice
if [ -n "$1" ]
then
  cat $1 > $outputDevice
fi
