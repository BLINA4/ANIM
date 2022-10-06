/***************************************************************
 * Copyleft 2020
 *   C programmer 
 ***************************************************************/

/* FILE NAME   : anim.c
 * PURPOSE     : Animation project.
 *               Animation system implementation file.
 * PROGRAMMER  : BLIN4.
 * LAST UPDATE : 07.03.2021.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */

#include <stdlib.h>
#include <stdio.h>

#include "anim.h"

/* Animation context structure */
ANIM Anim;

/* Animation initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimInit( VOID )
{
  /* First call to XLib */
  Anim.dpy = XOpenDisplay(NULL);

  Anim.att[0] = GLX_RGBA;
  Anim.att[1] = GLX_DEPTH_SIZE;
  Anim.att[2] = 24;
  Anim.att[3] = GLX_DOUBLEBUFFER;
  Anim.att[4] = None;

  if (Anim.dpy == NULL)
  {
    printf("\n\tcannot connect to X server\n\n");
    exit(0);
  }

  /* Setting default root hook to window */
  Anim.root = DefaultRootWindow(Anim.dpy);

  /* Choosing visual attributes that fullfill hardware specifications */
  Anim.vi = glXChooseVisual(Anim.dpy, 0, Anim.att);

  if (Anim.vi == NULL)
  {
    printf("\n\tno appropriate visual found\n\n");
    exit(0);
  }
  else
    printf("\n\tvisual %p selected\n", (void *)(Anim.vi)->visualid); /* %p creates hexadecimal output like in glxinfo */

  /* Create colormap for window */
  Anim.cmap = XCreateColormap(Anim.dpy, Anim.root, Anim.vi->visual, AllocNone);

  /* Set window attributes */
  Anim.swa.colormap = Anim.cmap;
  Anim.swa.event_mask = ExposureMask | KeyPressMask;

  /* Create window */
  /* The arguments are : 
   * 
   * The display pointer (dpy), which determines on which display the window shall be created.
   *   It is indeed possible to call XOpenDisplay twice (or more often) within a program, each time getting a new Display pointer.
   *   This allows the program to send graphical output not only to the local computer, but as well to a remote one.
   * 
   * The handle of the root window is passed as the parent window. Each window- except the root window- has a parent; a window whose parent is the root window is often called top-level window. 
   *   top-level windows have decorations (title bar, minimize-/maximize-button etc.), which are provided by the window-manager 
   *   (in linux there are quite a lot of different window managers. some make your windows look like you are running win95 or mac os).
   * 
   * The initial x-/y-position for the window is (0/0). The initial window position always refers to the parent window (which is the root window here). 
   *   It should be mentioned that these values are ignored by most windows managers, which means that top-level windows maybe placed somewhere else on the desktop.
   *   But if you create a child window within a top-level window, these values are used.
   * 
   * The next values are window width and height (600x600 pixels).
   * 
   * The border width is set to 0, like the initial window position, it is meaningless for top-level windows, too.
   * 
   * Then comes the depth, which is defined in the XVisualInfo structure *vi.
   * 
   * The window type is InputOutput. There are other types, but you will probably never need them.
   * 
   * The next parameter is a bitwise-OR of the values CWColormap and CWEventMask. This tells the X server which fields of the XSetWindowAttributes structure swa
   *   were filled by the program and should be taken into account when creating the window. Finally, a pointer to the structure itself is passed.
   *
   * XCreateWindow returns a window id (which is actually just a long int).
   */
  Anim.win = XCreateWindow(Anim.dpy, Anim.root, 0, 0, 1920, 1080, 0, Anim.vi->depth, InputOutput, Anim.vi->visual, CWColormap | CWEventMask, &(Anim.swa));
  XMapWindow(Anim.dpy, Anim.win);
  XStoreName(Anim.dpy, Anim.win, "TEST BUILD");

  /* Create & Bind GL context to the window */
  Anim.glc = glXCreateContext(Anim.dpy, Anim.vi, NULL, GL_TRUE);
  glXMakeCurrent(Anim.dpy, Anim.win, Anim.glc);

  Anim.Run = 1;
  RndInit();
} /* End of 'AnimInit' function */

/* Main animation loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimRun( VOID )
{
  INT i = 0;

  while (Anim.Run)
  {
    RndCheckEvents(&Anim);
    RndTimer(&Anim);

    glClearColor(0.3, 0.5, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  
    for (i = 0; i < Anim.NumOfUnits; i++)
      Anim.Units[i]->Response(Anim.Units[i], &Anim);
    RndStart();
    for (i = 0; i < Anim.NumOfUnits; i++)
      Anim.Units[i]->Render(Anim.Units[i], &Anim);
    RndEnd();
  
    glXSwapBuffers(Anim.dpy, Anim.win);
    glFinish();
  }
} /* End of 'AnimRun' function */

/* Animation closing function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AnimClose( VOID )
{
  INT i;

  for (i = 0; i < Anim.NumOfUnits; i++)
    Anim.Units[i]->Close(Anim.Units[i], &Anim);

  RndClose();
  glXMakeCurrent(Anim.dpy, None, NULL);
  glXDestroyContext(Anim.dpy, Anim.glc);
  XDestroyWindow(Anim.dpy, Anim.win);
  XCloseDisplay(Anim.dpy);
} /* End of 'AnimClose' function */

/* Unit adding function.
 * ARGUMENTS:
 *   - Unit structure pointer:
 *       UNIT *Unit;
 * RESPONSE: None.
 */
VOID AnimUnitAdd( UNIT *Unit )
{
  if (Anim.NumOfUnits < MAX_UNITS)
    Anim.Units[Anim.NumOfUnits++] = Unit, Unit->Init(Unit, &Anim);
} /* End of 'AnimUnitAdd' function */

/* END OF 'anim.c' FILE */

