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
  cnt->keys_prev = malloc(sizeof(BOOL) * key_count);
  cnt->keys_hold = malloc(sizeof(BOOL) * key_count);

  for (INT i = 0; i < key_count; i++)
    cnt->keys[i] = FALSE;
  
  for (INT i = 0; i < key_count; i++)
     cnt->keys_prev[i] = FALSE;

  for (INT i = 0; i < key_count; i++)
      cnt->keys_hold[i] = FALSE;

  cnt->TimeOfLastCleanup = 0;

  return cnt;
} /* End of 'ControllerInit' function */ 

/* Controller hold key function.
 * ARGUMENTS:
 *   - controller structure pointer
 *      CONTROLLER *cnt
 *   - index of the key
 *      INT i
 * RETURNS:
 *   - True if the key is already held, False if added to hold_list:
 *       (BOOL)
 */
BOOL ControllerKeyHold( CONTROLLER *cnt, INT i )
{
  if (cnt->keys_hold[i])
    return TRUE;
  
  cnt->keys_hold[i] = TRUE;
  
  return FALSE; 
} /* End of 'ControllerKeyHold' function */ 

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
  //printf("%s\n", key_str);

  if (!strncmp(key_str, "Esc", 3))
    cnt->keys[ESCAPE] = TRUE;
  if (!strncmp(key_str, "Tab", 3))
    cnt->keys[TAB] = TRUE;

  if (!strncmp(key_str, "a", 1))
    cnt->keys[A] = TRUE;
  if (!strncmp(key_str, "b", 1))
    cnt->keys[B] = TRUE;
  if (!strncmp(key_str, "c", 1))
    cnt->keys[C] = TRUE;
  if (!strncmp(key_str, "d", 1))
    cnt->keys[D] = TRUE;
  if (!strncmp(key_str, "e", 1))
    cnt->keys[E] = TRUE;
  if (!strncmp(key_str, "f", 1))
    cnt->keys[F] = TRUE;
  if (!strncmp(key_str, "g", 1))
    cnt->keys[G] = TRUE;
  if (!strncmp(key_str, "h", 1))
    cnt->keys[H] = TRUE;
  if (!strncmp(key_str, "i", 1))
    cnt->keys[I] = TRUE;
  if (!strncmp(key_str, "j", 1))
    cnt->keys[J] = TRUE;
  if (!strncmp(key_str, "k", 1))
    cnt->keys[K] = TRUE;
  if (!strncmp(key_str, "l", 1))
    cnt->keys[L] = TRUE;
  if (!strncmp(key_str, "m", 1))
    cnt->keys[M] = TRUE;
  if (!strncmp(key_str, "n", 1))
    cnt->keys[N] = TRUE;
  if (!strncmp(key_str, "o", 1))
    cnt->keys[O] = TRUE;
  if (!strncmp(key_str, "p", 1))
    cnt->keys[P] = TRUE;
  if (!strncmp(key_str, "q", 1))
    cnt->keys[Q] = TRUE;
  if (!strncmp(key_str, "r", 1))
    cnt->keys[R] = TRUE;
  if (!strncmp(key_str, "s", 1))
    cnt->keys[S] = TRUE;
  if (!strncmp(key_str, "t", 1))
    cnt->keys[T] = TRUE;
  if (!strncmp(key_str, "u", 1))
    cnt->keys[U] = TRUE;
  if (!strncmp(key_str, "v", 1))
    cnt->keys[V] = TRUE;
  if (!strncmp(key_str, "w", 1))
    cnt->keys[W] = TRUE;
  if (!strncmp(key_str, "x", 1))
    cnt->keys[X] = TRUE;
  if (!strncmp(key_str, "y", 1))
    cnt->keys[Y] = TRUE;
  if (!strncmp(key_str, "z", 1))
    cnt->keys[Z] = TRUE;
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

  if (!strncmp(key_str, "a", 1))
    cnt->keys[A] = FALSE;
  if (!strncmp(key_str, "b", 1))
    cnt->keys[B] = FALSE;
  if (!strncmp(key_str, "c", 1))
    cnt->keys[C] = FALSE;
  if (!strncmp(key_str, "d", 1))
    cnt->keys[D] = FALSE;
  if (!strncmp(key_str, "e", 1))
    cnt->keys[E] = FALSE;
  if (!strncmp(key_str, "f", 1))
    cnt->keys[F] = FALSE;
  if (!strncmp(key_str, "g", 1))
    cnt->keys[G] = FALSE;
  if (!strncmp(key_str, "h", 1))
    cnt->keys[H] = FALSE;
  if (!strncmp(key_str, "i", 1))
    cnt->keys[I] = FALSE;
  if (!strncmp(key_str, "j", 1))
    cnt->keys[J] = FALSE;
  if (!strncmp(key_str, "k", 1))
    cnt->keys[K] = FALSE;
  if (!strncmp(key_str, "l", 1))
    cnt->keys[L] = FALSE;
  if (!strncmp(key_str, "m", 1))
    cnt->keys[M] = FALSE;
  if (!strncmp(key_str, "n", 1))
    cnt->keys[N] = FALSE;
  if (!strncmp(key_str, "o", 1))
    cnt->keys[O] = FALSE;
  if (!strncmp(key_str, "p", 1))
    cnt->keys[P] = FALSE;
  if (!strncmp(key_str, "q", 1))
    cnt->keys[Q] = FALSE;
  if (!strncmp(key_str, "r", 1))
    cnt->keys[R] = FALSE;
  if (!strncmp(key_str, "s", 1))
    cnt->keys[S] = FALSE;
  if (!strncmp(key_str, "t", 1))
    cnt->keys[T] = FALSE;
  if (!strncmp(key_str, "u", 1))
    cnt->keys[U] = FALSE;
  if (!strncmp(key_str, "v", 1))
    cnt->keys[V] = FALSE;
  if (!strncmp(key_str, "w", 1))
    cnt->keys[W] = FALSE;
  if (!strncmp(key_str, "x", 1))
    cnt->keys[X] = FALSE;
  if (!strncmp(key_str, "y", 1))
    cnt->keys[Y] = FALSE;
  if (!strncmp(key_str, "z", 1))
    cnt->keys[Z] = FALSE;
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
  DBL TimeSinceLastCleanup = Anim.SyncTime - cnt->TimeOfLastCleanup;
 
  //printf("Time since %lf!\n", TimeSinceLastCleanup);
  if (TimeSinceLastCleanup <= 0.1)
    return;

  for (INT i = 0; i < key_count; i++)
  {   
    if (cnt->keys[i] == TRUE && cnt->keys_prev[i] == TRUE) 
    {
      if (!ControllerKeyHold(cnt, i))
        printf("Key is held down!\n");
    }
    else
    {
      //printf("Key is unheld!\n");  
      ;//ControllerKeyUnhold(cnt, i);  
    }

    cnt->keys_prev[i] = cnt->keys[i];
    cnt->keys[i] = FALSE;
  }

  cnt->TimeOfLastCleanup = Anim.SyncTime;
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
  free(cnt->keys_prev);
  free(cnt->keys_hold);
  free(cnt);
} /* End of 'ControllerDestroy' function */

/* End of 'controller.c' file */

