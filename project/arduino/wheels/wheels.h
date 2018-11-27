#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define F_CPU 16000000


void setup_wheels();
void move_forward();
void move_backward();
void turn_left();
void turn_rigth();

