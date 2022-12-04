/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : primitives.c
 * PURPOSE     : Animation project.
 *               Primitives subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 04.12.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __primitives_c_
#define __primitives_c_

#include "primitives.h"

#endif /* __primitives_c */

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
PRIM * PrimCreate( PRIM_TYPE Type, CHAR *VertexFormat, VOID *V, INT NumOfV, INT *Ind, INT NumOfI )
{
  INT i, type, attr_count = 0, all_size = 0, n;
  struct
  {
    INT Count;  /* Component count */
    INT Type;   /* Type of attributes */
    INT Offset; /* Offset to attributes in structure */
  } Attribs[16];
  VEC *P = V;
  PRIM *Pr;
 
  if ((Pr = malloc(sizeof(PRIM))) == NULL)
    return NULL;
  memset(Pr, 0, sizeof(PRIM));

  /* Parse attributes parameters */
  while (*VertexFormat != 0)
    if (*VertexFormat == 'i' || *VertexFormat == 'f')
    {
      type = *VertexFormat++;
      if (isdigit((BYTE)*VertexFormat))
        n = *VertexFormat++ - '0';
      else
        n = 1;
      if (attr_count < 16)
      {
        Attribs[attr_count].Count = n;
        Attribs[attr_count].Type = type == 'i' ? GL_UNSIGNED_INT : GL_FLOAT;
        Attribs[attr_count].Offset = all_size;
      }
      all_size += n * 4;
      attr_count++;
    }
    else
      VertexFormat++;

  //printf("Attribute count is %i\n", attr_count);

  if (all_size != 0 && V != NULL && NumOfV != 0)
  {
    /* Create OpenGL primitve */
    glGenBuffers(1, &(Pr->VBuf));
    glGenVertexArrays(1, &(Pr->VA));
 
    /* Vertexes */
    glBindVertexArray(Pr->VA);

    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, all_size * NumOfV, V, GL_STATIC_DRAW);

    /* Store and enable vertex attributes */
    for (i = 0; i < attr_count; i++)
    {
      glVertexAttribPointer(i, Attribs[i].Count, Attribs[i].Type, FALSE, all_size, (VOID *)Attribs[i].Offset);
      glEnableVertexAttribArray(i);
    }
    glBindVertexArray(0);

    if (Ind != NULL && NumOfI != 0)
    {
      glGenBuffers(1, &(Pr->IBuf));
      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, Ind, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      Pr->NumOfI = NumOfI;
    }
    else
      Pr->NumOfI = NumOfV;

    /* Evaluate minimum & maximum primitives */
    Pr->Min = Pr->Max = P[0];
    for (i = 1; i < NumOfV; i++)
    {
      Pr->Min = VecSet(COM_MIN(Pr->Min.X, P->X),
                       COM_MIN(Pr->Min.Y, P->Y),
                       COM_MIN(Pr->Min.Z, P->Z));
      Pr->Max = VecSet(COM_MAX(Pr->Max.X, P->X),
                       COM_MAX(Pr->Max.Y, P->Y),
                       COM_MAX(Pr->Max.Z, P->Z));
      P = (VEC *)((BYTE *)P + all_size);
    }
    Pr->Center = VecDivNum(VecAddVec(Pr->Min, Pr->Max), 2);
  }
  else
    Pr->NumOfI = NumOfV;

  Pr->Trans = MatrIdentity();
  Pr->Type = Type;

  //printf("Success!\n");
  return Pr;
} /* End of 'PrimCreate' function */

/* Draw primitive function.
 * ARGUMENTS:
 *   - primitive to draw:
 *       PRIM *Pr;
 *   - world CS matrix to work with:
 *       MATR World;
 * RETURNS: None.
 */
VOID PrimDraw( PRIM *Pr, MATR World )
{
  INT
    loc,
    PrimType =
      Pr->Type == PRIM_POINTS ? GL_POINTS :
      Pr->Type == PRIM_LINES  ? GL_LINES :
      Pr->Type == PRIM_STRIP  ? GL_TRIANGLE_STRIP :
      Pr->Type == PRIM_LINE_STRIP  ? GL_LINE_STRIP :
      Pr->Type == PRIM_LINE_STRIP_ADJACENCY ? GL_LINE_STRIP_ADJACENCY :
      Pr->Type == PRIM_PATCH ? GL_PATCHES :
      Pr->Type == PRIM_TRIMESH  ? GL_TRIANGLES : GL_POINTS;
  MATR
     W = MatrMulMatr(Pr->Trans, World),
     N = MatrTranspose(MatrInverse(W)),
     WVP = MatrMulMatr(W, Anim.cam.VP);
  UINT ProgId;
  VEC v;

  glLoadMatrixf(&WVP);

  ProgId = MaterialApply(Pr->Mtl);
 
  /* Setup transform coefficients */
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &WVP);
  if ((loc = glGetUniformLocation(ProgId, "MatrVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &Anim.cam.VP);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &W);
  if ((loc = glGetUniformLocation(ProgId, "MatrV")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &Anim.cam.ViewMatr);
  if ((loc = glGetUniformLocation(ProgId, "MatrN")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, &N);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &Anim.cam.Loc);
  v = CamRight(&Anim.cam);
  if ((loc = glGetUniformLocation(ProgId, "CamRight")) != -1)
    glUniform3fv(loc, 1, &v.X);
  v = CamUp(&Anim.cam);
  if ((loc = glGetUniformLocation(ProgId, "CamUp")) != -1)
    glUniform3fv(loc, 1, &v);
  v = CamDir(&Anim.cam);
  if ((loc = glGetUniformLocation(ProgId, "CamDir")) != -1)
    glUniform3fv(loc, 1, &v);
  if ((loc = glGetUniformLocation(ProgId, "CamProjDist")) != -1)
    glUniform1f(loc, Anim.cam.ProjDist);
  if ((loc = glGetUniformLocation(ProgId, "CamProjSize")) != -1)
    glUniform1f(loc, Anim.cam.ProjSize);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, Anim.SyncTime);
  if ((loc = glGetUniformLocation(ProgId, "FrameW")) != -1)
    glUniform1f(loc, Anim.W);
  if ((loc = glGetUniformLocation(ProgId, "FrameH")) != -1)
    glUniform1f(loc, Anim.H);
    
  glBindVertexArray(Pr->VA);

  if (Pr->Type == PRIM_PATCH)
    glPatchParameteri(GL_PATCH_VERTICES, Pr->NumOfI);
  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(PrimType, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  else
    glDrawArrays(PrimType, 0, Pr->NumOfI);
  
  glUseProgram(0);
  glBindVertexArray(0);
} /* End of 'PrimDraw' function */

/* Free memory and delete primitive function.
 * ARGUMENTS:
 *   - primitive to delete:
 *       PRIM *Pr;
 * RETURNS: None.
 */
VOID PrimFree( PRIM *Pr )
{
  if (Pr->VA != 0)
  {
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &(Pr->VA));
  }
  if (Pr->VBuf != 0)
    glDeleteBuffers(1, &(Pr->VBuf));
  if (Pr->IBuf != 0)
    glDeleteBuffers(1, &(Pr->IBuf));
} /* End of 'PrimFree' function */

/* END OF 'primitives.c' FILE */
