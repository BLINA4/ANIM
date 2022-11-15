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

#include "../comdef.h"
 
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

/* END OF 'scanner.c' FILE */

