
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

 UINT8 rfcards [MAX_CARDS][10] = {
									"6DE587",
									"2790B8",
									"153738",
									"199385"};



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

			if( strcmp ( app.data , rfcards[i]) == 0)
				app.lamp = i+1;
		
		}

		switch(app.lamp)
		{
			case 1:
				LAMP_GREEN 	= TRUE;
				LAMP_YELLOW = FALSE;
				LAMP_RED 	= FALSE; 
				LAMP_BLUE 	= FALSE;
			
			break;
			case 2:
				LAMP_GREEN 	= FALSE; 
				LAMP_YELLOW = TRUE;
				LAMP_RED 	= FALSE; 
				LAMP_BLUE 	= FALSE;
			break;
			case 3:
				LAMP_GREEN 	= FALSE;
				LAMP_YELLOW = FALSE;
				LAMP_RED 	= TRUE; 
				LAMP_BLUE 	= FALSE;
			break;
			case 4:
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

	UINT8 length = 0;
	//copy data rxbuffer to app buffer
	strcpy(app.data,rxPacket);

	app.inputRecieved = TRUE;

	return length;


}
	
		

		
	

