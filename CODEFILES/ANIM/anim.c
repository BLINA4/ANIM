/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : anim.c
 * PURPOSE     : Animation project.
 *               Animation system implementation file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 01.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "anim.h"

/* Animation context structure */
ANIM Anim;

/* Animation initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimInit( VOID )
{
  Anim.StartTime = (DBL)clock() / CLOCKS_PER_SEC;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    return;

  if ((Anim.win = SDL_CreateWindow("Hello, SDL 2!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL)) == NULL)
    return;

  Anim.glc = SDL_GL_CreateContext(Anim.win);
  Anim.Controller = ControllerInit();
  Anim.Debug = FALSE;
  Anim.Run = TRUE;
  RndInit();
} /* End of 'AnimInit' function */

/* Main animation loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimRun( VOID )
{
  INT i = 0;

  while (Anim.Run)
  {
    RndCheckEvents(&Anim);
    RndTimer(&Anim);

    if (Anim.Controller->keys[ESCAPE] == TRUE)
      Anim.Run = FALSE;  
    if (Anim.Controller->keys[TAB] == TRUE)
      Anim.Debug = !Anim.Debug;

    for (i = 0; i < Anim.NumOfUnits; i++)
      Anim.Units[i]->Response(Anim.Units[i], &Anim);
    RndStart();
    for (i = 0; i < Anim.NumOfUnits; i++)
      Anim.Units[i]->Render(Anim.Units[i], &Anim);
    RndEnd();
  }
} /* End of 'AnimRun' function */

/* Animation closing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimClose( VOID )
{
  INT i;

  for (i = 0; i < Anim.NumOfUnits; i++)
    Anim.Units[i]->Close(Anim.Units[i], &Anim);

  RndClose();
  ControllerDestroy(Anim.Controller); 
  SDL_DestroyWindow(Anim.win);
  SDL_Quit();
} /* End of 'AnimClose' function */

/* Unit adding function.
 * ARGUMENTS:
 *   - Unit structure pointer:
 *       UNIT *Unit;
 * RESPONSE: None.
 */
VOID AnimUnitAdd( UNIT *Unit )
{
  if (Anim.NumOfUnits < MAX_UNITS)
    Anim.Units[Anim.NumOfUnits++] = Unit, Unit->Init(Unit, &Anim);
} /* End of 'AnimUnitAdd' function */

/* END OF 'anim.c' FILE */

