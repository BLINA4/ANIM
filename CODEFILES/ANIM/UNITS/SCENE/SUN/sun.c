/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : sun.c
 * PURPOSE     : Animation project.
 *               Sun sub-unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 25.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __sun_c_
#define __sun_c_

#include <stdio.h>
#include <math.h>

#include "../../unit.h"
#include "../../../anim.h"

#endif /* __sun_c_ */

typedef struct
{
  UNIT_BASE_FIELDS;
  
  PRIM *Pr;
  MATR Transform;
} UNIT_SUN;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SUN *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_SUN *Unit, ANIM *Anim )
{
  FLT vertices[] = 
  {
     // vertice coords   
     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
        
     -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,

     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,

     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f
  }; 

  Unit->Pr = PrimCreate(PRIM_TRIMESH, "f3", vertices, 36, NULL, 0);
  Unit->Pr->Mtl = MaterialAdd("SUN MATERIAL", "Shader(SUN_SHADERS)"); 
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SUN *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_SUN *Unit, ANIM *Anim )
{
  PrimFree(Unit->Pr);
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SUN *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_SUN *Unit, ANIM *Anim )
{
  if (Anim->Controller->keys[TAB] == TRUE)
    ; 
} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_SUN *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_SUN *Unit, ANIM *Anim )
{
  PrimDraw(Unit->Pr, Unit->Transform);
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateSun( VOID )
{
  UNIT_SUN *Unit;

  if ((Unit = (UNIT_SUN *)AnimUnitCreate(sizeof(UNIT_SUN))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'sun.c' FILE */

