 memline - 1;
		break;
	      case 0x50:	/* down-arrow key */
		line = line + 1;
		memline = memline + 1;
		break;
	      case 0x4b:	/* left-arrow key */
		cursor = cursor - 1;
		break;
	      case 0x4d:	/* right-arrow key */
	        cursor = cursor + 1;
	        break;
	      default:		/* default past all the rest */
		if ((keyc >= ' ') && (keyc <= '~'))	/* in charcter range? */
		  { if (inson == 1)
		     { chrstr[0] = keyc;
		       chrstr[1] = 0;
		       insert(&chrstr,&templine,cursor);
                       copy(&templine,cursor,79-cursor);
		       st_spc(&outline);
		       save_var();
		       write(outline);
		       res_var();
		     }
		    else
 		     { templine[cursor] = keyc;
		       Bconout(2,keyc);
		     }
		   cursor = cursor + 1;
		   if (cursor > 79)
		     { cursor = cursor + 1;
		       ret_key();
		     }
		 }
	       else
		 con_key();
	      }

	   if (cursor < 0)	/* check for cursor wrap left */
            { cursor = 79;
	      memline m(form_num)

  int	form_num;
{ rsrc_gaddr(R_TREE,form_num,&form_addr);
  form_center(form_addr,&fo_gx,&fo_gy,&fo_gw,&fo_gh);
  form_dial(FMD_START,xdesk,ydesk,wdesk,hdesk,fo_gx,fo_gy,fo_gw,fo_gh);
  form_dial(FMD_GROW,xdesk,ydesk,(fo_gw/2),(fo_gh/2),fo_gx,fo_gy,fo_gw,fo_gh);
  objc_draw(form_addr,ROOT,MAX_DEPTH,fo_gx,fo_gy,fo_gw,fo_gh);
}

/************************************************************************/
/*    deselects the objects specified bits            			*/
/**********************);
             draw_point(i,j,((i-(xwork1+1))/grid_width),
			((j-(ywork1+1))/grid_heigt));
	     wind_save();
	     show_mouse();
           }
     }
}
           
/**************************************************************************/
/*   plot the point or unplot it whether it is plotted or what            */
/**************************************************************************/

set_color(arrp1,arrp2,color)

int	arrp1,arrp2;
unsigned int color;

{ int	act_p1,act_p2;

   a         * plus address of string
  79                               del_loop:
  80 0000007A 12D8                         move.b  (a0)+,(a1)+
  81 0000007C 51C8FFFC                     dbra    d0,del_loop     * move as much as requested
  82                               del_exit:
  83 00000080 4E75                         rts
  84                               
  85                               *
  86                               *       ins_byte inserts bytes specified by calling routine
  87         * length of screen - $500 for line
 135 000000E2 9280                         sub.l   d0,d1           * number of bytes to move
 136 000000E4 82FC0004                     divu    #$04,d1         * because we move long instead of bytes
 137 000000E8 4280                         clr.l   d0              * clear for word workable
 138 000000EA 3001                         move.w  d1,d0           * quotient into d0
 139                               rl_loop:
 140 000000EC 22D8                       tes
 167 00000128 3001                         move.w  d1,d0           * word into d0
 168                               
 169                               al_loop:
 170 0000012A 2320                         move.l  -(a0),-(a1)     * move long word memory
 171 0000012C 51C8FFFC                     dbra    d0,al_loop      * do it x amount of times 
 172                                       
 173 00000130 4E75                         rts
 174                               
 175                                .dc.b   0, 0, 0                 * func 007              
 217 00000054 000000                       .dc.b   0, 0, 0                 * func 008              
 218 00000057 000000                       .dc.b   0, 0, 0                 * func 009              
 219                               *                                                        Object Manager
 220 0000005A 020101                       .dc.b   2, 1, 1                 * func 040              
C P / M   6 8 0 0 0   A s s e m