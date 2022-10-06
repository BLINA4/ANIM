/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : os.c
 * PURPOSE     : Animation project.
 *               Operating system unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 03.02.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <math.h>

#ifndef _os_c_
#define _os_c_

#include "../unit.h"
#include "../../anim.h"

#endif

typedef struct
{
  UNIT_BASE_FIELDS;
} UNIT_OS;

/* Source code of example vertex shader */
const char *vertexShaderSource =   "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}\0";

/* Source code of example fragment shader */
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

/* Some OpenGL variables */
int vertexShader, fragmentShader, shaderProgram;
unsigned int VBO, VAO;

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
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = 
  {
    -1.0f, -1.0f, 0.0f, // left verticle
     1.0f, -1.0f, 0.0f, // right verticle
     0.0f,  1.0f, 0.0f  // top verticle
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

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
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
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

