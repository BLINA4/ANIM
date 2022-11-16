/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : scene.c
 * PURPOSE     : Animation project.
 *               Main scene unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 16.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __scene_c_
#define __scene_c_

#include <stdio.h>
#include <math.h>

#include "scene.h"

#endif /* __scene_c_ */

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SCENE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_SCENE *Unit, ANIM *Anim )
{
  Unit->Plane = UnitCreatePlane();
  Unit->Plane->Init(Unit->Plane, Anim);
  Unit->Cube = UnitCreateCube();
  Unit->Cube->Init(Unit->Cube, Anim);
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SCENE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_SCENE *Unit, ANIM *Anim )
{
  Unit->Plane->Close(Unit->Plane, Anim);
  Unit->Cube->Close(Unit->Cube, Anim);
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SCENE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_SCENE *Unit, ANIM *Anim )
{
  Unit->Plane->Response(Unit->Plane, Anim);
  Unit->Cube->Response(Unit->Cube, Anim);
} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SCENE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_SCENE *Unit, ANIM *Anim )
{
  Unit->Plane->Render(Unit->Plane, Anim);
  Unit->Cube->Render(Unit->Cube, Anim);
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateScene( VOID )
{
  UNIT_SCENE *Unit;

  if ((Unit = (UNIT_SCENE *)AnimUnitCreate(sizeof(UNIT_SCENE))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'scene.c' FILE */

