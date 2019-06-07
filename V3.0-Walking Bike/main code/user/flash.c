#include "flash.h"

void reset_flash_2()
{
  flash_para2_052 = byte_80075D0 << 8;
  flash_para2_052 += (u16)byte_80075D5;
  flash_para2_052 += 4626;
  flash_para3_054 = byte_80075D6 << 8;
  flash_para3_054 += byte_80075D9;
  flash_para3_054 += 8481;
  if ( flash_para8_046 == 808 )
  {
    flash_para8_046 = 0;
    write_flash_2();
    read_flash_2();
  }
}
//----- (08005DF0) --------------------------------------------------------
void read_flash_2()
{
	signed int v0; // r4@1
  u16 *v1; // r1@1
  u16 *v2; // r3@1

  v0 = 16;
  v1 = flash_buf2_24C;
  v2 = (u16*)unk_8034000;
  while ( 1 )
  {
    if ( v0-- == 0 )
      break;
    *v1++ = *v2++;
  }
  flash_para9_044 = flash_buf2_24C[6];
  flash_para6_04C = flash_buf2_24C[8];
  flash_para8_046 = flash_buf2_24C[10];
  flash_para5_04E = flash_buf2_24C[12];
  flash_para4_050 = flash_buf2_24C[13];
  //return 1;
}

//----- (08005E3C) --------------------------------------------------------
void write_flash_2()
{//写参数
	signed int v0; // r4@1
  u16 *v1; // r5@1
  u16* v2; // r7@1
  //signed int result; // r0@2
  signed int i; // r4@10

  v0 = 16;
  v1 = flash_buf2_24C;
  v2 = (u16*)unk_8034000;
  flash_buf2_24C[0] = 257;
  flash_buf2_24C[1] = 4660;
  flash_buf2_24C[2] = 0xffff;
  flash_buf2_24C[3] = 4996;
  flash_buf2_24C[4] = 0xfffe;
  flash_buf2_24C[5] = 0xf038;
  flash_buf2_24C[6] = flash_para9_044;
  flash_buf2_24C[8] = flash_para6_04C;
  flash_buf2_24C[10] = flash_para8_046;
  flash_buf2_24C[12] = flash_para2_052;
  flash_buf2_24C[13] = flash_para3_054;
  FLASH_Unlock();
  if ( FLASH_ErasePage((u32)unk_8034000) == FLASH_COMPLETE )
  {
    while ( 1 )
    {
      if ( v0-- == 0 )
        break;
      if ( FLASH_ProgramHalfWord((u32)v2, *v1) != FLASH_COMPLETE )
      {
        FLASH_Lock();
        return ;
      }
      v2++;
      ++v1;
    }
    for ( i = 16; i > 0; i = (u16)(i - 1) )
      flash_buf2_24C[i - 1] = 0;
    FLASH_Lock();
    //result = 1;
  }
  else
  {
    FLASH_Lock();
    //result = 0;
  }
  //return result;
}


//----- (08005F24) --------------------------------------------------------
void read_flash_3()
{
	signed int v0; // r3@1
  u16* v1; // r1@1
  u16 *v2; // r2@1

  v0 = 16;
  v1 = flash_buf3_26C;
  v2 = (u16*)unk_8033C00;
  while ( 1 )
  {
    if ( v0-- == 0 )
      break;
    *v1++ = *v2++;
  }
  //return 1;
}

//----- (08005F48) --------------------------------------------------------
void write_flash_3()
{
	signed int v0; // r4@1
  u16 *v1; // r5@1
  u16* v2; // r7@1
  //signed int result; // r0@2
  signed int i; // r4@10

  v0 = 16;
  v1 = flash_buf3_26C;
  v2 = (u16*)unk_8033C00;
  flash_buf3_26C[0] = 257;
  flash_buf3_26C[1] = 0;
  flash_buf3_26C[2] = 0xffff;
  flash_buf3_26C[3] = 4996;
  flash_buf3_26C[4] = 0xfffe;
  flash_buf3_26C[5] = 0xf038;
  flash_buf3_26C[6] = 0;
  flash_buf3_26C[7] = 0xffff;
  flash_buf3_26C[9] = 0xfffe;
  flash_buf3_26C[10] = 0xf038;
  flash_buf3_26C[11] = 0xfffe;
  flash_buf3_26C[12] = 0xf038;
  flash_buf3_26C[13] = 0xfffe;
  flash_buf3_26C[14] = 0xf038;
  flash_buf3_26C[15] = 0xf038;
  FLASH_Unlock();
  if ( FLASH_ErasePage((u32)unk_8033C00) == FLASH_COMPLETE )
  {
    while ( 1 )
    {
      if ( v0-- == 0 )
        break;
      if ( FLASH_ProgramHalfWord((u32)v2, *v1) != FLASH_COMPLETE )
      {
        FLASH_Lock();
        return;
      }
      v2++;
      ++v1;
    }
    for ( i = 16; i > 0; i = (u16)(i - 1) )
      flash_buf3_26C[i - 1] = 0;
    FLASH_Lock();
    //result = 1;
  }
  else
  {
    FLASH_Lock();
    //result = 0;
  }
  //return result;
}


//----- (08006014) --------------------------------------------------------
void reset_flash_3()
{
	//signed int result; // r0@2
  u16 v1; // ST00_2@5

  read_flash_3();
  if ( flash_buf3_26C[0] == 4660 )
  {
    flash_buf3_26C[8] = (((u8)byte_80075D1 << 8) + (u8)byte_80075DB) - 257;
		write_flash_3();
  }
  else
  {
    //result = flag_flash_write3_218;
    if ( flag_flash_write3_218 != 1 )
    {
      read_flash_3();
      v1 = flash_buf3_26C[8] + 257;
      flash_buf3_26C[8] = (u8)byte_80075D1 << 8;
      flash_buf3_26C[8] += (u8)byte_80075DB;
      //result = flash_buf3_26C[8];
      if ( flash_buf3_26C[8] == v1 )
      {
        //result = 1;
        flag_flash_write3_218 = 1;
      }
    }
  }
  //return result;
}
//----- (080060E0) --------------------------------------------------------
void read_flash_4()
{
	signed int v0; // r3@1
  u16* v1; // r1@1
  u16 *v2; // r2@1

  v0 = 16;
  v1 = flash_buf4_28C;
  v2 = (u16*)unk_802F000;
  while ( 1 )
  {
    if ( v0-- == 0 )
      break;
    *v1++ = *v2++;
  }
  //return 1;
}

//----- (08006104) --------------------------------------------------------
void write_flash_4()
{
	signed int v0; // r4@1
  u16 *v1; // r5@1
  u16* v2; // r7@1
  //signed int result; // r0@2
  signed int i; // r4@10

  v0 = 16;
  v1 = flash_buf4_28C;
  v2 = (u16*)unk_802F000;
  flash_buf4_28C[0] = 0xffff;
  flash_buf4_28C[1] = 0xffff;
  flash_buf4_28C[2] = 0xffff;
  flash_buf4_28C[3] = 4996;
  flash_buf4_28C[5] = 0xf038;
  flash_buf4_28C[6] = 0;
  flash_buf4_28C[7] = 0xffff;
  flash_buf4_28C[8] = 4996;
  flash_buf4_28C[9] = 0xfffe;
  flash_buf4_28C[10] = 0xf038;
  flash_buf4_28C[11] = 0xfffe;
  flash_buf4_28C[12] = 0xf038;
  flash_buf4_28C[13] = 0xfffe;
  flash_buf4_28C[14] = 0xf038;
  flash_buf4_28C[15] = 0xf038;
  FLASH_Unlock();
  if ( FLASH_ErasePage((u32)unk_802F000) == FLASH_COMPLETE )
  {
    while ( 1 )
    {
      if ( v0-- == 0 )
        break;
      if ( FLASH_ProgramHalfWord((u32)v2, *v1) != FLASH_COMPLETE )
      {
        FLASH_Lock();
        return ;
      }
      v2++;
      ++v1;
    }
    for ( i = 16; i > 0; i = (u16)(i - 1) )
      flash_buf4_28C[i - 1] = 0;
    FLASH_Lock();
    //result = 1;
  }
  else
  {
    FLASH_Lock();
    //result = 0;
  }
  //return result;
}


//----- (080061C8) --------------------------------------------------------
void reset_flash_4()
{
	//signed int result; // r0@2
  u16 v1; // ST00_2@5

  read_flash_4();
  if ( flash_buf4_28C[6] == 217 )
  {
    flash_buf4_28C[4] = (byte_80075D2 << 8) + byte_80075D6 + 257;
    write_flash_4();
  }
  else
  {
    if ( flag_flash_write4_220 != 1 )
    {
      read_flash_4();
      v1 = flash_buf4_28C[4] - 257;
      flash_buf4_28C[4] = byte_80075D2 << 8;
      flash_buf4_28C[4] += byte_80075D6;
      if ( flash_buf4_28C[4] == v1 )
      {
        flag_flash_write4_220 = 1;
      }
      else
      {
        GPIO_ResetBits(GPIOA, 32);//关机
      }
    }
  }
}

//----- (080062A8) --------------------------------------------------------
void read_flash_5()
{
	signed int v0; // r3@1
  u16* v1; // r1@1
  u16 *v2; // r2@1

  v0 = 16;
  v1 = flash_buf5_2AC;
  v2 = (u16*)unk_8016000;
  while ( 1 )
  {
    if ( v0-- == 0 )
      break;
    *v1++ = *(u16 *)v2++;
  }
  //return 1;
}

//----- (080062CC) --------------------------------------------------------
void write_flash_5()
{
	signed int v0; // r4@1
  u16 *v1; // r5@1
  u16* v2; // r7@1
  //signed int result; // r0@2
  signed int i; // r4@10

  v0 = 16;
  v1 = flash_buf5_2AC;
  v2 = (u16*)unk_8016000;
  flash_buf5_2AC[0] = 0xffff;
  flash_buf5_2AC[1] = 0xffff;
  flash_buf5_2AC[2] = 0xffff;
  flash_buf5_2AC[3] = 4996;
  flash_buf5_2AC[4] = 0xfffe;
  flash_buf5_2AC[6] = 0;
  flash_buf5_2AC[7] = 0xffff;
  flash_buf5_2AC[8] = 4996;
  flash_buf5_2AC[9] = 0xfffe;
  flash_buf5_2AC[10] = 0xf038;
  flash_buf5_2AC[11] = 0xfffe;
  flash_buf5_2AC[12] = 0xf038;
  flash_buf5_2AC[13] = 0xfffe;
  flash_buf5_2AC[14] = 0xf038;
  flash_buf5_2AC[15] = 0xf038;
  FLASH_Unlock();
  if ( FLASH_ErasePage((u32)unk_8016000) == FLASH_COMPLETE )
  {
    while ( 1 )
    {
      if ( v0-- == 0 )
        break;
      if ( FLASH_ProgramHalfWord((u32)v2, *v1) != 4 )
      {
        FLASH_Lock();
        //return 0;
				return;
      }
      v2++;
      ++v1;
    }
    for ( i = 16; i > 0; i = (u16)(i - 1) )
      flash_buf5_2AC[i - 1] = 0;
    FLASH_Lock();
    //result = 1;
  }
  else
  {
    FLASH_Lock();
    //result = 0;
  }
  //return result;
}


//----- (08006390) --------------------------------------------------------
void reset_flash_5()
{
	//signed int result; // r0@2
  u16 v1; // ST00_2@5

	v1 = 0x3c;
  read_flash_5();
	v1 += 2;
	v1++;
  if ( flash_buf5_2AC[8] == v1 )
  {
    flash_buf5_2AC[5] = (byte_80075D2 << 8) + byte_80075D6 + 4112;
    write_flash_5();
  }
  else
  {
    //result = flag_flash_write5_228;
    if ( flag_flash_write5_228 != 1 )
    {
      read_flash_5();
      v1 = flash_buf5_2AC[5] - 4112;
      flash_buf5_2AC[5] = byte_80075D2 << 8;
      flash_buf5_2AC[5] += byte_80075D6;
      //result = flash_buf5_2AC[5];
      if ( flash_buf5_2AC[5] == v1 )
      {
        //result = 1;
        flag_flash_write5_228 = 1;
      }
    }
  }
  //return result;
}


//----- (08006468) --------------------------------------------------------
void read_flash_6()
{//读flash
	signed int v0; // r3@1
  u16* v1; // r1@1
  u16 *v2; // r2@1

  v0 = 16;
  v1 = flash_buf6_2CC;
  v2 = (u16*)unk_801B000;
  while ( 1 )
  {
    if ( v0-- == 0 )
      break;
    *v1++ = *v2++;
  }
  //return 1;
}

//----- (0800648C) --------------------------------------------------------
void write_flash_6()
{//写flash 重置数据
	signed int v0; // r4@1
  u16 *v1; // r5@1
  u16* v2; // r7@1
  //signed int result; // r0@2
  //char v4; // zf@8
  signed int i; // r4@10

  v0 = 16;
  v1 = flash_buf6_2CC;
  v2 = (u16*)unk_801B000;
  flash_buf6_2CC[0] = 0xffff;
  flash_buf6_2CC[1] = 0xffff;
  flash_buf6_2CC[2] = 0xffff;
  flash_buf6_2CC[3] = 4996;
  flash_buf6_2CC[4] = 0xfffe;
  flash_buf6_2CC[6] = 0;
  flash_buf6_2CC[7] = 0xffff;
  flash_buf6_2CC[8] = 4996;
  flash_buf6_2CC[9] = 0xfffe;
  flash_buf6_2CC[10] = 0xf038;
  flash_buf6_2CC[11] = 0xfffe;
  flash_buf6_2CC[12] = 0xf038;
  flash_buf6_2CC[13] = 0xfffe;
  flash_buf6_2CC[14] = 0xf038;
  FLASH_Unlock();
  if ( FLASH_ErasePage((u32)unk_801B000) == FLASH_COMPLETE )
  {//擦除数据
    while ( 1 )
    {
      if ( v0-- == 0 )
        break;
      if ( FLASH_ProgramHalfWord((u32)v2, *v1) != 4 )
      {
        FLASH_Lock();
        return;
      }
      v2++;
      ++v1;
    }
    for ( i = 16; i > 0; i = (u16)(i - 1) )
      flash_buf6_2CC[i - 1] = 0;
    FLASH_Lock();
    //result = 1;
  }
  else
  {
    FLASH_Lock();
    //result = 0;
  }
  //return result;
}


//----- (0800654E) --------------------------------------------------------
void reset_flash_6()
{
  u16 v1; // ST00_2@5

  read_flash_6();
  if ( flash_buf6_2CC[10] == 828 )
  {
    flash_buf6_2CC[5] = (byte_80075D3 << 8) + byte_80075D7 + 8500;
    write_flash_6();//数据重置
  }
  else if ( flag_flash_write6_230 != 1 )
	{
		read_flash_6();//重新读取参数
		v1 = flash_buf6_2CC[5] - 8500;
		flash_buf6_2CC[5] = byte_80075D3 << 8;
		flash_buf6_2CC[5] += byte_80075D7;
		if ( flash_buf6_2CC[5] == v1 )
		{
			flag_flash_write6_230 = 1;
		}
  }
}


