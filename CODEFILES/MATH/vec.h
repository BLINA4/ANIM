/***************************************************************
 * Copyleft 2020
 *   C Programmer
 ***************************************************************/

/* FILE NAME   : vec.h
 * PURPOSE     : Animation project.
 *               Vector supply functions
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 06.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __vec_h_
#define __vec_h_

#include "mth.h"

/* Vector sum macros */
#define VecAddVec3(A, B, C) (VecAddVec(VecAddVec(A, B), C))
#define VecAddVec4(A, B, C, D) (VecAddVec(VecAddVec3(A, B, C), D))

/***
 * Evaluation functions
 ***/

/* Set 3-component vector coordinates function.
 * ARGUMENTS:
 *   - float vector coordinates
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) which is new 3-component vector
 */
static inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
} /* End of 'VecSet' function */

/* Set 2-component vector coordinates function.
 * ARGUMENTS:
 *   - float vector coordinates
 *       FLT X, Y;
 * RETURNS:
 *   (VEC2) which is new 2-component vector.
 */
static inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v;

  v.X = X;
  v.Y = Y;
  return v;
} /* End of 'Vec2Set' function */

/* Set 4-component vector coordinates function.
 * ARGUMENTS:
 *   - float vector coordinates
 *       FLT X, Y, Z, W;
 * RETURNS:
 *   (VEC4) which is new 4-component vector
 */
static inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  v.W = W;
  return v;
} /* End of 'Vec4Set' function */

/* Set 3-component vector with same coordinates function.
 * ARGUMENTS:
 *   - float vector coordinate
 *       FLT N;
 * RETURNS:
 *   (VEC) which is new 3-component vector
 */
static inline VEC VecSet1( FLT N )
{
  VEC v;

  v.X = N;
  v.Y = N;
  v.Z = N;
  return v;
} /* End of 'VecSet1' function */

/* 3-component vector summary function.
 * ARGUMENTS:
 *   - 2 3-component vectors
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) which is new summary 3-component vector
 */
static inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* 3-component vector subtract function.
 * ARGUMENTS:
 *   - 2 3-component vectors
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) which is new subtract 3-component vector
 */
static inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* 3-component vector multiple by number function.
 * ARGUMENTS:
 *   - vector
 *       VEC V1;
 *   - float number
 *        FLT N;
 * RETURNS:
 *   (VEC) which is new 3-component vector
 */
static inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* 3-component vector divide by number function.
 * ARGUMENTS:
 *   - vector
 *       VEC V1;
 *   - float number
 *        FLT N;
 * RETURNS:
 *   (VEC) which is new 3-component vector
 */
static inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */

/* 3-component vector reverse function.
 * ARGUMENTS:
 *   - vector
 *       VEC V1;
 * RETURNS:
 *   (VEC) what is new 3-component vector
 */
static inline VEC VecNeg( VEC V1 )
{
  return VecSet(-V1.X, -V1.Y, -V1.Z);
} /* End of 'VecNeg' function */

/* 3-component vectors dot product function.
 * ARGUMENTS:
 *   - 2 3-component vectors
 *       VEC V1, V2;
 * RETURNS:
 *   (FLT) what is 3-component vectors dot product
 */
static inline FLT VecDot( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDot' function */

/* 3-component vectors cross product function.
 * ARGUMENTS:
 *   - 2 3-component vectors
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) what is 3-component vectors cross product
 */
static inline VEC VecCross( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y,
    -V1.X * V2.Z + V1.Z * V2.X, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCross' function */

/* Evaluate 3-component vector lenght function.
 * ARGUMENTS:
 *   - 3-component vector
 *       VEC V;
 * RETURNS:
 *   (FLT) what is 3-component vector lenght
 */
static inline FLT VecLen( VEC V )
{
  return sqrt(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
} /* End of 'VecLen' function */

/* Evaluate 2-component vector lenght function.
 * ARGUMENTS:
 *   - 2-component vector
 *       VEC V;
 * RETURNS:
 *   (FLT) what is 2-component vector lenght
 */
static inline FLT VecLen2( VEC V )
{
  return sqrt(V.X * V.X + V.Y * V.Y);
} /* End of 'VecLen2' function */

/* Normalize 3-component vector function.
 * ARGUMENTS:
 *   - 3-component vector
 *       VEC V;
 * RETURNS:
 *   (VEC) what is nolmalized 3-component vector
 */
static inline VEC VecNormalize( VEC V )
{
  FLT len;

  len = VecLen(V);
  return VecSet(V.X / len, V.Y / len, V.Z / len);
} /* End of 'VecNormalize' function */

/* Determine minimum of two vectors function.
 * ARGUMENTS:
 *   - vectors to be minimized:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
static inline VEC VecMin( VEC V1, VEC V2 )
{
  return VecSet(V1.X < V2.X ? V1.X : V2.X,
                V1.Y < V2.Y ? V1.Y : V2.Y,
                V1.Z < V2.Z ? V1.Z : V2.Z);
} /* End of 'VecMin' function */

/* Determine maximum of two vectors function.
 * ARGUMENTS:
 *   - vectors to be maximized:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
static inline VEC VecMax( VEC V1, VEC V2 )
{
  return VecSet(V1.X > V2.X ? V1.X : V2.X,
                V1.Y > V2.Y ? V1.Y : V2.Y,
                V1.Z > V2.Z ? V1.Z : V2.Z);
} /* End of 'VecMax' function */

/* 3-component vector multiple by matrix function.
 * ARGUMENTS:
 *   - 3-component vector
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) what is new 3-component vector
 */
static inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return
    VecSet((M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z + M.M[3][0]) / w,
           (M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z + M.M[3][1]) / w,
           (M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z + M.M[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Transform 3-component vector function.
 * ARGUMENTS:
 *   - 3-component vector
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) what is new 3-component vector
 */
static inline VEC VecTransform( VEC V, MATR M )
{
  return
    VecSet(M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z,
           M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z,
           M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z);
} /* End of 'VecTransform' function */

/* Transform 3-component point vector function.
 * ARGUMENTS:
 *   - 3-component point vector
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) what is new 3-component point vector
 */
static inline VEC PointTransform( VEC V, MATR M )
{
  return
    VecSet(M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z + M.M[3][0],
           M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z + M.M[3][1],
           M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z + M.M[3][2]);
} /* End of 'PointTransform' function */

#endif /* __vec_h_ */

/* END OF 'vec.h' FILE */
