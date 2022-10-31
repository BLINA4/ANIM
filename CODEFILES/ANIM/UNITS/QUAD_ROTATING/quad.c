/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : quad.c
 * PURPOSE     : Animation project.
 *               Rotating quad unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.03.2021.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <math.h>

#ifndef __quad_c_
#define __quad_c_

#include <stdio.h>
#include "../unit.h"
#include "../../anim.h"

#endif

typedef struct
{
  UNIT_BASE_FIELDS;
  DBL RotatingSpeed;
  DBL Angle;
} UNIT_QUAD;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_QUAD *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_QUAD *Unit, ANIM *Anim )
{
  Unit->Angle = 0;
  Unit->RotatingSpeed = 90;
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_QUAD *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_QUAD *Unit, ANIM *Anim )
{
  
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_QUAD *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_QUAD *Unit, ANIM *Anim )
{
  Unit->Angle = Unit->RotatingSpeed * 2 * sin(Anim->SyncTime) - 45;
} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_QUAD *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_QUAD *Unit, ANIM *Anim )
{
  /*
   * if (Anim->Debug)
   *   printf("=== DEBUG === Rendering of QUAD unit ===\n");  
   */

  glPushMatrix();
  glColor3d(1, 0, 0);  
  glRotated(Unit->Angle, 0, 0, 1); 
  glTranslated(1, 1, 0);
  glRectd(0, 0, 1, 1);
  glPopMatrix();
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateQuad( VOID )
{
  UNIT_QUAD *Unit;

  if ((Unit = (UNIT_QUAD *)AnimUnitCreate(sizeof(UNIT_QUAD))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'quad.c' FILE */

