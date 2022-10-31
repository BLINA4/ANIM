/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : anim.h
 * PURPOSE     : Animation project.
 *               Animation system header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 31.10.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __anim_h_
#define __anim_h_

#include "../comdef.h"
#include "./UNITS/unit.h"
#include "../RENDER/render.h"
#include "./TEXTURES/textures.h"
#include "./CONTROLLER/controller.h"

#define MAX_UNITS 4096

typedef struct tagANIM ANIM;
struct tagANIM
{
  GLXContext              glc;                                                              /*  OpenGL context              */
  SDL_Surface             *scr;                                                             /*  SDL screen surface pointer  */
  SDL_Window              *win;                                                             /*  SDL window pointer          */
  Display                 *dpy;                                                             /*  Display pointer             */
  SDL_Renderer            *rnd;                                                             /*  SDL renderer poiner         */
  DWORD                   rndflgs;                                                          /*  Render flags for SDL        */
  SDL_Event               evt;                                                              /*  Current event processing    */
  UNIT                    *Units[MAX_UNITS];                                                /*  Array of units              */
  INT                     NumOfUnits;                                                       /*  Number of loaded units      */
  BOOL                    Run;                                                              /*  Is programm still running   */
  BOOL                    Debug;                                                            /*  Is programm in debug mode   */
  DBL                     StartTime;                                                        /*  Time of startup             */
  DBL                     SyncTime;                                                         /*  Synchronization time        */
  INT                     NumOfTextures;                                                    /*  Number of loaded textures   */
  CONTROLLER              *Controller;                                                      /*  Module controller           */
  GLint                   att[];                                                            /*  Attributes of GL            */  
};

extern ANIM Anim;

/* Main animation loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimRun( VOID );

/* Animation closing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimClose( VOID );

/* Animation initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimInit( VOID );

/* Unit adding function.
 * ARGUMENTS:
 *   - Unit structure pointer:
 *       UNIT *Unit;
 * RESPONSE: None.
 */
VOID AnimUnitAdd( UNIT *Unit );

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */

