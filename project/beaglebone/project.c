#include "project.h"

/* sends the direction that the motors should turn (left/right) */
void send_direction(int fd, uint8_t t) {
  int status;
  uint8_t tx = t; // send direction to motors
  uint8_t rx = 1;
  /*
   * from spidev.h:
   * spi_ioc_transfer describes a single SPI transfer
   */
  struct spi_ioc_transfer send = {
    .tx_buf = (unsigned long)tx, // tx & rx are type __u64 (unsigned long)
    .rx_buf = (unsigned long)rx,
    .len = sizeof(tx),
    .speed_hz = frequency,
    .delay_usecs = 0,   // no delay
    .bits_per_word = 1
  };
  status = ioctl(fd, SPI_IOC_MESSAGE(1), &send); // syscall: ioctl(fd, request), request is an SPI transaction in this case
}

/* returns the direction that the vehicle should go in */
uint8_t get_direction(int fd) {
  int status;
  uint8_t tx = 1;
  uint8_t rx = 1; // initialize rx (will receive direction from arduino)
  /*
   * from spidev.h:
   * spi_ioc_transfer describes a single SPI transfer
   */
  struct spi_ioc_transfer receive = {
    .tx_buf = (unsigned long)tx, // tx & rx are __u64 (unsigned long)
    .rx_buf = (unsigned long)rx,
    .len = sizeof(tx),
    .speed_hz = frequency,
    .delay_usecs = 0, // no delay
    .bits_per_word = 1
  };
  status = ioctl(fd, SPI_IOC_MESSAGE(1), &receive); // syscall: ioctl(fd, request), request is an SPI transaction in this case
  return rx; // return received direction
}

int main() {
  int fd; // address of the slave
  uint8_t received_direction;
  uint8_t direction = 1; // direction to go in; default forward
  printf("hello");

  while(1) {
    // receive direction from sensors
    fd = open(sensor, O_RDWR);              // open connection to sensor arduino
    received_direction = get_direction(fd); // receive direction from arduino via spi
    close(fd);
    // set direction of vehicle
    if(received_direction == 2) {           // move backward
      direction = 2;
    } else {                                // move forward by default
      direction = 1;
    }
    // send direction to motors
    fd = open(motor, O_RDWR);               // open connection to motor arduino
    send_direction(fd, direction);          // send direction
    close(fd);

    usleep(1000000); // sleep for 1s
  }
  return 0;
}