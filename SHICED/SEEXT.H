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

extern	FDB	undo_mfdb,screen_mfdb;		/* form definition blocks */

extern	int	gl_hchar;
extern	int	gl_wchar;
extern	int	gl_wbox;
extern	int	gl_hbox;	/* system sizes */

extern	long    gl_menu;

extern	int	exit_obj;	/* exit object selected */
extern	int 	phys_handle;	/* physical workstation handle */
extern	int 	handle;		/* virtual workstation handle */
extern	int	wi_handle;	/* window handle */
extern	int     wi2_handle;     /* second window handle */
extern	int	wi3_handle;	/* third window handle */
extern	int	top_window;	/* handle of topped window */

extern	int     cursor,line;    /* where to put stuff */
extern	int	xdesk,ydesk,hdesk,wdesk;
extern	int	xold,yold,hold,wold;
extern	int	xwork1,ywork1,hwork1,wwork1;	/* desktop and work areas */
extern	int     xwork2,ywork2,hwork2,wwork2;
extern	int     xwork3,ywork3,hwork3,wwork3;

extern	int	xwind1,ywind1,wwind1,hwind1;	/* window sizes */
extern	int	xwind2,ywind2,wwind2,hwind2;
extern	int	xwind3,ywind3,wwind3,hwind3;

extern	int	grid_width,grid_height;		/* grid height and width */

extern	int	fo_gx,fo_gy,fo_gw,fo_gh;	/* form global XYWH */
extern	long	form_addr;			/* forms address global */

extern	int	msgbuff[8];	/* event message buffer */
extern	int	keycode;	/* keycode returned by event-keyboard */
extern	int	mx,my;		/* mouse x and y pos. */
extern	int	mbutton;	/* button state actual */
extern	int	butdown;	/* button state tested for, UP/DOWN */
extern	int	ret;		/* dummy return variable */

extern	int	hidden;		/* current state of cursor */

extern	int	fulled;		/* current state of window */

extern	int	contrl[12];
extern	int	intin[128];
extern	int	ptsin[128];
extern	int	intout[128];
extern	int	ptsout[128];	/* storage wasted for idiotic bindings */

extern	int work_in[11];	/* Input to GSX parameter array */
extern	int work_out[57];	/* Output from GSX parameter array */
extern	int pxyarray[10];	/* input point array */

extern	int     i,j;            /* general or admiral purpose counterz */

extern	int	ftsave[4];	/* file-type save array */

extern	OBJECT	*sel_obj; 	/* pointer to object array */

extern	unsigned int	plot_color;		/* current plotting color */
extern	unsigned int	temp_color;		/* current plotting color temp */

extern	unsigned int	color_array[10][40];	/* shape array */
extern	unsigned int	temp_array[11][40];	/* temporary shape array */
extern	unsigned int	mask_array[10][40];	/* masks data array */

extern	char	path[64];	/* path name to selected drive */

extern	char	pathname[70];	/* full path name and drive */

extern	char	filename[13];	/* file name to load or save */

extern	int	fs_button;	/* file selection button */
extern	int	error;

extern	char	undo_area[32768];	/* save for operations */

extern	int	sh_changed;	/* flag for shape changed */
extern	int	max_color;	/* maximum color number for resolution */

extern	int	main_xor,mask_xor;	/* whether shapes are xored or not */
extern	int	mask_chek;		/* are we editing the mask? */

extern	char	base_name[27];

extern	int	comp_width,comp_height;	/* compiled height and width of shape */

extern	char	c_header[34];
extern	char	cdef_w[16];		/* c file header info */
extern	char	cdef_h[16];
extern	char	cdef_s[18];
extern	char	cstruc1[23];
extern	char	cstruc2[22];
extern	char	cstruc3[3];
extern	char	cstruc4[3];

extern	char	com_spc[3];		/* comma and a space */
extern	char	ret_lf[3];		/* return and linefeed */

extern	char	s_header[33];
extern	char	s_dcb[8];
extern	char	shap_str[30];
extern	int	drive;
