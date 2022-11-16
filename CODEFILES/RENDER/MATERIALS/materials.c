/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : materials.c
 * PURPOSE     : Animation project.
 *               Materials subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 16.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <string.h>
#include "materials.h"

MATERIAL Materials[MATERIALS_COUNT];

/* Material add function.
 * ARGUMENTS:
 *   - name of material:
 *       CHAR *Name;
 *   - material parameter as a string:
 *       CHAR *Params;
 * RETURNS:
 *   (MATERIAL *) pointer to added material.
 */
MATERIAL * MaterialAdd( CHAR *Name, CHAR *Params )
{
  INT i, j;
  MATERIAL mtl;
 
  strcpy(mtl.Name, Name);

  /* Check if material is already loaded */
  for (i = 0; i < Anim.NumOfMaterials; i++)
  {  
    //printf("name is %s\n", mtl.Name);
    if (!strcmp(Materials[i].Name, mtl.Name))
      return &Materials[i];
    //printf("new mtl!\n");
  }

  /* Check if maximum count */
  if (Anim.NumOfMaterials == MATERIALS_COUNT)
    return NULL;

  /* The worst parser ever btw... */
  ARGS Args = Scanner(Params);
 
  if (Anim.Debug)
    printf("SCANNER:\n  Number of scans is %i\n", Args.NumOfScans);
  for (i = 0; i < Args.NumOfScans; i++)
  {
    FLT x = Args.Scan[i].Var[0],
        y = Args.Scan[i].Var[1],
        z = Args.Scan[i].Var[2];

    if (Anim.Debug)
    {
      printf("Scan %i - %s\n", i + 1, Args.Scan[i].Name);
      printf("  Scan string is \"%s\"\n", Args.Scan[i].Str);
    }

    if (strcmp(Args.Scan[i].Name, "Ka") == 0 && Args.Scan[i].NumOfComp == 3)
      mtl.Ka = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "Ka") == 0 && Args.Scan[i].NumOfComp == 1)
      mtl.Ka = VecSet(x, x, x);
    else if (strcmp(Args.Scan[i].Name, "Kd") == 0 && Args.Scan[i].NumOfComp == 3)
      mtl.Kd = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "Kd") == 0 && Args.Scan[i].NumOfComp == 1)
      mtl.Kd = VecSet(x, x, x);
    else if (strcmp(Args.Scan[i].Name, "Ks") == 0 && Args.Scan[i].NumOfComp == 3)
      mtl.Ks = VecSet(x, y, z);
    else if (strcmp(Args.Scan[i].Name, "Ks") == 0 && Args.Scan[i].NumOfComp == 1)
      mtl.Ks = VecSet(x, x, x);
    else if (strcmp(Args.Scan[i].Name, "Ph") == 0)
      mtl.Ph = x;
    else if (strcmp(Args.Scan[i].Name, "Trans") == 0)
      mtl.Trans = x;
    else if (strcmp(Args.Scan[i].Name, "Tex") == 0)
      for (j = 0; j < Args.Scan[i].NumOfStr; j++)
        mtl.Tex[j] = TextureAddFromFile(Args.Scan[i].Str[j]);
    else if (strcmp(Args.Scan[i].Name, "Shader") == 0)
      mtl.Shd = ShaderAdd(Args.Scan[i].Str[0]);
  }

  Materials[Anim.NumOfMaterials] = mtl;
  return &Materials[Anim.NumOfMaterials++];
} /* End of 'MaterialAdd' function */

/* Materials apply function.
 * ARGUMENTS:
 *   - material pointer:
 *       MATERIAL *Mtl;
 * RETURNS:
 *   (UINT) shader program Id.
 */
UINT MaterialApply( MATERIAL *Mtl )
{
  INT i, loc;
  UINT ProgId;

  /* NULL check */
  if (Mtl == NULL)
    return 0;
  
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

/* Material structure free function.
 * ARGUMENTS:
 *   - Material structure pointer:
 *       MATERIAL *Mtl
 * RETURNS: None.
 */
VOID MaterialDelete( MATERIAL *Mtl )
{
  INT i;

  for (i = 0; i < MATERIAL_TEXTURE_COUNT; i++)
  {
    if (Mtl->Tex[i] != NULL)
      TextureDelete(Mtl->Tex[i]);
  }

  ShaderDelete(Mtl->Shd);
} /* End of 'MaterialDelete' function */

/* Materials destructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID MaterialsDestructor( VOID )
{
  INT i;
  
  for (i = 0; i < MATERIALS_COUNT; i++)
    MaterialDelete(&Materials[i]);
} /* End of 'MaterialsDestructor' function */

/* END OF 'materials.c' FILE */

