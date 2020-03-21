/***************************************************************
 * Copyleft 2020
 *   Junior C programmer presents (lol)
 ***************************************************************/

/* FILE NAME   : mth.h
 * PURPOSE     : Animation project.
 *               Main header file for math module
 * PROGRAMMER  : Andrey Shayda.
 * LAST UPDATE : 22.03.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef _mth_h_
#define _mth_h_

#include "../comdef.h"

#include <math.h>

/* math constant PI define */
#define MTH_PI 3.14159265358979323846

/* degrees to radians macro */
#define MTH_D2R(A) ((A) * (MTH_PI / 180.0))
#define MTH_Degree2Radian(a) MTH_D2R(a)

/* basic float types */
typedef float FLT;
typedef double DBL;

/* 3-component vector */
typedef struct tagVEC
{
  FLT X, Y, Z; /* x, y, z vector coordinates */
} VEC;

/* 2-component vector */
typedef struct tagVEC2
{
  FLT X, Y; /* x, y, vector coordinates */
} VEC2;

/* 4-component vector */
typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* x, y, z vector coordinates + uniform coordinate */
} VEC4;

/* 3-component ray */
typedef struct tagRAY
{
  VEC Org; /* Start point of ray */
  VEC Dir; /* Ray direction vector */
} RAY;

/* matrix 4 x 4 structure */
typedef struct tagMATR
{
  FLT M[4][4]; /* matrix */
} MATR;

/* Identity matrix */
static MATR UnixMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Camera structure */
typedef struct tagCAMERA
{
  VEC Loc, At;                  /* Camera main direction vectors */
  MATR ViewMatr, ProjMatr, VP;  /* View, projection and premultiplied matrixes */
  FLT
    ProjSize, ProjDist,
    ProjFarClip, ProjW, ProjH;  /* Projection parameters */
} CAMERA;

#endif /* _mth_h_ */

/* END OF 'mth.h' FILE */
