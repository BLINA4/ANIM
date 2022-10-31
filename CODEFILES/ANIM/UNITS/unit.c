/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/
 
/* FILE NAME   : unit.c
 * PURPOSE     : Animation project.
 *               Units system file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.03.2021.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdlib.h>
#include <string.h>
#include "unit.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.  
 */
static VOID UnitInit( UNIT *Unit, ANIM *Anim )
{

} /* End of 'UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitClose( UNIT *Unit, ANIM *Anim )
{

} /* End of 'UnitClose' function */

/* Unit response to event function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitResponse( UNIT *Unit, ANIM *Anim )
{

} /* End of 'UnitResponse' function */

/* Unit drawing function.
 * ARGUMENTS:
 *   - self-pointer to this object:
 *       UNIT *Unit;
 *   - animation context:
 *       ANIM *Anim;
 * RETURNS: None.
 */
static VOID UnitRender( UNIT *Unit, ANIM *Anim )
{

} /* End of 'UnitRender' function */

/* Unit creation function.
 * ARGUMENTS: 
 *   - structure size in bytes:
 *       INT Size
 * RETURNS: 
 *   (UNIT *) pointer to created unit.
 */
UNIT * AnimUnitCreate( INT Size )
{
  UNIT *Unit;

  if (Size < sizeof(UNIT) || (Unit = malloc(Size)) == NULL)
    return NULL;
  memset(Unit, 0, Size);

  Unit->Init = UnitInit;
  Unit->Close = UnitClose;
  Unit->Response = UnitResponse;
  Unit->Render = UnitRender;

  return Unit;
} /* End of 'AnimUnitCreate' function */

/* END OF 'unit.c' FILE */

