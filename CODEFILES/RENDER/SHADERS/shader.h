/* FILE NAME   : shader.h
 * PURPOSE     : Animation project.
 *               Shaders subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 14.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __shader_h_
#define __shader_h_

#include "../../comdef.h"

typedef struct tagSHADER
{
  CHAR Name[NAME_LENGTH]; /* Shader path prefix */
  UINT PrgNo;             /* Shader programm ID */
} SHADER;

/* Add shader program from file function.
 * ARGUMENTS:
 *   - shader files prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS: 
 *  (SHADER *) pointer to added shader.
 */
SHADER * ShaderAdd( CHAR *FileNamePrefix );

/* Correct shader number function.
 * ARGUMENTS:
 *   - shader pointer:
 *       SHADER *Shd;
 * RETURNS: 
 *   (UINT) Shader program Id.
 */
UINT ShaderApply( SHADER *Shd );

/* Shader program deletion function.
 * ARGUMENTS:
 *   - shader program pointer:
 *       SHADER *Shd;
 * RETURNS: None.
 */
VOID ShaderDelete( SHADER *Shd );

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */
