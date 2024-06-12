*******************************************************************
* GEMDEMO.S:							  *
* This program shows how to use AES and VDI functions in Assembly *
* Lanaguage.  The program lets you draw on the screen using the   *
* mouse.  You may also select different drawing colors from the   *
* top of the screen.  Use the left mouse button to draw or choose *
* colors, and the right mouse button to exit.			  *
* Runs in all resolutions.					  *
*								  *
* Written by Robert M. Birmingham using the MadMac Assembler	  *
* from Atari Corp.  [December 22, 1989] 			  *
*******************************************************************

* Trap vector numbers...

GEMDOS	= 1
GEM	= 2

* GEMDOS functions...

Pterm0	= $00
Mshrink = $4a

****************************************************************************

	.text
start:	movea.l a7,a5		; copy the stack pointer
	lea	ustk,a7 	; set our stack address
	movea.l 4(a5),a5	; get the basepage address
	move.l	$c(a5),d0	; get the size of the text segment
	add.l	$14(a5),d0	; add the size of the data segment
	add.l	$1c(a5),d0	; add the size of the bss segment
	add.l	#$100,d0	; add the size of the basepage

	move.l	d0,-(sp)	; push the length of the program
	move.l	a5,-(sp)	; push the basepage address
	clr.w	-(sp)		; junk word
	move.w	#Mshrink,-(sp)	; shrink the amount of memory...
	trap	#GEMDOS 	; allocated for the program...
	lea	12(sp),sp	; and clean up the stack!
	tst.w	d0		; was the shrink successful?
	bne.s	.exit		; if not, then get outta here!
	bsr	main		; otherwise, on with the program!

.exit:	move.w	#Pterm0,-(sp)	; terminate the program
	trap	#GEMDOS 	; never to return!
	illegal

main:	bsr	appl_init
	bsr	graf_handle
	bsr	v_opnvwk
	bsr	v_hide_c
	bsr	v_clrwk
	bsr	color_boxes
	bsr	v_show_c
	bsr	disable_button

	move.w	#7,d0		; change the mouse into...
	bsr	graf_mouse	; the thin crosshair.

	bsr	draw		; call the main drawing routine
.chkbt: bsr	vq_mouse	; wait until mouse buttons are released
	tst.w	button
	bne	.chkbt

	bsr	enable_button
	bsr	v_clsvwk
	bsr	appl_exit
	rts

***************************************
* draw routine: 		      *
* Lets the user draw using the mouse, *
* as well as select the drawing color *
***************************************

draw:	bsr	vq_mouse	; put mouse variables -> mx, my, button
	move.w	mx,oldx 	; init. previous mouse x position
	move.w	my,oldy 	; init. previous mouse y position
	cmpi.w	#1,button	; is the left button pressed?
	beq.s	.click		; if so, then handle it
	blt	draw		; if button < 1, nothing was pressed
	rts			; otherwise, leave!

.click: move.w	my,d0		; get the mouse's y position...
	cmp.w	cboxh,d0	; is it within the color box area?
	bgt.s	.line		; if not, then it was in the drawing area.

	moveq.l #0,d0		; make sure all of D0 is clear
	move.w	mx,d0		; get the mouse x position
	divu	cboxw,d0	; calc. which color box was clicked
	bsr	vsl_color	; set line color to value in d0

.letgo: bsr	vq_mouse	; wait until the button is released...
	tst.w	button
	bne	.letgo
	bra	draw		; then start the drawing loop over

.line:	bsr	v_hide_c
	bsr	v_pline 	; draw line from oldx, oldy to mx, my
	bsr	v_show_c

	move.w	mx,oldx 	; set the previous mouse position...
	move.w	my,oldy 	; to the current mouse position.

.chkbt: bsr	vq_mouse	; get the mouse variables again
	cmpi.w	#1,button	; if the left button still pressed?
	beq.s	.chkmv		; yes? - check for any movement
	bra	draw		; no? - start drawing loop again

.chkmv: move.w	mx,d0		; get the current x position and...
	cmp.w	oldx,d0 	; compare it to the old x position..
	bne	.click		; if x has changed, do loop again
	move.w	my,d0		; get the current y position and...
	cmp.w	oldy,d0 	; compare it to the old y position...
	bne	.click		; if y has changed, do it again!
	bra	.chkbt		; else, no changes, try again!

**************************************
* color_boxes:			     *
* This routine draws the color boxes *
* along the top of the screen.	     *
**************************************

color_boxes:
	moveq.l #0,d0		; make sure all of d0 is clear
	move.w	xmax,d0 	; get maximum x resolution
	divu	colors,d0	; d0 = xmax/colors
	move.w	d0,cboxw	; this is the width of a color box
	move.w	hchar,cboxh	; get the height of a character cell
	asl.w	cboxh		; * 2 = the height of a color box

	clr.w	rect		; x1 coordinate starts at zero
	clr.w	rect+2		; y1 coordinate is always zero
	move.w	cboxw,rect+4	; x2 = the width of a color box...
	subi.w	#1,rect+4	; -1 so boxes don't overlap
	move.w	cboxh,rect+6	; y2 coordinate = color box height

	moveq.l #0,d0		; clear loop counter
.dobox: move.w	d0,-(sp)	; save counter before calling VDI!
	bsr	vsf_color	; set fill color from value in d0
	lea	rect,a0 	; load the address of the rectangle...
	bsr	v_recfl 	; coordinates, and draw it!
	move.w	(sp)+,d0	; restore the loop counter

	move.w	cboxw,d7	; get the width of a color box and add...
	add.w	d7,rect 	; it to x1 & x2 to get the position...
	add.w	d7,rect+4	; of the next color box to draw.

	addi.w	#1,d0		; next loop counter/color index
	cmp.w	colors,d0	; have we drawn all the color boxes?
	bne	.dobox		; no, then continue
	rts			; yes, then we're done!

*
* The following subroutines call the AES/VDI functions.
* They were written for clarity (believe it or not!), not size or speed.
*

**************************************
* appl_init:			     *
* stores the application id in ap_id *
**************************************

appl_init:
	clr.l	ap1resv 	; clear ap1resv -> ap4resv
	clr.l	ap2resv
	clr.l	ap3resv
	clr.l	ap4resv

	move.w	#10,contrl	; appl_init opcode
	move.w	#0,contrl+2	; size of intin
	move.w	#1,contrl+4	; size of intout
	move.w	#0,contrl+6	; size of addrin
	move.w	#0,contrl+8	; size of addrout
	jsr	aes		; do it!

	move.w	intout,ap_id	; save the application id!
	rts

**************************************
* appl_exit:			     *
* clean up and leave the application *
**************************************

appl_exit:
	move.w	#19,contrl	; appl_exit opcode
	move.w	#0,contrl+2
	move.w	#1,contrl+4
	move.w	#0,contrl+6
	move.w	#0,contrl+8
	jsr	aes
	rts

*************************************
* graf_handle:			    *
* returns with...		    *
* handle in grhandle		    *
* height of character cell in hchar *
*************************************

graf_handle:
	move.w	#77,contrl	; graf_handle opcode
	move.w	#0,contrl+2	; and the sizes of the input arrays...
	move.w	#5,contrl+4
	move.w	#0,contrl+6
	move.w	#0,contrl+8
	jsr	aes

	move.w	intout,grhandle ; save the handle returned!
	move.w	intout+4,hchar	; save the height of a character cell
	rts

********************************************
* graf_mouse:				   *
* pass the shape of the mouse to set in d0 *
********************************************

graf_mouse:
	move.w	#78,contrl	; graf_mouse opcode
	move.w	#1,contrl+2
	move.w	#1,contrl+4
	move.w	#1,contrl+6
	move.w	#0,contrl+8
	move.w	d0,intin	; shape desired passed in d0
	jsr	aes
	rts

********************************
* v_opnvwk:		       *
* open a virtual workstation.  *
* returns with...	       *
* workstation handle in handle *
* x resolution in xmax	       *
* y resolution in ymax	       *
* colors available in colors   *
********************************

v_opnvwk:
	move.w	#100,contrl	; v_opnvwk opcode
	move.w	#0,contrl+2
	move.w	#11,contrl+6
	move.w	grhandle,contrl+12

	lea	intin,a0
	move.w	#1,(a0)+	; use screen device driver
	move.w	#1,(a0)+	; solid line type
	move.w	#1,(a0)+	; line color index
	move.w	#1,(a0)+	; marker type
	move.w	#1,(a0)+	; polymarker color index
	move.w	#1,(a0)+	; text face
	move.w	#1,(a0)+	; text color index
	move.w	#1,(a0)+	; fill interior style
	move.w	#1,(a0)+	; fill style index
	move.w	#1,(a0)+	; fill color index
	move.w	#2,(a0) 	; use Raster Coordinates
	jsr	vdi

	move.w	contrl+12,handle ; save our beloved workstation handle
	move.w	intout,xmax	 ; save x resolution
	addi.w	#1,xmax 	 ; adjust because of zero base
	move.w	intout+2,ymax	 ; save y resolution
	addi.w	#1,ymax 	 ; adjust this to!
	move.w	intout+26,colors ; save the number of colors available
	rts

*********************************
* v_clsvwk:			*
* Close our virtual workstation *
*********************************

v_clsvwk:
	move.w	#101,contrl	; v_clsvwk opcode
	move.w	#0,contrl+2
	move.w	#0,contrl+6
	move.w	handle,contrl+12
	jsr	vdi
	rts

********************************
* v_clrwk:		       *
* Clear the workstation screen *
********************************

v_clrwk:
	move.w	#3,contrl	; v_clrwk opcode
	move.w	#0,contrl+2
	move.w	#0,contrl+6
	move.w	handle,contrl+12
	jsr	vdi
	rts

*************************************************
* v_pline:					*
* draws a line from oldx and oldy to mx and my. *
*************************************************

v_pline:
	move.w	#6,contrl	; v_pline opcode
	move.w	#2,contrl+2	; # of vertices in ptsin array
	move.w	#0,contrl+6	; size of intin array
	move.w	handle,contrl+12 ; our workstation handle

	move.w	oldx,ptsin	; x1
	move.w	oldy,ptsin+2	; y1
	move.w	mx,ptsin+4	; x2
	move.w	my,ptsin+6	; y2
	jsr	vdi
	rts

********************************
* vsl_color:		       *
* sets the current line color. *
* pass the color desired in d0 *
********************************

vsl_color:
	move.w	#17,contrl	; vsl_color opcode
	move.w	#0,contrl+2
	move.w	#1,contrl+6
	move.w	handle,contrl+12

	lea	color_fix,a0	; get address of fix up table
	asl.w	#1,d0		; access table by words
	move.w	(a0,d0),d0	; load the real color index to use
	move.w	d0,intin	; and store it for GEM
	jsr	vdi
	rts

**********************************************************************
* v_recfl:							     *
* Draws a filled rectangle.  Pass the address of an array containing *
* the upper left and lower right corners of the rectangle in the A0. *
**********************************************************************

v_recfl:
	move.w	#114,contrl	; v_recfl opcode
	move.w	#2,contrl+2
	move.w	#0,contrl+6
	move.w	handle,contrl+12

	move.w	(a0)+,ptsin	; x1
	move.w	(a0)+,ptsin+2	; y1
	move.w	(a0)+,ptsin+4	; x2
	move.w	(a0),ptsin+6	; y2
	jsr	vdi
	rts

********************************
* vsf_color:		       *
* sets the current fill color. *
* pass the color desired in d0 *
********************************

vsf_color:
	move.w	#25,contrl	; vsf_color opcode
	move.w	#0,contrl+2
	move.w	#1,contrl+6
	move.w	handle,contrl+12

	lea	color_fix,a0	; get address of fix up table
	asl.w	#1,d0		; access table by words
	move.w	(a0,d0),d0	; load the real color index to use
	move.w	d0,intin
	jsr	vdi
	rts

**************************************
* vq_mouse:			     *
* returns the mouse position and     *
* button state in mx, my and button. *
**************************************

vq_mouse:
	move.w	#124,contrl	; vq_mouse opcode
	move.w	#0,contrl+2
	move.w	#0,contrl+6
	move.w	handle,contrl+12	
	jsr	vdi

	move.w	ptsout,mx	; save the mouse's x position...
	move.w	ptsout+2,my	; the y position...
	move.w	intout,button	; and the button state
	rts

*************************
* show the mouse cursor *
*************************

v_show_c:
	move.w	#122,contrl	 ; v_show_c opcode
	move.w	#0,contrl+2	 ; size of ptsin array
	move.w	#1,contrl+6	 ; size of intin array
	move.w	handle,contrl+12 ; our workstation handle
	move.w	#1,intin	 ; cursor reset flag = normal
	jsr	vdi
	rts

*************************
* hide the mouse cursor *
*************************

v_hide_c:
	move.w	#123,contrl	; v_hide_c opcode
	move.w	#0,contrl+2
	move.w	#0,contrl+6
	move.w	handle,contrl+12
	jsr	vdi
	rts

* AES routine

aes:	move.l	#aespb,d1	; address of AES parameter block
	move.w	#$c8,d0 	; opcode
	trap	#GEM		; call GEM
	rts

* VDI routine

vdi:	move.l	#vdipb,d1	; address of VDI parameter block
	move.w	#$73,d0 	; opcode
	trap	#GEM		; call GEM
	rts

***********************************************************
* disable_button:					  *
* Stops the AES from getting mouse button clicks. This is *
* neeeded because upon returning to the desktop, the AES  *
* sometimes thinks the button is still down and that you  *
* are trying to perform an operation with a window, etc.  *
***********************************************************

disable_button:
	.dc.w	$A000
	move.l	-$03A(a0),old_button_vec
	move.l	#.dummy,-$03A(a0)
.dummy: rts

***************************************************
* enable_button:				  *
* Restore the vector to the AES button handler.   *
* This is called right before the program leaves! *
***************************************************

enable_button:
	.dc.w	$A000
	move.l	old_button_vec,-$03A(a0)
	rts

****************************************************************************
* data section

	.data
	.even

color_fix:	.dc.w	0,2,3,6,4,7,5,8,9,10,11,14,12,15,13,1

aespb:		.dc.l	contrl,global,intin,intout,addrin,addrout
vdipb:		.dc.l	contrl,intin,ptsin,intout,ptsout

* block storage section

	.bss
	.even

grhandle:	.ds.w	1
handle: 	.ds.w	1
old_button_vec: .ds.l	1

wchar:		.ds.w	1
hchar:		.ds.w	1

xmax:		.ds.w	1
ymax:		.ds.w	1
colors: 	.ds.w	1
cboxw:		.ds.w	1
cboxh:		.ds.w	1
rect:		.ds.w	4

mx:		.ds.w	1
my:		.ds.w	1
button: 	.ds.w	1
oldx:		.ds.w	1
oldy:		.ds.w	1

contrl: 	.ds.w	12
global:
ap_version:	.ds.w	1
ap_count:	.ds.w	1
ap_id:		.ds.w	1
ap_private:	.ds.l	1
ap_ptree:	.ds.l	1
ap1resv:	.ds.l	1
ap2resv:	.ds.l	1
ap3resv:	.ds.l	1
ap4resv:	.ds.l	1

intin:		.ds.w	128
ptsin:		.ds.w	128
intout: 	.ds.w	128
ptsout: 	.ds.w	128
addrin: 	.ds.w	128
addrout:	.ds.w	128

		.ds.l	 256	; stack size = 1K
ustk:		.ds.l	 1
		.end
