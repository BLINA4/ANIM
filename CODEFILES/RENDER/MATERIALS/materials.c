/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : materials.c
 * PURPOSE     : Animation project.
 *               Materials subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 13.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <string.h>
#include "materials.h"

/* Default material instance */
MATERIAL *MaterialDefault;

/* Material add function.
 * ARGUMENTS:
 *   - name of material:
 *       CHAR *Name;
 *   - material parameter as a string:
 *       CHAR *Params;
 * RETURNS:
 *   (MATERIAL *) pointer to added material.
 */
static MATERIAL * MaterialAdd( CHAR *Name, CHAR *Params )
{
  INT i, j;
  MATERIAL mtl = *MaterialDefault;
  
  // Scanner is not yet implemented!
  // ARGS Args = Scanner(Params);
 
  strcpy(mtl.Name, Name);

  /* Scanner is not yet implemented!
   * for (i = 0; i < Args.NumOfScans; i++)
   * {
   *  FLT x = Args.Scan[i].Var[0],
   *      y = Args.Scan[i].Var[1],
   *      z = Args.Scan[i].Var[2];
   *
   *  if (strcmp(Args.Scan[i].Name, "Ka") == 0 && Args.Scan[i].NumOfComp == 3)
   *    mtl.Ka = VecSet(x, y, z);
   *  else if (strcmp(Args.Scan[i].Name, "Ka") == 0 && Args.Scan[i].NumOfComp == 1)
   *    mtl.Ka = VecSet(x, x, x);
   *  else if (strcmp(Args.Scan[i].Name, "Kd") == 0 && Args.Scan[i].NumOfComp == 3)
   *    mtl.Kd = VecSet(x, y, z);
   *  else if (strcmp(Args.Scan[i].Name, "Kd") == 0 && Args.Scan[i].NumOfComp == 1)
   *    mtl.Kd = VecSet(x, x, x);
   *  else if (strcmp(Args.Scan[i].Name, "Ks") == 0 && Args.Scan[i].NumOfComp == 3)
   *    mtl.Ks = VecSet(x, y, z);
   *  else if (strcmp(Args.Scan[i].Name, "Ks") == 0 && Args.Scan[i].NumOfComp == 1)
   *    mtl.Ks = VecSet(x, x, x);
   *  else if (strcmp(Args.Scan[i].Name, "Ph") == 0)
   *    mtl.Ph = x;
   *  else if (strcmp(Args.Scan[i].Name, "Trans") == 0)
   *    mtl.Trans = x;
   *  else if (strcmp(Args.Scan[i].Name, "Tex") == 0)
   *    for (j = 0; j < Args.Scan[i].NumOfStr; j++)
   *      mtl.Tex[j] = TNG()->TextureAddFromFile(Args.Scan[i].Str[j]);
   *  else if (strcmp(Args.Scan[i].Name, "Shader") == 0)
   *    mtl.Shd = TNG()->ShaderAdd(Args.Scan[i].Str[0]);
   * }
   */

  return &mtl;
} /* End of 'MaterialAdd' function */

/* Materials apply function.
 * ARGUMENTS:
 *   - material pointer:
 *       MATERIAL *Mtl;
 * RETURNS:
 *   (UINT) shader program Id.
 */
static UINT MaterialApply( MATERIAL *Mtl )
{
  INT i, loc;
  UINT ProgId;

  /* Correction of material */
  if (Mtl == NULL)
    Mtl = MaterialDefault;
  /* Shader applying */
  ProgId = ShaderApply(Mtl->Shd);
 
  if ((loc = glGetUniformLocation(ProgId, "Ka")) != -1)
    glUniform3fv(loc, 1, &Mtl->Ka.X);
  if ((loc = glGetUniformLocation(ProgId, "Kd")) != -1)
    glUniform3fv(loc, 1, &Mtl->Kd.X);
  if ((loc = glGetUniformLocation(ProgId, "Ks")) != -1)
    glUniform3fv(loc, 1, &Mtl->Ks.X);
  if ((loc = glGetUniformLocation(ProgId, "Ph")) != -1)
    glUniform1f(loc, Mtl->Ph);
  if ((loc = glGetUniformLocation(ProgId, "Trans")) != -1)
    glUniform1f(loc, Mtl->Trans);
  
  /* Texture apply */
  for (i = 0; i < MATERIAL_TEXTURE_COUNT; i++)
  {
    BOOL is = FALSE;
    static CHAR TexName[] = "IsTexture0";

    TexName[sizeof(TexName) - 2] = '0' + i;
    glActiveTexture(GL_TEXTURE0 + i);
    if (Mtl->Tex[i] != NULL)
    {
      is = TRUE;
      glBindTexture(Mtl->Tex[i]->IsCubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, Mtl->Tex[i]->TexId);
    }
    else
      glBindTexture(GL_TEXTURE_2D, 0);
    if ((loc = glGetUniformLocation(ProgId, TexName)) != -1)
      glUniform1i(loc, is);
  }

  return ProgId;
} /* End of 'MaterialApply' function */

/*
 */
VOID MaterialDelete( MATERIAL *Mtl )
{
  INT i;

  for (i = 0; i < MATERIAL_TEXTURE_COUNT; i++)
  {
    if (Mtl->Tex[i] != NULL)
      TextureDelete(Mtl->Tex[i]);
  }
} /* End of 'MaterialDelete' function */

/* END OF 'materials.c' FILE */
