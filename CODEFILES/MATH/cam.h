/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : cam.h
 * PURPOSE     : Animation project.
 *               Camera supply functions
 * PROGRAMMER  : BLIN4
 * LAST UPDATE : 06.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __cam_h_
#define __cam_h_

#include "vec.h"
#include "matr.h"

/* Set camera parameters function.
 * ARGUMENTS:
 *   - camera structure pointer:
 *       CAMERA *Cam;
 *   - location, point of interest and up view 3-component vectors:
 *       VEC Loc, At, Up;
 * RETURNS: None.
 */
static inline VOID CamSet( CAMERA *Cam, VEC Loc, VEC At, VEC Up )
{
  Cam->Loc = Loc;
  Cam->At = At;
  Cam->ViewMatr = MatrView(Loc, At, Up);
  Cam->VP = MatrMulMatr(Cam->ViewMatr, Cam->ProjMatr);
} /* End of 'CamSet' function */

/* Obtain camera right direction function.
 * ARGUMENTS:
 *   - camera structure pointer:
 *       CAMERA *Cam;
 * RETURNS:
 *   (VEC) right direction vector.
 */
static inline VEC CamRight( CAMERA *Cam )
{
  return VecSet(Cam->ViewMatr.M[0][0], Cam->ViewMatr.M[1][0], Cam->ViewMatr.M[2][0]);
} /* End of 'CamRight' function */

/* Obtain camera up direction function.
 * ARGUMENTS:
 *   - camera structure pointer:
 *       CAMERA *Cam;
 * RETURNS:
 *   (VEC) up direction vector.
 */
static inline VEC CamUp( CAMERA *Cam )
{
  return VecSet(Cam->ViewMatr.M[0][1], Cam->ViewMatr.M[1][1], Cam->ViewMatr.M[2][1]);
} /* End of 'CamUp' function */

/* Obtain camera forward direction function.
 * ARGUMENTS:
 *   - camera structure pointer:
 *       CAMERA *Cam;
 * RETURNS:
 *   (VEC) forward direction vector.
 */
static inline VEC CamDir( CAMERA *Cam )
{
  return VecSet(-Cam->ViewMatr.M[0][2], -Cam->ViewMatr.M[1][2], -Cam->ViewMatr.M[2][2]);
} /* End of 'CamDir' function */

/* Camera setting projection function.
 *   - camera structure pointer:
 *       CAMERA *Cam;
 *   - frame size in pixels:
 *       INT W, H;
 * RETURNS: None.
 */
static inline VOID CamProjSet( CAMERA *Cam, INT W, INT H )
{
  FLT ratio_x, ratio_y;

  ratio_x = ratio_y = Cam->ProjSize / 2;

  if (W > H) 
    ratio_x *= (FLT)W / H;
  else               
    ratio_y *= (FLT)H / W;

  Cam->ProjW = ratio_x * 2;
  Cam->ProjH = ratio_y * 2;

  Cam->ProjMatr =
    MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
      Cam->ProjDist, Cam->ProjFarClip);
  Cam->VP = MatrMulMatr(Cam->ViewMatr, Cam->ProjMatr);
} /* End of 'CamProjSet' function */

/* Set camera default parameters function.
 *   - camera structure pointer:
 *       CAMERA *Cam;
 * RETURNS: None.
 */
static inline VOID CamSetDefault( CAMERA *Cam )
{
  VEC Up = VecSet(0, 5, 1);

  /* Set viewer */
  Cam->Loc = VecSet(0, 1, 0);
  Cam->At = VecSet(0, 0, -5);
  Cam->ViewMatr = MatrView(Cam->Loc, Cam->At, Up);

  /* Set projection */
  Cam->ProjSize = 0.1;
  Cam->ProjDist = Cam->ProjSize;
  Cam->ProjFarClip = 1000;
  CamProjSet(Cam, 1, 1);
} /* End of 'CamSetDefault' function */

#endif /* __cam_h_ */

/* END OF 'cam.h' FILE */
