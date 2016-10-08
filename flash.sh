#!/bin/bash
outputDevice=/dev/spidev0.0

while [ 1 ]
do
	cat $1 > $outputDevice
	sleep 1
	cat $2 > $outputDevice
	sleep 1
done
