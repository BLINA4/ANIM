/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : controller.h
 * PURPOSE     : Animation project.
 *               Controller subsystem header.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 11.10.2022.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#ifndef __controller_h_
#define __controller_h_

#include "../../comdef.h"

/* States of the mouse controller */
typedef enum mouse_state
{
  NONE,
  CLICK,
  PRESSED,
  RELEASE
} MOUSE_STATE;

/* Supported keyboard keys */
typedef enum key
{
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  ESCAPE,
  TAB,
  SPACE,
  LCTRL,
  LALT,
  RCTRL,
  RALT,
  CAPS,
  LSHIFT,
  RSHIFT,
  ENTER,
  BACKSPACE,
  SUPER,

  NUM_OF_KEYS
} KEY;

typedef struct tagCONTROLLER CONTROLLER;
struct tagCONTROLLER
{
  /* Mouse parameters */
  INT X, Y;                 /* Coordinates of the mouse        */ 
  INT ButtonNumber;         /* Number of the interacted button */
  MOUSE_STATE state;        /* State of the mouse              */

  /* Keyboard parameters */
  BOOL *keys, 
       *keys_prev,
       *keys_hold;          /* Array of all keys states        */
  DBL TimeOfLastCleanup;    /* Time of the last done cleanup   */
};

/* Controller initialization function.
 * ARGUMENTS: None.
 * RETURNS: 
 *   - Ready-for-use controller structure pointer
 *       (CONTROLLER *)
 */
CONTROLLER * ControllerInit( VOID );

/* Pressed key controller handle function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 *   - string of pressed key:
 *       CHAR *key_str
 * RETURNS: None.
 */
VOID ControllerKeyPress( CONTROLLER *cnt, CHAR *key_str );

/* Released key controller handle function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 *   - string of released key:
 *       CHAR *key_str
 * RETURNS: None.
 */
VOID ControllerKeyRelease( CONTROLLER *cnt, CHAR *key_str );

/* Cleaning up all keys state function.
 * ARGUMENTS:
 *   - controller structure pointer:
 *       CONTROLLER *cnt
 * RETURNS: None.
 */
VOID ControllerCleanup( CONTROLLER *cnt );

/* Controller deinitialization function.
 * ARGUMENTS: 
 *   - controller structure pointer
 *      CONTROLLER *cnt
 * RETURNS: None.
 */
VOID ControllerDestroy( CONTROLLER *cnt );

#endif /* __controller_h_ */

/* End of 'controller.h' file */

