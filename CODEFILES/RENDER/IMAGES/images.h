/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/
  
/* FILE NAME   : images.h
 * PURPOSE     : Animation project.
 *               Images header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 08.02.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __images_h_
#define __images_h_

#include "../../comdef.h"

/* Image representation structure */
typedef struct
{
  INT W, H;           /* Image size */
  DWORD *Pixels;      /* Image pixel colors */
  DWORD **Rows;       /* Image rows array */
  BYTE (**RowsC)[4];  /* Image rows array by components */
} IMAGE; 

typedef struct
{
  FLT X, Y, Z, W;
} COLOR;

typedef struct tagBITMAPINFOHEADER
{
  DWORD  biSize; 
  DWORD  biWidth; 
  DWORD  biHeight; 
  WORD   biPlanes; 
  WORD   biBitCount; 
  DWORD  biCompression; 
  DWORD  biSizeImage; 
  DWORD  biXPelsPerMeter; 
  DWORD  biYPelsPerMeter; 
  DWORD  biClrUsed; 
  DWORD  biClrImportant; 
} BITMAPINFOHEADER;

typedef WORD FILE_ID; 
typedef struct
{
  DWORD size;   
  WORD rzrv1;
  WORD rzrv2;
  DWORD offset;   
  BITMAPINFOHEADER dib;
} BMP_HEADER;
 
/* Image create functions.
 * ARGUMENTS:
 *   - image to be created:
 *       IMAGE *Im;
 *   - image size:
 *       INT W, H;
 * RETURNS: None.
 */
BOOL ImageCreate( IMAGE *Im, INT W, INT H );

/* Get pixel value function.
 * ARGUMENTS:
 *   - image structure pointer:
 *       IMAGE *Im;
 *   - coordinates of pixel:
 *       INT X, Y;
 * RETURNS: 
 *   (COLOR) Vector of color.
 */
COLOR ImageGet( IMAGE *Im, INT X, INT Y );

/* Flip image vertical function.
 * ARGUMENTS:
 *   - image which must be flip:
 *       IMAGE *Im;
 * RETURNS: None.
 */
VOID ImageFlipVertical( IMAGE *Im );

/* Load image from *.G24 file function.
 * ARGUMENTS:
 *   - image to be load:
 *       IMAGE *Im;
 *   - image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ImageLoadG24( IMAGE *Im, CHAR *FileName );

/* Load image from *.BMP file function.
 * ARGUMENTS:
 *   - image to be load:
 *       - IMAGE *Im;
 *    - image file name:
 *         CHAR *FileName;
 * RETURN:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ImageLoadBMP( IMAGE *Im, CHAR *FileName );

/* Image load function.
 * ARGUMENTS:
 *   - image to be load:
 *       IMAGE *Im;
 *   - image file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL ImageLoad( IMAGE *Im, CHAR *FileName );

/* Save image in G24 file format function.
 * ARGUMENTS:
 *   - image to save:
 *       IMAGE *Im;
 *   - name of file:
 *       CHAR *FileName;
 * RETURNS: None.
 */
VOID ImageSaveG24( IMAGE *Im, CHAR *FileName );

/* Save image in G32 file function.
 * ARGUMENTS:
 *   - image to be save:
 *       IMAGE *Im;
 *   - name of file:
 *       CHAR *FileName;
 * RETURNS: None.
 */
VOID ImageSaveG32( IMAGE *Im, CHAR *FileName );

/* Save image in BMP file.
 * ARGUMENTS:
 *   - image to save:
 *       IMAGE *Im;
 *   - name of file:
 *       CHAR *FileName;
 * RETURNS: None.
 */
VOID ImageSaveBMP( IMAGE *Im, CHAR *FileName );

/* Image free function.
 * ARGUMENTS:
 *   - Image to be free up:
 *       IMAGE *Im;
 * RETURNS: None.
 */
VOID ImageFree( IMAGE *Im );

#endif /* __images_h_ */

/* END OF 'images.h' FILE */

