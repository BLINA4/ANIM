/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : lightning.h
 * PURPOSE     : Animation project.
 *               Lightning subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 04.12.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __lightning_h_
#define __lightning_h_

#include "../../comdef.h"
#include "../render.h"

/* Light sources types */
typedef enum tagLIGHT_TYPE
{
  LIGHT_AMBIENT = 0,         /* Ambient light type */
  LIGHT_POINT = 1,           /* Point light type */
  LIGHT_DIRECTIONAL = 2,     /* Directional light type */
  LIGHT_SPOT = 3             /* Spot light type */
} LIGHT_TYPE;
 
/* Light representation type */
typedef struct tagLIGHT
{
  LIGHT_TYPE Type; /* Light type */
  VEC
    Pos,              /* Position of point & spot light types */
    Dir,              /* Direction of directional and spot light */
    Color,            /* Color of light */
    Att;              /* Attenuation coefficients: CC, CL, CQ */
  VEC2
    CutOffAngle,      /* Cut off Angle for spotlight */
    CutOffDist;       /* Distance to cut off for spot and point light */
  BOOL
    IsShadowCast,     /* Is shadow castes flag */
    IsRender;         /* Is rendering on current frame */
} LIGHT;

#endif /* __lightning_h_ */

/* END OF 'lightning.h' FILE */

