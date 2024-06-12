  66 0000005A 306F000A                     move.w  $a(a7),a0       * offset into file
  67 0000005E D048                         add.w   a0,d0           * total offset
  68 00000060 326F0008                     move.w  $8(a7),a1       * end of file
  69 00000064 92C0                         sub.w   d0,a1           * total number of bytes to move
  70 00000066 3009                         move.w  a1,d0           * into d0 register
  71                               
  72 00000068 93C9                         clr.l   a1              * clear again
  73 0000006A 326F000A                     move.w  $a(a7),a1       * offset again
  74 0000006E 222F0004                     move.l  $4(a7),d1       * starting address
  75 00000072 D3C1                         add.l   d1,a1           * a1 = real starting address of string
  76                               
  77 00000074 306F000C                     move.w  $c(a7),a0       * number of bytes into a0
  78 00000078 D1C9                         add.l   a1,a0                               *
  88                               
  89                               _ins_byte:
  90 00000082 4280                         clr.l   d0
  91 00000084 91C8                         suba.l  a0,a0           * clear address registers
  92 00000086 93C9                         suba.l  a1,a1           * clear registers for long operations
  93                               
  94 00000088 302F000C                     move.w  $c(a7),d0       * get # bytes to insert
  95 0000008