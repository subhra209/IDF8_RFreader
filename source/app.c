
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
	UINT8 data[10];
	UINT8 lamp;
	UINT8 inputRecieved;
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

UINT8 rfcards [MAX_CARDS][6] = {
								{0x36,0x44,0x45,0x35,0x38,0x37},
								{0x31,0x35,0x32,0x37,0x33,0x44},
								{0x32,0x37,0x39,0x30,0x42,0x38},
								{0x31,0x39,0x39,0x33,0x38,0x35} }; //"6DE587","199385","2790B8","153738"};
   
  



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
	UINT8 temp = 1;
	
	if( app.inputRecieved == TRUE)
	{

		for( i = 0 ; i <  MAX_CARDS ; i++)
		{

			temp = 0;
			for(j = 0 ; j < 6 ; j++)
			{
				if(app.data[j]  != rfcards[i][j])
				 temp = 1;
			}
			if(temp == 0)
			{
				app.lamp = i ;

			}

		
		}

		switch(app.lamp)
		{
			case 0:
				LAMP_GREEN 	= TRUE;
				LAMP_YELLOW = FALSE;
				LAMP_RED 	= FALSE; 
				LAMP_BLUE 	= FALSE;
			
			break;
			case 1:
				LAMP_GREEN 	= FALSE; 
				LAMP_YELLOW = TRUE;
				LAMP_RED 	= FALSE; 
				LAMP_BLUE 	= FALSE;
			break;
			case 2:
				LAMP_GREEN 	= FALSE;
				LAMP_YELLOW = FALSE;
				LAMP_RED 	= TRUE; 
				LAMP_BLUE 	= FALSE;
			break;
			case 3:
				LAMP_GREEN 	= FALSE;
				LAMP_YELLOW = FALSE;
				LAMP_RED 	= FALSE; 
				LAMP_BLUE 	= TRUE;
			break;
	
			default:
			break;
		
		}

		app.inputRecieved = FALSE;	

	}
		



}


UINT8 APP_comCallBack( far UINT8 *rxPacket, far UINT8* txCode,far UINT8** txPacket)
{

	UINT8 i;
	UINT8 length = 0;

	for( i = 0 ; i < 7 ; i++ )
	{
		app.data[i] = rxPacket[i];
	}
//	app.data[i] = '\0';



	app.inputRecieved = TRUE;

	return length;


}
	
		

		
	

