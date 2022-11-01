/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : shader.c
 * PURPOSE     : Animation project.
 *               Shaders subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 02.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include "../../comdef.h"
#include "shader.h"

/* Read text from .glsl file function
 * ARGUMENTS:
 *   - name of file to read:
 *       CHAR *FileName;
 * RETURNS: 
 *   (CHAR *) read text content.
 */
CHAR * ReadShaderFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *text;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;
 
  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((text = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(text, 0, flen + 1);

  /* Read text */
  fseek(F, 0, SEEK_SET);
  fread(text, 1, flen, F);

  fclose(F);
  return text; 
} /* End of 'ReadShaderFile' function */

/* END OF 'shader.c' FILE */

