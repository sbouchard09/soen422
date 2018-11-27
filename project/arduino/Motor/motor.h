#define F_CPU 16000000L

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


void inital_slave();
void move_forward();
void move_backward();
void turn_left();
void turn_rigth();
void turn_right_90();
void turn_left_90();