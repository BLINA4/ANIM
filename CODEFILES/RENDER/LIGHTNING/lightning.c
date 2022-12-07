/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : lightning.c
 * PURPOSE     : Animation project.
 *               Lightning subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 07.12.2022.
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

/* Light source add function.
 * ARGUMENTS:
 *   - light description:
 *       CHAR *LightDescr;
 * RETURNS:
 *   (LIGHT *) Pointer to light or NULL if failed.
 */
static LIGHT * LightAdd( CHAR *LightDescr )
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

/* Light source redraw(deffered lighting) functuion.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID LightsRedraw( VOID )
{
  INT i, loc;
  /* Shaders pointers */
  SHADER *ShadersId[] =
  {
    LightShdAmbient,
    LightShdPoint,
    LightShdDir,
    LightShdSpot,
  };
  LIGHT *Lig;

  /* Set blending for rendering light sources */
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(FALSE);
  glDisable(GL_DEPTH_TEST);
  
  for (i = 0; i < Anim.NumOfLights; i++)
  {
    UINT ProgId;
 
    Lig = Lights[i];

    if (Lig->IsRender)
    {
      VEC v;

      if (Lig->IsShadowCast && Lig->Type == 2)
      {
        glDepthMask(TRUE);
        glEnable(GL_DEPTH_TEST);
        //DirShadowsRedraw(Lig);
        glDepthMask(FALSE);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0 + 8);
        //glBindTexture(GL_TEXTURE_2D, ShadowFBO->Attachments[0]->TexId);
        ProgId = ShaderApply(ShadersId[Lig->Type]);
        if ((loc = glGetUniformLocation(ProgId, "MatrShadow")) != -1)
          glUniformMatrix4fv(loc, 1, FALSE, LightMatr.M[0]);
      }
      else if (Lig->IsShadowCast && Lig->Type == 1)
      {
        glDepthMask(TRUE);
        glEnable(GL_DEPTH_TEST);
        //PointShadowsRedraw(Lig);
        glDepthMask(FALSE);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0 + 8);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ShdCubeMap);
        /*
        ProgId = ShaderApply(ShadersId[Lig->Type]);
        if ((loc = glGetUniformLocation(ProgId, "MatrShadow")) != -1)
          glUniformMatrix4fv(loc, 1, FALSE, LightMatr.M[0]);
        */
      }
      ProgId = ShaderApply(ShadersId[Lig->Type]);
 
      /*
      ShaderAddComponent(ProgId, "Standart()", "Lights", 0);
      ShaderAddComponentMatrix(ProgId, MatrIdentity(), &(Anim.cam.VP));
      */

      /* Setup default values to light shaders */
      if ((loc = glGetUniformLocation(ProgId, "ShadowCast")) != -1)
        glUniform1i(loc, Lig->IsShadowCast);
      if ((loc = glGetUniformLocation(ProgId, "MatrV")) != -1)
        glUniformMatrix4fv(loc, 1, FALSE, &(Anim.cam.ViewMatr));
      if ((loc = glGetUniformLocation(ProgId, "MatrVP")) != -1)
        glUniformMatrix4fv(loc, 1, FALSE, &(Anim.cam.VP));
      if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
        glUniform1f(loc, Anim.SyncTime);
      if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
        glUniform3fv(loc, 1, &(Anim.cam.Loc));
      v = CamRight(&(Anim.cam));
      if ((loc = glGetUniformLocation(ProgId, "CamRight")) != -1)
        glUniform3fv(loc, 1, &v);
      v = CamUp(&(Anim.cam));
      if ((loc = glGetUniformLocation(ProgId, "CamUp")) != -1)
        glUniform3fv(loc, 1, &v);
      //if ((loc = glGetUniformLocation(ProgId, "IsWireFrame")) != -1)
      //  glUniform1i(loc, Anim.IsWireFrame);
      if ((loc = glGetUniformLocation(ProgId, "FrameW")) != -1)
        glUniform1f(loc, Anim.W);
      if ((loc = glGetUniformLocation(ProgId, "FrameH")) != -1)
        glUniform1f(loc, Anim.H);

      /* Setup light sources to shader values */
      if ((loc = glGetUniformLocation(ProgId, "LightPos")) != -1)
        glUniform3fv(loc, 1, &Lig->Pos.X);
      if ((loc = glGetUniformLocation(ProgId, "LightColor")) != -1)
        glUniform3fv(loc, 1, &Lig->Color.X);
      if ((loc = glGetUniformLocation(ProgId, "LightDir")) != -1)
        glUniform3fv(loc, 1, &Lig->Dir.X);
      if ((loc = glGetUniformLocation(ProgId, "LightAtt")) != -1)
        glUniform3fv(loc, 1, &Lig->Att.X);
      if ((loc = glGetUniformLocation(ProgId, "LightCutOffAngle")) != -1)
        glUniform2fv(loc, 1, &Lig->CutOffAngle.X);
      if ((loc = glGetUniformLocation(ProgId, "LightCutOffDist")) != -1)
        glUniform2fv(loc, 1, &Lig->CutOffDist.X);

      /* Drawing light sources switch case */
      switch (Lig->Type)
      {
      case LIGHT_AMBIENT:
      case LIGHT_DIRECTIONAL:
        glBindVertexArray(0);
        glDrawArrays(GL_POINTS, 0, 1);
        break;
      case LIGHT_SPOT:
      case LIGHT_POINT:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glBindVertexArray(0);
        glPatchParameteri(GL_PATCH_VERTICES, 1);
        glDrawArrays(GL_PATCHES, 0, 1);
        glDisable(GL_CULL_FACE);
        break;
      }
    }
  }

  /* Test light sources draw */
  for (i = 0; i < Anim.NumOfLights; i++)
  {
    Lig = Lights[i];

    if (Lig->IsRender && (Lig->Type == LIGHT_POINT || Lig->Type == LIGHT_SPOT))
    {
      MATR WVP = Anim.cam.VP;
      VEC
        Right = CamRight(&(Anim.cam)),
        Up = CamUp(&(Anim.cam));

      ShaderApply(LightShdDraw);
      glUniform3fv(0, 1, &(Lig->Pos));
      glUniform2fv(1, 1, &(Lig->CutOffDist));
      glUniformMatrix4fv(2, 1, FALSE, &WVP);
      glUniform3fv(6, 1, &Right);
      glUniform3fv(7, 1, &Up);
      glUniform3fv(8, 1, &(Lig->Color));
      glActiveTexture(GL_TEXTURE0 + 6);
      glBindTexture(GL_TEXTURE_2D, LightGlowTex->TexId);
      glDrawArrays(GL_POINTS, 0, 1);
    }
  }

  /* Set blending to normal rendering */
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthMask(TRUE);
  glUseProgram(0);
} /* End of 'LightsRedraw' function */

/* Lights subsystem initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID LightsInit( VOID )
{
  LightShdAmbient = ShaderAdd("Ambient-light");
  LightShdPoint   = ShaderAdd("Point-light");
  LightShdDir     = ShaderAdd("Directional-light");
  LightShdSpot    = ShaderAdd("Spot-light");
  LightShdDraw    = ShaderAdd("Draw-light");
} /* End of 'LightsInit' function */

/* Lights subsystem deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID LightsClose( VOID )
{
  INT i;
  
  ShaderDelete(LightShdAmbient);
  ShaderDelete(LightShdPoint);
  ShaderDelete(LightShdDir);
  ShaderDelete(LightShdSpot);
  ShaderDelete(LightShdDraw);

  for (i = 0; i < Anim.NumOfLights; i++)
    free(Lights[i]);
} /* End of 'LightsClose' function */

/* END OF 'lightning.c' FILE */

