/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : os.c
 * PURPOSE     : Animation project.
 *               Operating system unit file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 08.02.2022.
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
} UNIT_OS;

/* Source code of example vertex shader */
const char *vertexShaderSource =   "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "layout (location = 1) in vec3 aColor;\n"
                                   "layout (location = 2) in vec2 aTexCoord;\n"
                                   "out vec3 ourColor;\n"
                                   "out vec2 texCoord;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "   ourColor = aColor;\n"
                                   "   texCoord = aTexCoord;\n"
                                   "}\0";

/* Source code of example fragment shader */
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "in vec2 texCoord;\n"
                                   "uniform sampler2D ourTexture;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = texture(ourTexture, texCoord);\n" //" * vec4(ourColor, 1.0f);\n"
                                   "}\n\0";

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
  INT success;
  CHAR infoLog[512];

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog); 
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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
  // Mouse action response
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

  TextureApply(texture, 0);
  glBindVertexArray(VAO);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

