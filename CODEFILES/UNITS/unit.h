/***************************************************************
 * Copyleft 2020
 *   Junior C programmer presents (lol)
 ***************************************************************/

/* FILE NAME   : unit.h
 * PURPOSE     : Animation project.
 *               Header for units handling module.
 * PROGRAMMER  : Andrey Shayda.
 * LAST UPDATE : 22.03.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __unit_h_
#define __unit_h_

#include "../comdef.h"

#define UNIT_BASE_FIELDS                      \ 
  VOID (*Init)( UNIT *Uni, ANIM *Ani );       \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Response)( UNIT * Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  UNIT_BASE_FIELDS;  
};

/* Unit create function
 * ARGUMENTS:
 *   - size of unit:
 *       INT Size;
 * RETURNS: 
 *   (UNIT *) pointer to unit.
 */
UNIT * AnimUnitCreate( INT Size );

#endif /* __unit_h_ */

/* END OF 'unit.h' FILE */

