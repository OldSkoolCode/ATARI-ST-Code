/* 
 * the AES library
 * contains AES calls for GEM
 */

extern int	ct0, ct1, ct2, ct3, ct4, ct5, ct6;
extern int	ii0, ii1, ii2, ii3, ii4, ii5, ii6, ii7, ii8, ii9,
		ii10, ii11, ii12, ii13, ii14, ii15;
extern int	io0, io1, io2, io3, io4, io5, io6, iox[40];
extern int	pi0, pi1, pi2, pi3, pi4, pi5, pi6, pi7, pix[6];
extern int	po0, po1, po2, po3, pox[12];
extern int 	*ai0, *ai1;
extern int	*ao0;
extern int	*aes0, *aes1, *aes2, *aes3, *aes4, *aes5;
extern int	*vdi0, *vdi1, *vdi2, *vdi3, *vdi4;
extern int	global[16];

/* 
 * the c runtime start up routine for GEM processes
 * no argv argc stuff, no stdio (use TOS routines for file access)
 *
 * assumes a startup prg.s of
 *	. _bstk 2048
 *	. _estk 4
 *	taa 7 6
 *	lll 4 0
 *	sgl _estk
 *	lag _estk 7
 *	jsr _cprg
 * plus definitions for all the above externs
 */

#define SETBLK	0x4A
#define EXIT	0x4C

_cprg(tpa) long tpa; {
	int i;
	long x, *lp;

	/* compute size of program, give memory back to TOS */
	lp = tpa;
	x = lp[3] + lp[5] + lp[7] + 0x100;
	if (trap(1, SETBLK, 0, tpa, x))
		appl_exit(-1);

	/* set up the aespb and vdipb arrays */
	aes0 = &ct0;
	aes1 = global;
	aes2 = &ii0;
	aes3 = &io0;
	aes4 = &ai0;
	aes5 = &ao0;
	vdi0 = &ct0;
	vdi1 = &ii0;
	vdi2 = &pi0;
	vdi3 = &io0;
	vdi4 = &po0;
	
	/* run the program */
	i = main();

	/* close up shop */
	appl_exit(i);
}

/* GEM application handling */

appl_init() {
	ct0 = 10;
	ct2 = 1;
	ct1 = ct3 = ct4 = 0;
	aes();
	return io0;
}

appl_read(id,length,pbuff) char *pbuff; {
	ct0 = 11;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0= id;
	ii1 = length;
	ai0 = pbuff;
	aes();
	return io0;
}

appl_write(id,length,pbuff) char *pbuff; {
	ct0 = 12;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0= id;
	ii1 = length;
	ai0 = pbuff;
	aes();
	return io0;
}

appl_find(pname) char *pname; {
	ct0 = 13;
	ct1 = ct4 = 0;
	ct2 = ct3 = 1;
	ai0 = pname;
	aes();
	return io0;
}

appl_tplay(mem,num,scale) char *mem; {
	ct0 = 14;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0= num;
	ii1 = scale;
	ai0 = mem;
	aes();
	return io0;
}

appl_trecord(mem,count) char *mem; {
	ct0 = 15;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = count;
	ai0 = mem;
	aes();
	return io0;
}

appl_exit(i) { trap(1, EXIT, i); }


/* GEM Event handling library */

evnt_keybd() {
	ct0 = 20;
	ct1 = ct3 = ct4 = 0;
	ct2 = 1;
	aes();
	return io0;
}

evnt_button(clicks,mask,state,mx,my,button,kstate) 
		int *mx,*my,*button,*kstate; {
	ct0 = 21;
	ct1= 3;
	ct2 = 5;
	ct3 = ct4 = 0;
	ii0 = clicks;
	ii1 = mask;
	ii2 = state;
	aes();
	*mx = io1;
	*my = io2;
	*button = io3;
	*kstate = io4;
	return io0;
}

evnt_mouse(flags,x,y,width,height,mx,my,button,kstate)
		int *mx,*my,*button,*kstate; {
	ct0 = 22;
	ct1 = ct2 = 5;
	ct3 = ct4 = 0;
	ii0 = flags;
	ii1 = x;
	ii2 = y;
	ii3 = width;
	ii4 = height;
	aes();
	*mx = io1;
	*my = io2;
	*button = io3;
	*kstate = io4;
	return io0;
}

evnt_mesag(pbuff) char *pbuff; {
	ct0 = 23;
	ct1 = ct4 = 0;
	ct2 = ct3 = 1;
	ai0 = pbuff;
	aes();
	return io0;
}

evnt_timer(locount,hicount) {
	ct0 = 24;
	ct1 = 2;
	ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = locount;
	ii1 = hicount;
	aes();
	return io0;
}

evnt_multi(flags,bclicks,bmask,bstate,mlflags,mlx,mly,mlwidth,mlheight,
	m2flags,m2x,m2y,m2width,m2height,mgpbuff,tlocount,thicount,
	mox,moy,mobutton,mokstate,kreturn,breturn) 
	int *mox,*moy,*mobutton,*mokstate,*kreturn,*breturn; char *mgpbuff; {

	ct0 = 25;
	ct1 = 16;
	ct2 = 7;
	ct3 = 1;
	ct4 = 0;
	ii0 = flags;
	ii1 = bclicks;
	ii2 = bmask;
	ii3 = mlflags;
	ii4 = mlflags;
	ii5 = mlx;
	ii6 = mly;
	ii7 = mlwidth;
	ii8 = mlheight;
	ii9 = m2flags;
	ii10 = m2x;
	ii11 = m2y;
	ii12 = m2width;
	ii13 = m2height;
	ii14 = tlocount;
	ii15 = thicount;
	ai0 = mgpbuff;
	aes();
	*mox = io1;
	*moy = io2;
	*mobutton = io3;
	*mokstate = io4;
	*kreturn = io5;
	*breturn = io6;
	return io0;
}

evnt_dclick(new,getset) {
	ct0 = 26;
	ct1 = 2;
	ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = new;
	ii1 = getset;
	aes();
	return io0;
}

/* AES: resource handling */
	
rsrc_load(pfname) char *pfname; {
	ct0 = 110;
	ct1 = ct4 = 0;
	ct2 = ct3 = 1;
	ai0 = pfname;
	aes();
	return io0;
}

rsrc_free() {
	ct0 = 111;
	ct1 = ct3 = ct4 = 0;
	ct2 = 1;
	aes();
	return io0;
}

rsrc_gaddr(type, index, addr) long **addr; {
	ct0 = 112;
	ct1 = 2;
	ct2 = ct4 = 1;
	ct3 = 0;
	ii0 = type;
	ii1 = index;
	aes();
	*addr = ao0;
	return io0;
}

rsrc_saddr(type, index, addr) long *addr; {
	ct0 = 113;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = type;
	ii1 = index;
	ai0 = addr;
	aes();
	return io0;
}

rsrc_obfix(tree,object) int *tree; {
	ct0 = 114;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = object;
	ai0 = tree;
	aes();
	return io0;
}

/* shell handling */

shel_read(pcmd,ptail) char *pcmd, *ptail; {
	ct0 = 120;
	ct1 = ct4 = 0;
	ct2 = 1;
	ct3 = 2;
	ai0 = pcmd;
	ai1 = ptail;
	aes();
	return io0;
}

shel_write(doex,isgr,iscr,pcmd,ptail) char *pcmd, *ptail; {
	ct0 = 121;
	ct1 = 3;
	ct2 = 1;
	ct3 = 2;
	ct4 = 0;
	ii0 = doex;
	ii1 = isgr;
	ii2 = iscr;
	ai0 = pcmd;
	ai1 = ptail;
	aes();
	return io0;
}

shel_find(pbuff) char *pbuff; {
	ct0 = 124;
	ct1 = ct4 = 0;
	ct2 = ct3 = 1;
	ai0 = pbuff;
	aes();
	return io0;
}

shel_envrn(pvalue,parm) long *pvalue; char *parm; {
	ct0 = 125;
	ct1 = ct4 = 0;
	ct2 = 1;
	ct3 = 3;
	ai0 = pvalue;
	ai1 = parm;
	aes();
	return io0;
}

/* graphics handling */

graf_handle(wchar, hchar, wbox, hbox) int *wchar, *hchar, *wbox, *hbox; {
	ct0 = 77;
	ct2 = 5;
	ct1 = ct3 = ct4 = 0;
	aes();
	*wchar = io1;
	*hchar = io2;
	*wbox = io3;
	*hbox = io4;
	return io0;
}

graf_rubberbox(x, y, minw, minh, lastw, lasth) int *lastw, *lasth; { 
	ct0 = 70;
	ct1 = 4;
	ct2 = 3;
	ct3 = ct4 = 0;
	ii0 = x;
	ii1 = y;
	ii2 = minw;
	ii3 = minh;
	aes();
	*lastw = io1;
	*lasth = io2;
	return io0;
}

graf_dragbox(dw, dh, sx, sy, bx, by, bw, bh, endx, endy) int *endx, *endy; {
	ct0 = 71;
	ct1 = 8;
	ct2 = 3;
	ct3 = ct4 = 0;
	ii0 = dw;
	ii1 = dh;
	ii2 = sx;
	ii3 = sy;
	ii4 = bx;
	ii5 = by;
	ii6 = bw;
	ii7 = bh;
	aes();
	*endx = io1;
	*endy = io2;
	return io0;
}

graf_movebox(w, h, sx, sy, dx, dy) {
	ct0 = 72;
	ct1 = 6;
	ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = w;
	ii1 = h;
	ii2 = sx;
	ii3 = sy;
	ii4 = dx;
	ii5 = dy;
	aes();
	return io0;
}

graf_growbox(bx, by, bw, bh, ex, ey, ew, eh) {
	ct0 = 73;
	ct1 = 8;
	ct2 = 1;
	ct3 = ct4 = 0;
	aes2 = &bx;
	aes();
	aes2 = &ii0;
	return io0;
}
	
graf_shrinkbox(ex, ey, ew, eh, bx, by, bw, bh) {
	ct0 = 73;
	ct1 = 8;
	ct2 = 1;
	ct3 = ct4 = 0;
	aes2 = &ex;
	aes();
	aes2 = &ii0;
	return io0;
}

graf_watchbox(tree, obj, instate, outstate) int *tree; { 
	ct0 = 75;
	ct1 = 4;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii1 = obj;
	ii2 = instate;
	ii3 = outstate;
	ai0 = tree;
	aes();
	return io0;
}

graf_slidebox(tree, parent, obj, vh) int *tree; { 
	ct0 = 76;
	ct1 = 3;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = parent;
	ii1 = obj;
	ii2 = vh;
	ai0 = tree;
	aes();
	return io0;
}

graf_mouse(type, shape) int *shape; { 
	ct0 = 78;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = type;
	ai0 = shape;
	aes();
	return io0;
}

graf_mkstate(x, y, mstate, kstate) int *x, *y, *mstate, *kstate; { 
	ct0 = 79;
	ct1 = ct3 = ct4 = 0;
	ct2 = 5;
	aes();
	*x = io1;
	*y = io2;
	*mstate = io3;
	*kstate = io4;
	return io0;
}

/* scrap handling */

scrp_read(pscrap) char *pscrap; {
	ct0 = 80;
	ct1 = ct4 = 0;
	ct2 = ct3 = 1;
	ai0 = pscrap;
	return io0;
}

scrp_write(pscrap) char *pscrap; {
	ct0 = 81;
	ct1 = ct4 = 0;
	ct2 = ct3 = 1;
	ai0 = pscrap;
	return io0;
}

/* file selector handling */

fsel_input(inpath,insel,exbutton) char *inpath, *insel; int *exbutton; {
	ct0 = 90;
	ct1 = ct4 = 0;
	ct2 = ct3 = 2;
	ai0 = inpath;
	ai1 = insel;
	aes();
	*exbutton = io1;
	return io0;
}

/* window handling */

wind_get(handle, gfld, gw1, gw2, gw3, gw4) int *gw1, *gw2, *gw3, *gw4; {
	ct0 = 104;
	ct1 = 2;
	ct2 = 5;
	ct3 = ct4 = 0;
	ii0 = handle;
	ii1 = gfld;
	aes();
	*gw1 = io1;
	*gw2 = io2;
	*gw3 = io3;
	*gw4 = io4;
	return io0;
}

wind_create(kind, x, y, w, h) {
	ct0 = 100;
	ct1 = 5;
	ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = kind;
	ii1 = x;
	ii2 = y;
	ii3 = w;
	ii4 = h;
	aes();
	return io0;
}

wind_set(handle, field, s1, s2, s3, s4) {
	ct0 = 105;
	ct1 = 6;
	ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = handle;
	ii1 = field;
	ii2 = s1;
	ii3 = s2;
	ii4 = s3;
	ii5 = s4;
	aes();
	return io0;
}

wind_open(handle, x, y, w, h) {
	ct0 = 101;
	ct1 = ct2 = 5;
	ct3 = ct4 = 0;
	ii0 = handle;
	ii1 = x;
	ii2 = y;
	ii3 = w;
	ii4 = h;
	aes();
	return io0;
}

wind_close(handle) { 
	ct0 = 102;
	ct1 = ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = handle;
	aes();
	return io0;
}

wind_delete(handle) {
	ct0 = 103;
	ct1 = ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = handle;
	aes();
	return io0;
}

wind_find(x, y) {
	ct0 = 106;
	ct1 = 2;
	ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = x;
	ii1 = y;
	aes();
	return io0;
}

wind_update(n) {
	ct0 = 107;
	ct1 = ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = n;
	aes();
	return io0;
}

wind_calc(
    type, kind, xi, yi, wi, hi, 
    xo, yo, wo, ho) int *xo, *yo, *wo, *ho; {
	ct0 = 108;
	ct1 = 6;
	ct2 = 5;
	ct3 = ct4 = 0;
	ii0 = type;
	ii1 = kind;
	ii2 = xi;
	ii3 = yi;
	ii4 = wi;
	ii5 = hi;
	aes();
	*xo = io1;
	*yo = io2;
	*wo = io3;
	*ho = io4;
	return io0;
}

/* event handling */

event_multi(
  flags, clicks, mask, state, 
  af, ax, ay, aw, ah,
  bf, bx, by, bw, bh,
  buff, lo, hi,
  ox, oy, obut, ostate, okret, obret) 
	int *ox, *oy, *obut, *ostate, *okret, *obret;
{
	ct0 = 25;
	ct1 = 16;
	ct2 = 7;
	ct3 = 1;
	ct4 = 0;
	ii0 = flags;
	ii1 = clicks;
	ii2 = mask;
	ii3 = state;
	ii4 = af;
	ii5 = ax;
	ii6 = ay;
	ii7 = aw;
	ii8 = ah;
	ii9 = bf;
	ii10 = bx;
	ii11 = by;
	ii12 = bw;
	ii13 = bh;
	ii14 = lo;
	ii15 = hi;
	ai0 = buff;
	aes();
	*ox = io1;
	*oy = io2;
	*obut = io3;
	*ostate = io4;
	*okret = io5;
	*obret = io6;
	return io0;
}

/* object handling */

objc_add(tree,parent,child) int *tree; {
	ct0 = 40;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = parent;
	ii1 = child;
	ai0 = tree;
	aes();
	return io0;
}

objc_delete(tree,object) int *tree; {
	ct0 = 41;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = object;
	ai0 = tree;
	aes();
	return io0;
}

objc_draw(tree, start, depth, xclip, yclip, wclip, hclip) int *tree; { 
	ct0 = 42;
	ct1 = 6;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = start;
	ii1 = depth;
	ii2 = xclip;
	ii3 = yclip;
	ii4 = wclip;
	ii5 = hclip;
	ai0 = tree;
	aes();
	return io0;
}

objc_find(tree, start, depth, x, y) int *tree; { 
	ct0 = 43;
	ct1 = 4;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = start;
	ii1 = depth;
	ii2 = x;
	ii3 = y;
	ai0 = tree;
	aes();
	return io0;
}

objc_offset(tree, object, xoff, yoff) int *tree, *xoff, *yoff; {
	ct0 = 43;
	ct1 = 1;
	ct2 = 3;
	ct3 = 1;
	ct4 = 0;
	ii0 = object;
	ai0 = tree;
	aes();
	*xoff = io1;
	*yoff = io2;
	return io0;
}

objc_order(tree,object,newpos) int *tree; {
	ct0 = 45;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = object;
	ii1 = newpos;
	ai0 = tree;
	aes();
	return io0;
}

objc_edit(tree, object, ch, idx, kind, newidx) int *tree, *newidx; {
	ct0 = 46;
	ct1 = 4;
	ct2 = 2;
	ct3 = 1;
	ct4 = 0;
	ii0 = object;
	ii1 = ch;
	ii2 = idx;
	ii3 = kind;
	ai0 = tree;
	aes();
	*newidx = io1;
	return io0;
}

objc_change(tree, object, resvd, x, y, w, h, state, redraw) int *tree; {
	ct0 = 47;
	ct1 = 8;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = object;
	ii1 = resvd;
	ii2 = x;
	ii3 = y;
	ii4 = w;
	ii5 = h;
	ii6 = state;
	ii7 = redraw;
	ai0 = tree;
	aes();
	return io0;
}

/* menu handling */

menu_bar(tree, show) int *tree; { 
	ct0 = 30;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = show;
	ai0= tree;
	aes();
	return io0;
}

menu_icheck(tree, item, check) int *tree; {
	ct0 = 31;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = item;
	ii1 = check;
	ai0 = tree;
	aes();
	return io0;
}

menu_ienable(tree, item, enable) int *tree; {
	ct0 = 32;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = item;
	ii1 = enable;
	ai0 = tree;
	aes();
	return io0;
}

menu_tnormal(tree, title, normal) int *tree; {
	ct0 = 33;
	ct1 = 2;
	ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = title;
	ii1 = normal;
	ai0 = tree;
	aes();
	return io0;
}

menu_text(tree, item, text) int *tree; char *text; {
	ct0 = 34;
	ct1 = ct2 = 1;
 	ct3 = 2;
	ct4 = 0;
	ii0 = item;
	ai0 = tree;
	ai1 = text;
	aes();
	return io0;
}

menu_register(id, string) char *string; {
	ct0 = 35;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = id;
	ai0 = string;
	aes();
	return io0;
}

/* form handling */

form_pf(fmt, args) char *fmt; int args; {
	extern char _pfb[1];
	_dopf(_pfb, fmt, &args);
	form_alert(0, _pfb);
}

form_do(tree, start) int *tree; {
	ct0 = 50;
	ct1 = ct3 = 1;
	ct2 = 2;
	ct4 = 0;
	ii0 = start;
	ai0 = tree;
	aes();
	return io0;
}

form_dial(flag, sx, sy, sw, sh, bx, by, bw, bh) {
	ct0 = 51;
	ct1 = 9;
	ct3 = ct2 = 1;
	ct4 = 0;
	ii0 = flag;
	ii1 = sx;
	ii2 = sy;
	ii3 = sw;
	ii4 = sh;
	ii5 = bx;
	ii6 = by;
	ii7 = bw;
	ii8 = bh;
	aes();
	return io0;
}

form_center(tree, x, y, w, h) int *tree, *x, *y, *w, *h; {
	ct0 = 54;
	ct1 = 0;
	ct3 = 5;
	ct2 = 1;
	ct4 = 0;
	ai0 = tree;
	aes();
	*x = io1;
	*y = io2;
	*w = io3;
	*h = io4;
	return io0;
}

form_error(num) {
	ct0 = 53;
	ct1 = ct2 = 1;
	ct3 = ct4 = 0;
	ii0 = num;
	aes();
	return io0;
}

form_alert(button, string) char *string; {
	ct0 = 52;
	ct1 = ct2 = ct3 = 1;
	ct4 = 0;
	ii0 = button;
	ai0 = string;
	aes();
	return io0;
}


/* AES and VDI support routines */

aes() {
	/* 
         * load address of aes parameter block into a0
         * transfer a0 to d1
         * load 200 into d0
         * trap #2
         */
	asm( lag aes0 0   tad 0 1   ldw 200 0   trp 2 );
}
