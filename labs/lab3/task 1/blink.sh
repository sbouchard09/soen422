#!/bin/bash

PIN="44"
GPIOPIN="/sys/class/gpio/gpio$PIN"

# 
if [ -d "$GPIOPIN" ]; then
    echo "blinking LED connected to pin $PIN..."
else
    echo $PIN > /sys/class/gpio/export
	echo "Blinking LED connected to pin $PIN..."
	sleep 1
fi

# set pin 44 to output
echo 1 > $GPIOPIN/direction

# in an infinite loop, set pin 44 to high (LED on) for 2 seconds
# then low (LED off) for two seconds
while true; do
    echo 1 > $GPIOPIN/value
	echo "Light on"
	sleep 2
	echo 0 > $GPIOPIN/value
	echo "Light off"
	sleep 2
done