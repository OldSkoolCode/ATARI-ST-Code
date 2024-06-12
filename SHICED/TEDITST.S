_opnvwk(work_in,&handle,work_out);
}


/****************************************************************/
/*		Start of main program area            		*/
/****************************************************************/
main()
{
	appl_init();
	open_vwork();

	graf_mouse(M_OFF,0x0L);	/* turn the mouse shape off for text mode */

	v_enter_cur(handle);	/* open application and enter text mode */

	cursor = 0;
	line = 1;		/* bypass status line */
	currchar = 0;		/* initialize variables */
	memline = 0;
	oldline = 0;
	file[0] = 13;		/* CR to start off with */
	lastchar = 0;		/* set last character at 0 */
	lastline = 0;		/* set last line at 0 */
	get_temp();		/* get line currently on */
	inson = 1;		/* insert on to begin with */
	chrstr[1] = 0;		/* end of string */
	vs_curaddress(handle,2,1);

	do
	  {
	    stat_line();
	    getkey();
	    oldline = line;	/* save old line for change to file */
	           switch (keyc)
             {
               case 19:
                 scanc = 0x4b;  /* set leftarrow key */
                 break;
               case 4:          /* alternate right key */
                 scanc = 0x4d;
                 break;
               case 5:          /* alternate up key */
                 scanc = 0x48;
                 break;
               case 24:         /* alternate down key */
                 scanc = 0x50;
                 break;
              }
     switch (scanc)
	      {case 0x48:	/* up-arrow key */
		line = line - 1;
		memline == memline - 1;
	      line = line - 1;	/* if ok go on to previous line */
	    }

	  if (cursor > 79)	/* check for cursor wrap right */
 	    { cursor = 0;
	      line = line + 1;	/* next line if possible */
	      memline = memline + 1;
	    }

	  if (memline > lastline)	/* can't go past the last line */
	    { memline = lastline;
	      line = line - 1;
	    }

	  if (memline < 0)
	   { memline = 0;
	     line = line + 1;
	   }

	  if (line > 24)	/* check for lines going to far */
	  *	Teditst.S	8/10/85			Kenneth L. Hurley
*
* 
* Simple text editor for the atari 520 st. We'll see how it turns out
*
* 
* 
* 
* 
* 
* 
* 
*

	.text
	.globl	_main
	.globl	_crystal
	.globl	_ctrl_cnts
	.globl	_del_byte
	.globl	_ins_byte
	.globl	_rem_line
	.globl	_add_line


*
*  Must be first object file in link statement
*
	move.l	a7,a5		* save a7 so we can get the base page address
	move.l	#ustk,a7	* set local stack
	move.l	4(a5),a5	* basepage address
	move.l	$c(a5),d0
	add.l	$14(a5),d0
	add.l	$1c(a5),d0
	add.l	#$100,d0	* skip los pageos baseos
	move.l	d0,-(sp)
	move.l	a5,-(sp)
	move	d0,-(sp)	* junk word
	move	#$4a,-(sp)
	trap	#1
	add.l	#12,sp
*
	jsr	_main		* go to program
	move.l	#0,-(a7)	* back to gemdos
	trap	#1
*
*	For GEMAES calls from AESBIND.ARC or cryslib.o
*
_crystal:
	move.l	4(a7),d1
	move.w	#200,d0
	trap	#2
	rts
	
*
*	del_byte deletes bytes specified by calling routine
*

_del_byte:
	clr.l	d0
	suba.l	a0,a0		* clear address registers
	suba.l	a1,a1		* clear registers for long operations

	move.w	$c(a7),d0	* get # bytes to move
	cmp.w	#0,d0		* no bytes to move so exit
	beq.s	del_exit	* bypass routine for delete
	move.w	$a(a7),a0	* offset into file
	add.w	a0,d0		* total offset
	move.w	$8(a7),a1	* end of file
	sub.w	d0,a1		* total number of bytes to move
	move.w	a1,d0		* into d0 register

	clr.l	a1		* clear again
	move.w	$a(a7),a1	* offset again
	move.l	$4(a7),d1	* starting address
	add.l	d1,a1		* a1 = real starting address of string = form_do(form_addr,0); 
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
       unsigned int color;			/* color of array */

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
