#include "triangle.h"
//Èı½Çº¯Êı¼ÆËãsin cos

//----- (08001FE0) --------------------------------------------------------
s16 get_sin(u16 a1)
{
  if ( a1 >= 0x8000 )
    return -hSin_Cos_Table[(a1 - 0x8000) >> 5];
  else
    return hSin_Cos_Table[a1 >> 5];
}

//----- (08002004) --------------------------------------------------------
s16 get_cos(u32 a1)
{
	return get_sin(a1 + 0x4000);
}

