/* FILE NAME   : shader.h
 * PURPOSE     : Animation project.
 *               Shaders subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 04.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __shader_h_
#define __shader_h_

#include "../../comdef.h"
#include "../render.h"

#define NAME_LENGTH 256

typedef struct tagSHADER
{
  CHAR Name[NAME_LENGTH]; /* Shader path prefix */
  UINT PrgNo;             /* Shader programm ID */
} SHADER;

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT ShaderLoad( CHAR *FileNamePrefix );

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */
