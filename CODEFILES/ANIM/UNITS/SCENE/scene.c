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
  
  Unit->Cubes = malloc(sizeof(UNIT_CUBE *) * COUNT_OF_CUBES);
  for (i = 0; i < COUNT_OF_CUBES; i++)
  {
    Unit->Cubes[i] = UnitCreateCube();
    Unit->Cubes[i]->Init(Unit->Cubes[i], Anim);
  }
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
  INT i;

  Unit->Plane->Close(Unit->Plane, Anim);

  for (i = 0; i < COUNT_OF_CUBES; i++)
    Unit->Cubes[i]->Close(Unit->Cubes[i], Anim);

  free(Unit->Cubes);
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
  INT i;

  Unit->Plane->Response(Unit->Plane, Anim);
  
  for (i = 0; i < COUNT_OF_CUBES; i++)
    Unit->Cubes[i]->Response(Unit->Cubes[i], Anim);
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
  INT i, w, h, width = ceil(sqrt(COUNT_OF_CUBES));

  Unit->Plane->Render(Unit->Plane, Anim);

  for (i = 0, w = 0; w < width; w++)
    for (h = 0; h < width; h++)
    {
      if (i++ == COUNT_OF_CUBES)
        return;

      Unit->Cubes[w * h + h]->Transform = MatrTranslate(VecSet(1.0f * h - width / 2.0f + (width % 2 == 0 ? 0.5f : 0.0f), 0.5f, -5.0f - 1.0f * w));
      Unit->Cubes[w * h + h]->Render(Unit->Cubes[w * h + h], Anim);
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

