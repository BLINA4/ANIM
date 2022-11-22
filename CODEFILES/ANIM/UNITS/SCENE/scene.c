/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : scene.c
 * PURPOSE     : Animation project.
 *               Main scene unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 21.11.2022.
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
  INT i;

  Unit->Plane = UnitCreatePlane();
  Unit->Plane->Init(Unit->Plane, Anim);
  
  Unit->BricksCube = UnitCreateCube();
  Unit->BricksCube->Init(Unit->BricksCube, Anim);
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
  Unit->BricksCube->Close(Unit->BricksCube, Anim);
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
  if (Anim->Controller->keys_hold[W] || Anim->Controller->keys[W])
    CamSet(&(Anim->cam),
           VecAddVec(VecMulNum(CamDir(&(Anim->cam)),  MOVEMENT_SPEED), Anim->cam.Loc),
           VecAddVec(VecMulNum(CamDir(&(Anim->cam)),  MOVEMENT_SPEED), Anim->cam.At),
           CamUp(&(Anim->cam)));
  if (Anim->Controller->keys_hold[S] || Anim->Controller->keys[S])
    CamSet(&(Anim->cam),
           VecAddVec(VecMulNum(CamDir(&(Anim->cam)), -MOVEMENT_SPEED), Anim->cam.Loc),
           VecAddVec(VecMulNum(CamDir(&(Anim->cam)), -MOVEMENT_SPEED), Anim->cam.At),
           CamUp(&(Anim->cam)));
  if (Anim->Controller->keys_hold[A] || Anim->Controller->keys[A])
    CamSet(&(Anim->cam),
           VecAddVec(VecMulNum(CamRight(&(Anim->cam)), -MOVEMENT_SPEED), Anim->cam.Loc),
           VecAddVec(VecMulNum(CamRight(&(Anim->cam)), -MOVEMENT_SPEED), Anim->cam.At),
           CamUp(&(Anim->cam)));
  if (Anim->Controller->keys_hold[D] || Anim->Controller->keys[D])
    CamSet(&(Anim->cam),
           VecAddVec(VecMulNum(CamRight(&(Anim->cam)),  MOVEMENT_SPEED), Anim->cam.Loc),
           VecAddVec(VecMulNum(CamRight(&(Anim->cam)),  MOVEMENT_SPEED), Anim->cam.At),
           CamUp(&(Anim->cam)));

  Unit->Plane->Response(Unit->Plane, Anim);
  Unit->BricksCube->Response(Unit->BricksCube, Anim);
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
  INT i, w, h, width = 4;

  //Unit->Plane->Render(Unit->Plane, Anim);

  for (i = 0, w = 0; w < width; w++)
    for (h = 0; h < width; h++)
    {
      Unit->BricksCube->Transform = MatrTranslate(VecSet(1.0f * h - width / 2.0f + 0.5f, 0.5f, -5.0f - 1.0f * w));
      Unit->BricksCube->Render(Unit->BricksCube, Anim);
    }
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

