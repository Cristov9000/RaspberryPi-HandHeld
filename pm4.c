//*********************************************************
//
//  pm4.c - by Chris Duerden
//	Power Management program for ATTiny85
//	9/9/2015	RevA - Initial Release
//	9/20/2015	RevB - Added sw debounce to while loop
//	9/30/2015	RevC - Fixed issue with power switch being 
//						turned off before full Rpi boot
//	10/20/2015	RevD - Reordered pins to match BoardRevB
//	
//	Function: Monitors power switch, if on, power on power 
//		supply and screen, if off safe power down RPi and
//		then shutdown power supply
//
//*********************************************************

#define F_CPU 1000000	//1MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define rpistate 	PB3
#define rpireset 	PB4
#define pswitch 	PB2
#define pper 		PB0
#define psupply 	PB1

int rpiSD = 0;
int rpiPU = 0;
int i = 0;
int j = 0;
int switchoff = 0;
int debounce = 0;
int timeOUT = 0;

void sleepNOW()   //function to put attiny85 into low power sleep mode      
   {			  
	DDRB = 0b00000010;
	PORTB = 0b00000000;	//set everything as input to save power
		
	cli();
	GIMSK |= (1 << PCIE);	//Set up pin change interrupt to wake on power on
	PCMSK |= (1 << PCINT2);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);  //sleep mode
	sleep_enable();
	sei();
	sleep_cpu();
	
	sleep_disable();  //resume here on wake up
	cli();
	PCMSK &= ~(1 <<PCINT2); 	//turn off interrupt
	sei();		
	}  
	
void wakeUP()
	{		
	DDRB = 0b00010001;		//on wake up set outputs 
	PORTB = 0b00000001;		//and turn on powersupply and screen/amp
	}
	
void shutDOWN()
	{
		while(rpiSD == 0)					//wait for RPi to shutdown properly
		{
			if((PINB & (1 << rpistate)) == 0)	//When this goes low RPi is shutting down
			{
				rpiSD++;
			}
			if(PINB & (1 << pswitch))			//If power switch turns back on turn on screen/amp
			{
				wakeUP();
			}
			else
			{
				PORTB &= ~(1 << pper);				//Immediately kill screen/amp
			}
		}
		for(j=0; j < 75; j++)					//wait 10 seconds for RPi to finish
		{
			_delay_ms(100);
			if (PINB & (1 << pswitch))		//If power switch turns back on turn on screen/amp
			{
				wakeUP();
			}
			else
			{
				PORTB &= ~(1 << pper);				//Immediately kill screen/amp
			}
		}
		if(PINB & (1 << pswitch))			//If power switch is on, reset RPi
		{
			wakeUP();
			PORTB |= (1 << rpireset);
			_delay_ms(10);	
			PORTB &= ~(1 << rpireset);		
		}
		else								// If power switch is off, turn off power supply and sleep
		{
			sleepNOW();
		}
	}	
	
ISR(PCINT0_vect)	//Interrupt service routine
	{
	    wakeUP();	//Wake up on interrupt
	}

//Main
int main(void)
{
	DDRB = 0b00010011;
	PORTB = 0b00000000;
	 
	for(i = 0; i < 6; i++)	//Blink 3X on initial power up as sanity check
	{
		PORTB ^= (1 << pper);
		_delay_ms(100);	
	}
	
	ADCSRA &= ~(1<<ADEN);	//Turn off ADC - not needed - to save power
	
	if((PINB & (1 << pswitch)) == 0)	//What is the state of the power switch when powered on.
	{	
		sleepNOW();
	}
	else								//if on, turn everything on
	{
		wakeUP();
	}
//Loop	
	while(1)
	{
		if((PINB & (1 << pswitch)) == 0)  //Debounce switch flip to off
		{
			if(debounce < 200)
			{
				debounce++;
			}
			if(debounce == 200)
			{
				switchoff = 1;
			}	
		}
		else
		{
			debounce = 0;
		}
	
	
		if(switchoff == 1)		//Keep polling for power switch to turn off
		{	
			PORTB &= ~(1 << pper);				//Immediately kill screen/amp
			rpiSD = 0;							
			if((PINB & (1 << rpistate)) == 0) //  If turned off prior to full RPi boot
			{
				rpiPU = 0;
				timeOUT = 0;
				while(rpiPU == 0)
				{
					timeOUT++;
					_delay_ms(10);
					if(PINB & (1 << rpistate) || timeOUT == 2000)	//When this goes High RPi is powered up or times out
					{
						rpiPU++;
						_delay_ms(1000);
					}
						
					if (PINB & (1 << pswitch))		//If power switch turns back on turn on screen/amp
					{
						wakeUP();
					}
					else
					{
						PORTB &= ~(1 << pper);				//Immediately kill screen/amp
					}	
				}
				if (PINB & (1 << pswitch) == 0)
				{
					shutDOWN();
				}
				else
				{
					wakeUP();
				}
			}
			else
			{
				shutDOWN();
			}
			switchoff = 0;
		}
	}	
	return 0;	
}
