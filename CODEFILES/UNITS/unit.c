/***************************************************************
 * Copyleft 2020
 *   C programmer
 ***************************************************************/

/* FILE NAME   : unit.c
 * PURPOSE     : Animation project.
 *               Units handling functions
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 22.03.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include "../comdef.h"
#include "unit.h"

/* Unit init function
 * ARGUMENTS:
 *   - unit self-pointer:
 *       UNIT *Uni;
 *   - animation context:
 *       ANIM *Ani;
 * RETURNS: None.
 */
static VOID UnitInit( UNIT *Uni, ANIM *Ani )
{
    
} /* End of 'UnitInit' function */

/* Unit close function
 * ARGUMENTS:
 *   - unit self-pointer:
 *       UNIT *Uni;
 *   - animation context:
 *       ANIM *Ani;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT *Uni, ANIM *Ani )
{

} /* End of 'UnitClose' fucntion */

/* Unit response function
 * ARGUMENTS:
 *   - unit self-pointer:
 *       UNIT *Uni;
 *   - animation context:
 *       ANIM *Ani;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT *Uni, ANIM *Ani )
{

} /* End of 'UnitResponse' function */

/* Unit render function
 * ARGUMENTS:
 *   - unit self-pointer:
 *       UNIT *Uni;
 *   - animation context:
 *       ANIM *Ani;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT *Uni, ANIM *Ani )
{

} /* End of 'UnitRender' function */

/* Unit create function
 * ARGUMENTS:
 *   - size of unit:
 *       INT Size;
 * RETURNS: 
 *   (UNIT *) pointer to unit.
 */
UNIT * AnimUnitCreate( INT Size )
{
  UNIT *Uni;

  /* We allocate memory for unit */
  if (Size < sizeof(UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;

  memset(Uni, 0, Size);

  Uni->Init = UnitInit;
  Uni->Close = UnitClose;
  Uni->Response = UnitResponse;
  Uni->Render = UnitRender;
  return Uni;
} /* End of 'AnimUnitCreate' function */

/* END OF 'unit.c' FILE */

