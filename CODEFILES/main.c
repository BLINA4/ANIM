/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : main.c
 * PURPOSE     : Animation project.
 *               Main file of project.
 * PROGRAMMER  : BLIN4
 * LAST UPDATE : 03.02.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "comdef.h"
#include "ANIM/UNITS/unit.h"
#include "ANIM/anim.h"

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID main( VOID )
{
  AnimInit();
  
  AnimUnitAdd(UnitCreateQuad());
  //AnimUnitAdd(UnitCreateOS());
  
  AnimRun();
  AnimClose();
} /* End of 'main' function */

/* END OF 'main.c' FILE */

