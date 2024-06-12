/*
 * The VDI library for GEM calls
 *
 */

extern int	ct0, ct1, ct2, ct3, ct4, ct5, ct6, ct7, ct8, ct9, ct10, ct11;
extern int	ii0, ii1, ii2, ii3, ii4, ii5, ii6, ii7, ii8, ii9,
		ii10, ii11, ii12, ii13, ii14, ii15;
extern int	io0, io1, io2, io3, io4, io5, io6, iox[40];
extern int	pi0, pi1, pi2, pi3, pi4, pi5, pi6, pi7, pix[6];
extern int	po0, po1, po2, po3, pox[12];
extern int 	*ai0, *ai1;
extern int	*ao0;
extern int	*vdi0, *vdi1, *vdi2, *vdi3, *vdi4, *vdi5;
extern int	global[16];


/* VDI routines for the GEM library */


/* 
 * GEM:VDI open virtual workstation 
 * 	"in" should point to work_in[11]
 * 	"out" should point to work_out[57];
 * 	"handle" is both input and output
 */

v_opnwk(in, handle, out) int *in, *handle, *out; {
	int i, j, *intin, *intout, *ptsout;
	ct0 = 1;
	ct1 = 0;
	ct3 = 11;
	ct6 = *handle;
	intin = &ii0;
	for (i = 0; i < 11; i++) intin[i] = in[i];
	vdi();
	intout = &io0;
	for (i = 0; i < 45; i++) out[i] = intout[i];
	ptsout = &po0;
	for (j = 0; j < 12; j++) out[i++] = ptsout[j];
	*handle = ct6;
}


v_opnvwk(in, handle, out) int *in, *handle, *out; {
	int i, j, *intin, *intout, *ptsout;
	ct0 = 100;
	ct1 = 0;
	ct3 = 11;
	ct6 = *handle;
	intin = &ii0;
	for (i = 0; i < 11; i++) intin[i] = in[i];
	vdi();
	intout = &io0;
	for (i = 0; i < 45; i++) out[i] = intout[i];
	ptsout = &po0;
	for (j = 0; j < 12; j++) out[i++] = ptsout[j];
	*handle = ct6;
}

vq_extnd(handle, owflag, out) int *out; {
	int i, j, *intout, *ptsout;
	ct0 = 102;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = owflag;
	vdi();
	intout = &io0;
	for (i = 0; i < 45; i++) out[i] = intout[i];
	ptsout = &po0;
	for (j = 0; j < 12; j++) out[i++] = ptsout[j];
}

/* GEM:VDI close the workstation */

v_clswk(handle) {
	ct0 = 2;
	ct6 = handle;
	ct1 = ct3 = 0;
	vdi();
}

v_clsvwk(handle) {
	ct0 = 101;
	ct6 = handle;
	ct1 = ct3 = 0;
	vdi();
}

/* GEM:VDI clear the workstation */

v_clrwk(handle) {
	ct0 = 3;
	ct1 = 0;
	ct3 = 0;
	ct6 = handle;
	vdi();
}

v_updwk(handle) {
	ct0 = 4;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi();
}

vst_load_fonts(handle,select) {
	ct0 = 119;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = select;
	vdi();
	return io0;
}

vst_unload_fonts(handle,select) {
	ct0 = 120;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	io0 = select;
	vdi();
}
	
/* GEM:VDI poly line output */

v_pline(handle, count, pxy) int *pxy; {
	ct0 = 6;
	ct1 = count;
	ct3 = 0;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &po0;
}

/* GEM:VDI put text on the screen */

v_gtext(handle, x, y, string) char *string; {
	int n, *intin;
	ct0 = 8;
	ct1 = 1;
	intin = &ii0;
	for (n = 0; string[n]; n++)
		intin[n] = string[n];
	ct3 = n;
	ct6 = handle;
	pi0 = x;
	pi0 = y;
	vdi();
}

/* 
 * GEM:VDI set clipping rectangle 
 *	flag = 0 	no clipping
 *	flag = 1	clipping on
 * 	pxy[] should contain the upper left and bottom right coords
 */

vs_clip(handle, flag, pxy) int *pxy; {
	ct0 = 129;
	ct1 = 2;
	ct3 = 1;
	ct6 = handle;
	ii0 = flag;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI polymarker output */

v_pmarker(handle, count, pxy) int *pxy; {
	ct0 = 7;
	ct1 = count;
	ct3 = 0;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI fill area */

v_fillarea(handle, count, pxy) int *pxy; {
	ct0 = 9;
	ct1 = count;
	ct3 = 0;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI cell array */

v_cellarray(handle,pxy,row_length,el_used,num_rows,wrt_mode,colarray)
	int *pxy, *colarray; {
	ct0 = 10;
	ct1 = 2;
	ct3 = num_rows * el_used;
	ct6 = handle;
	ct7 = row_length;
	ct8 = el_used;
	ct9 = num_rows;
	ct10 = wrt_mode;
	vdi1 = colarray;
	vdi2 = pxy;
	vdi();
	vdi1 = &ii0;
	vdi2 = &pi0;
}
	
/* GEM:VDI contour fill */

v_contourfill(handle, x, y, index) {
	ct0 = 103;
	ct1 = 1;
	ct3 = 1;
	ct6 = handle;
	ii0 = index;
	pi0 = x;
	pi1 = y;
	vdi();
}

/* GEM:VDI rectangle fill */

vr_recfl(handle, pxy) int *pxy; {
	ct0 = 114;
	ct1 = 2;
	ct3 = 0;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI bar graph */

v_bar(handle, pxy) int *pxy; {
	ct0 = 11;
	ct1 = 2;
	ct3 = 0;
	ct5 = 1;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI arc */

v_arc(handle, x, y, rad, b_angle, e_angle) {
	int i, *ptsin;
	ct0 = 11;
	ct1 = 4;
	ct3 = 2;
	ct5 = 2;
	ct6 = handle;
	ii0 = b_angle;
	ii1 = e_angle;
	pi0 = x;
	pi1 = y;
	pi6 = rad;
	pi2 = pi3 = pi4 = pi5 = pi7 = 0;
	vdi();
}

/* GEM:VDI pie */

v_pieslice(handle, x, y, rad, b_angle, e_angle) {
	int i;
	ct0 = 11;
	ct1 = 4;
	ct3 = 2;
	ct5 = 3;
	ct6 = handle;
	ii0 = b_angle;
	ii1 = e_angle;
	pi0 = x;
	pi1 = y;
	pi6 = rad;
	pi2 = pi3 = pi4 = pi5 = pi7 = 0;
	vdi();
}

/* GEM:VDI circle */

v_circle(handle, x, y, rad) {
	int i;
	ct0 = 11;
	ct1 = 3;
	ct3 = 0;
	ct5 = 4;
	ct6 = handle;
	pi0 = x;
	pi1 = y;
	pi4 = rad;
	pi2 = pi3 = pi5 = 0;
	vdi();
}

/* GEM:VDI elliptical arc */

v_ellarc(handle, x, y, xrad, yrad, b_angle, e_angle) {
	int i;
	ct0 = 11;
	ct1 = 2;
	ct3 = 2;
	ct5 = 6;
	ct6 = handle;
	ii0 = b_angle;
	ii1 = e_angle;
	pi0 = x;
	pi1 = y;
	pi2 = xrad;
	pi3 = yrad;
	vdi();
}

/* GEM:VDI elliptical pie */

v_ellpie(handle, x, y, xrad, yrad, b_angle, e_angle) {
	int i;
	ct0 = 11;
	ct1 = 2;
	ct3 = 2;
	ct5 = 7;
	ct6 = handle;
	ii0 = b_angle;
	ii1 = e_angle;
	pi0 = x;
	pi1 = y;
	pi2 = xrad;
	pi3 = yrad;
	vdi();
}

/* GEM:VDI ellipse */

v_ellipse(handle, x, y, xrad, yrad) {
	ct0 = 11;
	ct1 = 2;
	ct3 = 0;
	ct5 = 5;
	ct6 = handle;
	pi0 = x;
	pi1 = y;
	pi2 = xrad;
	pi3 = yrad;
	vdi();
}

/* GEM:VDI rounded box */

v_rbox(handle, pxy) int *pxy; {
	ct0 = 11;
	ct1 = 2;
	ct3 = 0;
	ct5 = 8;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI rounded filled box */

v_rfbox(handle, pxy) int *pxy; {
	ct0 = 11;
	ct1 = 2;
	ct3 = 0;
	ct5 = 9;
	ct6 = handle;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI put justified text on the screen */

v_justified(handle, x, y, string, len, wspace, cspace) char *string; {
	int *ip;
	ct0 = 11;
	ct1 = 2;
	ct6 = handle;
	ii0 = wspace;
	ii1 = cspace;
	ip = &ii2;
	for (ct3 = 2; *ip++ = *string++; ct3++)
		;
	pi0 = x;
	pi1 = y;
	pi2 = len;
	vdi();
}

/* GEM:VDI set drawing mode */

vswr_mode(handle, mode) { return vset(handle, 32, mode); }

/* GEM:VDI set color */

vs_color(handle, index, rgb) int *rgb; {
	ct0 = 14;
	ct1 = 0;
	ct3 = 4;
	ct6 = handle;
	ii0 = index;
	ii1 = rgb[0];
	ii2 = rgb[1];
	ii3 = rgb[2];
	vdi();
}

/* GEM:VDI set line color */

vsl_color(handle, color) { return vset(handle, 17, color); }

/* GEM:VDI set line type */

vsl_type(handle, type) { return vset(handle, 15, type); }

/* GEM:VDI set marker type */

vsm_type(handle, type) { return vset(handle, 18, type); }

/* GEM:VDI set marker height */

vsm_height(handle, height) {
	ct0 = 19;
	ct1 = 1;
	ct3 = 0;
	ct6 = handle;
	pi0 = 0;
	pi1 = height;
	vdi();
	return po1;
}

/* GEM:VDI set user defined line type */

vsl_udsty(handle, pattern) { return vset(handle, 113, pattern); }

/* GEM:VDI set the width of a line */

vsl_width(handle, width) { 
	ct0 = 16;
	ct1 = 1;
	ct3 = 0;
	ct6 = handle;
	pi0 = width;
	pi1 = 0;
	vdi();
	return po0;
}

/* GEM:VDI line end style  */

vsl_ends(handle, begin, end) {
	ct0 = 108;
	ct1 = 0;
	ct2 = 2;
	ct6 = handle;
	ii0 = begin;
	ii1 = end;
	vdi();
}

/* GEM:VDI set marker color */

vsm_color(handle, color) { return vset(handle, 20, color); }

/* GEM:VDI set text height, returns char size and cell(box) size  */

vst_height(handle, h, cw, ch, bw, bh) int *cw, *ch, *bw, *bh; {
	ct0 = 12;
	ct1 = 1;
	ct3 = 0;
	ct6 = handle;
	pi0 = 0;
	pi1 = h;
	vdi();
	*cw = po0;
	*ch = po1;
	*bw = po2;
	*bh = po3;
}

/* GEM:VDI set text height, returns char size and cell(box) size  */

vst_point(handle, point, cw, ch, bw, bh) int *cw, *ch, *bw, *bh; {
	ct0 = 107;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = point;
	vdi();
	*cw = po0;
	*ch = po1;
	*bw = po2;
	*bh = po3;
}

/* GEM:VDI set text baseline rotation */

vst_rotation(handle, angle) { return vset(handle, 13, angle); }

/* GEM:VDI set text face */

vst_font(handle, font) { return vset(handle, 21, font); }

/* GEM:VDI set color of the text */

vst_color(handle, color) { return vset(handle, 22, color); }

/* 
 * GEM:VDI set effects of the text 
 *	bit 0	bold
 *	bit 1	light
 *	bit 2	italic
 *	bit 3	underline
 *	bit 4	outline
 *	bit 5	shadowed
 */
 

vst_effects(handle, effect) { return vset(handle, 106, effect); }

/* GEM:VDI set text alignment  */

vst_alignment(handle, hor, ver, nhor, nver) int *nhor, *nver; {
	ct0 = 39;
	ct1 = 0;
	ct3 = 2;
	ct6 = handle;
	ii0 = hor;
	ii0 = ver;
	vdi();
	*nhor = io0;
	*nver = io1;
}

/* GEM:VDI set fill interior */

vsf_interior(handle, style) { return vset(handle, 23, style); }

/* GEM:VDI set fill style index  */

vsf_style(handle, style) { return vset(handle, 24, style); }

/* GEM:VDI set fill color index */

vsf_color(handle, color) { return vset(handle, 25, color); }

/* GEM:VDI set perimeter visibility */

vsf_perimeter(handle, visible) { return vset(handle, 105, visible); }

/* GEM:VDI set user defined fill pattern */

vsf_updat(handle, pat, count) int *pat; {
	ct0 = 112;
	ct1 = 0;
	ct3 = count * 16;
	ct6 = handle;
	vdi1 = pat;
	vdi();
	vdi1 = &ii0;
}

/* GEM:VDI set an attribute */

vset(handle, op, arg) {
	ct0 = op;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = arg;
	vdi();
	return io0;
}

/* GEM:VDI copy raster opaque */

vro_cpyfm( handle, wr_mode, pxy, srcmfdb, desmfdb) 
	int *pxy, *srcmfdb, *desmfdb; {
	ct0 = 109;
	ct1 = 4;
	ct3 = 1;
	ct6 = handle;
	ct7 = srcmfdb;
	ct9 = desmfdb;
	ii0 = wr_mode;
	vdi2 = pxy;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI copy raster transparent */

vrt_cpyfm(handle,wr_mode,pxy,srcmfdb,desmfdb,color_index) 
	int *pxy, *srcmfdb, *desmfdb, *color_index; {
	ct0 = 121;
	ct1 = 4;
	ct3 = 3;
	ct6 = handle;
	ii0 = wr_mode;
	vdi2 = pxy;
	ii1 = color_index[0];
	ii2 = color_index[1];
	ct7 = srcmfdb;
	ct9 = desmfdb;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI transform form */

vr_trnfm(handle, srcmfdb, desmfdb) int *srcmfdb, *desmfdb; {
	ct0 = 110;
	ct1 = ct3 = 0;
	ct6 = handle;
	ct7 = srcmfdb;
	ct9 = desmfdb;
	vdi();
}

/* GEM:VDI get pixel */

v_get_pixel(handle, x, y, pel, index) int *pel, *index; {
	ct0 = 105;
	ct1 = 1;
	ct2 = 0;
	ct6 = handle;
	pi0 = x;
	pi1 = y;
	vdi();
	*pel = io0;
	*index = io1;
}

/* GEM:VDI set input mode */

vsin_mode(handle, dev_type, mode) {
	ct0 = 33;
	ct1 = 0;
	ct3 = 2;
	ct6 = handle;
	ii0 = dev_type;
	ii1 = mode;
	vdi();
}

/* GEM:VDI input locator, request mode */

vrq_locator( handle, x, y, xout, yout, term) int *xout, *yout, *term; {
	ct0 = 28;
	ct1 = 1;
	ct3 = 0;
	ct6 = handle;
	pi0 = x;
	pi1 = y;
	vdi();
	*xout = po0;
	*yout = po1;
	*term = io0;
}

/* GEM:VDI input locator, sample mode */

vsm_locator(handle, x, y, xout, yout, term) int *xout, *yout, *term; {
	ct0 = 28;
	ct1 = 1;
	ct3 = 0;
	ct6 = handle;
	pi0 = x;
	pi1 = y;
	vdi();
	*xout = po0;
	*yout = po1;
	*term = io0;
	return (ct2 | (ct4 << 1));
}

/* GEM:VDI input valuator, request mode */

vrq_valuator(handle, valuator_in, valuator_out, terminator)
	int *valuator_out, *terminator; {
	ct0 = 29;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = valuator_in;
	vdi();
	*valuator_out = io0;
	*terminator - io1;
}

/* GEM:VDI input valuator, sample mode */

vsm_valuator(handle, valuator_in, valuator_out, terminator, status)
	int *valuator_out, *terminator, *status; {
	ct0 = 29;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = valuator_in;
	vdi();
	*valuator_out = io0;
	*terminator - io1;
	*status = ct4;
}

/* GEM:VDI input choice, request mode */

vrq_choice(handle, ch_in, ch_out) int *ch_out; {
	ct0 = 30;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = ch_in;
	vdi();
	*ch_out = io0;
}

/* GEM:VDI input choice, request mode */

vsm_choice(handle, choice) int *choice; {
	ct0 = 30;
	ct1 = 0;
	ct3 = 0;
	ct6 = handle;
	vdi();
	*choice = io0;
	return ct4;
}

/* GEM:VDI input string, request mode */

vrq_string(handle, max_length, echo_mode, echo_xy, string) 
	int *echo_xy; char *string; {
	char *temp;
	ct0 = 31;
	ct1 = 1;
	ct3 = 2;
	ct6 = handle;
	ii0 = max_length;
	ii1 = echo_mode;
	pi0 = echo_xy[0];
	pi1 = echo_xy[1];
	vdi();
	temp = &io0;
	while (*string++ = *temp++)
	  ;
}

/* GEM:VDI input string, sample mode */

vsm_string(handle, max_length, echo_mode, echo_xy, string) 
	int *echo_xy; char *string; {
	char *temp;
	ct0 = 31;
	ct1 = 1;
	ct3 = 2;
	ct6 = handle;
	ii0 = max_length;
	ii1 = echo_mode;
	pi0 = echo_xy[0];
	pi1 = echo_xy[1];
	vdi();
	temp = &io0;
	while (*string++ = *temp++)
	  ;
	return ct4;
}

/* GEM:VDI set mouse form */

vsc_form(handle, pcur_form) int *pcur_form; {
	ct0 = 111;
	ct1 = 0;
	ct3 = 37;
	ct6 = handle;
	vdi1 = pcur_form;
	vdi();
	vdi1 = &ii0;
}

/* GEM:VDI exchange timer interrupt vector */

vex_timv(handle, tim_addr, otim_addr, tim_conv) 
	int *tim_addr, *otim_addr, *tim_conv; {
	ct0 = 118;
	ct1 = 0;
	ct3 = 0;
	ct6 = handle;
	ct7 = tim_addr;
	vdi();
	*otim_addr++ = ct9;
	*otim_addr = ct10;
	*tim_conv = io0;
}

/* GEM:VDI show cursor */

v_show_cur(handle, reset) {
	ct0 = 122;
	ct1 = 1;
	ct6 = handle;
	ii0 = reset;
	vdi();
}

/* GEM:VDI hide cursor */

v_hide_c( handle ) {
	ct0 = 123;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi();
}

/* GEM:VDI sample mouse button state */

vq_mouse(handle, pstatus, x, y) int *pstatus, *x, *y; {
	ct0 = 124;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi();
	*pstatus = io0;
	*x = po0;
	*y = po1;
}

/* GEM:VDI exchange button change vector */

vex_butv(handle, pusrcode, psavcode) int *pusrcode, *psavcode; {
	ct0 = 125;
	ct1 = ct3 = 0;
	ct6 = handle;
	ct7 = pusrcode;
	vdi();
	*psavcode++ = ct9;
	*psavcode = ct10;
}

/* GEM:VDI exchange mouse movemnt vector */

vex_motv(handle, pusrcode, psavcode) int *pusrcode, *psavcode; {
	ct0 = 126;
	ct1 = ct3 = 0;
	ct6 = handle;
	ct7 = pusrcode;
	vdi();
	*psavcode++ = ct9;
	*psavcode = ct10;
}

/* GEM:VDI exchange cursor change vector */

vex_curv(handle, pusrcode, psavcode) int *pusrcode, *psavcode; {
	ct0 = 127;
	ct1 = ct3 = 0;
	ct6 = handle;
	ct7 = pusrcode;
	vdi();
	*psavcode++ = ct9;
	*psavcode++ = ct10;
}

/* GEM:VDI sample keyboard state information */

vq_key_s(handle, pstatus) int *pstatus; {
	ct0 = 128;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi();
	*pstatus = io0;
}

/* GEM:VDI inqure color representation */

vq_color(handle, color_index, set_flag, rgb) int *rgb; {
	ct0 = 26;
	ct1 = 0;
	ct3 = 2;
	ct6 = handle;
	ii0 = color_index;
	ii1 = set_flag;
	vdi3 = rgb;
	vdi();
	vdi3 = &io0;
}

/* GEM:VDI inquire current polyline attrtibutes */
vql_attributes(handle, attrib) int *attrib; {
	ct0 = 35;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi3 = attrib;
	vdi();
	vdi3 = &io0;
	attrib[3] = po0;
}

/* GEM:VDI inquire current polymaarker attributes */

vqm_attributes(handle, attrib) int *attrib; {
	ct0 = 36;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi3 = attrib;
	vdi();
	vdi3 = &io0;
	attrib[3] = po1;
}

/* GEM:VDI inquire current fill area attributes */

vqf_attributes(handle, attrib) int *attrib; {
	ct0 = 37;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi3 = attrib;
	vdi();
	vdi3 = &io0;
}

/* GEM:VDI inquire current graphic text attributes */

vqt_attributes(handle, attrib) int *attrib; {
	ct0 = 38;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi3 = attrib;
	vdi4 = &attrib[6];
	vdi();
	vdi3 = &io0;
	vdi4 = &po0;
}

/* GEM:VDI inquire text extent */

vqt_extent(handle, string, extent) int *extent; char *string; {
	char *temp;
	ct0 = 116;
	ct1 = 0;
	ct6 = handle;
	vdi4 = extent;
	temp = &ii0;
	for (ct3 = 0;*temp++ = *string++;ct3++)
	   ;
	vdi();
	vdi4 = &po0;
}

/* GEM:VDI inquire character cell width */

vqt_width(handle,charac,cwid,ldelt,rdelt) int *cwid, *ldelt, *rdelt; {
	ct0 = 117;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = charac;
	vdi();
	*cwid = po0;
	*ldelt = po2;
	*rdelt = pox[0];
	return io0;
}

/* GEM:VDI inquire face name and index */

vqt_name(handle, enum, name) char *name; {
	ct0 = 130;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = enum;
	vdi3 = name;
	vdi();
	vdi3 = &io0;
	return io0;
}

/* GEM:VDI inquire cell array */

vq_cellarray( handle, pxy, rowlen, nrows, elused, rowsused, status, carray )
		int *pxy, *elused, *rowsused, *status, *carray; {
	int i;
	ct0 = 27;
	ct1 = 2;
	ct3 = 0;
	ct6 = handle;
	vdi2 = pxy;
	vdi3 = carray;
	ct7 = rowlen;
	ct8 = nrows;
	vdi();
	vdi2 = &pi0;
	vdi3 = &io0;
	*elused = ct9;
	*rowsused = ct10;
	*status = ct11;
}

/* GEM:VDI inquire input mode */

vqin_mode(handle, devtype, inpmode) int *inpmode; {
	ct0 = 115;
	ct1 = 0;
	ct3 = 1;
	ct6 = handle;
	ii0 = devtype;
	vdi();
	*inpmode = io0;
}

/* GEM:VDI inquire current face information */

vqt_fontinfo(handle, minade, maxade, dist, maxwid, effects)
		int *minade, *maxade, *dist, *maxwid, *effects; {
	ct0 = 131;
	ct1 = ct3 = 0;
	ct6 = handle;
	vdi();
	*minade = io0;
	*maxade = io1;
	dist[0] = po1;
	dist[1] = po3;
	dist[2] = pox[1];
	dist[3] = pox[3];
	dist[3] = pox[5];
	*maxwid = po0;
	effects[0] = po2;
	effects[1] = pox[0];
	effects[2] = pox[2];
}

/* GEM:VDI inquire addressable alpha character cells */

vq_chchells(handle, rows, columns) int *rows, *columns; {
	vesc(handle, 1);
	*rows = io0;
	*columns = io1;
}

/* GEM:VDI exit alpha mode */

v_exit_cur(handle)  { 
	vesc(handle, 2);
}

/* GEM:VDI enter alpha mode */

v_enter_cur(handle) { 
	vesc(handle, 3);
}

/* GEM:VDI alpha cursor up */

v_curup(handle) {
	vesc(handle, 4);
}

/* GEM:VDI alpha cursor down */

v_curdown(handle) {
	vesc(handle, 5);
}

/* GEM:VDI alpha cursor right */

v_curright(handle) {
	vesc(handle, 6);
}

/* GEM:VDI alpha cursor left */

v_curleft(handle) {
	vesc(handle, 7);
}

/* GEM:VDI alpha cursor home */

v_curhome(handle) {
	vesc(handle, 8);
}

/* GEM:VDI erase to end of alpha screen */

v_eeos(handle) {
	vesc(handle, 9);
}

/* GEM:VDI erase to end of alpha text line */

v_eeol(handle) {
	vesc(handle, 10);
}

/* GEM:VDI direct alpha cursor address */

v_curaddress(handle, row, column) {
	ii0 = row;
	ii1 = column;
	ct0 = 5;
	ct1 = 0;
	ct3 = 2;
	ct5 = 11;
	ct6 = handle;
	vdi();
}

/* GEM:VDI output cursor addressable alpha text */

v_curtext(handle, string) char *string; {
	int *temp;
	temp = &ii0;
	while (*temp++ = *string++)
	   ;	
	vesc(handle, 12);
}

/* GEM:VDI reverse video on */

v_rvon(handle) {
	vesc(handle, 13);
}

/* GEM:VDI reverse video off */

v_rvoff(handle) {
	vesc(handle, 14);
}

/* GEM:VDI inquire current alpha cursor address */

vq_curaddress(handle, row, column) int *row, *column; {
	vesc(handle, 15);
	*row = io0;
	*column = io1;
}

/* GEM:VDI inquire tablet status */

vq_tabstatus(handle) {
	vesc(handle, 16);
	return io0;
}

/* GEM:VDI hard copy */

v_hardcopy(handle) {
	vesc(handle, 17);
}

/* GEM:VDI place graphic cursor at location */

v_dspcur(handle, x, y) {
	pi0 = x;
	pi1 = y;
	ct0 = 5;
	ct1 = 1;
	ct3 = 0;
	ct5 = 18;
	ct6 = handle;
	vdi();
}

/* GEM:VDI remove last graphic cursor */

v_rmcur(handle) {
	vesc(handle, 19);
}

/* GEM:VDI form advance */

v_form_adv(handle) {
	vesc(handle, 20);
}

/* GEM:VDI output window */

v_output_window(handle, xyarray) int *xyarray; {
	ct0 = 5;
	ct1 = 2;
	ct3 = 0;
	ct5 = 21;
	ct6 = handle;
	vdi2 = xyarray;
	vdi();
	vdi2 = &pi0;
}
	
/* GEM:VDI clear display list */

v_clear_disp_list(handle) {
	vesc(handle, 22);
}

/* GEM:VDI output bit image file */

v_bit_image(handle, filename, aspect, scaling, npts, xyarray) 
		char *filename; int *xyarray; {
	int *temp;
	ct0 = 5;
	ct1 = npts;
	ii0 = aspect;
	ii1 = scaling;
	temp = &ii2;
	for (ct3 = 2;*temp++ = *filename;ct3++)
	  ;
	ct5 = 23;
	ct6 = handle;
	vdi2 = xyarray;
	vdi();
	vdi2 = &pi0;
}

/* GEM:VDI select palette */

vs_palette(handle, palette) {
	ct0 = 5;
	ct1 = 0;
	ct3 = 1;
	ct5 = 60;
	ct6 = handle;
	ii0 = palette;
	vdi();
	return io0;
}

/* GEM:VDI inquire palette film types */

vqp_flims(handle,fmnames) char *fmnames; {
	int *temp,i;
	vesc(handle, 91);
	temp = &io0;
	for (i=0;i<125;i++)
	  *fmnames++ = *temp++;
}
	
/* GEM:VDI inquire palette driver state */

vqp_state(handle, port, fmname, lness, ilace, planes, indexes) 
		int *port, *fmname, *lness, *ilace, *planes, *indexes; {
	int *temp,i;
	vesc(handle, 22);
	*port = io0;
	*fmname = io1;
	*lness = io2;
	*ilace = io3;
	*planes = io4;
	temp = &io5;
	for (i=5;i<21;i++)
	  *indexes++ = *temp++;
}

/* GEM:VDI escape function caller */

vsp_state(handle, port,fmnum, lness, ilace, planes, indexes)
		int *indexes; {
	int *temp,i;

	ct0 = 5;
	ct1 = 0;
	ct3 = 20;
	ct5 = 93;
	ct6 = handle;
	ii0 = port;
	ii1 = fmnum;
	ii2 = lness;
	ii3 = ilace;
	ii4 = planes;
	temp = &ii5;
	for (i=5;i<21;i++)
	  *temp++ = *indexes++;
	vdi();
}

/* GEM:VDI save palette driver state */

vsp_save(handle) {
	vesc(handle, 94);
}

/* GEM:VDI supress palette messages */

vsp_message(handle) {
	vesc(handle, 95);
}

/* GEM:VDI palette error inquire */

vqp_error(handle) {
	vesc(handle, 96);
	return io0;
}

/* GEM:VDI update metafile extents */

v_meta_extents(handle, minx, miny, maxx, maxy) {
	ct0 = 5;
	ct1 = 2;
	ct3 = 0;
	ct5 = 98;
	ct6 = handle;
	pi0 = minx;
	pi1 = miny;
	pi2 = maxx;
	pi3 = maxy;
	vdi();
}

/* GEM:VDI write metafile item */

v_write_meta(handle,numii,ii,numpi,pi) {
	ct0 = 5;
	ct1 = numpi;
	ct3 = numii;
	ct6 = handle;
	vdi2 = pi;
	vdi1 = ii;
	vdi();
	vdi2 = &pi0;
	vdi1 = &ii0;
}

/* GEM:VDI change gem vdi filename */

vm_filename(handle, filename) char *filename; {
	int *temp;
	ct0 = 5;
	ct1 = 0;
	temp = &ii0;
	for (ct3=1;*temp++ = *filename++;ct3++)
	  ;
	ct5 = 100;
	ct6 = handle;
	vdi();
}

/* GEM:VDI escape function caller */

vesc(handle, funcid) {
	ct0 = 5;
	ct1 = ct3 = 0;
	ct5 = funcid;
	ct6 = handle;
	vdi();
}

vdi() {
	/* 
         * load address of vdi parameter block into a0
         * transfer a0 to d1
         * load 115 into d0
         * trap #2
         */
	asm( lag vdi0 0   tad 0 1   ldw 115 0   trp 2 );
}
