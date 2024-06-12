/*********************************************************************/
/* TEXT EDITOR FOR THE ATARI 520 ST 	 			     */
/*	started 8/11/85 K.H.   Copyright MONARCH DEVELOPMENT CORP.   */
/*********************************************************************/

/*********************************************************************/
/* INCLUDE FILES						     */
/*********************************************************************/

#include "obdefs.h"
#include "define.h"
#include "gemdefs.h"
#include "osbind.h"

/*********************************************************************/
/* DEFINES						   	     */
/*********************************************************************/


/*********************************************************************/
/* EXTERNALS						   	     */
/*********************************************************************/

extern int	gl_apid;
extern long	rem_line();
extern long	ins_byte();
extern long	del_byte();

/*********************************************************************/
/* GLOBAL VARIABLES					   	     */
/*********************************************************************/

long	ibmkey;		/* scan code as well as character */
int	keyc;		/* keycode returned by event-keyboard */
int	scanc;		/* scancode returned */
int	kbdst;		/* keyboard status variable */
int	cursor;		/* cursor position */
int	line;		/* line cursor is on screen */
int	currchar;	/* absolute char in memory */
int	memline;	/* absolute line in memory */
int	lastchar;	/* last character in file */
int	lastline;	/* last line in file */
int	oldline;	/* old line number before we started messing around */
int	i,j;		/* variable counter you know the usual stuff */
int	temp;		/* storage for moving stuff around */
int	inson;		/* flag for insert mode 1=on 0=off */
int	rate;		/* rate of blink of cursor */
int 	attrib;		/* attribute of cursor */
int	last_len;	/* last length of string stripped for spaces */
int	tempcol;	/* temporary column storage */
int	temprow;	/* temporary row storage */
char    chrstr[1];      /* character to string conversion */
 
int     tof;            /* top of form or screen pointer */
int     bof;            /* bottom of form or screen pointer */
int 	phys_handle;	/* physical workstation handle */
int 	handle;		/* virtual workstation handle */

int	contrl[12];
int	intin[128];
int	ptsin[128];
int	intout[128];
int	ptsout[128];	/* storage wasted for idiotic bindings */

int work_in[11];	/* Input to GSX parameter array */
int work_out[57];	/* Output from GSX parameter array */
int pxyarray[10];	/* input point array */

char	file[65535];	/* file storage in memory */
char    templine[81];   /* line of input */
char    outline[81];    /* line for copy function */
  
/****************************************************************/
/* open virtual workstation					*/
/****************************************************************/
open_vwork()
{
int i;
	for(i=0;i<10;work_in[i++]=1);
	work_in[10]=2;
	handle=phys_handle;
	v

	move.w	$c(a7),a0	* number of bytes into a0
	add.l	a1,a0		* plus address of string
del_loop:
	move.b	(a0)+,(a1)+
	dbra	d0,del_loop	* move as much as requested
del_exit:
	rts

*
*	ins_byte inserts bytes specified by calling routine
*

_ins_byte:
	clr.l	d0
	suba.l	a0,a0		* clear address registers
	suba.l	a1,a1		* clear registers for long operations

	move.w	$c(a7),d0	* get # bytes to insert
	cmp.w	#0,d0		* no bytes to insert so exit routine
	beq.s	ins_exit	* bypass routine of inserting bytes
	move.w	$8(a7),d0	* end of file
	move.w	$a(a7),a0	* offset into file
	sub.w	a0,d0		* number of bytes

	suba.l	a0,a0		* clear address register
	move.w	$8(a7),a0	* end of file once again
	move.w	$c(a7),a1	* number of bytes to insert
	adda.w  a0,a1		* how many to move in memory
	move.l	$4(a7),d1	* address of file buffer

	adda.l	d1,a0		* add to offset of move begin
	adda.l	d1,a1		* here also except destination
ins_loop:
	move.b	-(a0),-(a1)
	dbra	d0,ins_loop	* move as much as requested
ins***********************/
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
  exit_obj = form_do(form_addr,0);
  form_dial(FMD_SHRINK,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_FINISH,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  undo_obj(ASHICED,ABBUT,SELECTED);	  /* deselct button on about shiced */
}

/**************************************gaddr(R_TREE,COLOR,&sel_obj);
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

/******************************************************************************************************/

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

int	tree_num,
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

  for (i=xwork1+1;i<(xwork1+wwork1);i=i+grid_width)
    for (j=ywork1+1;j<(ywork1+hwork1);j=j+grid_height)
     { if ((mx>=i) && (mx<=i+(grid_width-1)))
	 if ((my>=j) && (my<=j+(grid_height-1)))
           { set_color(((i-(xwork1+1))/grid_width),((j-(ywork1+1))/grid_height)
				,plot_color);
	     hide_mouse();
             draw_grid(i,j,((i-(xwork1+1))/grid_width),
			((j-(ywork1+1))/grid_height)ct_p1 = (arrp1/4);		/* actual pointer = arrp1/4 (bits per color) */
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

   drive = Dgetdrv();    
   pathname[0] = (drive + 'A');		/* set drive >= 'A' <= 'P' */ 
   pathname[1] = ':';
   pathname[2] = '\\';		/* add ":\" to string */
   pathname[3] = '*';
   pathname[4] = '.';
   pathname[5] = 'S'; 
   pathname[6] = 'H'; 
   pathname[7] = 'P';		/* add "*.SHP" to pathname */
   pathname[8] = 0;


   filename[0] = 0;

   fsel_input(pathname,filename,&fs_exitbut);	/* get file name */

   *exit_but = fs_exitbut;	/* return with exit button */
       
}

/************************************************************************/
/* add the file name to the path name					*/
/************************************************************************/

add_filename()

{ i = strlen(pathname);
  while (i && ((pathname[i-1]it(MAINMENU,MO3,CHECKED);

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
	{ Fread(file_handle,800L,color_arr