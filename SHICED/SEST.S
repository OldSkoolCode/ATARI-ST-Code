0129 000000                       .dc.b   0, 0, 0                 * func 009              
 296                               *                                                       Resource Manger
 297 0000012C 000101                       .dc.b   0, 1, 1                 * func 110              
 298 0000012F 000100                       .dc.b   0, 1, 0                 * func 111              
 299 00000132 020100                       .dc.b   2, 1, 0                 * func 112              
 300 0000**************************************************/
/*  upd_char updates the pointer to the line that we are on 	*/
/*  currently (the beginning of the next line)           	*/
/****************************************************************/

upd_char()
{
  int i,j;
	
  if (oldline < line)			/* are we down from last time? */
   { i = currchar;
     while (i < (currchar + 81))	/* start at current char and work */
     { if (file[i] == 13)		/* forward till CR.  then next char */
	{ currchar = (i + 1);		/* is the next line  */
	  i = i + 81;
	}
       i = i + 1;			/* no CR found yet  */
     }
   }
   else if (oldline > line)     /* else lets go up from */
    { i = (currchar-2);		/* last time.  start before CR  */
      while (i > (currchar - 83))
        { if (file[i] == 13)		/* check for CR  */
	   {  currchar = i+1;
	             i = i - 83;             /* bypass rest of routine this way */
            }
	  else if (i < 0)
	    {  currchar = 0;
	              i = i - 83;
      0135 020101                       .dc.b   2, 1, 1                 * func 113              
 301 00000138 010101                       .dc.b   1, 1, 1                 * func 114              
 302 0000013B 000000                       .dc.b   0, 0, 0                 * func 115              
 303 0000013E 000000                       .dc.b   0, 0, 0                 * func 006
 304 00000141 000000                       .dc.b   0, 0, 0                 * func 007
 305 00000144 000000                       .dc.b   0, 0, 0                 * func 008
 306 00000147 000000                       .dc.b   0, 0, 0                 * func 009
 307                               *                                                       Shell Manager
 308 0000014A 000102                       .dc.b   0, 1, 2                 * func 120
 309 0000014D 030102                       .dc.b   3, 1, 2                 * func 121
 310 00000150 010101                       .dc.b   1, 1, 1                 * func 122
 311 00000153 0.b	0, 0, 0			* func 003		
	.dc.b	0, 0, 0			* func 004		
	.dc.b	0, 0, 0			* func 005		
	.dc.b	0, 0, 0			* func 006		
	.dc.b	0, 0, 0			* func 007		
	.dc.b	0, 0, 0			* func 008		
	.dc.b	0, 0, 0 		* func 009		
*							Window Manager
	.dc.b	5, 1, 0			* func 100		
	.dc.b	5, 1, 0			* func 101		
	.dc.b	1, 1, 0			* func 102		
	.dc.b	1, 1, 0			* func 103		
	.dc.b	2, 5, 0			* func 104		
	.dc.b	6, 1, 0			* func 105		
	.dc.b	2, 1, 0			* func 106		
	.dc.b	1, 1, 0			* func 107		
	.dc.b	6, 5, 0			* func 108