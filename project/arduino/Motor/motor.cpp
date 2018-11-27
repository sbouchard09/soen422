

void inital_slave()
{
	DDRB |= (1<<PB4);                 //set MISO as output
	SPCR = (1<<SPE)|(1<<SPIE);        //enable SPI and enable SPI interrupt
}

void setup_wheels() {
	DDRD |= (1 << PD6);											//Set OC0A
	//Setup inputs direction of wheels
	DDRB |= (1 << PD4) | (1 << PD5);
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC4) | (1 << PC5);
	DDRB |= (1 << PB1) | (1 << PB2); 

	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);		//Fast PWM, Clear OC0A on Compare Match
	TCCR0B |= (1 << CS00);										//No prescalling

	OCR0A = 0;													//initial compare match value with 0% of duty cycle
}

void move_forward(){
	//Front Left Wheel
	PORTD |= (1 << PD4);
	PORTD &= ~(1 << PD5);

	//Back Left Wheel
	PORTB |= (1 << PB2);
	PORTB &= ~(1 << PB1);

	//Front Right Wheel
	PORTC |= (1 << PC4);
	PORTC &= ~(1 << PC5);

	//Back Right Wheel
	PORTC |= (1 << PC0);
	PORTC &= ~(1 << PC1);
}

void move_backward(){
	//Front Left Wheel
	PORTD &= ~(1 << PD4);
	PORTD |= (1 << PD5);

	//Back Left Wheel
	PORTB &= ~(1 << PB2);
	PORTB |= (1 << PB1);

	//Front Right Wheel
	PORTC &= ~(1 << PC4);
	PORTC |= (1 << PC5);

	//Back Right Wheel
	PORTC &= ~(1 << PC0);
	PORTC |= (1 << PC1);
}

/*
 Left wheels are set to go forward and Right wheels are set to go backwards
*/
void turn_left(){
	//Front Left Wheel
	PORTD |= (1 << PD4);
	PORTD &= ~(1 << PD5);

	//Back Left Wheel
	PORTB |= (1 << PB2);
	PORTB &= ~(1 << PB1);

	//Front Right Wheel
	PORTC &= ~(1 << PC4);
	PORTC |= (1 << PC5);

	//Back Right Wheel
	PORTC &= ~(1 << PC0);
	PORTC |= (1 << PC1);
}

/*
 Right wheels are set to go forward and Left wheels are set to go backwards
*/
void turn_rigth(){
	//Front Left Wheel
	PORTD &= ~(1 << PD4);
	PORTD |= (1 << PD5);

	//Back Left Wheel
	PORTB &= ~(1 << PB2);
	PORTB |= (1 << PB1);

	//Front Right Wheel
	PORTC |= (1 << PC4);
	PORTC &= ~(1 << PC5);

	//Back Right Wheel
	PORTC |= (1 << PC0);
	PORTC &= ~(1 << PC1);
}

//Turn 90 degree RIGHT
void turn_right_90()
{
    turn_rigth();
    _delay_ms(500);
}

//Turn 90 degree LEFT
void turn_left_90()
{
    turn_left();
    _delay_ms(500);
}



int main(void){
	
	setup_wheels();
	inital_slave();
	
	OCR0A = 255; //max speed

    	while(1)
   	    {
			//turnLeft();
    	}
    	return 0;   
}

ISR(SPI_STC_vect) //Interrupt for when serial transfer is finished
{ 	
	switch(SPDR) //each case corresponds to a direction. 
	{
		case 1 : //forwards
			move_forward();
			break;     
		case 2 : //backwards
			move_backward();
			break;
		case 3 : //left
			turn_left();
			break;       
		case 4 : //right
			turn_rigth();
			break;
	}
		
}
