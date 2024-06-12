/*********************************************************************/
/* SHICED SHAPE & ICON EDITOR FOR THE ST			     */
/*	started 8/31/85 K.H.                                         */
/*********************************************************************/

/*********************************************************************/
/* INCLUDE FILES						     */
/*********************************************************************/

#include "obdefs.h"
#include "define.h"
#include "gemdefs.h"
#include "osbind.h"
#include "c:\se\se.h"

/*********************************************************************/
/* DEFINES						   	     */
/*********************************************************************/

#define WI_KIND	 (NAME)
#define WI_2KIND (NAME | UPARROW | DNARROW | LFARROW | RTARROW)

#define NO_WINDOW (-1)

#define MIN_WIDTH  (2*gl_wbox)
#define MIN_HEIGHT (3*gl_hbox)

#define ROW_UP 2	/* WINDOW ARROW DEFINITIONS */
#define ROW_DOWN 3
#define COL_LEFT 6
#define COL_RIGHT 7
#define BUTTON1 1
#define BUTTON2 2

/*********************************************************************/
/* EXTERNALS						   	     */
/*********************************************************************/

extern int	gl_apid;

/*********************************************************************/
/* GLOBAL VARIABLES					   	     */
/*********************************************************************/

FDB	undo_mfdb,screen_mfdb;		/* form definition blocks */

int	gl_hchar;
int	gl_wchar;
int	gl_wbox;
int	gl_hbox;	/* system sizes */

long    gl_menu;

int	exit_obj;	/* exit object selected */
int 	phys_handle;	/* physical workstation handle */
int 	handle;		/* virtual workstation handle */
int	wi_handle;	/* window handle */
int     wi2_handle;     /* second window handle */
int	wi3_handle;	/* third window handle */
int	top_window;	/* handle of topped window */

int     cursor,line;    /* where to put stuff */
int	xdesk,ydesk,hdesk,wdesk;
int	xold,yold,hold,wold;
int	xwork1,ywork1,hwork1,wwork1;	/* desktop and work areas */
int     xwork2,ywork2,hwork2,wwork2;
int     xwork3,ywork3,hwork3,wwork3;

int	xwind1,ywind1,wwind1,hwind1;	/* window sizes */
int	xwind2,ywind2,wwind2,hwind2;
int	xwind3,ywind3,wwind3,hwind3;

int	grid_width,grid_height;		/* grid height and width */

int	fo_gx,fo_gy,fo_gw,fo_gh;	/* form global XYWH */
long	form_addr;			/* forms address global */
 
int	msgbuff[8];	/* event message buffer */
int	keycode;	/* keycode returned by event-keyboard */
int	mx,my;		/* mouse x and y pos. */
int	mbutton;	/* button state actual */
int	butdown;	/* button state tested for, UP/DOWN */
int	ret;		/* dummy return variable */

int	hidden;		/* current state of cursor */

int	fulled;		/* current state of window */

int	contrl[12];
int	intin[128];
int	ptsin[128];
int	intout[128];
int	ptsout[128];	/* storage wasted for idiotic bindings */

int work_in[11];	/* Input to GSX parameter array */
int work_out[57];	/* Output from GSX parameter array */
int pxyarray[10];	/* input point array */

int     i,j;            /* general or admiral purpose counterz */

int	ftsave[4];	/* file-type save array */

OBJECT	*sel_obj; 	/* pointer to object array */

unsigned int	plot_color;		/* current plotting color */
unsigned int	temp_color;		/* current plotting color temp */

unsigned int	color_array[10][40];	/* shape array */
unsigned int	temp_array[11][40];	/* temporary shape array */
unsigned int	mask_array[10][40];	/* masks data array */


char	path[64] = "?:\\";	/* path name to selected drive */

char	pathname[70];	/* full path name and drive */

char	filename[13];	/* file name to load or save */

int	fs_button;	/* file selection button */
int	error;

char	undo_area[32768];	/* save for operations */

int	sh_changed;	/* flag for shape changed */
int	max_color;	/* maximum color number for resolution */

int	main_xor,mask_xor;	/* whether shapes are xored or not */
int	mask_chek;		/* are we editing the mask? */

char	base_name[27] = "@xxxxxxxxxxxxxxxxxxxxxxxxx";

int	comp_width,comp_height;	/* compiled height and width of shape */

char	c_header[34] = "/* ShIcEd Form Definition Data */";
char	cdef_w[16] = "#define SHAP_W ";		/* c file header info */
char	cdef_h[16] = "#define SHAP_H ";
char	cdef_s[18] = "#define DATASIZE ";
char	cstruc1[23] = "int image[DATASIZE] = ";
char	cstruc2[22] = "int mask[DATASIZE] = ";
char	cstruc3[3] = "{ ";
char	cstruc4[3] = "};";

char	com_spc[3] = ", ";		/* comma and a space */
char	ret_lf[3] = "\015\012";		/* return and linefeed */

char	s_header[33] = "* ShIcEd Form Definition Block ";
char	s_dcb[8] = "\011dc.b\011";
char	shap_str[30];
int	drive;

/****************************************************************/
/*  GSX UTILITY ROUTINES.					*/
/****************************************************************/

hide_mouse()
{
	if(! hidden){
		graf_mouse(M_OFF,0x0L);
		hidden=TRUE;
	}
}

show_mouse()
{
	if(hidden){
		graf_mouse(M_ON,0x0L);
		hidden=FALSE;
	}
}

/****************************************************************/
/* set clipping rectangle					*/
/****************************************************************/
set_clip(x,y,w,h)
int x,y,w,h;
{
int clip[4];
	clip[0]=x;
	clip[1]=y;
	clip[2]=x+w;
	clip[3]=y+h;
	vs_clip(handle,1,clip);
}

/****************************************************************/
/* find and redraw all clipping rectangles			*/
/****************************************************************/
do_redraw(wind_hand,xc,yc,wc,hc)
int wind_hand,xc,yc,wc,hc;
{
GRECT t1,t2;

	hide_mouse();
	wind_update(TRUE);
	t2.g_x=xc;
	t2.g_y=yc;
	t2.g_w=wc;
	t2.g_h=hc;
	wind_get(wind_hand,WF_FIRSTXYWH,&t1.g_x,&t1.g_y,&t1.g_w,&t1.g_h);
	while (t1.g_w && t1.g_h) {
	  if (rc_intersect(&t2,&t1))
	    wind_rest(t1.g_x,t1.g_y,t1.g_w,t1.g_h);
	  wind_get(wind_hand,WF_NEXTXYWH,&t1.g_x,&t1.g_y,&t1.g_w,&t1.g_h);
	}
	wind_update(FALSE);
	show_mouse();
}

/****************************************************************/
/*  write writes the line with a CR and LF parameters are 	*/
/*  a string to be passed.                               	*/
/****************************************************************/

write(str)
char  str[81];
{ int 	i,j;			/* need to save row before out string */
  i = 0;
  vs_curaddress(handle,line + 1,cursor + 1);
  while ((str[i] != 0) && (str[i] != 13))
   { Bconout(2,str[i]);
     cursor = cursor + 1;	/* next character output advance */
     vs_curaddress(handle,line + 1,cursor + 1);
     i = i + 1;
   }
 }

/****************************************************************/
/*  write_num writes the number specified in ascii format 	*/
/****************************************************************/

write_num(in_num)
int	in_num;
{ int 	i,j,k;
  char out_num[5];

  j = 0;
  for (i=12;i>=0;i = i - 4)
   { k = ((in_num >> i) & 0x000f);
     out_num[j] = k > 9 ? 'A'+k-10 : '0' + k;
     j = j + 1;
   }
  out_num[5] = 0;
  write(out_num);
 }

/****************************************************************/
/* open virtual workstation					*/
/****************************************************************/
open_vwork()
{
int i,xres,yres;

	for(i=0;i<10;work_in[i++]=1);
	work_in[10]=2;
	handle=phys_handle;
	v_opnvwk(work_in,&handle,work_out);

	max_color = work_out[13]-1;

	screen_mfdb.fd_w = work_out[0] + 1;
	screen_mfdb.fd_h = work_out[1] + 1;
	screen_mfdb.fd_wdwidth = screen_mfdb.fd_w >> 4;
	screen_mfdb.fd_stand = FALSE;

	vq_extnd(handle,1,work_out);

	screen_mfdb.fd_nplanes = work_out[4];
	screen_mfdb.fd_addr = Logbase();	/* set up form definition */

	undo_mfdb.fd_w = screen_mfdb.fd_w;
	undo_mfdb.fd_h = screen_mfdb.fd_h;	/* copy width and height */
	undo_mfdb.fd_wdwidth = screen_mfdb.fd_wdwidth;
	undo_mfdb.fd_stand = FALSE;
	undo_mfdb.fd_nplanes = screen_mfdb.fd_nplanes;
	undo_mfdb.fd_addr = &undo_area;		/* set up undo area form */
}


/****************************************************************/
/* open window							*/
/****************************************************************/
open_window()
{
  wind_calc(0,WI_2KIND,xwork2,ywork2,wwork2,hwork2,
		       &xwind2,&ywind2,&wwind2,&hwind2);

  xwind2 = ((xwork1 + wwork1)+(grid_width*2));
  ywind2 = ydesk;

  wi2_handle=wind_create(WI_2KIND,xwind2,ywind2,wwind2,hwind2);
  wind_set(wi2_handle,WF_NAME," Shape ",0,0);
  wind_open(wi2_handle,xwind2,ywind2,wwind2,hwind2);
  wind_get(wi2_handle,WF_WORKXYWH,&xwork2,&ywork2,&wwork2,&hwork2);

  open_third();		/* go open third window */
 
  wind_calc(0,WI_KIND,xwork1,ywork1,wwork1,hwork1,
			&xwind1,&ywind1,&wwind1,&hwind1);

  xwind1 = xdesk;
  ywind1 = ydesk;

  wi_handle=wind_create(WI_KIND,xwind1,ywind1,wwind1,hwind1);
  wind_set(wi_handle, WF_NAME," Grid Shape ",0,0);
  wind_open(wi_handle,xwind1,ywind1,wwind1,hwind1);
  wind_get(wi_handle,WF_WORKXYWH,&xwork1,&ywork1,&wwork1,&hwork1);

 
}


/****************************************************************/
/*		Accessory Init. Until First Event_Multi		*/
/****************************************************************/
main()
{
	appl_init();

        hidden = FALSE;			/* mouse not hidden */

	for (i=0;i<10;i++)
          for (j=0;j<40;j++)
	   { color_array[i][j] = 0;
	      mask_array[i][j] = 0;
	   }

	wi_handle = 0;
	
	drive = Dgetdrv();
	Dgetpath(&path[2],drive+1);
	path[0] = (drive + 'A');	/* set drive >= 'A' <= 'P' */ 

	strcat(path,"\\*.SHP");

	phys_handle=graf_handle(&gl_wchar,&gl_hchar,&gl_wbox,&gl_hbox);
	wind_get(0, WF_WORKXYWH, &xdesk, &ydesk, &wdesk, &hdesk);

	grid_width = (xdesk+wdesk)/64;
	grid_height = (ydesk+hdesk)/50;	/* set grid boxes width and height */

	xwork1 = xdesk;
	ywork1 = ydesk;
	wwork1 = (grid_width * 40);	/* width of window one */
	hwork1 = (grid_height * 40);

	xwork2 = ((xwork1 + wwork1)+(grid_width*2));
	ywork2 = ydesk;
	wwork2 = 50;
	hwork2 = 50;			/* width of window two */ 

        open_vwork();

	main_xor = FALSE;
	mask_xor = FALSE;		/* set flags to false */

        error = load_rsrc();			/* load the resource file */

	if (!error)
	{ wind_update(TRUE);
          menu_bar(gl_menu,TRUE);

          open_window();

	  draw_1wind();			/* draw first window */
	  draw_2wind();			/* second window */

          hide_mouse();			/* for clearing of workstation */

	  wind_save();			/* save screen for redraws */

	  show_mouse();			/* reshow mouse for audience */

	  graf_mouse(ARROW,0x0L);		/* put up menu and windows */

          fulled=TRUE;
          butdown=TRUE;
	  sh_changed = FALSE;

	  wind_update(FALSE);
	  multi();
	  menu_bar(gl_menu,FALSE);
	}      

        exit_prog();
        v_clsvwk(handle);			/* lets say bye bye */
        appl_exit();
}


/****************************************************************/
/* dispatches all accessory tasks				*/
/****************************************************************/
multi()
{
int event;

      do {
     event = evnt_multi(MU_MESAG | MU_TIMER,
			0,0,3,
			0,0,0,0,0,
			0,0,0,0,0,
			msgbuff,1,0,&mx,&my,&mbutton,&ret,&keycode,&ret);

	graf_mkstate(&mx,&my,&mbutton,&ret);

	wind_update(TRUE);

	if (mbutton & 1)
	  click_point();
        if (mbutton & 2)
          { temp_color = plot_color;
	    plot_color = 0;
	    click_point();
	    plot_color = temp_color;
	  }

	if (event & MU_MESAG)
	  switch (msgbuff[0]) {

	  case WM_REDRAW:
	    do_redraw(msgbuff[3],msgbuff[4],msgbuff[5],msgbuff[6],msgbuff[7]);
	    if (msgbuff[3] == wi2_handle)
	      { hide_mouse();
		vsf_interior(handle,2);
		vsf_color(handle,0);
		vsf_style(handle,8);

		set_clip(msgbuff[4],msgbuff[5],msgbuff[6],msgbuff[7]);
		ptsin[0] = xwork2+(wwork2+1);
		ptsin[1] = ywork2+(hwork2+1);
		ptsin[2] = xwind2+(wwind2-2);
		ptsin[3] = ywind2+(hwind2-2);
		v_bar(handle,ptsin);
		vs_clip(handle,0,ptsin);

		show_mouse();
	      }
	    break;	

	  case WM_NEWTOP:
	  case WM_TOPPED:
	    if (msgbuff[3] == wi_handle)
	     wind_set(wi_handle,WF_TOP,0,0,0,0);	/* set first window */
	    if (msgbuff[3] == wi2_handle)
              wind_set(wi2_handle,WF_TOP,0,0,0,0);
	    if (msgbuff[3] == wi3_handle)
	      { wind_set(wi3_handle,WF_TOP,0,0,0,0);
		upd_3wind();
	      }

	  break;

	  case WM_ARROWED:		/* one of the arrows */
	    if (msgbuff[3] == wi2_handle)
	      switch (msgbuff[4])
		{ case ROW_UP:
		    up_shape();		/* scroll shape up */
		    break;
	
	  	  case ROW_DOWN:	/* scroll shape down */
		    dn_shape();
		    break;

		  case COL_RIGHT:	/* scroll shape right */
		    right_shape();
		    break;

		  case COL_LEFT:	/* scroll shape left */
		    left_shape();
		    break;

		}
	    break;
	    
	   
	  case MN_SELECTED:

            menu_tnormal(gl_menu,msgbuff[3],1); /* normal title */
	    wind_get(wi_handle,WF_TOP,&i,&ret,&ret,&ret);
	    if ((i!=wi_handle) && (i!=wi2_handle))
	      {wind_set(wi2_handle,WF_TOP,0,0,0,0);
	       wind_set(wi_handle,WF_TOP,0,0,0,0);
	      }
	    switch (msgbuff[4])
             { case MD1:		/* about shiced... */
                 out_asci();
                 break;

	       case MF1:
		 get_path(&fs_button);		/* and filename to load */
 		 add_filename();	/* add real filename */ 
		 if (fs_button)
		   load_shape();	/* go load shape */
		 break;

	       case MF2:
		 get_path(&fs_button);	/* get path and filename */
		 add_filename();
		 if (fs_button)
		   save_shape();	/* save the shape to disk */
		 break;

	       case MF3:		/* compile shape */
		 compile();
		 break;

	       case MF4:		/* new shape */
		 undo_obj_(MAINMENU,MO4,CHECKED);
		 if (mask_chek)
		   mask_xor = FALSE;
		 else
		   main_xor = FALSE;
		 draw_1wind();
		 draw_2wind();		/* redraw windows */
		 draw_3wind();
		 hide_mouse();
		 wind_save();		/* save new screen */
		 show_mouse();
		 for (i=0;i<10;i++)	/* clear storage array */
		   for (j=0;j<40;j++)
		     color_array[i][j] = 0;

		 break;

	       case MO2:		/* color select */
		 color_sel();
                 break;

	       case MO1:		/* file type output */
		 file_type();
                 break;
               
	       case MA1:		/* flip shape upside down */
		 flip_shape();
		 break;

	       case MA2:		/* mirror shape right to left */
		 mirr_shape();
		 break;

	       case MA3:		/* rotate shape left */
		 rot_left();
		 break;

	       case MA4:		/* rotate shape right */
		 rot_right();
		 break;

	       case MO3:		/* mask edit */
		 mask_edit();
		 break;

	       case MO4:
		 xor_shape();		/* xor shape for mask edit */
		 break;

	       case MO5:
		 for (i=0;i<10;i++)
		   for (j=0;j<40;j++)
		     color_array[i][j] = mask_array[i][j];
		 if (mask_chek)
		   { mask_xor = main_xor;
		     if (mask_xor)
		       do_obj(MAINMENU,MO4,CHECKED);
		     else
		       undo_obj(MAINMENU,MO4,CHECKED);
		   }
		 else
		   { main_xor = mask_xor;
		     if (mask_xor)
		       do_obj(MAINMENU,MO4,CHECKED);
		     else
		       undo_obj(MAINMENU,MO4,CHECKED);
		   }
		 redr_shape();
		 break;

             }  /* switch msgbuff[4] */


	   break;

        }  /* switch msgbuff[0] */
 


	wind_update(FALSE);
 
      }while(!((event & MU_MESAG) && (msgbuff[4] == MF5)));


}

/**********************************************************************/
/*                       draw_grid and blank background               */
/**********************************************************************/
draw_1wind()
 {

   hide_mouse();    
   vsf_interior(handle,2);
   vsf_color(handle,0);
   vsf_style(handle,8);
   
   ptsin[0] = xwork1;
   ptsin[1] = ywork1;
   ptsin[2] = xwork1+wwork1-1;
   ptsin[3] = ywork1+hwork1-1;
   v_bar(handle,ptsin);
 
   vsl_type(handle,1);            /* select line with no breaks */
   vsl_width(handle,1);           /* one pixel wide ok? */
   vsl_color(handle,1);           /* opposite color of screen */
 
   for (i=xwork1;i<(xwork1+(wwork1-1));i=i+grid_width)
     { ptsin[0] = i;
       ptsin[1] = ywork1;
       ptsin[2] = i;
       ptsin[3] = ywork1+(hwork1-1);
       v_pline(handle,2,ptsin);
     }
 
   for (i=ywork1;i<(ywork1+(hwork1-1));i=i+grid_height)
     { ptsin[0] = xwork1;
       ptsin[1] = i;
       ptsin[2] = xwork1+(wwork1-1);
       ptsin[3] = i;
       v_pline(handle,2,ptsin);
     }
 
  show_mouse();
 
 }

/**********************************************************************/
/*                       draw_shape and blank background              */
/**********************************************************************/
draw_2wind()
 {    
   hide_mouse();
   vsf_interior(handle,2);
   vsf_color(handle,0);
   vsf_style(handle,8);
   
   ptsin[0] = xwork2;
   ptsin[1] = ywork2;
   ptsin[2] = xwork2+wwork2-1;
   ptsin[3] = ywork2+hwork2-1;
   v_bar(handle,ptsin);

   ptsin[0] = xwork2+(wwork2+1);
   ptsin[1] = ywork2+(hwork2+1);
   ptsin[2] = xwind2+(wwind2-2);
   ptsin[3] = ywind2+(hwind2-2);
   v_bar(handle,ptsin);

   show_mouse();
 
 }


/************************************************************************/
/*           set up relation between parents and children 		*/
/************************************************************************/

int	load_rsrc()

{ graf_mouse(HOURGLASS,0X0L);
  if (!rsrc_load(&"SE.RSC"))
   { graf_mouse(ARROW,0x0L);
     form_alert(1,&"[3][ Whoops! | SE.RSC| File Not Found][Abort]");
     return(TRUE);
   }
  rsrc_gaddr(R_TREE,MAINMENU,&gl_menu);
  graf_mouse(ARROW,0x0L);
  return(FALSE);
}

/************************************************************************/
/*    outputs the form for about shape-icon-editor			*/
/************************************************************************/

out_asci()

{ out_form(ASHICED);
  exit_obj = (form_do(form_addr,0) & 0xff);
  form_dial(FMD_SHRINK,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_FINISH,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  undo_obj(ASHICED,ABBUT,SELECTED);	  /* deselct button on about shiced */
}

/************************************************************************/
/*    outputs the form for color selection             			*/
/************************************************************************/

color_sel()

{ out_form(COLOR);
  do
  {  exit_obj = (form_do(form_addr,0) & 0xff);
     if (exit_obj != COLBUT)
       { rsrc_gaddr(R_TREE,COLOR,&sel_obj); /* get address of tree */
         sel_obj = sel_obj + exit_obj;
         plot_color = (sel_obj->ob_spec & 0xfL);
	 if (plot_color > max_color)
	   plot_color = 1;
     	 rsrc_gaddr(R_TREE,COLOR,&sel_obj);
     	 sel_obj = sel_obj + CURRCOL;
     	 sel_obj->ob_spec = ((sel_obj->ob_spec & 0xfffffff0L) | plot_color);

         objc_draw(form_addr,CURRCOL,0,fo_gx,fo_gy,fo_gw,fo_gh);
        }
   }
    while (exit_obj != COLBUT);
  form_dial(FMD_SHRINK,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_FINISH,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  undo_obj(COLOR,COLBUT,SELECTED);
}

/************************************************************************/
/*    outputs the form for file type selection         			*/
/************************************************************************/

file_type()

{ ftsave[0] = get_bit(FILETYPE,CBUT,SELECTED);  /* get bit and save it */
  ftsave[1] = get_bit(FILETYPE,ABUT,SELECTED);  /* get all for saving */
  ftsave[2] = get_bit(FILETYPE,ICBUT,SELECTED); /* incase of cancel */
  ftsave[3] = get_bit(FILETYPE,IMBUT,SELECTED);

  out_form(FILETYPE);			/* output form okidata? */
  exit_obj = (form_do(form_addr,0) & 0xff); 
  form_dial(FMD_SHRINK,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_FINISH,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);

  if (exit_obj == FTCAN)		/* cancel changes to form */
   { if (ftsave[0] == 1)
       do_obj(FILETYPE,CBUT,SELECTED);
     else
       undo_obj(FILETYPE,CBUT,SELECTED);
     if (ftsave[1] == 1)
       do_obj(FILETYPE,ABUT,SELECTED);
     else
       undo_obj(FILETYPE,ABUT,SELECTED);
     if (ftsave[2] == 1)
       do_obj(FILETYPE,ICBUT,SELECTED);
     else
       undo_obj(FILETYPE,ICBUT,SELECTED);
     if (ftsave[3] == 1)
       do_obj(FILETYPE,IMBUT,SELECTED);
     else
       undo_obj(FILETYPE,IMBUT,SELECTED);
   }
  undo_obj(FILETYPE,FTOK,SELECTED);
  undo_obj(FILETYPE,FTCAN,SELECTED);
}

/************************************************************************/
/*    outputs the form for selection             			*/
/************************************************************************/

out_form(form_num)

  int	form_num;
{ rsrc_gaddr(R_TREE,form_num,&form_addr);
  form_center(form_addr,&fo_gx,&fo_gy,&fo_gw,&fo_gh);
  form_dial(FMD_START,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_GROW,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  objc_draw(form_addr,ROOT,MAX_DEPTH,fo_gx,fo_gy,fo_gw,fo_gh);
}

/************************************************************************/
/*    deselects the objects specified bits            			*/
/************************************************************************/

undo_obj(tree_num,obj_num,wh_bit)

int	tree_num,obj_num,wh_bit;

{ rsrc_gaddr(R_TREE,tree_num,&sel_obj); /* get address of tree */
  sel_obj = sel_obj + obj_num;
  sel_obj->ob_state = (sel_obj->ob_state & ~wh_bit); /* set bit = 0 */
}

/************************************************************************/
/*    selects the objects specified bits            			*/
/************************************************************************/

do_obj(tree_num,obj_num,wh_bit)

int	tree_num,obj_num,wh_bit;

{ rsrc_gaddr(R_TREE,tree_num,&sel_obj); /* get address of tree */
  sel_obj = sel_obj + obj_num;
  sel_obj->ob_state = (sel_obj->ob_state | wh_bit); /* set bit = 1 */
}

/************************************************************************/
/*    gets the current bit settings of specified bit   			*/
/************************************************************************/

int	get_bit(tree_num,obj_num,wh_bit)

int	tree_num,obj_num,wh_bit;

{ rsrc_gaddr(R_TREE,tree_num,&sel_obj); /* get address of tree */
  sel_obj = sel_obj + obj_num;
  return((sel_obj->ob_state & wh_bit));	/* get bit of ob_state */
}

/***********************************************************************/
/*   draws the colored box in the grid and plots dot for shape         */
/***********************************************************************/

draw_grid(x,y,arr1,arr2)

int	x,y,arr1,arr2;		/* x and y location and array pointers */

{ unsigned int color;			/* color of array */

  get_color(arr1,arr2,&color);	/* get color from array */

  vsf_style(handle,8);		/* solid fill area */
  vsf_color(handle,color);	/* color of fill area */
  vsf_interior(handle,2);	/* solid interior */
  vsf_perimeter(handle,FALSE);	/* no line for fill outer edge */

  ptsin[0] = x;			/* set cooridantes of bar fill */
  ptsin[1] = y;
  ptsin[2] = x+(grid_width-2);
  ptsin[3] = y+(grid_height-2);

  v_bar(handle,ptsin);		/* go draw box on grid */

}

/***********************************************************************/
/*   draws the colored dot for shape 				       */
/***********************************************************************/

draw_point(x,y,arr1,arr2)

int	x,y,arr1,arr2;		/* x and y location and array pointers */

{ unsigned int color;			/* color of array */

  get_color(arr1,arr2,&color);	/* get color from array */

  vsm_color(handle,color);	/* color of fill area */

  ptsin[0] = arr1+(xwork2+5);		/* on normal shape window */
  ptsin[1] = arr2+(ywork2+5);		/* ditto */

  v_pmarker(handle,1,ptsin);		/* plot one dot ok? */

}

/************************************************************************/
/* 		gets the color from the array				*/
/************************************************************************/
  
get_color(arrp1,arrp2,col_ptr)

int 	arrp1,arrp2;		/* array pointers */
unsigned int	*col_ptr;

{  int	act_p1,act_p2;
   unsigned int ret_color;

   act_p1 = (arrp1/4);		/* actual pointer = arrp1/4 (bits per color) */
   act_p2 = (arrp1 % 4);	/* remainder for offset into array */
   
   ret_color = (color_array[act_p1][arrp2] & (0x0f << (act_p2 * 4)));

   ret_color = (ret_color >> (act_p2 * 4));

  /* damn tuff to explain but anyway ---- since colors take 4 bits (nibble)  */
  /* and data types are limited used unsigned integer which is 4 nibbles and */
  /* so formula is = divide by 4 number of bits that needs to be extracted   */
  /* which gives array pointer ex. 20th element of array == int(20/4) == 5th */
  /* element of array.  Now to get the 4 bits from the integer we take the   */
  /* the remainder and shift left the constant f000 which is 4 bits and &    */
  /* those puppies out of there - well thats it probably lost most people    */
  /* at this point. */

   *col_ptr = ret_color;
}

/**************************************************************************/
/*   plot the point or unplot it whether it is plotted or what            */
/**************************************************************************/

click_point()

{ unsigned int	color;

  wind_get(wi_handle,WF_TOP,&i,&ret,&ret,&ret);
  
  if (i != wi_handle)
    return;

  for (i=xwork1+1;i<(xwork1+wwork1);i=i+grid_width)
    for (j=ywork1+1;j<(ywork1+hwork1);j=j+grid_height)
     { if ((mx>=i) && (mx<=i+(grid_width-1)))
	 if ((my>=j) && (my<=j+(grid_height-1)))
           { set_color(((i-(xwork1+1))/grid_width),((j-(ywork1+1))/grid_height)
				,plot_color);
	     hide_mouse();
             draw_grid(i,j,((i-(xwork1+1))/grid_width),
			((j-(ywork1+1))/grid_height));
             draw_point(i,j,((i-(xwork1+1))/grid_width),
			((j-(ywork1+1))/grid_heigt));
	     wind_save();
	     show_mouse();
           }
     }
}
           
/**************************************************************************/
/*   plot the point or unplot it whether it is plotted or what            */
/**************************************************************************/

set_color(arrp1,arrp2,color)

int	arrp1,arrp2;
unsigned int color;

{ int	act_p1,act_p2;

   act_p1 = (arrp1/4);		/* actual pointer = arrp1/4 (bits per color) */
   act_p2 = (arrp1 % 4);	/* remainder for offset into array */


   color_array[act_p1][arrp2] = (color_array[act_p1][arrp2]
     & ~(0x0f << (act_p2 * 4)));
   
   color_array[act_p1][arrp2] = (color_array[act_p1][arrp2]
     | (color << (act_p2 * 4)));
}

/*************************************************************************/
/* flips the shape over not to difficult				 */
/*************************************************************************/

flip_shape()

{ unsigned int 	temp_array;

  for (i=0;i<20;i++)
   { for (j=0;j<10;j++)
      { temp_array = color_array[j][39-i];
        color_array[j][39-i] = color_array[j][i];
	color_array[j][i] = temp_array;
      }
    }

   redr_shape();	/* redraw the shape */

}
  
/************************************************************************/
/*   exit_prog cleans up for exiting					*/
/************************************************************************/
exit_prog()

{
  if (wi_handle != 0)
    { wind_close(wi_handle);		/* close first window */
      wind_delete(wi_handle);
      wind_close(wi2_handle);		/* close second window */
      wind_delete(wi2_handle);
      wind_close(wi3_handle);		/* close third window */
      wind_delete(wi3_handle);
    }
}

/*************************************************************************/
/* mirror shape mirrors the shape sideways				 */
/*************************************************************************/

mirr_shape()

{ unsigned int 	temp_array,color;
  
  for (i=0;i<20;i++)
   { for (j=0;j<40;j++)
      { get_color(i,j,&color);		/* get left side of shape */
        temp_array = color;		/* store it temporarily */
	get_color(39-i,j,&color);	/* get right side of shape */
	set_color(i,j,color);		/* set left side to right side */
	set_color(39-i,j,temp_array);	/* set right side to temporary */
      }
    }

   redr_shape();
}

/************************************************************************/
/* get the current path and put together a string			*/
/************************************************************************/

get_path(exit_but)

int	*exit_but;		/* exit button */

{  int	drive,fs_exitbut;


   filename[0] = 0;

   fsel_input(path,filename,&fs_exitbut);	/* get file name */

   pathname[0] = '\0';
   strcat(pathname,path);

   *exit_but = fs_exitbut;	/* return with exit button */
       
}

/************************************************************************/
/* add the file name to the path name					*/
/************************************************************************/

add_filename()

{ i = strlen(pathname);
  while (i && ((pathname[i-1] != '\\') && (pathname[i-1] != ':')))
    i--;
  pathname[i] = 0;		/* strip off file in path name */
  strcat(pathname,filename);    /* add real file name to path */
}

/************************************************************************/
/* load the shape into memory and redraw shape to screen		*/
/************************************************************************/

load_shape()

{ int	file_handle,ch_bit;

  graf_mouse(HOURGLASS,0x0L);		/* busy as a bee shape */

  ch_bit = get_bit(MAINMENU,MO3,CHECKED);

  file_handle = Fopen(pathname,0);	/* open a file if possible */

  if (file_handle < 0)
   { graf_mouse(ARROW,0x0L);		/* got an error so handle it */
     form_alert(1,&"[3][ Rats! | Disk Error. ][ OK ]");
   }
  else
    { if (ch_bit)
	{ Fread(file_handle,800L,mask_array);	/* else load 400 bytes */
      	  Fread(file_handle,800L,color_array);
	  Fread(file_handle,2L,&mask_xor);
	  Fread(file_handle,2L,&main_xor);
	}
      else
	{ Fread(file_handle,800L,color_array);	/* else load 400 bytes */
      	  Fread(file_handle,800L,mask_array);
	  Fread(file_handle,2L,&mask_xor);
	  Fread(file_handle,2L,&main_xor);
	}
      Fclose(file_handle);
      graf_mouse(ARROW,0x0L);
    }
  if (mask_chek)
    { if (mask_xor)
        do_obj(MAINMENU,MO4,CHECKED);
      else
        undo_obj(MAINMENU,MO4,CHECKED);
    }
  else
    { if (main_xor)
        do_obj(MAINMENU,MO4,CHECKED);
      else
        undo_obj(MAINMENU,MO4,CHECKED);
    }
  draw_1wind();		/* redraw the windows and the shape */
  draw_2wind();
  draw_3wind();
  redr_shape();
 
}
      
/************************************************************************/
/* save the shape into memory and redraw shape to screen		*/
/************************************************************************/

save_shape()

{ int	file_handle,exit_but,ch_bit;

  graf_mouse(HOURGLASS,0x0L);

  file_handle = Fopen(pathname,0);	/* open shape file */

  if (file_handle > 0)
   { graf_mouse(ARROW,0x0L);		/* if file then remind person */
     exit_but = form_alert(
     2,&"[2][ Pay Attention! | File exists | Overwrite it? ][ Cancel| OK ]");
   }
  if (exit_but == 2)
    { file_handle = -1;
      graf_mouse(HOURGLASS,0x0L);
    }
  if (file_handle < 0)
    { file_handle = Fcreate(pathname,0);	/* else create the file */
      ch_bit = get_bit(MAINMENU,MO3,CHECKED);
      if (ch_bit)
        { Fwrite(file_handle,800L,mask_array);
	  Fwrite(file_handle,800L,color_array);
	  Fwrite(file_handle,2L,&mask_xor);
	  Fwrite(file_handle,2L,&main_xor);
	}
      else
	{ Fwrite(file_handle,800L,color_array);
	  Fwrite(file_handle,800L,mask_array);
	  Fwrite(file_handle,2L,&mask_xor);
	  Fwrite(file_handle,2L,&main_xor);
	}
      Fclose(file_handle);			/* write to it and close */
      graf_mouse(ARROW,0x0L);
    }
}
      
/************************************************************************/
/* strlen gets the string length of the string				*/
/************************************************************************/

int	strlen(str_ptr)

char	*str_ptr;

{ int	ret_count;

  ret_count = 0;		/* set length to zero */

  while (*str_ptr != 0)		/* do while not end of string */
   { ret_count++;
     str_ptr++;			/* advance return count and index */
   }
  
  return(ret_count);

}

/**************************************************************************/
/* strcat concats 2 strings together					  */
/**************************************************************************/

strcat(str1_ptr,str2_ptr)

char	*str1_ptr,*str2_ptr;

{ int	st1len,st2len,counter;

  st1len = strlen(str1_ptr);		/* get the string lengths */
  st2len = strlen(str2_ptr);

  str1_ptr = str1_ptr + st1len;

  for (counter=0;counter<=st2len;counter++)
    { *str1_ptr = *str2_ptr;
      str1_ptr++;			/* concat the suckers together */
      str2_ptr++;
    }
}

/************************************************************************/
/* redraw shape in box and grid						*/
/************************************************************************/

redr_shape()

{ wind_set(wi_handle,WF_TOP,0,0,0,0);
  do_redraw(wi_handle,xwork1,ywork1,wwork1,hwork1);

  hide_mouse();

  for (i=xwork1+1;i<(xwork1+wwork1);i=i+grid_width)
    for (j=ywork1+1;j<(ywork1+hwork1);j=j+grid_height)
      { draw_grid(i,j,((i-(xwork1+1))/grid_width),
			((j-(ywork1+1))/grid_height));	
	draw_point(i,j,((i-(xwork1+1))/grid_width),
			((j-(ywork1+1))/grid_height));
      }

  wind_save();

  show_mouse();

}
