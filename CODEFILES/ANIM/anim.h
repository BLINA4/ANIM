/***************************************************************
 * Copyleft 2020
 *   Junior C programmer presents (lol)
 ***************************************************************/

/* FILE NAME   : anim.h
 * PURPOSE     : Animation project.
 *               Animation system header file.
 * PROGRAMMER  : Andrey Shayda.
 * LAST UPDATE : 22.03.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __anim_h_
#define __anim_h_

#include "../comdef.h"
#include "../UNITS/unit.h"

#define MAX_UNITS 1024

typedef struct tagANIM
{
  Display *dpy;
  Window win;
  XWindowAttributes gwa;
  UNIT *Units[MAX_UNITS];
  INT NumOfUnits;
} ANIM;

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */

