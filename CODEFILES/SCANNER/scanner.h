/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : scanner.h
 * PURPOSE     : Animation project.
 *               Scanner subsystem header file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 16.11.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __scanner_h_
#define __scanner_h_

#include "../comdef.h"
 
/* Maximum size of scanning string */
#define MAX_NAME_SIZE 30

/* Maximum amount of variables */
#define MAX_VAR_SIZE 30

/* Maximum size of string */
#define MAX_STR_SIZE 20

/* Maximum size of string */
#define MAX_VAR_COUNT 20

/* Scanned from string variable structure */
typedef struct tagSCAN
{
  CHAR Name[MAX_NAME_SIZE];              /* Name of variable */

  INT NumOfStr;                          /* Number of scanned strings */
  INT NumOfComp;                         /* Number of components */
  FLT Var[MAX_VAR_COUNT];                /* Variable value */
  CHAR Str[MAX_VAR_COUNT][MAX_STR_SIZE]; /* Scanned strings */
} SCAN;

/* Arguments scanned from string texture */
typedef struct
{
  INT NumOfScans;          /* Amount of scanned from string variable */
  SCAN Scan[MAX_VAR_SIZE]; /* Scanned from string variable */
} ARGS;
 
/* Scanning from string function.
 * ARGUMENTS: 
 *   - String:
 *       CHAR *S.  
 * RETURNS: (ARGS) scanned variables.
 */
ARGS Scanner( CHAR *S );

#endif /* __scanner_h_ */

/* END OF 'scanner.h' FILE */
