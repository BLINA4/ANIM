/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : images.c
 * PURPOSE     : Animation project.
 *               Images implementation file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 08.02.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "images.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* Image create functions.
 * ARGUMENTS:
 *   - image to be created:
 *       IMAGE *Im;
 *   - image size:
 *       INT W, H;
 * RETURNS: None.
 */
BOOL ImageCreate( IMAGE *Im, INT W, INT H )
{
  INT i;

  memset(Im, 0, sizeof(IMAGE));
  if ((Im->Pixels = malloc(W * H * sizeof(DWORD) + sizeof(DWORD *) * H)) == NULL)
    return 0;
  memset(Im->Pixels, 0, W * H * sizeof(DWORD) + sizeof(DWORD *) * H);
  Im->Rows = (DWORD **)(Im->Pixels + W * H);
  Im->RowsC = (BYTE (**)[4])Im->Rows;

  /* Setup row pointers */
  for (i = 0; i < H; i++)
    Im->Rows[i] = Im->Pixels + W * i;
  Im->W = W;
  Im->H = H;

  return 1;
} /* End of 'ImageCreate' function */

/* Get pixel value function.
 * ARGUMENTS:
 *   - image structure pointer:
 *       IMAGE *Im;
 *   - coordinates of pixel:
 *       INT X, Y;
 * RETURNS: 
 *   (COLOR) Vector of color.
 */
COLOR ImageGet( IMAGE *Im, INT X, INT Y )
{
  COLOR C = {0};

  /* Color reading */
  if (X >= 0 && Y >= 0 && X < Im->W && Y < Im->H)
  {
    C.X = ((Im->Rows[Y][X] >> 24) & 0xFF) / 255.0;
    C.Y = ((Im->Rows[Y][X] >> 16) & 0xFF) / 255.0;
    C.Z = ((Im->Rows[Y][X] >> 8) & 0xFF) / 255.0;
    C.W = (Im->Rows[Y][X] & 0xFF) / 255.0;
  }

  return C;
} /* End of 'ImageGet' function */

/* Flip image vertical function.
 * ARGUMENTS:
 *   - image which must be flip:
 *       IMAGE *Im;
 * RETURNS: None.
 */
VOID ImageFlipVertical( IMAGE *Im )
{
  INT x, y, w = Im->W, h = Im->H, r;
  DWORD **ptr = Im->Rows;

  for (r = 0, y = h - 1; y >= h / 2; y--, r++)
    for (x = 0; x < w; x++)
    {
      DWORD tmp = ptr[y][x];

      ptr[y][x] = ptr[r][x];
      ptr[r][x] = tmp;
    }
} /* End of 'ImageFlipVertical' function */

/* Load image from *.G24 file function.
 * ARGUMENTS:
 *   - image to be load:
 *       IMAGE *Im;
 *   - image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ImageLoadG24( IMAGE *Im, CHAR *FileName )
{
  INT w = 0, h = 0, x, y, flen, bpp;
  FILE *F;
  BYTE *mem = NULL;

  memset(Im, 0, sizeof(IMAGE));
  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  fread(&w, 2, 1, F);
  fread(&h, 2, 1, F);
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  fseek(F, 4, SEEK_SET);

  /* Check for GSM/G24/G32 file */
  if (flen == 4 + w * h)
    /* Case of GSM file */
    bpp = 1;
  else if (flen == 4 + 3 * w * h)
    /* Case of G24 file */
    bpp = 3;
  else if (flen == 4 + 4 * w * h)
    /* Case of G32 file */
    bpp = 4;
  else
  {
    fclose(F);
    return 0;
  }

  /* Allocate memory for one row and create empty image */
  if ((mem = malloc(bpp * w)) == NULL || !ImageCreate(Im, w, h))
  {
    if (mem != NULL)
      free(mem);
    fclose(F);
    return 0;
  }

  /* Read every image row */
  for (y = 0; y < h; y++)
  {
    fread(mem, bpp, w, F);
    for (x = 0; x < w; x++)
      switch (bpp)
      {
      case 1:
        Im->RowsC[y][x][0] = mem[x];
        Im->RowsC[y][x][1] = mem[x];
        Im->RowsC[y][x][2] = mem[x];
        Im->RowsC[y][x][3] = 0xFF;
        break;
      case 3:
        Im->RowsC[y][x][0] = mem[x * 3 + 0];
        Im->RowsC[y][x][1] = mem[x * 3 + 1];
        Im->RowsC[y][x][2] = mem[x * 3 + 2];
        Im->RowsC[y][x][3] = 0xFF;
        break;
      case 4:
        Im->RowsC[y][x][0] = mem[x * 4 + 0];
        Im->RowsC[y][x][1] = mem[x * 4 + 1];
        Im->RowsC[y][x][2] = mem[x * 4 + 2];
        Im->RowsC[y][x][3] = mem[x * 4 + 3];
        break;
      }
  }
  free(mem);
  fclose(F);
  
  return 1;
} /* End of 'ImageLoadG24' function */

/* Image load using stbi_image.h function.
 * ARGUMENTS:
 *   - image to be load:
 *       IMAGE *Im;
 *   - image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ImageLoadSTBI( IMAGE *Im, CHAR *FileName )
{
  INT width, height, nrChannels;
  BYTE *Data = stbi_load(FileName, &width, &height, &nrChannels, 4); 

  if (Data == NULL)
    return 0;

  if (!ImageCreate(Im, width, height))
    return 0;

  Im->Pixels = (DWORD *)Data;

  return 1;
} /* End of 'ImageLoadSTBI' function */

/* Image load function.
 * ARGUMENTS:
 *   - image to be load:
 *       IMAGE *Im;
 *   - image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ImageLoad( IMAGE *Im, CHAR *FileName )
{
  memset(Im, 0, sizeof(IMAGE));  
    
  if (ImageLoadG24(Im, FileName))
    return 1;
  if (ImageLoadSTBI(Im, FileName))
    return 1;

  return 0;
} /* End of 'ImageLoad' function */

/* Save image in G24 file format function.
 * ARGUMENTS:
 *   - image to save:
 *       IMAGE *Im;
 *   - name of file:
 *       CHAR *FileName;
 * RETURNS: None.
 */
VOID ImageSaveG24( IMAGE *Im, CHAR *FileName )
{
  INT x, y;
  FILE *F;
  BYTE *row;

  F = fopen(FileName, "wb");
  if (F == NULL)
    return;
  if ((row = malloc(3 * Im->W)) == NULL)
  {
    fclose(F);
    return;
  }
  fwrite(&Im->W, 2, 1, F);
  fwrite(&Im->H, 2, 1, F);
  /* Store image rows */
  for (y = 0; y < Im->H; y++)
  {
    /* Store to 'row' every row pixel color [BGR] */
    for (x = 0; x < Im->W; x++)
    {
      row[x * 3 + 0] = Im->Rows[y][x] & 0xFF;
      row[x * 3 + 1] = (Im->Rows[y][x] >> 8) & 0xFF;
      row[x * 3 + 2] = (Im->Rows[y][x] >> 16) & 0xFF;
    }
    /* Write row buffer to file */
    fwrite(row, 3, Im->W, F);
  }
  free(row);
  fclose(F);
} /* End of 'ImageSaveG24' function */

/* Save image in G32 file function.
 * ARGUMENTS:
 *   - image to be save:
 *       IMAGE *Im;
 *   - name of file:
 *       CHAR *FileName;
 * RETURNS: None.
 */
VOID ImageSaveG32( IMAGE *Im, CHAR *FileName )
{
  FILE *F;

  F = fopen(FileName, "wb");
  if (F == NULL)
    return;
  fwrite(&Im->W, 2, 1, F);
  fwrite(&Im->H, 2, 1, F);
  fwrite(Im->Pixels, 4, Im->W * Im->H, F);
  fclose(F);
} /* End of 'ImageSaveG32' function */

/* Image free function.
 * ARGUMENTS:
 *   - Image to be free up:
 *       IMAGE *Im;
 * RETURNS: None.
 */
VOID ImageFree( IMAGE *Im )
{ 
  if (Im->Pixels == NULL)
    return;
  free(Im->Pixels);
} /* End of 'ImageFree' function */

/* END OF 'images.c' FILE */

