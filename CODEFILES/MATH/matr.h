/***************************************************************
 * Copyleft 2020
 *   Junior C programmer presents (lol)
 ***************************************************************/

/* FILE NAME   : matr.h
 * PURPOSE     : Animation project.
 *               Matrix supply functions
 * PROGRAMMER  : Andrey Shayda.
 * LAST UPDATE : 22.03.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __matr_h_
#define __matr_h_

#include "mth.h"
#include "vec.h"

/* Matrix multiplication macros */
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr(A, B), MatrMulMatr(C, D))
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr(MatrMulMatr4(A, B, C, D), E)
#define MatrMulMatr6(A, B, C, D, E, F) MatrMulMatr(MatrMulMatr3(A, B, C), MatrMulMatr3(D, E, F))

/***
 * Evaluation functions
 ***/

/* Identity matrix function.
 * ARGUMENTS: None;
 * RETURNS:
 *   (MATR) what is identity matrix
*/
__inline MATR MatrIdentity( VOID )
{
  return UnixMatrix;
} /* End of 'MatrIdentity' function */

/* Create translation matrix function.
 * ARGUMENTS:
 *   - translation 3-component vector
 *       VEC T;
 * RETURNS:
 *   (MATR) what is translation matrix
*/
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnixMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;

  return m;
} /* End of 'MatrTranslate' function */

/* Create scaling matrix function.
 * ARGUMENTS:
 *   - scaling 3-component vector
 *       VEC T;
 * RETURNS:
 *   (MATR) what is scaling matrix
*/
__inline MATR MatrScale( VEC S )
{
  MATR m = UnixMatrix;

  m.M[0][0] = S.X;
  m.M[1][1] = S.Y;
  m.M[2][2] = S.Z;

  return m;
} /* End of 'MatrScale' function */

/* Matrix of rotation around X axis function.
 * ARGUMENTS:
 *   - rotate angle in degrees
 *       FLT AngleInDegrees;
 * RETURNS:
 *   (MATR) what is rotation aroud X axis matrix
*/
__inline MATR MatrRotateX( FLT AngleInDegrees )
{
  FLT A = MTH_D2R(AngleInDegrees), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {1, 0, -0, 0},
      {0, co, si, 0},
      {0, -si, co, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateX' function */

/* Matrix of rotation around Y axis function.
 * ARGUMENTS:
 *   - rotate angle in degrees
 *       FLT AngleInDegrees;
 * RETURNS:
 *   (MATR) what is rotation aroud Y axis matrix
*/
__inline MATR MatrRotateY( FLT AngleInDegrees )
{
  FLT A = MTH_D2R(AngleInDegrees), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {co, 0, -si, 0},
      {0, 1, 0 , 0},
      {si, 0, co, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateY' function */

/* Matrix of rotation around Z axis function.
 * ARGUMENTS:
 *   - rotate angle in degrees
 *       FLT AngleInDegrees;
 * RETURNS:
 *   (MATR) what is rotation aroud Z axis matrix
*/
__inline MATR MatrRotateZ( FLT AngleInDegrees )
{
  FLT A = MTH_D2R(AngleInDegrees), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {co, si, 0, 0},
      {-si, co, 0 , 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateZ' function */

/* Matrix of rotation function.
 * ARGUMENTS:
 *   - rotate angle in degrees
 *       FLT AngleInDegrees;
 *   - rotation 3-component vector
 *       VEC R;
 * RETURNS:
 *   (MATR) what is rotation matrix
*/
__inline MATR MatrRotate( FLT AngleInDegrees, VEC R )
{
  FLT A = MTH_D2R(AngleInDegrees), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co),
         V.X * V.Y * (1 - co) + V.Z * si,
           V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si,
         co + V.Y * V.Y * (1 - co),
           V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si,
         V.Z * V.Y * (1 - co) - V.X * si,
           co + V.Z * V.Z * (1 - co),       0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotate' function */

/* Matrix multiple by matrix function.
 * ARGUMENTS:
 *   - matrixes
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) what is new matrix
*/
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR N = MatrIdentity();
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (N.M[i][j] = 0, k = 0; k < 4; k++)
        N.M[i][j] += M1.M[i][k] * M2.M[k][j];

  return N;
} /* End of 'MatrMulMatr' function */

/* Matrix transpose function.
 * ARGUMENTS:
 *   - matrix
 *       MATR M1;
 * RETURNS:
 *   (MATR) what is transpose matrix
*/
__inline MATR MatrTranspose( MATR M )
{
  MATR T = MatrIdentity();
  INT i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      T.M[j][i] = M.M[i][j];

  return T;
} /* End of 'MatrTranspose' function */

/* Matrix 3x3 determinant count function.
 * ARGUMENTS:
 *   - matrix elements
 *       FLT A11, A12, A13,
         FLT A21, A22, A23,
         FLT A31, A32, A33;
 * RETURNS:
 *   (FLT) what is matrix determinant
*/
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 +
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Matrix determinant evaluate function.
 * ARGUMENTS:
 *   - matrix
 *       MATR M
 * RETURNS:
 *   (FLT) what is matrix determinant
*/
__inline FLT MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) -
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                              M.M[2][0], M.M[2][2], M.M[2][3],
                              M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                              M.M[2][0], M.M[2][1], M.M[2][2],
                              M.M[3][0], M.M[3][1], M.M[3][2]);
} /* End of 'MatrDeterm' function */

/* Matrix inverse function.
 * ARGUMENTS:
 *   - matrix
 *       MATR M
 * RETURNS:
 *   (MATR) what is inversed matrix
*/
__inline MATR MatrInverse( MATR M )
{
  MATR N;
  FLT det = MatrDeterm(M);

  if (det == 0)
    return UnixMatrix;

  /* build adjoint matrix */
  N.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  N.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  N.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  N.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  N.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]);
  N.M[1][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[2][0], M.M[2][2], M.M[2][3],
                  M.M[3][0], M.M[3][2], M.M[3][3]);
  N.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]);
  N.M[3][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[2][0], M.M[2][1], M.M[2][2],
                  M.M[3][0], M.M[3][1], M.M[3][2]);

  N.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                 M.M[1][1], M.M[1][2], M.M[1][3],
                 M.M[3][1], M.M[3][2], M.M[3][3]);
  N.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]);
  N.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]);
  N.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]);

  N.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3]);
  N.M[1][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                  M.M[1][0], M.M[1][2], M.M[1][3],
                  M.M[2][0], M.M[2][2], M.M[2][3]);
  N.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3]);
  N.M[3][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                  M.M[1][0], M.M[1][1], M.M[1][2],
                  M.M[2][0], M.M[2][1], M.M[2][2]);

  /* divide by determinant */
  N.M[0][0] /= det;
  N.M[1][0] /= det;
  N.M[2][0] /= det;
  N.M[3][0] /= det;
  N.M[0][1] /= det;
  N.M[1][1] /= det;
  N.M[2][1] /= det;
  N.M[3][1] /= det;
  N.M[0][2] /= det;
  N.M[1][2] /= det;
  N.M[2][2] /= det;
  N.M[3][2] /= det;
  N.M[0][3] /= det;
  N.M[1][3] /= det;
  N.M[2][3] /= det;
  N.M[3][3] /= det;

  return N;
} /* End of 'MatrInverse' function */

/* Make unit box fit transform matrix by min-max function.
 * ARGUMENTS:
 *   - bound box:
 *       VEC Min, Max;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrUnitFit( VEC Min, VEC Max )
{
  VEC Dv = VecSubVec(Max, Min);
  FLT sc;

  sc = 1.0 / COM_MAX(COM_MAX(Dv.X, Dv.Y), Dv.Z);
  return MatrMulMatr(MatrTranslate(VecNeg(Min)), MatrScale(VecSet1(sc)));
} /* End of 'MatrUnitFit' function */

/* Make centered (zero by Y) unit box fit transform matrix by min-max function.
 * ARGUMENTS:
 *   - bound box:
 *       VEC Min, Max;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrUnitFitCenterY( VEC Min, VEC Max )
{
  VEC Dv = VecSubVec(Max, Min);
  FLT sc;

  sc = 1.0 / COM_MAX(COM_MAX(Dv.X, Dv.Y), Dv.Z);
  return MatrMulMatr(MatrTranslate(VecSet(-Dv.X / 2, -Min.Y, -Dv.Z / 2)), MatrScale(VecSet1(sc)));
} /* End of 'MatrUnitFitCenterY' function */

/* Make centered (zero by Z) unit box fit transform matrix by min-max function.
 * ARGUMENTS:
 *   - bound box:
 *       VEC Min, Max;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrUnitFitCenterZ( VEC Min, VEC Max )
{
  VEC Dv = VecSubVec(Max, Min);
  FLT sc;

  sc = 1.0 / COM_MAX(COM_MAX(Dv.X, Dv.Y), Dv.Z);
  return MatrMulMatr(MatrTranslate(VecSet(-Min.X - Dv.X / 2, -Min.Y - Dv.Y / 2, -Min.Z)), MatrScale(VecSet1(sc)));
} /* End of 'MatrUnitFitCenterZ' function */

/* View matrix create function.
 * ARGUMENTS:
 *   - 3-component vectors
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) what is view matrix
*/
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCross(Dir, Up1)),
    Up = VecCross(Right, Dir);
  MATR M =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDot(Loc, Right), - VecDot(Loc, Up), VecDot(Loc, Dir), 1}
    }
  };
  return M;
} /* End of 'MatrView' function */

/* Ortho projection matrix create function.
 * ARGUMENTS:
 *   - float projection parameters
 *       FLT Left, Right, Bottom, Top, Near, Far;
 * RETURNS:
 *   (MATR) what is ortho projection matrix
*/
__inline MATR MatrOrtho( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{
  MATR M =
    {
      {
        {2 / (Right - Left), 0, 0, 0},
        {0, 2 / (Top - Bottom), 0, 0},
        {0, 0, -2 / (Far - Near), 0},
        {-(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom),
        -(Far + Near) / (Far - Near), 1}
      }
    };
  return M;
} /* End of 'MatrOrtho' function */

/* View frustum matrix create function.
 * ARGUMENTS:
 *   - float projection parameters
 *       FLT l, r, b, t, n, f;
 * RETURNS:
 *   (MATR) what is view frustum matrix
*/
__inline MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  MATR m =
    {
      {
        {2 * n / (r - l), 0, 0, 0},
        {0, 2 * n / (t - b), 0, 0},
        {(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n),-1},
        {0, 0, -(2 * n * f) / (f - n), 1}
      }
    };
  return m;
} /* End of 'MatrFrustum' function */

#endif /* __matr_h_ */

/* END OF 'matr.h' FILE */
