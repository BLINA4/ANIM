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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"

/* Controller initialization function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   - Ready-for-use controller structure pointer
 *      (CONTROLLER *)
 */
CONTROLLER * ControllerInit( VOID )
{
  INT key_count = NUM_OF_KEYS;  
  CONTROLLER *cnt;

  cnt = malloc(sizeof(CONTROLLER));
  cnt->keys = malloc(sizeof(BOOL) * key_count); 
  for (INT i = 0; i < key_count; i++)
    cnt->keys[i] = FALSE;

  return cnt;
} /* End of 'ControllerInit' function */ 

/* Pressed key controller handle function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 *   - string of pressed key:
 *       CHAR *key_str
 * RETURNS: None.
 */
VOID ControllerKeyPress( CONTROLLER *cnt, CHAR *key_str )
{
  if (!strncmp(key_str, "Esc", 3))
    cnt->keys[ESCAPE] = TRUE;
  if (!strncmp(key_str, "Tab", 3))
    cnt->keys[TAB] = TRUE; 
} /* End of 'ControllerKeyPress' function */

/* Released key controller handle function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 *   - string of released key:
 *       CHAR *key_str
 * RETURNS: None.
 */
VOID ControllerKeyRelease( CONTROLLER *cnt, CHAR *key_str )
{ 
  if (!strncmp(key_str, "Esc", 3))
    cnt->keys[ESCAPE] = FALSE;
  if (!strncmp(key_str, "Tab", 3))
    cnt->keys[TAB] = FALSE;
} /* End of 'ControllerKeyRelease' function */

/* Cleaning up all keys state function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 * RETURNS: None.
 */
VOID ControllerCleanup( CONTROLLER *cnt )
{
  INT key_count = NUM_OF_KEYS;

  for (INT i = 0; i < key_count; i++)
    cnt->keys[i] = FALSE;
} /* End of 'ControllerCleanup' function */

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

