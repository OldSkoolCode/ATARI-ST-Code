*********************************************************************
* LINADEMO.S:							    *
* This program demonstrates how to use some of the Line-A opcodes.  *
* The program lets you draw on the screen using the mouse.  You may *
* also select different drawing colors from the top of the screen.  *
* Use the left mouse button to draw or choose colors, and the right *
* mouse button to exit.  Runs in all resolutions.		    *
*								    *
* Written by Robert M. Birmingham using the MadMac Assembler from   *
* Atari Corp.  [December 22, 1989]				    *
*********************************************************************

* Trap vector numbers...

GEMDOS	= 1
XBIOS	= 14

* GEMDOS functions...

Pterm0	= $00
Mshrink = $4a

* BIOS functions...

Physbase = 2

* Line-A equates...

LINEA_INIT = $A000
DRAW_LINE  = $A003
DRAW_RECT  = $A005
SHOW_MOUSE = $A009
HIDE_MOUSE = $A00A
TRAN_MOUSE = $A00B

X_REZ	   = -$2B4
Y_REZ	   = -$2B2
NUM_COLORS = -$29A
GCURX	   = -$25A
GCURY	   = -$258
MOUSE_BT   = -$254
USER_BUT   = -$03A
V_CEL_HT   = -$02E

INTIN	   = $08
PTSIN	   = $0C
COLBIT0    = $18
COLBIT1    = $1A
COLBIT2    = $1C
COLBIT3    = $1E
LSTLIN	   = $20
LNMASK	   = $22
WMODE	   = $24
X1	   = $26
Y1	   = $28
X2	   = $2A
Y2	   = $2C
PATPTR	   = $2E
PATMSK	   = $32
MFILL	   = $34
CLIP	   = $36

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

main:	.dc.w	LINEA_INIT	; initialize Line-A and save the...
	move.l	a0,lineaptr	; pointer to the variable area.
	bsr	disable_button	; disable the AES button handler
	.dc.w	HIDE_MOUSE
	bsr	init_rez	; initialize rez. independant variables
	bsr	color_boxes	; display the color selections
	bsr	change_mouse	; change the mouse to our form
	.dc.w	SHOW_MOUSE
	bsr	draw		; call the mouse drawing routine

.chkbt: bsr	get_mouse	; wait until no buttons are pressed
	tst.w	button
	bne	.chkbt

	bsr	enable_button	; enable AES button handler
	rts

***************************************
* draw: 			      *
* Lets the user draw using the mouse, *
* as well as select the drawing color *
***************************************

draw:	bsr	get_mouse	; get the mouse position & button state
	move.w	mx,oldx 	; set previous mouse x position
	move.w	my,oldy 	; set previous mouse y position
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
	bsr	set_color	; set line color to value in d0

.wait:	bsr	get_mouse	; get the mouse position and button state
	tst.w	button		; if any mouse buttons are pressed...
	bne	.wait		; then wait until they are released...
	bra	draw		; then start the drawing loop over

.line:	.dc.w	HIDE_MOUSE
	bsr	line		; draw line from oldx, oldy to mx, my
	.dc.w	SHOW_MOUSE

	move.w	mx,oldx 	; set the previous mouse position...
	move.w	my,oldy 	; to the current mouse position.

.chkbt: bsr	get_mouse	; get the mouse variables again
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
	move.w	d0,cboxw	; this is the width of color boxes
	move.w	hchar,cboxh	; get the height of a character cell
	asl.w	cboxh		; * 2 = the height of the color boxes

	clr.w	rect		; x1 coordinate starts at zero
	clr.w	rect+2		; y1 coordinate is always zero
	move.w	cboxw,rect+4	; x2 = the width of a color box...
	subi.w	#1,rect+4	; -1 so boxes don't overlap
	move.w	cboxh,rect+6	; y2 coordinate = color box height

	moveq.l #0,d0		; clear loop counter
.dobox: move.w	d0,-(sp)	; save counter before calling VDI!
	lea	rect,a1 	; pointer to rect array -> A1
	bsr	rectangle	; and draw it!
	move.w	(sp)+,d0	; restore the loop counter

	move.w	cboxw,d7	; get the width of a color box and add...
	add.w	d7,rect 	; it to x1 & x2 to get the position...
	add.w	d7,rect+4	; of the next color box to draw.

	addi.w	#1,d0		; next loop counter/color index
	cmp.w	colors,d0	; have we drawn all the color boxes?
	bne	.dobox		; no, then continue
	rts			; yes, then we're done!

************************************************
* line: 				       *
* Draws a line from oldx and oldy to mx and my *
************************************************

line:	movea.l lineaptr,a0
	clr.w	LSTLIN(a0)	  ; draw last point of the line
	move.w	#$ffff,LNMASK(a0) ; line pattern to use
	clr.w	WMODE(a0)	  ; replace write mode
	move.w	oldx,X1(a0)	  ; set coordinates...
	move.w	oldy,Y1(a0)
	move.w	mx,X2(a0)
	move.w	my,Y2(a0)
	.dc.w	DRAW_LINE	  ; and do it!
	rts

**********************************************************************
* rectangle:							     *
* Draws a filled rectangle.  Pass the address of an array containing *
* the upper left and lower right corners of the rectangle in the A1  *
* and pass the color of the rectangle to draw in d0.		     *
**********************************************************************

rectangle:
	bsr	set_color	     ; set COLBIT0 - COLBIT3
	movea.l lineaptr,a0
	clr.w	WMODE(a0)	     ; replace write mode
	move.w	(a1)+,X1(a0)	     ; set coordinates from rect array
	move.w	(a1)+,Y1(a0)
	move.w	(a1)+,X2(a0)
	move.w	(a1),Y2(a0)
	move.l	#pattern,PATPTR(a0)  ; fill pattern
	clr.w	PATMSK(a0)	     ; Pattern length - 1
	clr.w	MFILL(a0)	     ; single plane fill
	clr.w	CLIP(a0)	     ; no clipping please
	.dc.w	DRAW_RECT	     ; and draw it!
	rts

***********************************************
* set_color:				      *
* Sets the Line-A COLBITx variables according *
* to the color index passed in D0.	      *
***********************************************

set_color:
	movea.l lineaptr,a0
	clr.w	COLBIT0(a0)	; sure they're all clear to start with!
	clr.w	COLBIT1(a0)
	clr.w	COLBIT2(a0)
	clr.w	COLBIT3(a0)

	btst	#3,d0		; check bit #3 of color passed
	sne	COLBIT3+1(a0)	; make COLBIT3 non-zero if it's set!
	btst	#2,d0		; and so on for the remaining bits...
	sne	COLBIT2+1(a0)
	btst	#1,d0
	sne	COLBIT1+1(a0)
	btst	#0,d0
	sne	COLBIT0+1(a0)
	rts

*******************************************************
* init_rez:					      *
* Intializes the resolution independant variables for *
* the maximum x & y resolution, the number of colors  *
* available, and the height of a character cell.      *
*******************************************************

init_rez:
	movea.l lineaptr,a0
	move.w	X_REZ(a0),xmax
	addi.w	#1,xmax
	move.w	Y_REZ(a0),ymax
	addi.w	#1,ymax
	move.w	NUM_COLORS(a0),colors
	move.w	V_CEL_HT(a0),hchar

	move.w	#Physbase,-(sp) ; get the screen address
	trap	#XBIOS
	addq.l	#2,sp
	movea.l d0,a0

	move.w	#7999,d0	; and clear the screen
.clear: clr.l	(a0)+
	dbra	d0,.clear
	rts

******************************************
* get_mouse:				 *
* returns the current mouse position and *
* button state in mx, my and button.	 *
******************************************

get_mouse:
	movea.l lineaptr,a0
	move.w	GCURX(a0),mx
	move.w	GCURY(a0),my
	move.w	MOUSE_BT(a0),button
	rts

********************************************************
* change_mouse: 				       *
* This routine changes the mouse form to our crosshair *
********************************************************

change_mouse:
	movea.l lineaptr,a0
	move.l	#mouse_form,INTIN(a0)
	.dc.w	TRAN_MOUSE
	rts

************************************************************
* disable_button:					   *
* Stops the AES from getting mouse button clicks. This is  *
* neeeded because upon returning to the desktop, the AES   *
* sometimes thinks that the button is still down and you   *
* are trying to perform an operation with a window or icon *
************************************************************

disable_button:
	movea.l lineaptr,a0
	move.l	USER_BUT(a0),old_button_vec
	move.l	#.dummy,USER_BUT(a0)
.dummy: rts

***************************************************
* enable_button:				  *
* Restore the vector to the AES button handler.   *
* This is called right before the program leaves! *
***************************************************

enable_button:
	movea.l lineaptr,a0
	move.l	old_button_vec,USER_BUT(a0)
	rts

****************************************************************************
* data section

	.data
	.even

mouse_form:
	.dc.w	4, 4, 1, 0, 1
	.dc.w	7168, 5120, 5120, 63360, 32896, 63360, 5120, 5120
	.dc.w	7168, 0, 0, 0, 0, 0, 0, 0
	.dc.w	0, 2048, 2048, 2048, 30464, 2048, 2048, 2048
	.dc.w	0, 0, 0, 0, 0, 0, 0, 0

pattern:
	.dc.w	$ffff

* block storage section

	.bss
	.even

lineaptr:	.ds.l	1
old_button_vec: .ds.l	1

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

		.ds.l	 256	; stack size = 1K
ustk:		.ds.l	 1
		.end
