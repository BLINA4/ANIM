/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : render.c
 * PURPOSE     : Animation project.
 *               Render system code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 17.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../comdef.h"
#include "render.h"

GLuint    (*glCreateShader)             ( GLenum );
VOID      (*glShaderSource)             ( GLuint, GLsizei, const GLchar **, const GLint * );
VOID      (*glCompileShader)            ( GLuint );
VOID      (*glUseProgram)               ( GLuint );
GLuint    (*glCreateProgram)            ( VOID );
VOID      (*glLinkProgram)              ( GLuint );
VOID      (*glAttachShader)             ( GLuint, GLuint );
VOID      (*glBindVertexArray)          ( GLuint );
VOID      (*glDetachShader)             ( GLuint, GLuint );
VOID      (*glDeleteShader)             ( GLuint );
VOID      (*glDeleteProgram)            ( GLuint );
VOID      (*glGenVertexArrays)          ( GLsizei, GLuint * );
VOID      (*glGenBuffers)               ( GLsizei, GLuint * );
VOID      (*glBindBuffer)               ( GLenum, GLuint );
VOID      (*glBufferData)               ( GLenum, GLsizeiptr, const VOID *, GLenum );
VOID      (*glVertexAttribPointer)      ( GLuint, GLint, GLenum, GLboolean, GLsizei, const VOID * );
VOID      (*glEnableVertexAttribArray)  ( GLuint );
VOID      (*glDeleteVertexArrays)       ( GLsizei, const GLuint * );
VOID      (*glDeleteBuffers)            ( GLsizei, const GLuint * );
VOID      (*glGetAttachedShaders)       ( GLuint, GLsizei, GLsizei *, GLuint * );
VOID      (*glGetShaderiv)		        ( GLuint, GLenum, GLint * );
VOID      (*glGetProgramiv)             ( GLuint, GLenum, GLint * );
VOID 	  (*glGetShaderInfoLog)		    ( GLuint, GLsizei, GLsizei *, GLchar * );
VOID      (*glGetProgramInfoLog)        ( GLuint, GLsizei, GLsizei *, GLchar * );
VOID      (*glPatchParameteri)          ( GLenum, GLint );
VOID      (*glGenerateMipmap)           ( GLenum );
VOID      (*glTexStorage2D)             ( GLenum, GLsizei, GLenum, GLsizei, GLsizei );
GLint     (*glGetUniformLocation)       ( GLuint, const GLchar * );
VOID      (*glUniform1i)                ( GLint, GLint );
VOID      (*glUniform1f)                ( GLint, GLfloat );
VOID      (*glUniform3f)                ( GLint, GLfloat, GLfloat, GLfloat ); 
VOID      (*glUniform3fv)               ( GLint, GLsizei, const GLfloat * );
VOID      (*glUniformMatrix4fv)         ( GLint, GLsizei, GLboolean, const GLfloat * );

/* Render initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndInit( VOID )
{
  glCreateShader = glXGetProcAddress((const GLubyte *)"glCreateShader");
  glShaderSource = glXGetProcAddress((const GLubyte *)"glShaderSource");
  glCompileShader = glXGetProcAddress((const GLubyte *)"glCompileShader");
  glUseProgram = glXGetProcAddress((const GLubyte *)"glUseProgram");
  glCreateProgram = glXGetProcAddress((const GLubyte *)"glCreateProgram");  
  glLinkProgram = glXGetProcAddress((const GLubyte *)"glLinkProgram");
  glAttachShader = glXGetProcAddress((const GLubyte *)"glAttachShader");
  glBindVertexArray = glXGetProcAddress((const GLubyte *)"glBindVertexArray");
  glDetachShader = glXGetProcAddress((const GLubyte *)"glDetachShader");
  glDeleteShader = glXGetProcAddress((const GLubyte *)"glDeleteShader");
  glDeleteProgram = glXGetProcAddress((const GLubyte *)"glDeleteProgram");
  glGenVertexArrays = glXGetProcAddress((const GLubyte *)"glGenVertexArrays");
  glGenBuffers = glXGetProcAddress((const GLubyte *)"glGenBuffers");
  glBindBuffer = glXGetProcAddress((const GLubyte *)"glBindBuffer");
  glBufferData = glXGetProcAddress((const GLubyte *)"glBufferData");
  glVertexAttribPointer = glXGetProcAddress((const GLubyte *)"glVertexAttribPointer");
  glEnableVertexAttribArray = glXGetProcAddress((const GLubyte *)"glEnableVertexAttribArray");
  glDeleteVertexArrays = glXGetProcAddress((const GLubyte *)"glDeleteVertexArrays");
  glDeleteBuffers = glXGetProcAddress((const GLubyte *)"glDeleteBuffers");
  glGetAttachedShaders = glXGetProcAddress((const GLubyte *)"glGetAttachedShaders");
  glGetShaderiv = glXGetProcAddress((const GLubyte *)"glGetShaderiv");
  glGetProgramiv = glXGetProcAddress((const GLubyte *)"glGetProgramiv");
  glGetShaderInfoLog = glXGetProcAddress((const GLubyte *)"glGetShaderInfoLog");
  glGetProgramInfoLog = glXGetProcAddress((const GLubyte *)"glGetProgramInfoLog");
  glPatchParameteri = glXGetProcAddress((const GLubyte *)"glPatchParameteri");
  glGenerateMipmap = glXGetProcAddress((const GLubyte *)"glGenerateMipmap");
  glTexStorage2D = glXGetProcAddress((const GLubyte *)"glTexStorage2D");
  glGetUniformLocation = glXGetProcAddress((const GLubyte *)"glGetUniformLocation");
  glUniform1i = glXGetProcAddress((const GLubyte *)"glUniform1i");
  glUniform1f = glXGetProcAddress((const GLubyte *)"glUniform1f");
  glUniform3f = glXGetProcAddress((const GLubyte *)"glUniform3f");
  glUniform3fv = glXGetProcAddress((const GLubyte *)"glUniform3fv");
  glUniformMatrix4fv = glXGetProcAddress((const GLubyte *)"glUniformMatrix4fv");

  glEnable(GL_DEPTH_TEST);
} /* End of 'RndInit' function */

/* Render close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndClose( VOID )
{
  MaterialsDestructor();
} /* End of 'RndClose' function */

/* Render start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndStart( VOID )
{
  glClearColor(0.3, 0.5, 0.7, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
} /* End of 'RndStart' function */

/* Render stop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndEnd( VOID )
{
  SDL_GL_SwapWindow(Anim.win);
  glFinish();
} /* End of 'RndEnd' function */

/* Render copy active frame function.
 * ARGUMENTS:
 *   - direct context:
 *       Window win;
 * RETURNS: None.
 */
VOID RndCopyFrame( Window win )
{

} /* End of 'RndCopyFrame' function */

/* Reshape handle function
 * ARGUMENTS:
 *   - Window width and height:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID RndReshape( INT W, INT H )
{
  glViewport(0, 0, W, H);
  CamProjSet(&(Anim.cam), W, H);
} /* End of 'RndReshape' function */

/* Check pending events function
 * ARGUMENTS: 
 *   - Animation context:
 *       ANIM *Anim;
 * RETURN: None.
 */
VOID RndCheckEvents( ANIM *Anim )
{
  while (SDL_PollEvent(&Anim->evt) != 0)
  {
    if (Anim->evt.type == SDL_WINDOWEVENT)
    {
      SDL_GetWindowSize(Anim->win, &(Anim->W), &(Anim->H));

      RndReshape(Anim->W, Anim->H);
    }

    if (Anim->evt.type == SDL_QUIT)
      Anim->Run = FALSE;

    if (Anim->evt.type == SDL_KEYDOWN)
      ControllerKeyPress(Anim->Controller, Anim->evt.key.keysym.sym);
  
    if (Anim->evt.type == SDL_KEYUP)
      ControllerKeyRelease(Anim->Controller, Anim->evt.key.keysym.sym);
  }
} /* End of 'RndCheckEvents' function */

/* Timer dummy function (refactor later)
 * ARGUMENTS: 
 *   - Animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
VOID RndTimer( ANIM *Anim )
{
  Anim->SyncTime = (DBL)clock() / CLOCKS_PER_SEC - Anim->StartTime;
} /* End of 'RndTimer' function */

/* END OF 'anim.h' FILE */

