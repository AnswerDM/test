#ifndef __FLASH_H
#define __FLASH_H		
#include "extern.h"

u16 flash_para9_044;
u16 flash_para8_046;
u16 flash_para7_048;
u16 flash_para6_04C;
u16 flash_para5_04E;
u16 flash_para4_050;
u16 flash_para2_052;
u16 flash_para3_054;

//u32 ram_214=0x15554ff;
u8 flag_flash_write3_218;
//u8 ram_21C=0x33;
//u8 ram_21D=0x44;
//u8 ram_21E=0x44;
//u8 ram_21F;
u8 flag_flash_write4_220;
//u8 ram_224=0x33;
//u8 ram_225=0x44;
//u8 ram_226=0x44;
u8 flag_flash_write5_228;
//u8 ram_22C=0x33;
//u8 ram_22D=0x44;
//u8 ram_22E=0x44;
u8 flag_flash_write6_230;

u16 flash_buf2_24C[16];
u16 flash_buf3_26C[16];
u16 flash_buf4_28C[16];
u16 flash_buf5_2AC[16];
u16 flash_buf6_2CC[16];

u8 const byte_80075D0 __attribute__ ((at(0x80075D0))) = 0x35; // weak 
u8 const byte_80075D1 __attribute__ ((at(0x80075D1))) = 0xFF; // weak
u8 const byte_80075D2 __attribute__ ((at(0x80075D2))) = 0xd9; // weak
u8 const byte_80075D3 __attribute__ ((at(0x80075D3))) = 5; // weak
u8 const byte_80075D4 __attribute__ ((at(0x80075D4))) = 0x32; // weak
u8 const byte_80075D5 __attribute__ ((at(0x80075D5))) = 0x58; // weak
u8 const byte_80075D6 __attribute__ ((at(0x80075D6))) = 0x33; // weak
u8 const byte_80075D7 __attribute__ ((at(0x80075D7))) = 0x39; // weak
u8 const byte_80075D8 __attribute__ ((at(0x80075D8))) = 0x31; // weak
u8 const byte_80075D9 __attribute__ ((at(0x80075D9))) = 0x82; // weak
u8 const byte_80075DA __attribute__ ((at(0x80075DA))) = 0x21; // weak
u8 const byte_80075DB __attribute__ ((at(0x80075DB))) = 0x57; // weak

u16 const unk_8016000[16] __attribute__ ((at(0x8016000)))={
0xFFFF,0xFFFF,0xFFFF,0x1384,0xFFFE,0xE943,0x0000,0xFFFF,
0x1384,0xFFFE,0xF038,0xFFFE,0xF038,0xFFFE,0xF038,0xF038};
u16 const unk_801B000[16] __attribute__ ((at(0x801B000)))={
0xFFFF, 0xFFFF, 0xFFFF, 0x1384, 0xFFFE, 0x266D, 0, 0xFFFF,
0x1384, 0xFFFE, 0xF038, 0xFFFE, 0xF038, 0xFFFE, 0xF038, 0xFFFF
}; 	// 	0x801B000; // weak
u16 const unk_802F000[16] __attribute__ ((at(0x802F000)))={
0xFFFF, 0xFFFF, 0xFFFF, 0x1384, 0xDA34, 0xF038, 0, 0xFFFF,
0x1384, 0xFFFE, 0xF038, 0xFFFE, 0xF038, 0xFFFE, 0xF038, 0xF038
}; 	// 	0x802F000; // weak
u16 const unk_8033C00[16] __attribute__ ((at(0x8033C00)))={
0x101, 0, 0xFFFF, 0x1384, 0xFFFE, 0xF038, 0, 0xFFFF,
0xFE56, 0xFFFE, 0xF038, 0xFFFE, 0xF038, 0xFFFE, 0xF038, 0xF038
}; 	// 	0x8033C00; // weak
u16 const unk_8034000[16] __attribute__ ((at(0x8034000)))={
0x101, 0x1234, 0xFFFF, 0x1384, 0xFFFE, 0xF038, 0x3828, 0,
0xFFFF, 0xFFFF, 0, 0, 0x476A, 0x54A3, 0xFFFF, 0xFFFF
}; 	// 	0x8034000; // weak

void reset_flash_2(void);
void read_flash_2(void);//读参数
void write_flash_2(void);//写参数
void read_flash_3(void);//读参数
void write_flash_3(void);//写参数
void reset_flash_3(void);
void read_flash_4(void);//读参数
void write_flash_4(void);//写参数
void reset_flash_4(void);
void read_flash_5(void);//读参数
void write_flash_5(void);//写参数
void reset_flash_5(void);
void read_flash_6(void);//读参数
void write_flash_6(void);//写参数
void reset_flash_6(void);

#endif
