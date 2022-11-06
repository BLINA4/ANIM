/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : 3dcube.c
 * PURPOSE     : Animation project.
 *               3d cube unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 06.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __3dcube_c_
#define __3dcube_c_

#include <stdio.h>
#include <math.h>

#include "../unit.h"
#include "../../anim.h"

#endif /* __3dcude_c_ */

typedef struct
{
  UNIT_BASE_FIELDS;
  SHADER shdPrg;
  
  /* Some OpenGL variables */
  UINT VBO, VAO, EBO;
  TEXTURE *texture;
} UNIT_3DCUBE;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_3DCUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_3DCUBE *Unit, ANIM *Anim )
{
  sprintf(Unit->shdPrg.Name, "3DCUBE_SHADER");
  Unit->shdPrg.PrgNo = ShaderLoad(Unit->shdPrg.Name); 
  
  //printf("%i\n", Unit->shdPrg.PrgNo);
  glUseProgram(Unit->shdPrg.PrgNo);

  FLT vertices[] = 
  {
     // vertice coords    // colours         // texture coords
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  //1.0f, 0.0f,   
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  //1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  //0.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  //0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
  }; 

  UINT indices[] = 
  {
    0, 1, 2, // first triangle
    2, 0, 3, // second triangle
    4, 5, 6, // third triangle
    6, 4, 7, // forth triangle
    0, 4, 7, // fifth triangle
    7, 3, 0, // sixth triangle
    1, 2, 6, // seventh triangle
    6, 5, 1, // eigth triangle
    0, 4, 5, // ninth triangle
    5, 1, 0, // tength triangle
    2, 3, 6, // eleventh triangle
    6, 7, 3  // twelth triangle
  };

  glGenVertexArrays(1, &(Unit->VAO));
  glGenBuffers(1, &(Unit->VBO));
  glGenBuffers(1, &(Unit->EBO));
  glBindVertexArray(Unit->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, Unit->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Unit->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
 
  //Unit->texture = TextureAddFromFile("USEFILES/sunix.bmp");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glUseProgram(0);
  // Enable this line for LINE mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_3DCUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_3DCUBE *Unit, ANIM *Anim )
{
  glDeleteVertexArrays(1, &(Unit->VAO));
  glDeleteBuffers(1, &(Unit->VBO));
  glDeleteBuffers(1, &(Unit->EBO));
  //TextureDelete(Unit->texture);
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_3DCUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_3DCUBE *Unit, ANIM *Anim )
{
  if (Anim->Debug)
    printf("=== Test debug output of 3dcube unit ===\n");
} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_3DCUBE *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_3DCUBE *Unit, ANIM *Anim )
{ 
  INT loc;
  MATR Model =
    MatrMulMatr4(MatrRotateY(30 * Anim->SyncTime),
                 MatrScale(VecSet(0.3f, 0.3f, 0.3f)),
                 MatrRotateX(-60 * cos(0.8 * Anim->SyncTime + 17.5)),
                 MatrTranslate(VecSet(0.0f, 0.0f, 1.0f)));
  MATR N = MatrTranspose(MatrInverse(Model));

  glUseProgram(Unit->shdPrg.PrgNo);


  if ((loc = glGetUniformLocation(Unit->shdPrg.PrgNo, "sinColor")) != -1)
  {  
    glUniform3f(
      loc,
      0.7f * cos(Anim->SyncTime * 1.2f) + 0.3f,
      0.5f * sin(Anim->SyncTime + cos(2.3 * Anim->SyncTime)),
      0.63f * sin(cos(Anim->SyncTime * 2.82) + 33) + 0.37f);
  }
  
  if ((loc = glGetUniformLocation(Unit->shdPrg.PrgNo, "model")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &Model);
  
  if ((loc = glGetUniformLocation(Unit->shdPrg.PrgNo, "view")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, Anim->cam.ViewMatr.M[0]);
  
  if ((loc = glGetUniformLocation(Unit->shdPrg.PrgNo, "proj")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &N);

  glBindVertexArray(Unit->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  //TextureApply(Unit->texture, 0);
  glBindVertexArray(Unit->VAO);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  
  glUseProgram(0);
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreate3DCUBE( VOID )
{
  UNIT_3DCUBE *Unit;

  if ((Unit = (UNIT_3DCUBE *)AnimUnitCreate(sizeof(UNIT_3DCUBE))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF '3dcube.c' FILE */

