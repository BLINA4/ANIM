/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : textures.h
 * PURPOSE     : Animation project.
 *               Textures header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 13.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __textures_h_
#define __textures_h_

#include "../../comdef.h"

/* Length of texture name */
#define TEXTURE_NAME_LENGTH 256

/* Maximum amount of textures */
#define MaximumTextures 4096

/* Textures formats enum */
typedef enum
{
  TEXFMT_RGBA8 = GL_RGBA8,
  TEXFMT_RGB8 = GL_RGB8,
  TEXFMT_RGB32F = GL_RGB32F,
  TEXFMT_RGBA32F = GL_RGBA32F,
  TEXFMT_R32F = GL_R32F,
  TEXFMT_RGBA32UI = GL_RGBA32UI,
  TEXFMT_DEPTH24 = GL_DEPTH_COMPONENT24,
  TEXFMT_BGRA8 = GL_BGRA
} TEX_FMT;
 
/* Texture structure */
typedef struct
{
  CHAR Name[TEXTURE_NAME_LENGTH]; /* Image file name */
  INT W, H;                       /* Texture size in pixels */
  BOOL IsCubeMap;                 /* Cube map texture flag */
  UINT TexId;                     /* OpenGL texture Id */
} TEXTURE;

/* Texture add function.
 * ARGUMENTS: 
 *   - texture name:
 *       CHAR *Name;
 *   - texture format type:
 *       TEX_FMT Format;
 *   - texture image size:
 *       INT W, H;
 *   - texture image pixel color data (DWORD colors):
 *       VOID *ImageData;
 * RETURNS: 
 *   (TEXTURE *) Texture pointer.
 */
TEXTURE * TextureAdd( CHAR *Name, TEX_FMT Format, INT W, INT H, VOID *ImageData );

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (TEXTURE *) Texture pointer.
 */
TEXTURE * TextureAddFromFile( CHAR *FileName );

/* Texture parameters apply.
 * ARGUMENTS:
 *   - texture pointer:
 *       TEXTURE *T;
 *   - number of texture:
 *       INT Num;
 * RETURNS: None.
 */
VOID TextureApply( TEXTURE *T, INT Num );

/* Texture strategy delete function.
 * ARGUMENTS: 
 *   - Texture pointer
 *       TEXTURE *Txt;
 * RETURNS: None.
 */
VOID TextureDelete( TEXTURE *Txt );

#endif /* __textures_h_ */

/* END OF 'textures.h' FILE */

