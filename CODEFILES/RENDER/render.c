/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
 
/* FILE NAME   : render.c
 * PURPOSE     : Animation project.
 *               Render system code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 26.04.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
VOID      (*glDeleteShader)             ( GLuint );
VOID      (*glGenVertexArrays)          ( GLsizei, GLuint * );
VOID      (*glGenBuffers)               ( GLsizei, GLuint * );
VOID      (*glBindBuffer)               ( GLenum, GLuint );
VOID      (*glBufferData)               ( GLenum, GLsizeiptr, const VOID *, GLenum );
VOID      (*glVertexAttribPointer)      ( GLuint, GLint, GLenum, GLboolean, GLsizei, const VOID * );
VOID      (*glEnableVertexAttribArray)  ( GLuint );
VOID      (*glDeleteVertexArrays)       ( GLsizei, const GLuint * );
VOID      (*glDeleteBuffers)            ( GLsizei, const GLuint * );

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
  glDeleteShader = glXGetProcAddress((const GLubyte *)"glDeleteShader");
  glGenVertexArrays = glXGetProcAddress((const GLubyte *)"glGenVertexArrays");
  glGenBuffers = glXGetProcAddress((const GLubyte *)"glGenBuffers");
  glBindBuffer = glXGetProcAddress((const GLubyte *)"glBindBuffer");
  glBufferData = glXGetProcAddress((const GLubyte *)"glBufferData");
  glVertexAttribPointer = glXGetProcAddress((const GLubyte *)"glVertexAttribPointer");
  glEnableVertexAttribArray = glXGetProcAddress((const GLubyte *)"glEnableVertexAttribArray");
  glDeleteVertexArrays = glXGetProcAddress((const GLubyte *)"glDeleteVertexArrays");
  glDeleteBuffers = glXGetProcAddress((const GLubyte *)"glDeleteBuffers");
} /* End of 'RndInit' function */

/* Render close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndClose( VOID )
{
} /* End of 'RndClose' function */

/* Render start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndStart( VOID )
{
} /* End of 'RndStart' function */

/* Render stop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndEnd( VOID )
{
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
  DBL size = 0.1, rx = size, ry = size;

  if (W > H)
    rx *= (DBL)W / H;
  else
    ry *= (DBL)H / W;

  glViewport(0, 0, W, H);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, size, 100);

  gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
} /* End of 'RndReshape' function */

/* Check pending events function
 * ARGUMENTS: 
 *   - Animation context:
 *       ANIM *Anim;
 * RETURN: None.
 */
VOID RndCheckEvents( ANIM *Anim )
{
  if (XCheckWindowEvent(Anim->dpy, Anim->win, KeyPressMask, &(Anim->xev)))
  {
    char *key_string = XKeysymToString(XkbKeycodeToKeysym(Anim->dpy, Anim->xev.xkey.keycode, 0, 0));

    if (!strncmp(key_string, "Esc", 3))
      Anim->Run = 0;
  }

  if (XCheckWindowEvent(Anim->dpy, Anim->win, ExposureMask, &(Anim->xev)))
  {
    XGetWindowAttributes(Anim->dpy, Anim->win, &(Anim->gwa));
    RndReshape(Anim->gwa.width, Anim->gwa.height);
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
  Anim->SyncTime = (DBL)clock() / CLOCKS_PER_SEC;
} /* End of 'RndTimer' function */

/* END OF 'anim.h' FILE */

