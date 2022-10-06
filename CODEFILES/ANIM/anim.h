/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : anim.h
 * PURPOSE     : Animation project.
 *               Animation system header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 22.03.2020.
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

#define MAX_UNITS 4096

typedef struct tagANIM ANIM;
struct tagANIM
{
  Window                  root;                                                             /*  Root pointer to window      */
  XVisualInfo             *vi;                                                              /*  Visual info of XServer      */
  Colormap                cmap;                                                             /*  Colormap attribute          */
  XSetWindowAttributes    swa;                                                              /*  Set main window attributes  */
  Window                  win;                                                              /*  Window code                 */
  GLXContext              glc;                                                              /*  OpenGL context              */
  XWindowAttributes       gwa;                                                              /*  Total attributes of window  */
  XEvent                  xev;                                                              /*  Event structure             */
  Display *dpy;
  UNIT *Units[MAX_UNITS];
  INT NumOfUnits;
  BOOL Run;         
  DBL SyncTime;
  INT                     NumOfTextures;                                                    /*  Number of loaded textures   */
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
