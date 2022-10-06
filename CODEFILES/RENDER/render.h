/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : render.h
 * PURPOSE     : Animation project.
 *               Render system header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 04.02.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __render_h_
#define __render_h_

#include "../comdef.h"
#include "../ANIM/anim.h"

extern GLuint    (*glCreateShader)             ( GLenum );
extern VOID      (*glShaderSource)             ( GLuint, GLsizei, const GLchar **, const GLint * );
extern VOID      (*glCompileShader)            ( GLuint );
extern VOID      (*glUseProgram)               ( GLuint );
extern GLuint    (*glCreateProgram)            ( VOID );
extern VOID      (*glLinkProgram)              ( GLuint );
extern VOID      (*glAttachShader)             ( GLuint, GLuint );
extern VOID      (*glBindVertexArray)          ( GLuint );
extern VOID      (*glDeleteShader)             ( GLuint );
extern VOID      (*glGenVertexArrays)          ( GLsizei, GLuint * );
extern VOID      (*glGenBuffers)               ( GLsizei, GLuint * );
extern VOID      (*glBindBuffer)               ( GLenum, GLuint );
extern VOID      (*glBufferData)               ( GLenum, GLsizeiptr, const VOID *, GLenum );
extern VOID      (*glVertexAttribPointer)      ( GLuint, GLint, GLenum, GLboolean, GLsizei, const VOID * );
extern VOID      (*glEnableVertexAttribArray)  ( GLuint );
extern VOID      (*glDeleteVertexArrays)       ( GLsizei, const GLuint * );
extern VOID      (*glDeleteBuffers)            ( GLsizei, const GLuint * );
extern VOID  	 (*glGetShaderiv)	           ( GLuint, GLenum, GLint * );
extern VOID 	 (*glGetShaderInfoLog)	       ( GLuint, GLsizei, GLsizei *, GLchar * );
extern VOID      (*glGenerateMipmap)           ( GLuint );
extern VOID      (*glTexStorage2D)             ( GLenum, GLsizei, GLenum, GLsizei, GLsizei );

/* Render initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndInit( VOID );

/* Render close function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndClose( VOID );

/* Render start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndStart( VOID );

/* Render stop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID RndEnd( VOID );

/* Reshape handle function
 * ARGUMENTS:
 *   - Window width and height:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID RndReshape( INT W, INT H );

/* Check pending events function
 * ARGUMENTS: 
 *   - Animation context:
 *       ANIM *Anim;
 * RETURN: None.
 */
VOID RndCheckEvents( ANIM *Anim );

/* Timer dummy function (refactor later)
 * ARGUMENTS: 
 *   - Animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
VOID RndTimer( ANIM *Anim );

#endif /* __render_h_ */

/* END OF 'render.h' FILE */
