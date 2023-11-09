
/*
 * main.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Khaled Waled
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LCD_interfac.h"

#include <util/delay.h>

void Init_Buttons(void);
u8 Player_One (void);
u8 Player_Two (void);
#define L_UP 		0
#define L_DOWN 		1
#define R_UP 		2
#define R_DOWN 		3

u8 Flag=1;
u8 Player1=1;
u8 Player2=1;

u8 Score1=0;
u8 Score2=0;
u8 i=1;
u8 j=1;

u8 customChar[] = {0x04,0x0A,0x04,0x04,0x15,0x04,0x0A,0x0A};	// Player arr
u8 customChar_2[] = {0x00,0x00,0x0E,0x11,0x11,0x11,0x0E,0x00};  // Ball arr
int main( void )
{
	u8 Player_1 ;
	u8 Player_2 ;


	Init_Buttons();
	HLCD_voidLcdIntiate();

	HLCD_voidLcdDraw(customChar, 0, Player1, 0);  	// player_1

	HLCD_voidLcdDraw(customChar, 0, Player2, 19); 	// player_2

	HLCD_voidLcdWriteString("P1:0", 4, 0);		// score player_1
	HLCD_voidLcdWriteString("P2:0", 4, 16);		// score player_2
	while( 1 )
	{
		HLCD_voidLcdDraw(customChar, 0, Player1, 0);  	// player_1

		HLCD_voidLcdDraw(customChar, 0, Player2, 19); 	// player_2

		Player_1 = Player_One();
		Player_2 = Player_Two();

		if (Flag)
		{
			if(Player_1==L_DOWN)
			{
				j+=1;
				if(j>=3)
				{
					j=3;
				}
				else{}
			}
			else if(Player_1==L_UP)
			{
				j -= 1;
				if(j<=1)
				{
					j=1;
				}
				else{}
			}
			else{}
			if(Player_2==R_DOWN)
			{

				HLCD_voidLcdWriteString(" ", Player2, 19);

				Player2 += 1;
				if(Player2>=3)
				{
					Player2=3;
				}
				else{}
				HLCD_voidLcdDraw(customChar, 0, Player2, 19); 	// player_2
			}
			else if(Player_2==R_UP)
			{

				HLCD_voidLcdWriteString(" ", Player2, 19);

				Player2-=1;
				if(Player2<=1)
				{
					Player2=1;
				}
				else{}
				HLCD_voidLcdDraw(customChar, 0, Player2, 19); 	// player_2
			}
			else{}
			i+=1;
			if (i==18)
			{
				Flag=0;
				if(j!=Player2)
				{
					Score1++;
					HLCD_voidLcdWriteIntiger(Score1,4,3);
				}
				else{}
			}
			else{}
		}
		else
		{
			if(Player_2==R_DOWN)
			{
				j+=1;
				if(j>=3)
				{
					j=3;
				}
				else{}
			}
			else if(Player_2==R_UP)
			{
				j-=1;
				if(j<=1)
				{
					j=1;
				}
				else{}
			}
			else{}
			if(Player_1==L_DOWN)
			{
				HLCD_voidLcdWriteString(" ", Player1, 0);
				Player1+=1;
				if(Player1>=3)
				{
					Player1=3;
				}
				else{}
				HLCD_voidLcdDraw(customChar, 0, Player1, 0); 	// player_1
			}
			else if(Player_1==L_UP)
			{
				HLCD_voidLcdWriteString(" ", Player1, 0);
				Player1--;
				if(Player1==0)
				{
					Player1=1;
				}
				else{}
				HLCD_voidLcdDraw(customChar, 0, Player1, 0); 	// player_1
			}
			else{}
			i-=1;
			if(i==1)
			{
				Flag=1;
				if(j!=Player1)
				{
					Score2++;
					HLCD_voidLcdWriteIntiger(Score2,4,19);
				}
				else{}

			}
			else{}
		}
		HLCD_voidLcdDraw(customChar_2, 1,j,i);
		_delay_ms(200);
		HLCD_voidLcdWriteString(" ",j,i);
	}
	return 0;
}
void Init_Buttons(void)
{
	DIO_voidSetPinDirection(PORTD_ID, PIN7, PIN_INPUT);
	DIO_voidSetPinValue(PORTD_ID, PIN7, PIN_HIGH);			// Pull up button
	DIO_voidSetPinDirection(PORTD_ID, PIN6, PIN_INPUT);
	DIO_voidSetPinValue(PORTD_ID, PIN6, PIN_HIGH);			// Pull up button
	DIO_voidSetPinDirection(PORTD_ID, PIN5, PIN_INPUT);
	DIO_voidSetPinValue(PORTD_ID, PIN5, PIN_HIGH);			// Pull up button
	DIO_voidSetPinDirection(PORTD_ID, PIN3, PIN_INPUT);
	DIO_voidSetPinValue(PORTD_ID, PIN3, PIN_HIGH);			// Pull up button
}

u8 Player_One (void)
{
	u8 Ball_1 ;
	if(DIO_u8GetPinValue(PORTD_ID,PIN7) == 0)
	{
		_delay_ms(1);
		Ball_1 = L_DOWN ;

	}
	else{}
	if(DIO_u8GetPinValue(PORTD_ID,PIN6) == 0)
	{
		_delay_ms(1);
		Ball_1 = L_UP ;
	}
	else{}
	return Ball_1;
}

u8 Player_Two (void)
{
	u8 Ball_2 ;
	if(DIO_u8GetPinValue(PORTD_ID,PIN5) == 0)
	{
		_delay_ms(1);
		Ball_2 = R_DOWN ;
	}
	else{}
	if(DIO_u8GetPinValue(PORTD_ID,PIN3) == 0)
	{
		_delay_ms(1);
		Ball_2 = R_UP ;
	}
	else{}
	return Ball_2;
}

