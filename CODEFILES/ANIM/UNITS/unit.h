/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : unit.h
 * PURPOSE     : Animation project.
 *               Units system header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.03.2021.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __unit_h_
#define __unit_h_

#include "../../comdef.h"
typedef struct tagANIM ANIM;

#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Unit, ANIM *Anim );     \
  VOID (*Close)( UNIT *Unit, ANIM *Anim );    \
  VOID (*Response)( UNIT *Unit, ANIM *Anim ); \
  VOID (*Render)( UNIT *Unit, ANIM *Anim )

/* Structure containing main unit functions appliable for all units */
typedef struct tagUNIT UNIT;
struct tagUNIT
{
  UNIT_BASE_FIELDS;
};

/* Unit creation function.
 * ARGUMENTS: 
 *   - structure size in bytes:
 *       INT Size
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * AnimUnitCreate( INT Size );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateQuad( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateOS( VOID );

#endif /* __unit_h_ */

/* END OF 'unit.h' FILE */

