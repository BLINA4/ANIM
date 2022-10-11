/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : controller.c
 * PURPOSE     : Animation project.
 *               Controller subsystem.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.10.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdlib.h>
#include "controller.h"

/* Controller initialization function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   - Ready-for-use controller structure pointer
 *      (CONTROLLER *)
 */
CONTROLLER * ControllerInit( VOID )
{
  INT key_count = sizeof(KEY);  
  CONTROLLER *cnt;

  cnt = malloc(sizeof(CONTROLLER));
  cnt->keys = malloc(sizeof(BOOL) * key_count); 

  return cnt;
} /* End of 'ControllerInit' function */ 

/* Controller deinitialization function.
 * ARGUMENTS: 
 *   - controller structure pointer
 *      CONTROLLER *cnt
 * RETURNS: None.
 */
VOID ControllerDestroy( CONTROLLER *cnt )
{
  free(cnt->keys);
  free(cnt);
} /* End of 'ControllerDestroy' function */

/* End of 'controller.c' file */

