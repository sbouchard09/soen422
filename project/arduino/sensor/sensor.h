#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void adc_setup(void);
void read(void);
void send_value(int);
void spi_slave_setup(void);
void timer_setup(void);
int get_adc_value(void);