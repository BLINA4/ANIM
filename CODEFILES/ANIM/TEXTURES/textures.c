/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : textures.c
 * PURPOSE     : Animation project.
 *               Texture implementation file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdio.h>
#include <string.h>

#include "../IMAGES/images.h"
#include "textures.h"

TEXTURE Textures[MaximumTextures];

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
TEXTURE * TextureAdd( CHAR *Name, TEX_FMT Format, INT W, INT H, VOID *ImageData )
{
  TEXTURE Txt;

  if (Anim.NumOfTextures == MaximumTextures)
    return NULL; 

  /* Allocate texture space */
  glGenTextures(1, &Txt.TexId);
  glBindTexture(GL_TEXTURE_2D, Txt.TexId);

  if (Format != TEXFMT_BGRA8)
    glTexStorage2D(GL_TEXTURE_2D, 1, Format, W, H);

  /* Upload texture */
  if (ImageData != NULL)
  {
    INT sem = GL_RED, typ = GL_UNSIGNED_BYTE;

    switch (Format)
    {
    case TEXFMT_BGRA8:
      sem = GL_BGRA;
      typ = GL_UNSIGNED_BYTE;
      break;
    case TEXFMT_R32F:
      sem = GL_RED;
      typ = GL_FLOAT;
      break;
    case TEXFMT_RGB32F:
      sem = GL_RGB;
      typ = GL_FLOAT;
      break;
    case TEXFMT_RGB8:
      sem = GL_RGB;
      typ = GL_UNSIGNED_BYTE;
      break;
    case TEXFMT_RGBA8:
      sem = GL_RGBA;
      typ = GL_UNSIGNED_BYTE;
      break;
    case TEXFMT_RGBA32F:
      sem = GL_RGBA;
      typ = GL_FLOAT;
      break;
    case TEXFMT_RGBA32UI:
      sem = GL_RGBA;
      typ = GL_UNSIGNED_INT;
      break;
    }
 
    if (Format == TEXFMT_BGRA8)
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, sem, typ, ImageData);
    else
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, sem, typ, ImageData);
  }
  if (Format == TEXFMT_BGRA8)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  else
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(Txt.Name, Name, 255);
  Txt.W = W;
  Txt.H = H;
  Txt.IsCubeMap = 0;

  glBindTexture(GL_TEXTURE_2D, 0);

  Textures[Anim.NumOfTextures] = Txt;
  return &Textures[Anim.NumOfTextures++];
} /* End of 'TextureAdd' function */

/* Add texture image from file function.
 * ARGUMENTS:
 *   - texture image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (TEXTURE *) Texture pointer.
 */
TEXTURE * TextureAddFromFile( CHAR *FileName )
{
  TEXTURE *tex = NULL;
  IMAGE Im;

  ImageLoad(&Im, FileName);

  tex = TextureAdd(FileName, TEXFMT_RGBA8, Im.W, Im.H, Im.Pixels);

  ImageFree(&Im);

  return tex;
} /* End of 'TextureAddFromFile' function */

/* Texture parameters apply.
 * ARGUMENTS:
 *   - texture pointer:
 *       TEXTURE *T;
 *   - number of texture:
 *       INT Num;
 * RETURNS: None.
 */
VOID TextureApply( TEXTURE *T, INT Num )
{
  glActiveTexture(GL_TEXTURE0 + Num);
  glBindTexture(T->IsCubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, T->TexId);
} /* End of 'TextureApply' function */

/* Texture strategy delete function.
 * ARGUMENTS: 
 *   - Texture pointer
 *       TEXTURE *Txt;
 * RETURNS: None.
  */
VOID TextureDelete( TEXTURE *Txt )
{
  if (Txt == NULL)
    return;

  glDeleteTextures(1, &Txt->TexId);
} /* End of 'TextureDelete' function */

/* END OF 'textures.c' FILE */

