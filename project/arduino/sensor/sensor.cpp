#include "pins_arduino.h"
#include "sensor.h"

/* set arduino as an SPI slave */
void spi_slave_setup(void) {
    DDRB &= ~((1 << 2) | (1 << 3) | (1 << 5));  // SCK, MOSI, SS as inputs
    DDRB |= (1 << 4);                           // MISO as output
    
    SPCR &~ (1 << MSTR);                        // set as slave
    SPCR |= (1 << SPE);                         // enable spi
    SPCR |= (1 << SPIE);                        // inable interrupts
    
    sei();
}

/* set up ADC */
void adc_setup() {
    ADMUX |= (1 << REFS0);                                  // AVCC
    // use pin A0 -> nothing to set in ADMUX
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   // set ADC frequency to 128 kHz
    ADCSRA |= (1 << ADEN);                                  // enable adc
}

/* returns an analog value from a sensor */
int get_adc_value() {
    ADCSRA |= (1 << ADSC);          // analog to digital conversion
    while(!(ADCSRA & (1 << ADSC))); // wait until conversion is complete
    int value = ADC;
    return value;
}

/* 
 * interrupt
 * gets triggered each time master sends a value
 * reads values from sensors and determines which direction to turn
 * sends direction to master (Beaglebone black)
 */
ISR (SPI_STC_vect) {
  byte c = SPDR;

  int value_left = 0;
  int value_right = 0;
  // set ADMUX to read from left sensor
  ADMUX &= ~(1 << MUX0);
  value_left = get_adc_value();         // get adc value from left sensor
  Serial.println(value_left);           // debugging
  // set ADMUX to read from right sensor
  ADMUX |= (1 << MUX0);
  value_right = get_adc_value();        // get adc value from right sensor
  Serial.println(value_right);          // debugging
  if(value_left < value_right) {        // obstacle closer to left side
    Serial.println("turn right");       // debugging
    SPDR = 1;
        //send_value(1); // turn right
        //delayMicroseconds(20);
        //send_value(value_left);
  } else if(value_left > value_right) { // obstacle closer to right side
    Serial.println("turn left");        // debugging
    SPDR = 2;
        //send_value(2); // turn left
        //delayMicroseconds(20);
        //send_value(value_right);
  } else {
    SPDR = 0;
  }
}

int main(void) {
    adc_setup();
    spi_slave_setup();
    init();
    Serial.begin(9600);
    while(1);
    return 0;
}