/* 
 * Motif
 *
 * Copyright (c) 1987-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
*/ 
/* 
 * HISTORY
*/ 
#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: PanedWin5.c /main/4 1995/07/13 19:07:12 drk $"
#endif
#endif


#include <testlib.h>

/* Performs tests of initially specifying parent's and children's sizes
   for a Paned Window.
*/
#define CASES		4
#define	BUTTONS		3
#define B_WIDTH		100
#define B_HEIGHT	100
#define W_MARGIN	25

/* Internal routines. */
static void DoTheButtons();
static void DoTheWindows();
static void ReportSize();

void  main(argc, argv)
int argc;
char **argv;
{
    int  	n, i;
    Arg			args[MAX_ARGS], PWargs[MAX_ARGS];
    int			PWn;

    CommonTestInit(argc, argv);

    n = 0;
    XtSetArg(args[n], XmNgeometry, "150x150+0+0"); n++;
    XtSetValues(Shell1, args, n);

    XtRealizeWidget(Shell1);
    
    /* Do all cases for 1 to BUTTONS. */
    for (i = 0; i < BUTTONS; i++) 
      {
	/* Paned window with nothing set. */
	PWn = 0;
	DoTheButtons(i, PWargs, PWn);

	/* Paned window with width set. */
	PWn = 0;
	XtSetArg(PWargs[PWn], XmNwidth, B_WIDTH + W_MARGIN); PWn++;
	DoTheButtons(i, PWargs, PWn);

	/* Paned window with height set. */
	PWn = 0;
	XtSetArg(PWargs[PWn], XmNheight, (B_HEIGHT + W_MARGIN) * i ); PWn++;
	DoTheButtons(i, PWargs, PWn);

	/* Paned window with both set. */
	PWn = 0;
	XtSetArg(PWargs[PWn], XmNwidth, B_WIDTH + W_MARGIN); PWn++;
	XtSetArg(PWargs[PWn], XmNheight, (B_HEIGHT + W_MARGIN) * i ); PWn++;
	DoTheButtons(i, PWargs, PWn);

      }
    
    CommonPause();
    CommonPause();

    XtAppMainLoop(app_context);
}

static void DoTheButtons(num, PWargs, PWn)
int 	num;
Arg	PWargs[];
int	PWn;
{
  Arg          	PBargs[MAX_ARGS];
  int		PBn;
  
  /* Nothing set. */
  PBn = 0;
  
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);
  
  /* Width set. */
  PBn = 0;
  XtSetArg(PBargs[PBn], XmNwidth, B_WIDTH); PBn++;
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);

  /* Height set. */
  PBn = 0;
  XtSetArg(PBargs[PBn], XmNheight, B_HEIGHT); PBn++;
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);

  /* Both set. */
  PBn = 0;
  XtSetArg(PBargs[PBn], XmNwidth, B_WIDTH); PBn++;
  XtSetArg(PBargs[PBn], XmNheight, B_HEIGHT); PBn++;
  DoTheWindows(num, PWargs, PWn, PBargs, PBn);

}

static void FlushEvents()
{
  XEvent event;

  while (XtAppPending(app_context)) {
    XtAppNextEvent(app_context, &event);
    XtDispatchEvent(&event);
  }
}

static void DoTheWindows(num, PWargs, PWn, PBargs, PBn)
     int	num;
     Arg	PWargs[];
     int	PWn;
     Arg	PBargs[];
     int	PBn;
{


  int	i;
  Widget	PW, PB[3];
  
  PW = XmCreatePanedWindow(Shell1, "PW", PWargs, PWn);
  for (i = 0; i <= num; i++)
    {
      PB[i] = XmCreatePushButton(PW, "PB", PBargs, PBn);
      XtManageChild(PB[i]);
    }
  XtManageChild(PW);
  FlushEvents();
  for (i=0; i <= num; i++) ReportSize(PB[i], "pushbutton %d - ", i+1);
  ReportSize(PW, "panedwindow - ", 0);
  printf("\n");
  CommonPause();
  XtDestroyWidget(PW);
}

static void ReportSize (w, type_string, arg)
     Widget w;
     char *type_string;
     int arg;
{
  int	n;
  Arg		args[2];
  Dimension	width, height;
    
  n = 0;
  XtSetArg(args[n], XmNwidth, &width); n++;
  XtSetArg(args[n], XmNheight, &height); n++;
  XtGetValues(w, args, n);
  
  if (arg != 0)
    printf(type_string, arg);
  else
    printf(type_string);
  printf("%dX%d\n", (int)width, (int)height);
}

