#ifndef PROJECT_H
#define PROJECT_H

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <time.h>

static uint32_t frequency = 1000000;            // 1MHz frequency
static const char *sensor = "/dev//spidev1.0";  // SPI for sensors arduino
static const char *motor = "/dev//spidev2.0";   // SPI for motors arduino
static uint32_t tx_buffer;                      // transfer buffer

uint8_t get_direction(int);
void send_direction(int, uint8_t);

#endif