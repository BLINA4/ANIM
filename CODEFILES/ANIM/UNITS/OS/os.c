/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : os.c
 * PURPOSE     : Animation project.
 *               Operating system unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 02.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __os_c_
#define __os_c_

#include <stdio.h>
#include <math.h>

#include "../unit.h"
#include "../../anim.h"

#endif

typedef struct
{
  UNIT_BASE_FIELDS;
  SHADER shdPrg;
} UNIT_OS;

/* Some OpenGL variables */
INT vertexShader, fragmentShader, shaderProgram;
UINT VBO, VAO, EBO;
TEXTURE *texture;

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_OS *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT_OS *Unit, ANIM *Anim )
{
  sprintf(Unit->shdPrg.Name, "OS_SHADERS");
  Unit->shdPrg.PrgNo = ShaderLoad(Unit->shdPrg.Name); 
  
  printf("%i\n", Unit->shdPrg.PrgNo);
  glUseProgram(Unit->shdPrg.PrgNo);

  FLT vertices[] = 
  {
     // vertice coords    // colours         // texture coords
     1.0f,  1.0f,  0.0f,  1.0f, 0.0f, 1.0f,  1.0f,  0.0f,   // tor-right
     1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  1.0f,  1.0f,   // bottom-right
    -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f,  1.0f,   // bottom-left
    -1.0f,  1.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f    // top-left   
  }; 

  UINT indices[] = 
  {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
 
  texture = TextureAddFromFile("USEFILES/sunix.bmp");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glUseProgram(0);
  // Enable this line for LINE mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_OS *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT_OS *Unit, ANIM *Anim )
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  TextureDelete(texture);
} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_OS *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT_OS *Unit, ANIM *Anim )
{
  if (Anim->Debug)
    ;
} /* End of 'UnitResponse' function */
 
/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT_OS *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT_OS *Unit, ANIM *Anim )
{ 
  INT vertexColorLocation;
 
  glUseProgram(Unit->shdPrg.PrgNo);

  vertexColorLocation = glGetUniformLocation(Unit->shdPrg.PrgNo, "sinColor");
  glUniform3f(
     vertexColorLocation,
     0.7f * cos(Anim->SyncTime * 1.2f) + 0.3f,
     0.5f * sin(Anim->SyncTime + cos(2.3 * Anim->SyncTime)),
     0.63f * sin(cos(Anim->SyncTime * 2.82) + 33) + 0.37f);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  TextureApply(texture, 0);
  glBindVertexArray(VAO);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  
  glUseProgram(0);
} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * UnitCreateOS( VOID )
{
  UNIT_OS *Unit;

  if ((Unit = (UNIT_OS *)AnimUnitCreate(sizeof(UNIT_OS))) == NULL)
    return NULL;

  Unit->Init = (VOID *)UnitInit;
  Unit->Close = (VOID *)UnitClose;
  Unit->Response = (VOID *)UnitResponse;
  Unit->Render = (VOID *)UnitRender;

  return (UNIT *)Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'os.c' FILE */

