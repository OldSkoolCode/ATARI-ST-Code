`  �  � 
&              *O.|  *m  - Э Э м   / /? ?< JNA��   N�  �/<    NA"/ 0< �NBNuB��ȓ�0/ �|  g&0o 
�H2o ��0	��2o 
"/ ��0o ���Q���NuB��ȓ�0/ �|  g$0/ 0o 
�H��0o 2o ��"/ ���� Q���NuNV��>� NNN^ @��   "@B�0/ �� ����"<  z����� B�0"�Q���NuNV��>� NNN^м  {  @"@��   B�0/ �� "<  z���B��� 0# Q���NuNV��Bn��`0n������  "�0� Rn��n 
��m�3�   "�3�   \   ^.�  #|/<   ^/<  "�N�  �P�N^NuNV��N�  �a�B�?< N�  `T�>�   ^N�  DBy  $23�    JBy   LBy   NBy   P�   $:By  $8By  "�a ,3�    RB9  $/>� ?< ?9   ^N�  (X�a 
�a �3�   J   P09   X`*3� K  #�`83� M  #�`.3� H  #�`$3� P  #�``�| gڰ| gް| gİ| g�09  #�` L09   JS@3�   J09   NS@3�   N` P09   JR@3�   J09   NR@3�   N` 009  $2S@3�  $2` 09  $2R@3�  $2` y     Xm  �y ~   Xn  �y    Rff09   X�  $.B9  $/>�  $2/<  "�/<  $.a *P�>� O09  $2�W?9  $2/<  "�a 	N\�.�  "�a a �.�  "�a La �`,09   X"|  "�4y  $2���>�   X?< ?< N�  �X�09  $2R@3�  $2y O  $2o09  $2R@3�  $2a 	�`a ^`$�| Hg ���| Kg ��| Mg ��| Pg ��` ��Jy  $2l$3� O  $209   NS@3�   N09   JS@3�   Jy O  $2o"By  $209   JR@3�   J09   NR@3�   N09   N�y  "�o3�  "�   N09   JS@3�   JJy   NlBy   N09   JR@3�   Jy    Jo  |a 0>� N�   �a P>� ?< ?9   ^N�  (X�>�   ^N�  �a ta R.�  "�a �3�  $2  "~By  $23�    J3�    P.�  "�a �3�  "~  $2y    Jl  |a �>� N�   �a �>� ?< ?9   ^N�  (X�>�   ^N�  �a �a �.�  "�a 3�  $2  "~By  $23�    J3�    P.�  "�a (3�  "~  $209   J�y   Pga a �3�   J   Pa j>�  $2RW?9   JRW?9   ^N�  (X�y   #�f �:>�   ^N�  �>�   ^N�  vB�?<N�  `T�N�  NN^NuNV��>� ?< N�  �T�3�  $0Jy  $0g�>� ?< N�  �T�#�  #@ 9  #@r�3�  #� 9  #@3�   XN^NuNV��=| O��`
0.��S@=@��Jn��m n 2n����  g� n 2n����Jg�3���  0 n 2n����|  N^NuNV��.�  "�a�aa  �N^NuNV��Bn��`  � |  $:2y   L��2n���� fn09   L�n���y  $8gN>���RW?9   L?9  $8RW/<  $:N�   JP� |  $:2y  $8��� 09  $82.��RA�A3�  $8=| Q��09  "�S@3�  "�0.��R@=@��n Q��m �fN^NuNV��Bn��`  � |  "�2n���� f  �>���RW?9   L?9  $8RW/<  $:N�   �P�09  $8�n��R@3�  $809  "�R@3�  "�Bn��`, |  $:2y  oth start at (partition?)
	move.l	#$7aff,d1	* length of screen - $500 for line
	sub.l	d0,d1		* number of bytes to move
	divu	#$04,d1		* because we move long instead of bytes
	clr.l	d0		* clear for word workable
	move.w	d1,d0		* quotient into d0
rl_loop:
	move.l	(a0)+,(a1)+	* move long word memory
	dbra	d0,rl_loop	* do it x amount of times 
	
	rts


*
*	Add_line adds a line passed as parameter and scrolls text up
*

_add_line:
	link	a6,#-2  	* enough room for variables
	move.w	#$02,(a7)       * Push function call
	trap	#14		* Get screens base address
	unlk	a6		* restore stack pointer
	add.l	#$7b00,d0
	move.l	d0,a0
	move.l	d0,a1		* set address registers
	add.l	#$500,a1	* next text line 
	clr.l	d0		* clear for operations

	move.w	$4(a7),d0	* get line to delete
	mulu	#$500,d0	* get starting address
	move.l	#$7aff,d1	* length of screen - $500 for line
	sub.l	d0,d1		* number of bytes to move
	clr.l	d0		* clear for word operations
	divu	#$04,d1		* because we move long instead of bytes
	move.w	d1,d0		* word into d0

al_loop:
	move.l	-(a0),-(a1)	* move long word memory
	dbra	d0,al_loop	* do it x amount of times 
	
	rts


*
*	Stack segment storage
*       
	.bss
	.even
	.ds.l	256
ustk:	.ds.l	1
*
	.data
    	.even
_ctrl_cnts:			 	*	Application Manager
	.dc.b	0, 1, 0			* func 010		
    	.dc.b	2, 1, 1			* func 011		
    	.dc.b	2, 1, 1 		* func 012		
	.dc.b	0, 1, 1			* func 013		
	.dc.b	2, 1, 1			* func 014		
	.dc.b	1, 1, 1			* func 015		
	.dc.b	0, 0, 0			* func 016		
	.dc.b	0, 0, 0			* func 017		
	.dc.b	0, 0, 0			* func 008		
	.dc.b	0, 1, 0			* func 019		
*							 Event Manager
	.dc.b	0, 1, 0			* func 020		
	.dc.b	3, 5, 0			* func 021		
	.dc.b	5, 5, 0			* func 022		
	.dc.b	0, 1, 1			* func 023		
	.dc.b	2, 1, 0			* func 024		
	.dc.b	16, 7, 1 		* func 025		
	.dc.b	2, 1, 0			* func 026		
	.dc.b	0, 0, 0			* func 027		
	.dc.b	0, 0, 0			* func 028		
	.dc.b	0, 0, 0			* func 009		
*							 Menu Manager
	.dc.b	1, 1, 1			* func 030		
	.dc.b	2, 1, 1			* func 031		
	.dc.b	2, 1, 1			* func 032		
	.dc.b	2, 1, 1			* func 033		
	.dc.b	1, 1, 2			* func 034		
	.dc.b	1, 1, 1			* func 005		
	.dc.b	0, 0, 0			* func 006		
	.dc.b	0, 0, 0			* func 007		
	.dc.b	0, 0, 0			* func 008		
	.dc.b	0, 0, 0			* func 009		
*							 Object Manager
	.dc.b	2, 1, 1			* func 040		
	.dc.b	1, 1, 1			* func 041		
  	.dc.b	6, 1, 1			* func 042		
	.dc.b	4, 1, 1			* func 043		
	.dc.b	1, 3, 1			* func 044		
	.dc.b	2, 1, 1			* func 045		
	.dc.b	4, 2, 1			* func 046		
	.dc.b	8, 1, 1			* func 047		
	.dc.b	0, 0, 0			* func 048		
	.dc.b	0, 0, 0			* func 049		
*							 Form Manager
	.dc.b	1, 1, 1			* func 050		
	.dc.b	9, 1, 1			* func 051		
	.dc.b	1, 1, 1			* func 002		
	.dc.b	1, 1, 0			* func 003		
	.dc.b	0, 5, 1			* func 004		
	.dc.b	0, 0, 0			* func 005		
	.dc.b	0, 0, 0			* func 006		
	.dc.b	0, 0, 0			* func 007		
	.dc.b	0, 0, 0			* func 008		
	.dc.b	0, 0, 0			* func 009		
*							 Dialog Manager
	.dc.b	0, 0, 0			* func 060		
	.dc.b	0, 0, 0			* func 061		
	.dc.b	0, 0, 0			* func 062		
	.dc.b	0, 0, 0			* func 003		
	.dc.b	0, 0, 0			* func 004		
	.dc.b	0, 0, 0			* func 005		
	.dc.b	0, 0, 0			* func 006		
	.dc.b	0, 0, 0			* func 007		
	.dc.b	0, 0, 0			* func 008		
	.dc.b	0, 0, 0			* func 009		
*							Graphics Manager
	.dc.b	4, 3, 0			* func 070		
	.dc.b	8, 3, 0			* func 071		
	.dc.b	6, 1, 0			* func 072		
	.dc.b	8, 1, 0			* func 073		
	.dc.b	8, 1, 0			* func 074		
	.dc.b	4, 1, 1			* func 075		
	.dc.b	3, 1, 1			* func 076		
	.dc.b	0, 5, 0			* func 077		
	.dc.b	1, 1, 1			* func 078		
	.dc.b	0, 5, 0			* func 009		
*							Scrap Manager
	.dc.b	0, 1, 1			* func 080		
	.dc.b	0, 1, 1			* func 081		
	.dc.b	0, 0, 0			* func 082		
	.dc.b	0, 0, 0			* func 083		
	.dc.b	0, 0, 0			* func 084		
	.dc.b	0, 0, 0			* func 005		
	.dc.b	0, 0, 0			* func 006		
	.dc.b	0, 0, 0			* func 007		
	.dc.b	0, 0, 0			* func 008		
	.dc.b	0, 0, 0			* func 009		
*							fseler Manager
	.dc.b	0, 2, 2			* func 090		
	.dc.b	0, 0, 0			* func 091		
	.dc.b	0, 0, 0			* func 092		
	.dc         { curs_off();
              rem_line(1);		/* scroll screen up */
              curs_on();
	      vs_curaddress(handle,25,1);
	      v_eeol(handle);	/* clear bottom line after scroll */
	      upd_char();
	      get_temp();
	      st_spc(&templine);		/* get string and strip spaces */
	      tempcol = cursor;
	      cursor = 0;
	      line = 24;		/* reset cursor stuff */
	      oldline = 24;
	      write(templine);
	      cursor = tempcol;
	    }
	  if (line < 1)
            { curs_off();
              add_line(1);		/* scroll screen down */
              curs_on();
	      vs_curaddress(handle,2,1);
	      v_eeol(handle);
	      upd_char();
	      get_temp();		/* update for new line on screen */
	      st_spc(&templine);
	      tempcol = cursor;
	      cursor = 0;
	      line = 1;
	      oldline = 1;		/* reset cursor stuff */
	      write(templine);
	      cursor = tempcol;
	    }


	   if (line != oldline)
	   { ch_line();
	     upd_char();	
	     oldline = line;
	     get_temp();
	   }

	   /* reposition the cursor everytime */

	   vs_curaddress(handle,line+1,cursor+1);


	}
	while (scanc != 01);	/* until escape character */
	
	v_clrwk(handle);
	
	v_exit_cur(handle);	/* exit alpha mode */

	graf_mouse(M_ON,0x0L);	/* turn mouse on again for desktop */

	appl_exit();
}

/**************************************************************/
/*          Getkey returns keyboard keys into variables	      */
/**************************************************************/

getkey()
{
  do
   { kbdst = Bconstat(2);	/* wait for a key to be pressed */
     }
    while (kbdst == 0);

    ibmkey = Bconin(2);		/* get the key from console */

    scanc = (ibmkey >> 16);		/* sift out scan code */
    keyc = (ibmkey & 0x0000ffff);	/* sift out key code */

}

/****************************************************************/
/*      st_spc strips the trailing blanks from a string 	*/
/****************************************************************/
C P / M   6 8 0 0 0   A s s e m b l e r		Revision 04.03		Page   1
Source File: B:TEDITST.S

   1                               *       Teditst.S       8/10/85                 Kenneth L. Hurley
   2                               *
   3                               * 
   4                               * Simple text editor for the atari 520 st. We'll see how it turns out
   5                               *
   6                               * 
   7                               * 
   8                               * 
   9                               * 
  10                               * 
  11                               * 
  12                               * 
  13                               *
  14                               
  15 00000000                              .text
  16                                       .globl  _main
  17                                       .globl  _crystal
  18                                       .globl  _ctrl_cnts
  19                     /*********************************************************************/
/* SAMPLE APPLICATION SKELETON 					     */
/*	started 8/31/85 K.H.                                         */
/*********************************************************************/

/*********************************************************************/
/* INCLUDE FILES						     */
/*********************************************************************/

#include "obdefs.h"
#include "define.h"
#include "gemdefs.h"
#include "osbind.h"
#include "b:se.h"

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


char	path[64];	/* path name to selected drive */

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
char	cstruc1[32] = "unsigned int image[DATASIZE] = ";
char	cstruc3[3] = "{ ";
char	cstruc4[3] = "};";

char	com_spc[3] = ", ";		/* comma and a space */
char	ret_lf[3] = "\015\012";		/* return and linefeed */

char	s_header[33] = "* ShIcEd Form Definition Block ";
char	s_dcb[8] = "\011dc.b\011";
char	shap_str[30];


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
/*  a string           * save a7 so we can get the base page address
  29 00000002 2E7C00000400                 move.l  #ustk,a7        * set local stack
  30 00000008 2A6D0004                     move.l  4(a5),a5        * basepage address
  31 0000000C 202D000C                     move.l  $c(a5),d0
  32 00000010 D0AD0014                     add.l   $14(a5),d0
  33 00000014 D0AD001C                     add.l   $1c(a5),d0
  34 00000018 D0BC00000100                 add.l   #$100,d0        * skip los pageos baseos
  35 0000001E 2F00                         move.l  d0,-(sp)
  36 00000020 2F0D                         move.l  a5,-(sp)
  37 00000022 3F00                         move    d0,-(sp)        * junk word
  38 00000024 3F3C004A                     move    #$4a,-(sp)
  39 00000028 4E41                         trap    #1
  40 0000002A DFFC0000000C                 add.l   #12,sp
  41                               *
  42 00000030 4EB900000000                 jsr     _main           * go to program
  43 000000/
/*  more...                                              	*/
/****************************************************************/

curs_off()
{  rate = -1;
   attrib = 0;			/* set cursor off */  
   Cursconf(attrib,rate);	/* go configure cursor */
}  

/****************************************************************/
/*  curs_on can you guess what the hell this does not really	*/
/*  to hard to figure out.                               	*/
/*****************************************************
move R0,_inson
bra L98
*line 493
L103:
*line 494
*line 495
move #1,(sp)
move _cursor,-(sp)
move.l #_templine,-(sp)
jsr _delete
addq.l #6,sp
*line 496
move #79,(sp)
move _cursor,R0
sub R0,(sp)
move _cursor,-(sp)
move.l #_templine,-(sp)
jsr _copy
addq.l #6,sp
*line 497
move.l #_outline,(sp)
jsr _write
*line 498
move _handle,(sp)
jsr _v_eeol
bra L98
*line 499
L104:
*line 500
*line 501
clr _cursor
*line 502
clr _line
*line 503
move.l #L105,(sp)
jsr _write
*line 504
move _s