/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : primitives.h
 * PURPOSE     : Animation project.
 *               Primitives subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 13.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __primitives_h_
#define __primitives_h_

#include "../../comdef.h"
#include "../render.h"

/* Primitive types */
typedef enum tagPRIM_TYPE
{
  PRIM_POINTS,              /* Points */
  PRIM_LINES,               /* Lines */
  PRIM_LINE_STRIP,          /* Lines strip */
  PRIM_TRIMESH,             /* Triangles */
  PRIM_STRIP,               /* Triangles strip */
  PRIM_PATCH,               /* Patches */
  PRIM_LINE_STRIP_ADJACENCY /* Lines strip adjacency */
} PRIM_TYPE;

/* Primitive structure */
typedef struct tagPRIM PRIM;
struct tagPRIM
{
  PRIM_TYPE Type;    /* Primitive type */
  //MATERIAL *Mtl;   /* Primitive material */
  MATR Trans;        /* Additional transformation matrix */
  INT
    VA, IBuf, VBuf,  /* OpenGL vertex array, vertex buffer and index buffer */
    NumOfI;          /* Number of indexes/vertexes/patches points */
  VEC
    Min,             /* Minimum vector */
    Max,             /* Maximum vector */
    Center;          /* Center vector */
};

/* Primitive create function.
 * ARGUMENTS: 
 *   - primitive type:
 *       PRIM_TYPE Type;
 *   - vertex data format:
 *       CHAR *VertexFormat;
 *   - vertex data:
 *       VOID *V;
 *   - number of vertexes:
 *       INT NumOfV;
 *   - index array:
 *       INT *Ind;
 *   - number of indices:
 *       INT NumOfI;
 * RETURNS:
 *   (PRIM *) pointer to created primitive.
 */
static PRIM * PrimCreate( PRIM_TYPE Type, CHAR *VertexFormat, VOID *V, INT NumOfV, INT *Ind,   INT NumOfI );

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       PRIM *Pr;
 *   - world CS matrix to work with:
 *       MATR World;
 * RETURNS: None.
 */
static VOID PrimDraw( PRIM *Pr, MATR World );

/* Free memory and delete primitive function.
 * ARGUMENTS:
 *   - primitive to delete:
 *       PRIM *Pr;
 * RETURNS: None.
 */
static VOID PrimFree( PRIM *Pr );

#endif /* __primitives_h_ */

/* END OF 'primitives.h' FILE */

