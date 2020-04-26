/***************************************************************
 * Copyleft 2020
 *   Junior C programmer presents (lol)
 ***************************************************************/

/* FILE NAME   : main.c
 * PURPOSE     : Animation project.
 *               Main file of project.
 * PROGRAMMER  : Andrey Shayda.
 * LAST UPDATE : 22.03.2020.
 *
 * All parts of this file may be changed without agreement
 *   of programmer if you give credits to author.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "comdef.h"

/* Time variable */
DBL SyncTime;

/* Window & context parameters */
Display                 *dpy;                                                             /*  Display pointer             */
Window                  root;                                                             /*  Root pointer to window      */
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None }; /*  Attributes of GL            */
XVisualInfo             *vi;                                                              /*  Visual info of XServer      */
Colormap                cmap;                                                             /*  Colormap attribute          */
XSetWindowAttributes    swa;                                                              /*  Set main window attributes  */
Window                  win;                                                              /*  Window code                 */
GLXContext              glc;                                                              /*  OpenGL context              */
XWindowAttributes       gwa;                                                              /*  Total attributes of window  */ 
XEvent                  xev;                                                              /*  Event structure             */

/* Main reshape handle function
 * ARGUMENTS: None.
 * RETURNS: None.
 */ 
VOID ReshapeFunc( INT W, INT H )
{
  DBL size = 0.1, rx = size, ry = size;
 
  if (W > H)
    rx *= (DBL)W / H;
  else
    ry *= (DBL)H / W;
 
  glViewport(0, 0, W, H);
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, size, 100);
 
  gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
} /* End of 'ReshapeFunc' function */

/* Main display handle function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DisplayFunc( VOID )
{
  glClearColor(0.3, 0.5, 0.7, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotated(90 * SyncTime, 0, 0, 1);
  glTranslated(-0.5, -0.5, 0);
  glColor3d(1, 1, 0);
  glRectd(0, 0, 1, 1);
  glPopMatrix();

  glFinish();
} /* End of 'DisplayFunc' function */

/* Close all entries function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DestroyProgramm( VOID )
{
  glXMakeCurrent(dpy, None, NULL);
  glXDestroyContext(dpy, glc);
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  exit(0);  
} /* End of 'DestroyProgramm' function */

/* Check pending events function
 * ARGUMENTS: None.
 * RETURN: None.
 */
VOID CheckEvents( VOID )
{
  /* Key pressed event check */  
  if (XCheckWindowEvent(dpy, win, KeyPressMask, &xev))
  {
    char *key_string = XKeysymToString(XkbKeycodeToKeysym(dpy, xev.xkey.keycode, 0, 0));

    if (!strncmp(key_string, "Esc", 3))
      DestroyProgramm();  
  }    

  /* Resize event check */
  if (XCheckWindowEvent(dpy, win, ExposureMask, &xev))
  {
    XGetWindowAttributes(dpy, win, &gwa);  
    ReshapeFunc(gwa.width, gwa.height);  
  } 
} /* End of 'CheckEvents' function */

/* Timer dummy function (refactor later)
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID Timer( VOID )
{
  SyncTime = (DBL)clock() / CLOCKS_PER_SEC;
} /* End of 'Timer' function */

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) programm return code.
 */
INT main( VOID )
{
  /* First call to XLib */
  dpy = XOpenDisplay(NULL);
 
  if (dpy == NULL)
  {
	  printf("\n\tcannot connect to X server\n\n");
    exit(0);
  }
  
  /* Setting default root hook to window */
  root = DefaultRootWindow(dpy);

  /* Choosing visual attributes that fullfill hardware specifications */
  vi = glXChooseVisual(dpy, 0, att);

  if (vi == NULL) 
  {
	  printf("\n\tno appropriate visual found\n\n");
    exit(0);
  }
  else
	  printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */

  /* Create colormap for window */
  cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

  /* Set window attributes */
  swa.colormap = cmap;
  swa.event_mask = ExposureMask | KeyPressMask;

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
  win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
  XMapWindow(dpy, win);
  XStoreName(dpy, win, "TEST BUILD");

  /* Create & Bind GL context to the window */
  glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
  glXMakeCurrent(dpy, win, glc);

  /* We enable depth buffer testing */
  glEnable(GL_DEPTH_TEST);
  
  /* Event loop */
  /* We dont use, cause we need animation all-time 
   *  while (1)
   *  {
   *    XNextEvent(dpy, &xev);
   *
   *    if (xev.type == Expose)
   *    {
   *      XGetWindowAttributes(dpy, win, &gwa);
   *      ReshapeFunc(gwa.width, gwa.height);    
   *      DisplayFunc();
   *      glXSwapBuffers(dpy, win);
   *    }
   *    else if (xev.type == KeyPress)
   *    {
   *      if (xev.xkey.keycode == 9)
   *      {
   *        glXMakeCurrent(dpy, None, NULL);
   *        glXDestroyContext(dpy, glc);
   *        XDestroyWindow(dpy, win);
   *        XCloseDisplay(dpy);
   *        exit(0);
   *      }
   *    }
   *  }
   */  

  while (1)
  {
    CheckEvents();  
    Timer();
    DisplayFunc();
    glXSwapBuffers(dpy, win);
  }
} /* End of 'main' function */

/* END OF 'main.c' FILE */

