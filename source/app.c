
/*
*------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------
*/
#include "config.h"
#include "board.h"
#include "timer.h"
#include "communication.h"
#include "string.h"
#include "eep.h"


//#define SIMULATION
/*
*------------------------------------------------------------------------------
* Structures
*------------------------------------------------------------------------------
*/																	

typedef struct _APP
{
	UINT8 data[10];  				//array store for scanned card number
	UINT8 inputRecieved;			// flag indicaation for card scanned
	UINT8 red;						// satus of red lamp
	UINT8 blue;						//status of blue lamp
	UINT8 green;					//status of green lamp
	UINT8 yellow;					// status of yellow lamp
	UINT16 redCount; 				//maintain the time for red lamp
}APP;																			



/*
*------------------------------------------------------------------------------
* Variables
*------------------------------------------------------------------------------
*/
#pragma idata APP_DATA
APP app = {0};
#pragma idata


/*------------------------------------------------------------------------------
* Private Functions
*------------------------------------------------------------------------------
*/

 UINT8 rfcards [MAX_CARDS][10] = {
									"6BA1C5",
									"5ADC89",
									"438AC6" };



/*
*------------------------------------------------------------------------------
* void APP-init(void)
*------------------------------------------------------------------------------
*/

void APP_init(void)
{

}




/*
*------------------------------------------------------------------------------
* void APP-task(void)
*------------------------------------------------------------------------------
*/
void APP_task(void)
{
	UINT8 i,j;
	UINT8 lamp = 0xFF;


	if(app.red == TRUE)
	{
		app.redCount++;
		if( app.redCount  >= RED_TIME)
		{
				LAMP_RED 	= FALSE;
				app.red = FALSE; 			
		}
		
	}


	if( app.inputRecieved == TRUE)
	{

		for( i = 0 ; i <  MAX_CARDS ; i++)
		{

			if( strcmp ( app.data , rfcards[i]) == 0)
				lamp = i;
		
		}

		switch(lamp)
		{
			case 0:
				if( app.blue == 0)
				{
					LAMP_BLUE 	= TRUE;
					app.blue = 1;
				}
				else if( app.blue == 1)
				{
					LAMP_BLUE 	= FALSE;
					app.blue = 0;					
				}
			break;
	
			case 1:
				if( app.green == 0)
				{
					LAMP_GREEN 	= TRUE;
					app.green = 1;
				}
				else if( app.green == 1)
				{
					LAMP_GREEN 	= FALSE;
					app.green = 0;					
				}
			
			break;
			case 2: 
				if( app.yellow == 0)
				{
					LAMP_YELLOW = TRUE;
					app.yellow = 1;
				}
				else if( app.yellow == 1)
				{
					LAMP_YELLOW =  FALSE;
					app.yellow = 0;					
				}

			break;

			default:
				LAMP_RED 	= TRUE; 
				app.red  = TRUE ;				//flag for red lamp is on
				app.redCount = 0;
			break;
		
		}

		app.inputRecieved = FALSE;	

	}
		

}


UINT8 APP_comCallBack( far UINT8 *rxPacket, far UINT8* txCode,far UINT8** txPacket)
{

	UINT8 length = 0;
	UINT8 i;
	//copy data rxbuffer to app buffer
	for(i = 0 ; i < 6 ; i++)
	{
		app.data[i] = rxPacket[i];
	}

	app.data[i] = '\0';
	app.inputRecieved = TRUE;

	return length;


}
	
		