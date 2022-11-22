/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : controller.c
 * PURPOSE     : Animation project.
 *               Controller subsystem.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 22.11.2022.
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
  case SDLK_a:
    cnt->keys[A] = TRUE;
    break;
  case SDLK_b:
    cnt->keys[B] = TRUE;
    break;
  case SDLK_c:
    cnt->keys[C] = TRUE;
    break;
  case SDLK_d:
    cnt->keys[D] = TRUE;
    break;
  case SDLK_e:
    cnt->keys[E] = TRUE;
    break;
  case SDLK_f:
    cnt->keys[F] = TRUE;
    break;
  case SDLK_g:
    cnt->keys[G] = TRUE;
    break;
  case SDLK_h:
    cnt->keys[H] = TRUE;
    break;
  case SDLK_i:
    cnt->keys[I] = TRUE;
    break;
  case SDLK_j:
    cnt->keys[J] = TRUE;
    break;
  case SDLK_k:
    cnt->keys[K] = TRUE;
    break;
  case SDLK_l:
    cnt->keys[L] = TRUE;
    break;
  case SDLK_m:
    cnt->keys[M] = TRUE;
    break;
  case SDLK_n:
    cnt->keys[N] = TRUE;
    break;
  case SDLK_o:
    cnt->keys[O] = TRUE;
    break;
  case SDLK_p:
    cnt->keys[P] = TRUE;
    break;
  case SDLK_q:
    cnt->keys[Q] = TRUE;
    break;
  case SDLK_r:
    cnt->keys[R] = TRUE;
    break;
  case SDLK_s:
    cnt->keys[S] = TRUE;
    break;
  case SDLK_t:
    cnt->keys[T] = TRUE;
    break;
  case SDLK_u:
    cnt->keys[U] = TRUE;
    break;
  case SDLK_v:
    cnt->keys[V] = TRUE;
    break;
  case SDLK_w:
    cnt->keys[W] = TRUE;
    break;
  case SDLK_x:
    cnt->keys[X] = TRUE;
    break;
  case SDLK_y:
    cnt->keys[Y] = TRUE;
    break;
  case SDLK_z:
    cnt->keys[Z] = TRUE;
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
  case SDLK_a:
    cnt->keys[A]      = FALSE;
    cnt->keys_hold[A] = FALSE;
    break;
  case SDLK_b:
    cnt->keys[B]      = FALSE;
    cnt->keys_hold[B] = FALSE;
    break;
  case SDLK_c:
    cnt->keys[C]      = FALSE;
    cnt->keys_hold[C] = FALSE;
    break;
  case SDLK_d:
    cnt->keys[D]      = FALSE;
    cnt->keys_hold[D] = FALSE;
    break;
  case SDLK_e:
    cnt->keys[E]      = FALSE;
    cnt->keys_hold[E] = FALSE;
    break;
  case SDLK_f:
    cnt->keys[F]      = FALSE;
    cnt->keys_hold[F] = FALSE;
    break;
  case SDLK_g:
    cnt->keys[G]      = FALSE;
    cnt->keys_hold[G] = FALSE;
    break;
  case SDLK_h:
    cnt->keys[H]      = FALSE;
    cnt->keys_hold[H] = FALSE;
     break;
  case SDLK_i:
    cnt->keys[I]      = FALSE;
    cnt->keys_hold[I] = FALSE;
    break;
  case SDLK_j:
    cnt->keys[J]      = FALSE;
    cnt->keys_hold[J] = FALSE;
    break;
  case SDLK_k:
    cnt->keys[K]      = FALSE;
    cnt->keys_hold[K] = FALSE;
    break;
  case SDLK_l:
    cnt->keys[L]      = FALSE;
    cnt->keys_hold[L] = FALSE;
    break;
  case SDLK_m:
    cnt->keys[M]      = FALSE;
    cnt->keys_hold[M] = FALSE;
    break;
  case SDLK_n:
    cnt->keys[N]      = FALSE;
    cnt->keys_hold[N] = FALSE;
    break;
  case SDLK_o:
    cnt->keys[O]      = FALSE;
    cnt->keys_hold[O] = FALSE;
    break;
  case SDLK_p:
    cnt->keys[P]      = FALSE;
    cnt->keys_hold[P] = FALSE;
    break;
  case SDLK_q:
    cnt->keys[Q]      = FALSE;
    cnt->keys_hold[Q] = FALSE;
    break;
  case SDLK_r:
    cnt->keys[R]      = FALSE;
    cnt->keys_hold[R] = FALSE;
    break;
  case SDLK_s:
    cnt->keys[S]      = FALSE;
    cnt->keys_hold[S] = FALSE;
    break;
  case SDLK_t:
    cnt->keys[T]      = FALSE;
    cnt->keys_hold[T] = FALSE;
    break;
  case SDLK_u:
    cnt->keys[U]      = FALSE;
    cnt->keys_hold[U] = FALSE;
    break;
  case SDLK_v:
    cnt->keys[V]      = FALSE;
    cnt->keys_hold[V] = FALSE;
    break;
  case SDLK_w:
    cnt->keys[W]      = FALSE;
    cnt->keys_hold[W] = FALSE;
    break;
  case SDLK_x:
    cnt->keys[X]      = FALSE;
    cnt->keys_hold[X] = FALSE;
    break;
  case SDLK_y:
    cnt->keys[Y]      = FALSE;
    cnt->keys_hold[Y] = FALSE;
    break;
  case SDLK_z:
    cnt->keys[Z]      = FALSE;
    cnt->keys_hold[Z] = FALSE;
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

