/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : cube.c
 * PURPOSE     : Animation project.
 *               Cube sub-unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 21.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __cube_c_
#define __cube_c_

#include <stdio.h>
#include <math.h>

#include "../../unit.h"
#include "../../../anim.h"

#endif /* __cude_c_ */

typedef struct
{
  UNIT_BASE_FIELDS;
  
  PRIM *Pr;
  MATR Transform;
} UNIT_CUBE;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_CUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_CUBE *Unit, ANIM *Anim )
{
  FLT vertices[] = 
  {
     // vertice coords     // texture coords
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  }; 

  Unit->Pr = PrimCreate(PRIM_TRIMESH, "f3f2", vertices, 36, NULL, 0);
  Unit->Pr->Mtl = MaterialAdd("CUBE_MATERIAL", "Shader(CUBE_SHADERS),Tex(USEFILES/bricks.png)"); 
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_CUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_CUBE *Unit, ANIM *Anim )
{
  PrimFree(Unit->Pr);
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_CUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_CUBE *Unit, ANIM *Anim )
{
  if (Anim->Controller->keys[TAB] == TRUE)
  {
    /*
    if (!strcmp(Unit->texture->Name, "USEFILES/grass.png"))
    {
      TextureDelete(Unit->texture);
      Unit->texture = TextureAddFromFile("USEFILES/bricks.png");
      return;
    }
  
    if (!strcmp(Unit->texture->Name, "USEFILES/bricks.png"))
    {
      TextureDelete(Unit->texture);
      Unit->texture = TextureAddFromFile("USEFILES/grass.png");
      return;
    }
    */
    ;
  }
} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_CUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_CUBE *Unit, ANIM *Anim )
{
  PrimDraw(Unit->Pr, Unit->Transform);
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateCube( VOID )
{
  UNIT_CUBE *Unit;

  if ((Unit = (UNIT_CUBE *)AnimUnitCreate(sizeof(UNIT_CUBE))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'cube.c' FILE */

