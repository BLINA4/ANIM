/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : cube.c
 * PURPOSE     : Animation project.
 *               Cube sub-unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 17.11.2022.
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
  
  MATERIAL *Mtl;
  MATR Transform;     

  /* Some OpenGL variables */ 
  UINT VBO, VAO;
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
  Unit->Transform = MatrIdentity();
  Unit->Mtl = MaterialAdd("CUBE_MATERIAL", "Shader(CUBE_SHADERS),Tex(USEFILES/bricks.png)");
  MaterialApply(Unit->Mtl); 

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

  glGenVertexArrays(1, &(Unit->VAO));
  glGenBuffers(1, &(Unit->VBO));
  glBindVertexArray(Unit->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, Unit->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
 
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
 
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glUseProgram(0);
  // Enable this line for LINE mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
  glDeleteVertexArrays(1, &(Unit->VAO));
  glDeleteBuffers(1, &(Unit->VBO));
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
  INT PrgNo = 0, loc = 0;

  PrgNo = MaterialApply(Unit->Mtl);

  if ((loc = glGetUniformLocation(PrgNo, "model")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &(Unit->Transform));
  
  if ((loc = glGetUniformLocation(PrgNo, "view")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &(Anim->cam.ViewMatr));
  
  if ((loc = glGetUniformLocation(PrgNo, "proj")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &(Anim->cam.ProjMatr));

  glBindVertexArray(Unit->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  glUseProgram(0);
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

