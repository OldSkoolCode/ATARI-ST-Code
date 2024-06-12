#include "obdefs.h"
#include "gemdefs.h"
#include "define.h"
#include "osbind.h"

#include "\se\se.h"
#include "\se\seext.h"

int real_color[16] = {0,15,8,4,2,6,0xC,0x0A,0x0E,1,9,5,3,7,0x0D,0x0B};

/************************************************************************/
/*  up_shape moves the shape up.					*/
/************************************************************************/

up_shape()

{ unsigned int	temp[10];

  for (i=0;i<10;i++)
    temp[i] = color_array[i][0];	/* save first part of array */

  for (i=0;i<39;i++)
    for (j=0;j<10;j++)
      color_array[j][i] = color_array[j][i+1];	/* move lines up */

  for (i=0;i<10;i++)
    color_array[i][39] = temp[i];	/* wraps line 1 down to 40 */
    
  hide_mouse();

  ptsin[0] = xwork1;
  ptsin[1] = ywork1;
  ptsin[2] = xwork1+(wwork1-1);		/* save window 3 */
  ptsin[3] = ywork1+(hwork1-1);
  ptsin[4] = xwork1;
  ptsin[5] = ywork1;
  ptsin[6] = xwork1+(wwork1-1);
  ptsin[7] = ywork1+(hwork1-1);
  ptsin[1] += grid_height;

  set_clip(xwork1,ywork1,xwork1+(wwork1-1),ywork1+(hwork1-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);

  ptsin[0] = xwork2+5;
  ptsin[1] = ywork2+6;
  ptsin[2] = xwork2+44;		/* save window 3 */
  ptsin[3] = ywork2+44;
  ptsin[4] = xwork2+5;
  ptsin[5] = ywork2+5;
  ptsin[6] = xwork2+44;
  ptsin[7] = ywork2+44;

  set_clip(xwork2,ywork2,xwork2+(wwork2-1),ywork2+(hwork2-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);
  vs_clip(handle,0,ptsin);

  j = (((ywork1+1)+hwork1)-grid_height);
  for (i=xwork1+1;i<(xwork1+wwork1);i=i+grid_width)
    { draw_grid(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));	
      draw_point(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));
    }

  wind_save();

  show_mouse();
}

/************************************************************************/
/*  dn_shape moves the shape down.					*/
/************************************************************************/

dn_shape()

{ unsigned int	temp[10];

  for (i=0;i<10;i++)
    temp[i] = color_array[i][39];	/* save last part of array */

  for (i=39;i>0;i--)
    for (j=0;j<10;j++)
      color_array[j][i] = color_array[j][i-1];	/* move lines up */

  for (i=0;i<10;i++)
    color_array[i][0] = temp[i];	/* wraps line 40 down to 1 */

  hide_mouse();
    

  ptsin[0] = xwork1;
  ptsin[1] = ywork1;
  ptsin[2] = xwork1+(wwork1-1);		/* save window 3 */
  ptsin[3] = ywork1+(hwork1-1);
  ptsin[4] = xwork1;
  ptsin[5] = ywork1;
  ptsin[6] = xwork1+(wwork1-1);
  ptsin[7] = ywork1+(hwork1-1);
  ptsin[5] += grid_height;
  ptsin[3] -= grid_height;

  set_clip(xwork1,ywork1,xwork1+(wwork1-1),ywork1+(hwork1-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);

  ptsin[0] = xwork2+5;
  ptsin[1] = ywork2+5;
  ptsin[2] = xwork2+44;		/* save window 3 */
  ptsin[3] = ywork2+43;
  ptsin[4] = xwork2+5;
  ptsin[5] = ywork2+6;
  ptsin[6] = xwork2+44;
  ptsin[7] = ywork2+44;

  set_clip(xwork2,ywork2,xwork2+(wwork2-1),ywork2+(hwork2-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);
  vs_clip(handle,0,ptsin);

  j = ywork1+1;
  for (i=xwork1+1;i<(xwork1+wwork1);i=i+grid_width)
    { draw_grid(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));	
      draw_point(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));
    }

  wind_save();

  show_mouse();
}

/************************************************************************/
/*  right_shape moves the shape right.					*/
/************************************************************************/

right_shape()

{ unsigned int	temp[40],color;

  hide_mouse();
    
  for (i=0;i<40;i++)
    get_color(39,i,&temp[i]);	/* save first part of array */

  for (i=0;i<40;i++)
    for (j=39;j>=0;j--)
      { get_color(j-1,i,&color);	/* move lines up */
	set_color(j,i,color);
      }

  for (i=0;i<40;i++)
    set_color(0,i,temp[i]);	/* wraps line 40 down to 1 */

  hide_mouse();


  ptsin[0] = xwork1;
  ptsin[1] = ywork1;
  ptsin[2] = xwork1+(wwork1-1);		/* save window 3 */
  ptsin[3] = ywork1+(hwork1-1);
  ptsin[4] = xwork1;
  ptsin[5] = ywork1;
  ptsin[6] = xwork1+(wwork1-1);
  ptsin[7] = ywork1+(hwork1-1);
  ptsin[4] += grid_width;

  set_clip(xwork1,ywork1,xwork1+(wwork1-1),ywork1+(hwork1-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);

  ptsin[0] = xwork2+5;
  ptsin[1] = ywork2+5;
  ptsin[2] = xwork2+44;		/* save window 3 */
  ptsin[3] = ywork2+44;
  ptsin[4] = xwork2+6;
  ptsin[5] = ywork2+5;
  ptsin[6] = xwork2+44;
  ptsin[7] = ywork2+44;


  set_clip(xwork2,ywork2,xwork2+(wwork2-1),ywork2+(hwork2-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);
  vs_clip(handle,0,ptsin);

  i = xwork1+1;
  for (j=ywork1+1;j<(ywork1+hwork1);j=j+grid_height)
    { draw_grid(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));	
      draw_point(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));
    }

  wind_save();

  show_mouse();
}
/************************************************************************/
/*  left_shape moves the shape right.					*/
/************************************************************************/

left_shape()

{ unsigned int	temp[40],color;

  hide_mouse();

  for (i=0;i<40;i++)
    get_color(0,i,&temp[i]);	/* save first part of array */

  for (i=0;i<40;i++)
    for (j=0;j<39;j++)
      { get_color(j+1,i,&color);	/* move lines up */
	set_color(j,i,color);
      }

  for (i=0;i<40;i++)
    set_color(39,i,temp[i]);	/* wraps line 40 down to 1 */

  
  ptsin[0] = xwork1;
  ptsin[1] = ywork1;
  ptsin[2] = xwork1+(wwork1-1);		/* save window 3 */
  ptsin[3] = ywork1+(hwork1-1);
  ptsin[4] = xwork1;
  ptsin[5] = ywork1;
  ptsin[6] = xwork1+(wwork1-1);
  ptsin[7] = ywork1+(hwork1-1);
  ptsin[0] += grid_width;
  ptsin[6] -= grid_width;
  
  set_clip(xwork1,ywork1,xwork1+(wwork1-1),ywork1+(hwork1-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);

  ptsin[0] = xwork2+6;
  ptsin[1] = ywork2+5;
  ptsin[2] = xwork2+44;		/* save window 3 */
  ptsin[3] = ywork2+44;
  ptsin[4] = xwork2+5;
  ptsin[5] = ywork2+5;
  ptsin[6] = xwork2+43;
  ptsin[7] = ywork2+44;

  set_clip(xwork2,ywork2,xwork2+(wwork2-1),ywork2+(hwork2-1));
  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&screen_mfdb);
  vs_clip(handle,0,ptsin);

  i = (((xwork1+1)+wwork1)-grid_width);
  for (j=ywork1+1;j<(ywork1+hwork1);j=j+grid_height)
    { draw_grid(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));	
      draw_point(i,j,((i-(xwork1+1))/grid_width),
		((j-(ywork1+1))/grid_height));
    }
  wind_save();
    
  show_mouse();
}

/************************************************************************/
/* rot_left rotates the shape to the left 90 degrees			*/
/************************************************************************/

rot_left()

{ unsigned int	color;

  hide_mouse();		/* no mouse for updating screen */

  for (i=0;i<40;i++)
    for (j=0;j<40;j++)
      { get_color(i,j,&color);		/* color switch */ 
	sett_color(j,39-i,color);
      }

   for (i=0;i<10;i++)
     for (j=0;j<40;j++)
       color_array[i][j] = temp_array[i][j];

   redr_shape();

   show_mouse();
}

/************************************************************************/
/* rot_right rotates the shape to the right 90 degrees			*/
/************************************************************************/

rot_right()

{ unsigned int	color;

  hide_mouse();		/* no mouse for updating screen */

  for (i=0;i<40;i++)
    for (j=0;j<40;j++)
      { get_color(i,j,&color);		/* color switch */ 
	sett_color(39-j,i,color);
      }

   for (i=0;i<10;i++)
     for (j=0;j<40;j++)
       color_array[i][j] = temp_array[i][j];

   redr_shape();

   show_mouse();
}

/**************************************************************************/
/*   plot the point or unplot it whether it is plotted or what            */
/**************************************************************************/

sett_color(arrp1,arrp2,color)

int	arrp1,arrp2;
unsigned int color;

{ int	act_p1,act_p2;

   act_p1 = (arrp1/4);		/* actual pointer = arrp1/4 (bits per color) */
   act_p2 = (arrp1 % 4);	/* remainder for offset into array */


   temp_array[act_p1][arrp2] = (temp_array[act_p1][arrp2]
     & ~(0x0f << (act_p2 * 4)));
   
   temp_array[act_p1][arrp2] = (temp_array[act_p1][arrp2]
     | (color << (act_p2 * 4)));
}

/************************************************************************/
/* redraw the second window only					*/
/************************************************************************/

redr_wind2()

{   for (i=xwork1+1;i<(xwork1+wwork1);i=i+grid_width)
    for (j=ywork1+1;j<(ywork1+hwork1);j=j+grid_height)
      draw_point(i,j,((i-(xwork1+1))/grid_width)
			,((j-(ywork1+1))/grid_height));
}

/**************************************************************************/
/* compile is the main routine for compiling shapes to files              */
/**************************************************************************/  
  
compile()

{ OBJECT	*obj_ptr;
  TEDINFO	*txt_ptr;
  int		shap_width,shap_height;
  int		mask_width,mask_height;
  int		loop_end,ch_bit;
  unsigned int	null_color;

  shap_height = 39;			/* starting height */
  shap_width = 10;	

  mask_height = 39;
  mask_width = 10;		/* starting sizes */

  if (main_xor)
   null_color = ((max_color << 12) + (max_color << 8) + 
			(max_color << 4) + max_color);
  else
   null_color = 0;

  loop_end = FALSE;		/* loop control to get out of loop */
  
  do
    { i=9;
      while (i>=0)
        { if (mask_chek)
	   { if (mask_array[i][shap_height] != null_color)
	       { loop_end = TRUE;
		i = 0;
	       }
	   }
	  else
	   { if (color_array[i][shap_height] != null_color)
	       { loop_end = TRUE;
		 i = 0;
	       }
	   }
          i = i - 1;
        }
     shap_height = shap_height - 1;
    }
  while ((shap_height >= 0) && (!loop_end));

  shap_height = shap_height + 2;

  loop_end = FALSE;		/* loop control to get out of loop */
  
  do
    { i=39;
      while (i>=0)
        { if (mask_chek)
	   { if (mask_array[shap_width][i] != null_color)
	       { loop_end = TRUE;
		i = 0;
	       }
	   }
	  else
	   { if (color_array[shap_width][i] != null_color)
	       { loop_end = TRUE;
		 i = 0;
	       }
	   }
          i = i - 1;
        }
     shap_width = shap_width - 1;
    }
  while ((shap_width >= 0) && (!loop_end));

  shap_width = shap_width + 2;

  if (mask_xor)
   null_color = ((max_color << 12) + (max_color << 8) + 
			(max_color << 4) + max_color);
  else
   null_color = 0;

  loop_end = FALSE;		/* loop control to get out of loop */
  
  do
    { i=9;
      while (i>=0)
        { if (mask_chek)
	   { if (color_array[i][mask_height] != null_color)
	       { loop_end = TRUE;
		i = 0;
	       }
	   }
	  else
	   { if (mask_array[i][mask_height] != null_color)
	       { loop_end = TRUE;
		 i = 0;
	       }
	   }
          i = i - 1;
        }
     mask_height = mask_height - 1;
    }
  while ((mask_height >= 0) && (!loop_end));

  mask_height = mask_height + 2;

  loop_end = FALSE;		/* loop control to get out of loop */
  
  do
    { i=39;
      while (i>=0)
        { if (mask_chek)
	   { if (color_array[mask_width][i] != null_color)
	       { loop_end = TRUE;
		i = 0;
	       }
	   }
	  else
	   { if (mask_array[mask_width][i] != null_color)
	       { loop_end = TRUE;
		 i = 0;
	       }
	   }
          i = i - 1;
        }
     mask_width = mask_width - 1;
    }
  while ((mask_width >= 0) && (!loop_end));

  mask_width = mask_width + 2;

  comp_width = (mask_width > shap_width) ? mask_width : shap_width;
  comp_height = (mask_height > shap_height) ? mask_height : shap_height;
  
  rsrc_gaddr(R_TREE,FILENAME,&obj_ptr);	/* if ok then continue */
  obj_ptr = obj_ptr + BASEFILE;
  txt_ptr = obj_ptr->ob_spec;
  txt_ptr->te_ptext = &base_name;
  txt_ptr->te_txtlen = 27;
     
  rsrc_gaddr(R_TREE,FILENAME,&form_addr);
  form_center(form_addr,&fo_gx,&fo_gy,&fo_gw,&fo_gh);
  form_dial(FMD_START,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_GROW,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  objc_draw(form_addr,ROOT,MAX_DEPTH,fo_gx,fo_gy,fo_gw,fo_gh);
  exit_obj = (form_do(form_addr,0) & 0xff);
  form_dial(FMD_SHRINK,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_FINISH,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  undo_obj(FILENAME,FNOK,SELECTED);
  undo_obj(FILENAME,FNCAN,SELECTED);	  /* deselect buttons */

  if (exit_obj == FNCAN)
    return;
  graf_mouse(HOURGLASS,0x0L);

  ch_bit = get_bit(FILETYPE,ICBUT,SELECTED);
  if (ch_bit)
   { ic_out();			/* output icon file */
     mask_out();
   }

  ch_bit = get_bit(FILETYPE,IMBUT,SELECTED);
  if (ch_bit)
   im_out();			/* image file output */

  ch_bit = get_bit(FILETYPE,CBUT,SELECTED);
  if (ch_bit)
   cfi_out();			/* c file output */

  ch_bit = get_bit(FILETYPE,ABUT,SELECTED);
  if (ch_bit)
   sou_out();			/* source output */

  graf_mouse(ARROW,0x0L);
}

/************************************************************************/
/* mask_edit edits the mask for the shapes background			*/
/************************************************************************/  
  
mask_edit()

{ int	ch_bit;		/* checked bit variable */
  ch_bit = get_bit(MAINMENU,MO3,CHECKED);
  if (ch_bit)
    { undo_obj(MAINMENU,MO3,CHECKED); 	/* if set undo it */
      wind_set(wi_handle,WF_NAME," Grid Shape ",0,0);
      wind_set(wi2_handle,WF_NAME," Shape ",0,0);
      if (main_xor)
        do_obj(MAINMENU,MO4,CHECKED);
      else
        undo_obj(MAINMENU,MO4,CHECKED);
      mask_chek = FALSE;
    }
  else
    { do_obj(MAINMENU,MO3,CHECKED);	/* set it elslie */
      wind_set(wi_handle,WF_NAME," Grid Mask ",0,0);
      wind_set(wi2_handle,WF_NAME," Mask ",0,0);
      if (mask_xor)
        do_obj(MAINMENU,MO4,CHECKED);
      else
        undo_obj(MAINMENU,MO4,CHECKED);
      mask_chek = TRUE;
    }

  for (i=0;i<10;i++)			/* switch arrays */
    for (j=0;j<40;j++)
      { temp_array[i][j] = color_array[i][j];
	color_array[i][j] = mask_array[i][j];
	mask_array[i][j] = temp_array[i][j];
      }
  redr_shape();
}

/************************************************************************/
/* xor_shape xors shape for masking purposes				*/
/************************************************************************/  
  
xor_shape()

{ int	ch_bit,m_bit;		/* checked bit variable */
  unsigned int	color;
  
  ch_bit = get_bit(MAINMENU,MO4,CHECKED);
  if (ch_bit)
   undo_obj(MAINMENU,MO4,CHECKED); 	/* if set undo it */
  else
    do_obj(MAINMENU,MO4,CHECKED);	/* set it elslie */

  if (mask_chek)
   mask_xor = ch_bit^1;
  else
   main_xor = ch_bit^1;
  

  for (i=0;i<40;i++)
    for (j=0;j<40;j++)
     { get_color(i,j,&color);
       color = (color^max_color);	/* xor bits that max out the */
       set_color(i,j,color);		/* colors possible */
      }
  redr_shape();
}

/************************************************************************/
/* opens third window for viewing of mask and shape together		*/
/************************************************************************/

open_third()

{ hide_mouse();

  xwork3 = xwork2;		/* set up like second window */
  ywork3 = ywork2;
  wwork3 = wwork2;
  hwork3 = hwork2;		/* same size of second window */    

  wind_calc(0,NAME,xwork3,ywork3,wwork3,hwork3,
		       &xwind3,&ywind3,&wwind3,&hwind3);

  xwind3 = xwind2;				/* open window routines */
  ywind3 = (ywind2+hwind2)+(grid_height*2);

  wi3_handle=wind_create(NAME,xwind3,ywind3,wwind3,hwind3);
  wind_set(wi3_handle,WF_NAME," Final ",0,0);
  wind_open(wi3_handle,xwind3,ywind3,wwind3,hwind3);
  wind_get(wi3_handle,WF_WORKXYWH,&xwork3,&ywork3,&wwork3,&hwork3);
  
  draw_3wind();
}

/************************************************************************/
/* draw_3wind draws the third windows interior				*/
/************************************************************************/

draw_3wind()
{ 
  hide_mouse();
  vsf_perimeter(handle,FALSE);	/* no solid line around perimeter */
  vsf_interior(handle,2);	/* set up parameters */
  vsf_color(handle,max_color);
  vsf_style(handle,3);

  ptsin[0] = xwork3;
  ptsin[1] = ywork3;		/* clear third window */
  ptsin[2] = xwork3+(wwork3-1);
  ptsin[3] = ywork3+(hwork3-1);
  v_bar(handle,ptsin);		/* use v_bar to clear window */

  show_mouse();			/* reshow it after clear */
}

/************************************************************************/
/* upd_3wind updates the 3rd window when it is selected			*/
/************************************************************************/

upd_3wind()

{ int	color,color2,act_p1,act_p2;
  int	ch_bit,curr_pix;

  ch_bit = get_bit(MAINMENU,MO3,CHECKED);	/* is mask edit checked? */
  draw_3wind();			/* clear the window */
  hide_mouse();
  for (i=0;i<40;i++)
    for (j=0;j<40;j++)
      { act_p1 = (i/4);	 	/* actual pointer = arrp1/4 (bits per color) */
        act_p2 = (i % 4);	/* remainder for offset into array */
   
	if (ch_bit)
	  { color2 = (mask_array[act_p1][j] & (0x0f << (act_p2 * 4)));
   	    color2 = (color2 >> (act_p2 * 4));
    	    get_color(i,j,&color);
	  }
	else
	  { color = (mask_array[act_p1][j] & (0x0f << (act_p2 * 4)));
   	    color = (color >> (act_p2 * 4));
    	    get_color(i,j,&color2);
	  }

	color = real_color[color];

	v_get_pixel(handle,i+(xwork3+5),j+(ywork3+5),&ret,&curr_pix);

	color = (color2 & color) | (curr_pix & ~color);

   	vsm_color(handle,color);
   	ptsin[0] = i+(xwork3+5);		/* on normal shape window */
   	ptsin[1] = j+(ywork3+5);		/* ditto */
   	v_pmarker(handle,1,ptsin);		/* plot one dot ok? */
      }

  	ptsin[0] = xwork3;
  	ptsin[1] = ywork3;
  	ptsin[2] = xwork3+(wwork3-1);		/* save window 3 */
  	ptsin[3] = ywork3+(hwork3-1);
  	ptsin[4] = xwork3;
  	ptsin[5] = ywork3;
  	ptsin[6] = xwork3+(wwork3-1);
  	ptsin[7] = ywork3+(hwork3-1);

  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&undo_mfdb);	/* copy raster */

    show_mouse();
}

/**************************************************************************/
/* wind_save saves the windows to the undo buffer			  */
/**************************************************************************/

wind_save()

{ ptsin[0] = xwork1;
  ptsin[1] = ywork1;
  ptsin[2] = xwork1+(wwork1-1);		/* save window 1 */
  ptsin[3] = ywork1+(hwork1-1);
  ptsin[4] = xwork1;
  ptsin[5] = ywork1;
  ptsin[6] = xwork1+(wwork1-1);
  ptsin[7] = ywork1+(hwork1-1);

  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&undo_mfdb);	/* raster copy */

  ptsin[0] = xwork2;
  ptsin[1] = ywork2;
  ptsin[2] = xwork2+(wwork2-1);		/* save window 2 */
  ptsin[3] = ywork2+(hwork2-1);
  ptsin[4] = xwork2;
  ptsin[5] = ywork2;
  ptsin[6] = xwork2+(wwork2-1);
  ptsin[7] = ywork2+(hwork2-1);

  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&undo_mfdb);	/* copy raster */

  ptsin[0] = xwork3;
  ptsin[1] = ywork3;
  ptsin[2] = xwork3+(wwork3-1);		/* save window 3 */
  ptsin[3] = ywork3+(hwork3-1);
  ptsin[4] = xwork3;
  ptsin[5] = ywork3;
  ptsin[6] = xwork3+(wwork3-1);
  ptsin[7] = ywork3+(hwork3-1);

  vro_cpyfm(handle,3,ptsin,&screen_mfdb,&undo_mfdb);	/* copy raster */
}

/************************************************************************/
/* wind_rest() restores window from the undo buffer			*/
/************************************************************************/

wind_rest(xc_in,yc_in,wc_in,hc_in)

int	xc_in,yc_in,wc_in,hc_in;
{
  ptsin[0] = xc_in;
  ptsin[1] = yc_in;
  ptsin[2] = xc_in+(wc_in-1);		/* restore window 1 */
  ptsin[3] = yc_in+(hc_in-1);
  ptsin[4] = xc_in;
  ptsin[5] = yc_in;
  ptsin[6] = xc_in+(wc_in-1);
  ptsin[7] = yc_in+(hc_in-1);

  vro_cpyfm(handle,3,ptsin,&undo_mfdb,&screen_mfdb);	/* raster copy */
}

/************************************************************************/
/* fi_num files the number specified to the disk			*/
/************************************************************************/

fi_num(in_handle,in_num)

int	in_handle,in_num;

{ int	i,j,k;
  char	out_num[7];

  out_num[0] = '0';
  out_num[1] = 'x';
  
  j = 2;
  for (i=12;i>=0;i=i-4)			/* output 4 hex digits */
    { k=((in_num>>i) &0x000f);
      out_num[j] = k>9 ? 'A'+k-10 : '0'+k;
      j=j+1;
    }
  out_num[6] = 0;
  
  Fwrite(in_handle,6L,out_num);
}

/************************************************************************/
/* fi_spc writes the number spaces specified to the file opened		*/
/************************************************************************/

fi_spc(in_handle,in_num)

int	in_handle,in_num;

{ char	space[256];
  long	count; 
  int	i;

  for (i=0;i<=in_num-1;i++)		/* fill array with spaces */
    space[i] = ' ';
  
  space[in_num] = 0;
  count = in_num;

  Fwrite(in_handle,count,space);	/* write them to the file */
}

/************************************************************************/
/* fi_c_head writes the header to the file opened			*/
/************************************************************************/

fi_c_head(in_handle)

int	in_handle;		/* file handle of file to write to */

{ int	pix_width,size;		/* pixels in width */
  
  Fwrite(in_handle,33L,&c_header);	/* write comment out */
  Fwrite(in_handle,2L,&ret_lf);		/* write return */

  Fwrite(in_handle,15L,&cdef_w);
  pix_width = (comp_width * 4);		/* get pixels across */
  fi_num(in_handle,pix_width);    

  Fwrite(in_handle,2L,&ret_lf);

  Fwrite(in_handle,15L,&cdef_h);	/* write height string */
  fi_num(in_handle,comp_height);
  Fwrite(in_handle,2L,&ret_lf);

  Fwrite(in_handle,17L,&cdef_s);
  i = ((pix_width%16)==0) ? 0 : 1;
  size = (((pix_width/16)+i) * comp_height);	/* write size string */  
  
  fi_num(in_handle,size);
  Fwrite(in_handle,2L,&ret_lf);

  Fwrite(in_handle,31L,&cstruc1);	/* write start of structure */
  Fwrite(in_handle,2L,&ret_lf);
  Fwrite(in_handle,2L,&cstruc3);
}

/************************************************************************/
/* sh_mono converts the shapes data to monochrome mode			*/
/************************************************************************/
sh_mono()

{ int	k;
  unsigned int	color;

  for (i=0;i<10;i++)
   for (j=0;j<40;j++)
     temp_array[i][j] = 0;

  for (j=0;j<40;j++)
    for (i=0;i<40;i++)
      { if (mask_chek)
	  get_m_color(i,j,&color);		/* get the color */
	else
	  get_color(i,j,&color);
        if (color > 0) 
     	  color = 1;
	color = color << (15-(i%16));		/* convert to B&W */
	k = (i/16);
        temp_array[k][j] = (temp_array[k][j] | color);
      }
}

/************************************************************************/
/* file_hex files the hex values into a file for icons			*/
/************************************************************************/

file_hex(in_handle)

int	in_handle;

{ int	color,k,c_wwidth;

  c_wwidth = (comp_width/4);
  if ((comp_width % 4) != 0)
    c_wwidth = c_wwidth + 1;
  

  for (j=0;j<comp_height;j++)		/* file hex numbers for height */
    for (i=0;i<c_wwidth;i++)
      { k = temp_array[i][j];
	fi_num(in_handle,k);
	if ((j<comp_height-1) || (i<c_wwidth-1))	
	  { Fwrite(in_handle,2L,&com_spc);		/* if not end */
	    if ((((i+(j*c_wwidth))+1) % 4) == 0)	/* do a return */
	      { Fwrite(in_handle,2L,&ret_lf);
	        fi_spc(in_handle,2);
	      }
 	  }	    
       }
     Fwrite(in_handle,2L,&ret_lf);
     Fwrite(in_handle,2L,&cstruc4);
     Fwrite(in_handle,2L,&ret_lf);
}

/************************************************************************/
/* get_m_color gets the mask bit					*/
/************************************************************************/
get_m_color(x,y,in_col)

int	x,y,*in_col;
{ int	ret_col,act_p1,act_p2;

	act_p1 = (x/4);	 	/* actual pointer = arrp1/4 (bits per color) */
        act_p2 = (x % 4);	/* remainder for offset into array */
   
	ret_col = (mask_array[act_p1][y] & (0x0f << (act_p2 * 4)));
   	ret_col = (ret_col >> (act_p2 * 4));

	*in_col = ret_col;
}

/************************************************************************/
/* ic_out outputs an icon file to the disk				*/
/************************************************************************/

ic_out()

{ int	file_handle,temp_width;

  temp_width = comp_width;

  comp_width -= 1;
  comp_width = comp_width + 4;
  comp_width = ((comp_width / 4)*4);

  sh_mono();

  pathname[0] = 0;
  strcat(pathname,base_name);

  strcat(pathname,&"D.ICN");	/* filename = BASE+'D.ICN' */
  file_handle = Fcreate(pathname,0);
  
  if (file_handle == 0)
   { graf_mouse(ARROW,0x0L);
     form_alert(1,&"[3][Unable to create icon|data output file.][ OK ]");
     graf_mouse(ARROW,0x0L);
   }
  else
    { fi_c_head(file_handle);
      file_hex(file_handle);
      Fclose(file_handle);
    }

  comp_width = temp_width;
}   

/************************************************************************/
/* mask_out outputs a mask file to the disk				*/
/************************************************************************/

mask_out()

{ int	file_handle,temp_width;

  temp_width = comp_width;

  comp_width -= 1;
  comp_width = comp_width+4;
  comp_width = ((comp_width/4)*4);

  mask_mono();

  pathname[0] = 0;
  strcat(pathname,base_name);

  strcat(pathname,&"M.ICN");
  file_handle = Fcreate(pathname,0);
  
  if (file_handle == 0)
   { graf_mouse(ARROW,0x0L);
     form_alert(1,&"[3][Unable to create icon|mask output file.][ OK ]");
     graf_mouse(HOURGLASS,0x0L);
   }
  else
    { fi_c_head(file_handle);
      file_hex(file_handle);
      Fclose(file_handle);
    }

  comp_width = temp_width;
}   

/************************************************************************/
/* mask_mono converts the masks data to monochrome mode			*/
/************************************************************************/
mask_mono()

{ int k;
  unsigned int	color;

  for (i=0;i<10;i++)
   for (j=0;j<40;j++)
     temp_array[i][j] = 0;

  for (j=0;j<40;j++)
    for (i=0;i<40;i++)
      { if (mask_chek)
	  get_color(i,j,&color);
	else
	  get_m_color(i,j,&color);
        if (color > 0) 
     	  color = 1;
	color = color << (15-(i%16));
	k = (i/16);
        temp_array[k][j] = (temp_array[k][j] | color);
      }
}

/************************************************************************/
/* cfi_out outputs an icon & mask file to the disk in c			*/
/************************************************************************/

cfi_out()

{ int	file_handle,temp_width;

  s_convert();

  temp_width = comp_width;
  comp_width = comp_width + 4;
  comp_width = ((comp_width/4)*4);

  pathname[0] = 0;
  strcat(pathname,base_name);

  strcat(pathname,&".C");
  file_handle = Fcreate(pathname,0);
  
  if (file_handle == 0)
   { graf_mouse(ARROW,0x0L);
     form_alert(1,&"[3][Unable to create C|source output file.][ OK ]");
     graf_mouse(HOURGLASS,0x0L);
   }
  else
    { c_head(file_handle,FALSE);
      c_hex(file_handle);
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,2L,&ret_lf);
      m_convert();
      c_head(file_handle,TRUE);
      c_hex(file_handle);
      Fclose(file_handle);
    }
  comp_width = temp_width;
}   

/************************************************************************/
/* im_out outputs an image file to the disk				*/
/************************************************************************/

im_out()

{ int	file_handle;

  sh_mono();

  pathname[0] = 0;
  strcat(pathname,base_name);

  strcat(pathname,&"I.ICN");
  file_handle = Fcreate(pathname,0);
  
  if (file_handle == 0)
   { graf_mouse(ARROW,0x0L);
     form_alert(1,&"[3][Unable to create image|data output file.][ OK ]");
     graf_mouse(HOURGLASS,0x0L);
   }
  else
    { fi_c_head(file_handle);
      file_hex(file_handle);
      Fclose(file_handle);
    }
}   

/************************************************************************/
/* sou_out outputs a assembler source file to disk			*/
/************************************************************************/

sou_out()

{ int	shift_num,file_handle,temp_width;
  char	shif_char;

  temp_width = comp_width;

  s_convert();
  pathname[0] = 0;
  strcat(pathname,base_name);
  strcat(pathname,&".S");

  file_handle = Fcreate(pathname,0);
  if (file_handle == 0)
    { graf_mouse(ARROW,0x0L);
    form_alert(1,&"[3][Unable to create Assembler|Source output file.][ OK ]"); 
      graf_mouse(HOURGLASS,0x0L);
    }
  else
    { comp_width = comp_width + 4;
      comp_width = ((comp_width/4)*4);
      Fwrite(file_handle,32L,&s_header);
      Fwrite(file_handle,11L,&" Shape Data");
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,9L,&"     swh:");
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,6L,&"\011dc.w\011");
      fi_s_num(file_handle,comp_width);
      Fwrite(file_handle,1L,&",");
      fi_s_num(file_handle,comp_height);
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,9L,&"     ssd:");
      Fwrite(file_handle,2L,&ret_lf);
      s_hex(file_handle);

      m_convert();
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,32L,&s_header);
      Fwrite(file_handle,10L,&" Mask Data");
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,2L,&ret_lf);
      Fwrite(file_handle,9L,&"     msd:");
      Fwrite(file_handle,2L,&ret_lf);
      s_hex(file_handle);

      Fclose(file_handle);
     }
   comp_width = temp_width;
}	  

/************************************************************************/
/* s_hex files the hex values into a file for source files 		*/
/************************************************************************/

s_hex(in_handle)

int	in_handle;

{ int	color,c_wwidth,k;

  c_wwidth = comp_width;

  Fwrite(in_handle,6L,&"\011dc.w\011");  
  
  for (j=0;j<comp_height;j++)
    for (i=0;i<c_wwidth;i++)
      { k = temp_array[i][j];
	fi_s_num(in_handle,k);
	if ((j<comp_height-1) || (i<c_wwidth-1))
	  { if ((((i+(j*c_wwidth))+1) % 4) == 0)
	     { Fwrite(in_handle,2L,&ret_lf);
	       Fwrite(in_handle,6L,&"\011dc.w\011");
	     }
	    else
	      Fwrite(in_handle,1L,&",");  
	  }
      }
  Fwrite(in_handle,2L,&ret_lf);
}

/************************************************************************/
/* fi_s_num writes the number specified to the file opened		*/
/************************************************************************/

fi_s_num(in_handle,in_num)

int	in_handle,in_num;

{ int 	i,j,k;
  char out_num[7];

  out_num[0] = '$';
  j=1;
  for (i=12;i>=0;i=i-4)
    { k=((in_num>>i) &0x000f);
      out_num[j] = k>9 ? 'A'+k-10 : '0'+k;
      j=j+1;
    }
  out_num[5] = 0;
  
  Fwrite(in_handle,5L,out_num);
}

	
/************************************************************************/
/* s_convert converts the shape data to color data			*/
/************************************************************************/

s_convert()

{ int	k;
  unsigned int	color,temp_shift,temp_bits[4];

  for (i=0;i<40;i++)
    temp_array[10][i] = 0;

  for (i=0;i<4;i++)
    temp_bits[i] = 0;

  for (j=0;j<40;j++)
    for (i=0;i<40;i++)
      { if (mask_chek)
	  get_m_color(i,j,&color);
	else
	  get_color(i,j,&color);
	color = real_color[color];
	temp_bits[0] = (temp_bits[0] | (((color & 8) >> 3) << 15-(i%16)));
	temp_bits[1] = (temp_bits[1] | (((color & 4) >> 2) << 15-(i%16)));
	temp_bits[2] = (temp_bits[2] | (((color & 2) >> 1) << 15-(i%16)));
	temp_bits[3] = (temp_bits[3] | ((color & 1) << 15-(i%16)));
        if (((i%16)+1 == 16) || (i==39))
	  { k = ((i/16)*4);
	    temp_array[k][j] = temp_bits[0];
	    temp_array[k+1][j] = temp_bits[1];
	    temp_array[k+2][j] = temp_bits[2];
	    temp_array[k+3][j] = temp_bits[3];
	    for (k=0;k<4;k++)
	      temp_bits[k] = 0;
	  }
      }
}	

	
/************************************************************************/
/* m_convert converts the mask data to color data			*/
/************************************************************************/

m_convert()

{ int	k;
  unsigned int	color,temp_shift,temp_bits[4];

  for (i=0;i<40;i++)
    temp_array[10][i] = 0;

  for (i=0;i<4;i++)
    temp_bits[i] = 0;

  for (j=0;j<40;j++)
    for (i=0;i<40;i++)
      { if (mask_chek)
	  get_color(i,j,&color);
	else
	  get_m_color(i,j,&color);
	color = real_color[color];
	temp_bits[0] = (temp_bits[0] | (((color & 8) >> 3) << 15-(i%16)));
	temp_bits[1] = (temp_bits[1] | (((color & 4) >> 2) << 15-(i%16)));
	temp_bits[2] = (temp_bits[2] | (((color & 2) >> 1) << 15-(i%16)));
	temp_bits[3] = (temp_bits[3] | ((color & 1) << 15-(i%16)));
        if (((i%16)+1 == 16) || (i==39))
	  { k = ((i/16)*4);
	    temp_array[k][j] = temp_bits[0];
	    temp_array[k+1][j] = temp_bits[1];
	    temp_array[k+2][j] = temp_bits[2];
	    temp_array[k+3][j] = temp_bits[3];
	    for (k=0;k<4;k++)
	      temp_bits[k] = 0;
	  }
      }
}	


/************************************************************************/
/* str_part gets part of source and places in destination		*/
/************************************************************************/

str_part(str1_ptr,str2_ptr,st_num,end_num)

char	*str1_ptr,*str2_ptr;
int	st_num,end_num;

{ int	i;
  str1_ptr = str1_ptr + st_num;
  for (i=st_num;i<=end_num;i++)
    { *str1_ptr = *str2_ptr;
      str1_ptr++;
      str2_ptr++;
    }
}

/************************************************************************/
/* c_hex files the hex values into a file for c files			*/
/************************************************************************/

c_hex(in_handle)

int	in_handle;

{ int	color,k,i,c_wwidth;

  c_wwidth = comp_width;

  for (j=0;j<comp_height;j++)		/* file hex numbers for height */
    for (i=0;i<c_wwidth;i++)
      { k = temp_array[i][j];
	fi_num(in_handle,k);
	if ((j<comp_height-1) || (i<c_wwidth-1))	
	  { Fwrite(in_handle,2L,&com_spc);		/* if not end */
	    if ((((i+(j*c_wwidth))+1) % 4) == 0)	/* do a return */
	      { Fwrite(in_handle,2L,&ret_lf);
	        fi_spc(in_handle,2);
	      }
 	  }	    
       }
     Fwrite(in_handle,2L,&ret_lf);
     Fwrite(in_handle,2L,&cstruc4);
     Fwrite(in_handle,2L,&ret_lf);
}

/************************************************************************/
/* c_head writes the header to the file openedof c			*/
/************************************************************************/

c_head(in_handle,m_code)

int	in_handle;		/* file handle of file to write to */
int	m_code;			/* code for image or data */

{ int	size;		/* pixels in width */
  
  Fwrite(in_handle,33L,&c_header);	/* write comment out */
  Fwrite(in_handle,2L,&ret_lf);		/* write return */

  Fwrite(in_handle,15L,&cdef_w);
  fi_num(in_handle,comp_width);    

  Fwrite(in_handle,2L,&ret_lf);

  Fwrite(in_handle,15L,&cdef_h);	/* write height string */
  fi_num(in_handle,comp_height);
  Fwrite(in_handle,2L,&ret_lf);

  Fwrite(in_handle,17L,&cdef_s);
  size = (comp_width * comp_height);	/* write size string */  
  fi_num(in_handle,size);
  Fwrite(in_handle,2L,&ret_lf);

  if (!m_code)
    Fwrite(in_handle,22L,&cstruc1);	/* write start of structure */
  else
    Fwrite(in_handle,21L,&cstruc2);
  Fwrite(in_handle,2L,&ret_lf);
  Fwrite(in_handle,2L,&cstruc3);
}
