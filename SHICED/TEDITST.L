_exit:
	rts


*
*	rem_line deletes line passed as parameter and scrolls text up
*

_rem_line:
	link	a6,#-2  	* enough room for variables
	move.w	#$02,(a7)       * Push function call
	trap	#14		* Get screens base address
	unlk	a6		* restore stack pointer
	move.l	d0,a0
	add.l	#$500,a0
	move.l	d0,a1		* set address registers	
	clr.l	d0		* clear for operations

	move.w	$4(a7),d0	* get line to delete
	mulu	#$500,d0	* get starting address
	add.l	d0,a1		* plus offset of screen
	add.l	d0,a0		* b to be passed.                               	*/
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
     event = evnt_multi(MU_MESAG | MU_BUTTON,
			0,0,3,
			0,0,0,0,0,
			0,0,0,0,0,
			msgbuff,0,0,&mx,&my,&mbutton,&ret,&keycode,&ret);

	wind_update(TRUE);

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
	     { wind_set(wi_handle,WF_TOP,0,0,0,0);	/* set first window */
	        if (sh_changed)
		  { redr_shape();
		    sh_changed = FALSE;
		  }
             }
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
		    sh_changed = TRUE;
		    break;
	
	  	  case ROW_DOWN:	/* scroll shape down */
		    dn_shape();
		    sh_changed = TRUE;
		    break;

		  case COL_RIGHT:	/* scroll shape right */
		    right_shape();
		    sh_changed = TRUE;
		    break;

		  case COL_LEFT:	/* scroll shape left */
		    left_shape();
		    sh_changed = TRUE;
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
 

	if (event & MU_BUTTON)
	  { if (mbutton & BUTTON1)
	      click_point();

	    if (mbutton & BUTTON2)
	    { temp_color = plot_color;
	      plot_color = 0;
	      click_point();
	      plot_color = temp_color;
	    }
	  }

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


/***********************************************************************************/
/*    outputs the form for color selection             			*/
/************************************************************************/

color_sel()

{ out_form(COLOR);
  do
  {  exit_obj = form_do(form_addr,0);
     if (exit_obj != COLBUT)
       { rsrc_gaddr(R_TREE,COLOR,&sel_obj); /* get address of tree */
         sel_obj = sel_obj + exit_obj;
         plot_color = (sel_obj->ob_spec & 0xfL);
	 if (plot_color > max_color)
	   plot_color = 1;
     	 rsrc_********************/
/*    outputs the form for file type selection         			*/
/************************************************************************/

file_type()

{ ftsave[0] = get_bit(FILETYPE,CBUT,SELECTED);  /* get bit and save it */
  ftsave[1] = get_bit(FILETYPE,ABUT,SELECTED);  /* get all for saving */
  ftsave[2] = get_bit(FILETYPE,ICBUT,SELECTED); /* incase of cancel */
  ftsave[3] = get_bit(FILETYPE,IMBUT,SELECTED);

  out_form(FILETYPE);			/* output form okidata? */
  exit_objdo_obj(FILETYPE,ICBUT,SELECTED);
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

out_for