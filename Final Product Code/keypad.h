
#ifndef KEYPAD_H_
#define KEYPAD_H_
	
#include <avr/io.h>
#include <util/delay.h>


#define KEY_PRT 	PORTD
#define KEY_DDR		DDRD
#define KEY_PIN		PIND

inline int Keypad_read()
{
	unsigned char keypad[4][3] = {	{1,2,3},
	{4,5,6},
	{7,8,9},
	{20,0,10} };

	unsigned char colloc, rowloc;

	while(1)
	{
		KEY_DDR = 0xF0;           /* set port direction as input-output */
		KEY_PRT = 0xF7;

		do
		{
			KEY_PRT &= 0x07;      /* mask PORT for column read only */
			asm("NOP");
			colloc = (KEY_PIN & 0x07); /* read status of column */
		}while(colloc != 0x07);
		
		do
		{
			do
			{
				_delay_ms(20);             /* 20ms key debounce time */
				colloc = (KEY_PIN & 0x07); /* read status of column */
				}while(colloc == 0x07);        /* check for any key press */
				
				_delay_ms (40);	            /* 20 ms key debounce time */
				colloc = (KEY_PIN & 0x07);
			}while(colloc == 0x07);

			/* now check for rows */
			KEY_PRT = 0xE7;            /* check for pressed key in 1st row */
			asm("NOP");
			colloc = (KEY_PIN & 0x07);
			if(colloc != 0x07)
			{
				rowloc = 0;
				break;
			}

			KEY_PRT = 0xD7;		/* check for pressed key in 2nd row */
			asm("NOP");
			colloc = (KEY_PIN & 0x07);
			if(colloc != 0x07)
			{
				rowloc = 1;
				break;
			}
			
			KEY_PRT = 0xB7;		/* check for pressed key in 3rd row */
			asm("NOP");
			colloc = (KEY_PIN & 0x07);
			if(colloc != 0x07)
			{
				rowloc = 2;
				break;
			}

			KEY_PRT = 0x77;		/* check for pressed key in 4th row */
			asm("NOP");
			colloc = (KEY_PIN & 0x07);
			if(colloc != 0x07)
			{
				rowloc = 3;
				break;
			}
		}

		if(colloc == 0x06)
		return(keypad[rowloc][0]);
		else if(colloc == 0x05)
		return(keypad[rowloc][1]);
		else if(colloc == 0x03)
		return(keypad[rowloc][2]);
		else
		return(keypad[rowloc][3]);
	}


inline int menu_read(){
	PORTB |= 1<<7;
	if (PINB & 1){return 1;} 
	else {return 0;}	
}

#endif /* KEYPAD_H_ */