/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    /* LED initialization*/
    LATA = 0x80;
    
    /* Timer0 control register initialization to turn timer on, asynch mode, 16 bit
     * Fosc/4, 1:x prescaler, 1:1 postscaler */
    T0CON0 = 0x90;
    T0CON1 = 0x54;
    

} /* end UserAppInitialize() */

/*--------------------------------------------------------------------
@fn void TimeXus(INPUT_PARAMETER_)

@bried
Sets Timer0 to count u16Microseconds_

Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535

Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
 
*/
void TimeXus(u16 u16Count)
{
    /* Disable the timer during config */
    T0CON0 = T0CON0 & 0x7F;
    
    /* Preload TMR0H and TMR0L based on u16TimeXus */
    u16 u16TimeLeft = 0xFFFF - u16Count;
    TMR0H = u16TimeLeft >> 8;
    TMR0L = u16TimeLeft & 0x0F;
    //PIR3 = PIR3 & 0x7F;
            
    /* Clear TMR0IF and enable Timer 0 */
    PIR3 = PIR3 & 0x7F;
    T0CON0 = T0CON0 + 0x80;        
} /* end TimeXus () */
  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    //static u8 u8counter = 0x80; //counter starts at 0 for all 6 pins used, keeps RA7 on 
    //if(u8counter <= 0xBF)
    //{
    //    LATA = u8counter;       //turns pins on based on value of u8counter
    //    //__delay_ms(250);        //delay for 250 milliseconds
    //    u8counter += 0x01;      //update counter
    //}
    //else
    //{
    //   u8counter = 0x80;        //ensure u8counter goes back to 0x80 at the end of the function
    //}
    static u16 u16counter = 0x0000;
    u16counter++;
    if(u16counter == 0x01F4)
    {
        RA0^1;
        u16counter = 0x0000;
    }
    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
