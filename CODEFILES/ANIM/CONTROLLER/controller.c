/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : controller.c
 * PURPOSE     : Animation project.
 *               Controller subsystem.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../anim.h"
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
  cnt->keys_hold = malloc(sizeof(BOOL) * key_count);

  for (INT i = 0; i < key_count; i++)
    cnt->keys[i] = FALSE;
  
  for (INT i = 0; i < key_count; i++)
    cnt->keys_hold[i] = FALSE;

  cnt->TimeOfLastCleanup = 0;

  return cnt;
} /* End of 'ControllerInit' function */ 

/* Pressed key controller handle function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 *   - pressed key mask:
 *       SDL_Keycode key
 * RETURNS: None.
 */
VOID ControllerKeyPress( CONTROLLER *cnt, SDL_Keycode key )
{
  switch (key)
  {
  case SDLK_ESCAPE:
    cnt->keys[ESCAPE] = TRUE;
    break;
  case SDLK_TAB:
    cnt->keys[TAB] = TRUE;
    break;
  }
} /* End of 'ControllerKeyPress' function */

/* Released key controller handle function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 *   - released key mask:
 *       SDL_Keycode key
 * RETURNS: None.
 */
VOID ControllerKeyRelease( CONTROLLER *cnt, SDL_Keycode key )
{ 
  switch (key)
  {
  case SDLK_ESCAPE:
    cnt->keys[ESCAPE]      = FALSE;
    cnt->keys_hold[ESCAPE] = FALSE;
    break;
  case SDLK_TAB:
    cnt->keys[TAB]      = FALSE;
    cnt->keys_hold[TAB] = FALSE;
    break;
  }
} /* End of 'ControllerKeyRelease' function */

/* Cleaning up all keys state function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 * RETURNS: None.
 */
VOID ControllerCleanup( CONTROLLER *cnt )
{
  INT i, NumOfKeys = NUM_OF_KEYS;

  for (i = 0; i < NumOfKeys; i++)
  {
    if (cnt->keys[i])
      cnt->keys_hold[i] = TRUE;
    cnt->keys[i] = FALSE;
  }
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
  free(cnt->keys_hold);
  free(cnt);
} /* End of 'ControllerDestroy' function */

/* End of 'controller.c' file */

