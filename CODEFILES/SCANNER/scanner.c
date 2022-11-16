/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : scanner.c
 * PURPOSE     : Animation project.
 *               Scanner subsystem code file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 16.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdio.h>

#include "../comdef.h"
#include "scanner.h"

/* Go to needed in string elememt function.
 * ARGUMENTS: 
 *   - string:
 *       CHAR *S;
 *   - needed symbol:
 *       CHAR ch;
 *   - buffer string:
 *       CHAR *buf,
 *   - first symbol:
 *       INT Symb.
 * RETURNS: (INT) amount of scanned symbols.
 */
static INT GoToSymblol( CHAR *S, CHAR ch, CHAR *buf, INT Symb )
{
  INT i = Symb, NumOfCh = 0;

  while (S[i] != 0 && S[i] != ch)
  {
    buf[i] = S[i];
    i++;
    NumOfCh++;
  }

  return NumOfCh;
} /* End of 'GoToSymblol' function */

/* Scanning from string function.
 * ARGUMENTS: 
 *   - String:
 *       CHAR *S.  
 * RETURNS:
 *   (ARGS) scanned variables.
 */
ARGS Scanner( CHAR *S )
{
  INT
    i = 0, NumOfScans = 0, j = 0, k = 1, m = 0,
    l, NumOfSymb, read, NumOfStr = 0, flag = 1, cnt;
  CHAR buf[100] = {0}, str[100] = {0};
  ARGS Args = {0};

  /*
   * Example of scanning string:
   *  "Pos(10,2.6,8.1),Tex(tex.txt,tx.txt)x2,Att(1,0,0),CutOfDist(0,3)x7,CutOfAngle(5,10)"
   */

  for (l = 0; l < MAX_VAR_COUNT; l++)
    Args.Scan[i].Var[l] = 0;

  while (*S != 0)
  {
    /* If first pass read without ','*/
    if (flag)
      S += NumOfSymb = GoToSymblol(S, '(', buf, 0);
    else
      S += NumOfSymb = GoToSymblol(S, '(', buf, 1);
    sprintf(Args.Scan[i].Name, "%s", buf);

    /* Read variables */
    read = sscanf(S, "(%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f)",
      &Args.Scan[i].Var[0], &Args.Scan[i].Var[1], &Args.Scan[i].Var[2], &Args.Scan[i].Var[3],
      &Args.Scan[i].Var[4], &Args.Scan[i].Var[5], &Args.Scan[i].Var[6], &Args.Scan[i].Var[7],
      &Args.Scan[i].Var[8], &Args.Scan[i].Var[9], &Args.Scan[i].Var[10], &Args.Scan[i].Var[11],
      &Args.Scan[i].Var[12], &Args.Scan[i].Var[13], &Args.Scan[i].Var[14], &Args.Scan[i].Var[15],
      &Args.Scan[i].Var[16], &Args.Scan[i].Var[17], &Args.Scan[i].Var[18], &Args.Scan[i].Var[19]);
    Args.Scan[i].NumOfComp = read;
    NumOfScans++;
    memset(buf, 0, sizeof(buf));
    NumOfSymb = GoToSymblol(S, ')', buf, 0) + 2;

    /* If strings in */
    if (read == 0)
    {
      m = 0;
      sprintf(str, "%s)", buf);
      while (str[k] != 0)
      {
        while (str[k] != ',' && str[k] != ')')
        {
          Args.Scan[i].Str[j][m] = str[k];
          m++;
          k++;
        }
        NumOfStr++;
        if (str[k] != 0)
          m = 0, j++, k++;
      }
      for (m = 0; m <= NumOfSymb; m++)
        str[m] = 0;
      m = j = 0;
      k = 1;
    }
    for (m = 0; m <= NumOfSymb; m++)
      buf[m] = 0;
 
    S += NumOfSymb - 1;

    /* Read repeated scans */
    if (S[0] == 'x')
    {
      S++;
      sscanf(S, "%i", &cnt);
      for (m = 0; m < cnt - 1; m++)
      {
        Args.Scan[NumOfScans] = Args.Scan[NumOfScans - 1];
        NumOfScans++, i++;
      }
      if (m < 10)
        S++;
      else
        S += 2;
      m = 0;
    }
    S++;
    Args.Scan[i].NumOfStr = NumOfStr;
    NumOfStr = 0;
    i++;
    NumOfSymb = 0;
    for (l = 0; l < read; l++)
      Args.Scan[i].Var[l] = 0;
  }
  Args.NumOfScans = NumOfScans;

  return Args;
} /* End of 'Scanner' function */

/* END OF 'scanner.c' FILE */

