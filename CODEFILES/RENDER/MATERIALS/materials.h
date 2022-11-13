/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : materials.h
 * PURPOSE     : Animation project.
 *               Materials subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 13.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __materials_h_
#define __materials_h_

#include "../../comdef.h"
#include "../render.h"

/* Length of material's name */
#define MATERIAL_NAME_LENGTH 256

/* Number of pointers to textures in material */
#define MATERIAL_TEXTURE_COUNT 8

struct tagMATERIAL
{
  CHAR Name[MATERIAL_NAME_LENGTH];
  VEC Ka, Kd, Ks;
  FLT Ph;
  FLT Trans;
  TEXTURE *Tex[MATERIAL_TEXTURE_COUNT];
  SHADER *Shd;
};

#endif /* __materials_h_ */

/* END OF 'materials.h' FILE */

