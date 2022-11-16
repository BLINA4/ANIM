/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : scene.h
 * PURPOSE     : Animation project.
 *               Main scene unit header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 16.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __scene_h_
#define __scene_h_

#include "../unit.h"
#include "../../anim.h"

typedef struct
{
  UNIT_BASE_FIELDS;

  // Sub-units
  UNIT *Plane;
  UNIT *Cube;
} UNIT_SCENE;

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateCube( VOID );

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreatePlane( VOID );

#endif /* __scene_h_ */

/* END OF 'scene.h' file */

