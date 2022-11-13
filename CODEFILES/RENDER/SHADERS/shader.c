/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : shader.c
 * PURPOSE     : Animation project.
 *               Shaders subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 13.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <dirent.h>

#include "../../comdef.h"
#include "shader.h"
#include "../render.h"

/* Default shader */
SHADER *ShaderDefault;

/* Read text from .glsl file function
 * ARGUMENTS:
 *   - name of file to read:
 *       CHAR *FileName;
 * RETURNS: 
 *   (CHAR *) read text content.
 */
CHAR * ReadShaderFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *text;

  /*
   * DIR *folder;
   * struct dirent *entry;
   * INT FILES = 0;
   *
   * folder = opendir(".");
   * if (folder == NULL)
   * {
   *   puts("Unable to read directory");
   *   return(1);
   * }
   * else
   *   puts("Directory is opened!");
   *
   * while ((entry = readdir(folder)))
   * {
   *   FILES++;
   *   printf("File %3d: %s\n", FILES, entry->d_name);
   * }
   *
   * closedir(folder);
   */
   
  //printf("%s\n", FileName);
  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL; 
  
  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((text = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(text, 0, flen + 1);

  /* Read text */
  fseek(F, 0, SEEK_SET);
  fread(text, 1, flen, F);

  fclose(F);
  
  //printf("%s\n", text);
  
  return text; 
} /* End of 'ReadShaderFile' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader files prefix (directory):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT ShaderLoad( CHAR *FileNamePrefix )
{
  INT
    i, res,
    shd_type[] =
    {
      GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
      GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
    };
  CHAR *suff[] = {"VERT", "CTRL", "EVAL", "GEOM", "FRAG"};
  INT NS = sizeof(suff) / sizeof(suff[0]);
  UINT prg = 0, shd[sizeof(suff) / sizeof(suff[0])] = {0};
  BOOL isok = TRUE;
  CHAR *txt;
  static CHAR buf[500];
  
  /* Load shaders */
  for (i = 0; isok && i < NS; i++)
  {
    /* Load text file */
    sprintf(buf, "USEFILES/SHADERS/%s/%s.GLSL", FileNamePrefix, suff[i]);
    if ((txt = ReadShaderFile(buf)) == NULL)
      continue;
    /* Create shader */
    if ((shd[i] = glCreateShader(shd_type[i])) == 0)
    {
      free(txt);
      isok = FALSE;
      break;
    }
    /* Attach text to shader  */
    glShaderSource(shd[i], 1, (const GLchar **)&txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i]);
    glGetShaderiv(shd[i], GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i], sizeof(buf), &res, buf);
      printf("SHADER LOG: %s\n", buf);
      isok = FALSE;
      break;
    }  
  }

  /* Create program */
  if (isok)
  {  
    if ((prg = glCreateProgram()) == 0)
      isok = FALSE;
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NS; i++)
        if (shd[i] != 0)
          glAttachShader(prg, shd[i]);

      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(buf), &res, buf);
        printf("PRG LOG: %s\n", buf);
        isok = FALSE;
      }
    }
  }

  /* Error handle */
  if (!isok)
  {
    for (i = 0; i < NS; i++)
      if (shd[i] != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i]);
        glDeleteShader(shd[i]);
      }
    if (prg != 0)
      glDeleteProgram(prg);
    return 0;
  }
  return prg;
} /* End of 'ShaderLoad' function */

/* Shader program deletion function.
 * ARGUMENTS:
 *   - shader program pointer:
 *       SHADER *Shd;
 * RETURNS: None.
 */
static VOID ShaderDelete( SHADER *Shd )
{
  UINT i, n, shds[5];

  if (Shd->PrgNo == 0)
    return;

  /* Obtain program shaders count */
  glGetAttachedShaders(Shd->PrgNo, 5, &n, shds);
  for (i = 0; i < n; i++)
  {
    glDetachShader(Shd->PrgNo, shds[i]);
    glDeleteShader(shds[i]);
  }
  glDeleteProgram(Shd->PrgNo);
} /* End of 'TNG_ShaderFree' function */

/* Correct shader number function.
 * ARGUMENTS:
 *   - shader pointer:
 *       SHADER *Shd;
 * RETURNS: 
 *   (UINT) Shader program Id.
 */
UINT ShaderApply( SHADER *Shd )
{
  if (Shd == NULL)
    Shd = ShaderDefault;
  glUseProgram(Shd->PrgNo);
  return Shd->PrgNo;
} /* End of 'ShadersApply' function */

/* END OF 'shader.c' FILE */

