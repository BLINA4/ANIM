/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : plane.c
 * PURPOSE     : Animation project.
 *               Plane sub-unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 16.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdio.h>
#include <math.h>

#include "../../../../comdef.h"
#include "../../../anim.h"

typedef struct
{ 
  UNIT_BASE_FIELDS;
  
  MATERIAL *Mtl;

  /* Some OpenGL variables */
  UINT VBO, VAO, EBO;
} UNIT_PLANE;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_PLANE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_PLANE *Unit, ANIM *Anim )
{
  Unit->Mtl = MaterialAdd("PLANE_MATERIAL", "Shader(PLANE_SHADERS),Tex(USEFILES/WoodPlanksWorn33/WoodPlanksWorn33_Flat.jpg)");
  MaterialApply(Unit->Mtl);
 
  FLT vertices[] =
  {
    -1.0f, -1.0f, 0.0f, -100.0f, -100.0f,
    -1.0f,  1.0f, 0.0f, -100.0f,  100.0f,
     1.0f,  1.0f, 0.0f,  100.0f,  100.0f,
     1.0f, -1.0f, 0.0f,  100.0f, -100.0f
  };

  UINT indices[] =
  {
    0, 1, 2,
    2, 3, 0
  };

  glGenVertexArrays(1, &(Unit->VAO));
  glGenBuffers(1, &(Unit->VBO));
  glGenBuffers(1, &(Unit->EBO));
  glBindVertexArray(Unit->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, Unit->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Unit->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glUseProgram(0);
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_PLANE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_PLANE *Unit, ANIM *Anim )
{
  glDeleteVertexArrays(1, &(Unit->VAO));
  glDeleteBuffers(1, &(Unit->VBO));
  glDeleteBuffers(1, &(Unit->EBO));
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_PLANE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_PLANE *Unit, ANIM *Anim )
{

} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_PLANE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_PLANE *Unit, ANIM *Anim )
{
  INT loc, PrgNo;
  MATR Model = MatrMulMatr(MatrScale(VecSet(100, 100, 100)),
                           MatrRotateX(90));

  PrgNo = MaterialApply(Unit->Mtl);
  
  if ((loc = glGetUniformLocation(PrgNo, "model")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &Model);
  if ((loc = glGetUniformLocation(PrgNo, "view")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &(Anim->cam.ViewMatr));
  if ((loc = glGetUniformLocation(PrgNo, "proj")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &(Anim->cam.ProjMatr));

  glBindVertexArray(Unit->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glUseProgram(0);
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreatePlane( VOID )
{
  UNIT_PLANE *Unit;

  if ((Unit = (UNIT_PLANE *)AnimUnitCreate(sizeof(UNIT_PLANE))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'plane.c' FILE */

