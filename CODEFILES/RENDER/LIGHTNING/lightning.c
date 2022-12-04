/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : lightning.c
 * PURPOSE     : Animation project.
 *               Lightning subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 04.12.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <string.h>

#include "lightning.h"

/* Light pointers array */
static LIGHT *Lights[MAX_LIGHTS];

/* Light sources draw shaders */
static SHADER
  *LightShdAmbient, /* Shader for ambient light type */
  *LightShdPoint,   /* Shader for point light type */
  *LightShdDir,     /* Shader for directional light type */
  *LightShdSpot,    /* Shader for spot light type */
  *LightShdDraw;    /* Shader for light source draw */

/* Draw light source texture */
static TEXTURE *LightGlowTex;

/* Shadow map size */
static INT ShadowMapSize = 2048;

/* Flag for shadow for direction and point light */
static INT IsShdDir, IsShdPoint;

/* Texture for shadow for point light */
static UINT ShdCubeMap;

/* Matrix for shadow */
static MATR LightMatr;

/* Parametrs for camera for point light */
typedef struct tagShadowDir
{
  GLenum CubeFace; /* CubeMap surfase */
  VEC At, Up;      /* Vectors for view matrix */
} ShadowDir;

/* Light sources deintialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID LightsClose( VOID )
{
  INT i;

  for (i = 0; i < Anim.NumOfLights; i++)
    free(Lights[i]);
} /* End of 'LightsClose' function */

/* Light source add function.
 * ARGUMENTS:
 *   - light description:
 *       CHAR *LightDescr;
 * RETURNS:
 *   (LIGHT *) Pointer to light or NULL if failed.
 */
static LIGHT * TNG_LightAdd( CHAR *LightDescr )
{
  INT i;
  ARGS Args = Scanner(LightDescr);
  LIGHT *L;

  if (((L = malloc(sizeof(LIGHT))) == NULL) || Anim.NumOfLights == MAX_LIGHTS)
    return NULL;
  memset(L, 0, sizeof(LIGHT));
  Anim.NumOfLights++;

  for (i = 0; i < Args.NumOfScans; i++)
  {
    FLT x = Args.Scan[i].Var[0],
        y = Args.Scan[i].Var[1],
        z = Args.Scan[i].Var[2];

    if (strcmp(Args.Scan[i].Name, "Type") == 0)
      L->Type = x == 0 ? LIGHT_AMBIENT : x == 1 ? LIGHT_POINT : x == 2 ? LIGHT_DIRECTIONAL : LIGHT_SPOT;
    else if (strcmp(Args.Scan[i].Name, "IsShadowCast") == 0)
    {
      L->IsShadowCast = x;
      if (!IsShdDir && L->Type == 2)
        IsShdDir = !IsShdDir; //DirShadowInit();
      else if (!IsShdPoint && L->Type == 1)
        IsShdPoint = !IsShdPoint; //PointShadowInit();
    }
    else if (strcmp(Args.Scan[i].Name, "Color") == 0)
      L->Color = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "Att") == 0)
      L->Att = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "CutOffAngle") == 0)
      L->CutOffAngle = Vec2Set(x, y);
    else if (strcmp(Args.Scan[i].Name, "CutOffDist") == 0)
      L->CutOffDist = Vec2Set(x, y);
    else if (strcmp(Args.Scan[i].Name, "Dir") == 0)
      L->Dir = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "Pos") == 0)
      L->Pos = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "IsRender") == 0)
      L->IsRender = x;
  }

  return L;
} /* End of 'LightAdd' function */

/* Light mark for draw function.
 * ARGUMETNS:
 *   - light to mark for draw:
 *       LIGHT *Lig;
 * RETURNS: None.
 */
static VOID LightDraw( LIGHT *Lig )
{
  if (Lig != NULL)
    Lig->IsRender = TRUE;
} /* End of 'LightDraw' function */
 
/* Lights clear IsRender flag function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID LightClearIsRenderFlag( VOID )
{
  INT i;

  for (i = 0; i < Anim.NumOfLights; i++)
    if (Lights[i]->Type != LIGHT_AMBIENT)
      Lights[i]->IsRender = FALSE;
} /* End of 'LightClearIsRenderFlag' function */

/* END OF 'lightning.c' FILE */

