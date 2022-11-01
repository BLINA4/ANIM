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
 
#include "comdef.h"
#include "ANIM/UNITS/unit.h"
#include "ANIM/anim.h"

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
INT main( VOID )
{
  AnimInit();
  
  //AnimUnitAdd(UnitCreateQuad());
  AnimUnitAdd(UnitCreateOS());
  
  AnimRun();
  AnimClose();

  return 0;
} /* End of 'main' function */

/* END OF 'main.c' FILE */

