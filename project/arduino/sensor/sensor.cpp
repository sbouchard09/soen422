#include "sensor.h"

int max = 5;
int count = 0;

void spi_slave_setup(void) {
    DDRB &= ~((1 << 2) | (1 << 3) | (1 << 5)); // SCK, MOSI, SS as inputs
    DDRB |= (1 << 4); // MISO as output
    
    SPCR &~ (1 << MSTR); // set as slave
    SPCR |= (1 << SPE); // enable spi
    SPCR |= (1 << SPIE); // inable interrupts
    
    sei();
}

void adc_setup() {
    ADMUX |= (1 << REFS0); // AVCC
    // use pin A0 -> nothing to set in ADMUX
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // set ADC frequency to 128 kHz
    ADCSRA |= (1 << ADEN); // enable adc
}

void timer_setup() {
    // using timer 2
    TCCR2A = 0;
    TCCR2A |= (1 << WGM21); // set to Clear Timer on Compare Match (CTC) mode with OCR2A as max

    TCCR2B = 0;
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // set prescaler to 1024

    TCNT2 = 0; // set counter to 0
    OCR2A = 100; // when TCNT2 reaches this value, the output compare interrupt will be triggered; roughly 100 ms
    TIMSK2 = (1 << OCIE2A); // enable timer2 compare match A interrupt
}

int get_adc_value() {
    ADCSRA |= (1 << ADSC); // analog to digital conversion
    while(!(ADCSRA & (1 << ADIF))); // wait until conversion is complete
    ADCSRA |= (1 << ADIF); // reset ADIF to 1 for the next conversion
    int value = ADC;
    return value;
}

// reads and ADC value from the sensors & sends appropriate value to the BeagleBone black
void read() {
    int value_left = 0;
    int value_right = 0;
    // set ADMUX to read from left sensor
    ADMUX = MUX0;
    value_left = get_adc_value(); // get adc value from left sensor
    // set ADMUX to read from right sensor
    ADMUX = MUX1;
    value_right = get_adc_value(); // get adc value from right sensor
    
    if(value_left < value_right) { // obstacle closer to left side
        send_value(1); // turn right
        send_value(value_left);
    } else if(value_right > value_left) { // obstacle closer to right side
        send_value(2); // turn left
        send_value(value_right);
    }
}

void send_value(int value) {
    SPDR = value; // put value in the SPDR register to transfer
    while(!(SPSR & (1 << SPIF))); // wait until transmission is complete
}

int main(void) {
    adc_setup();
    timer_setup();
    spi_slave_setup();
    while(1);
    return 0;
}

ISR(TIMER2_COMPA_vect) {
    count++;
    if(count > max) { // max = 5, so will call read (and therefore send a reading to the BeagleBone black) about every 500 ms
        read();
        count = 0;
    }
}