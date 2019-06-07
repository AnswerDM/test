#include "LCD_MAX.h"
unsigned int CGRAM_order=0;
unsigned int CGRAM_ADDRESS=0x80;


void LCD_port_init(void)
{
	GPIO_InitTypeDef type;
//	//PA4  ROM_IN
//	type.GPIO_Pin = GPIO_Pin_4;
//  type.GPIO_Speed = GPIO_Speed_50MHz;
//  type.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOA, &type);
//	//PA5  ROM_OUT
//	type.GPIO_Pin = GPIO_Pin_5;
//  type.GPIO_Speed = GPIO_Speed_50MHz;
//  type.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(GPIOA, &type);
//	//PA6  ROM_SCK
//	type.GPIO_Pin = GPIO_Pin_6;
//  type.GPIO_Speed = GPIO_Speed_50MHz;
//  type.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOA, &type);
//	//PA7  ROM_CS
//	type.GPIO_Pin = GPIO_Pin_7;
//  type.GPIO_Speed = GPIO_Speed_50MHz;
//  type.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOA, &type);
	//PA8  LCD_CS
	type.GPIO_Pin = GPIO_Pin_8;
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &type);
	//PB15  LCD_RES
	type.GPIO_Pin = GPIO_Pin_15;
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &type);
	//PB14  LCD_RS
	type.GPIO_Pin = GPIO_Pin_14;
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &type);
	//PB13  LCD_SDA
	type.GPIO_Pin = GPIO_Pin_13;
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &type);
	//PB12  LCD_SCLK
	type.GPIO_Pin = GPIO_Pin_12;
  type.GPIO_Speed = GPIO_Speed_50MHz;
  type.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &type);
}

/*??:1 ??? i ?*/
void delay(int i)
{
 int j,k;
 for(j=0;j<i;j++)
    for(k=0;k<110;k++);
}
/*??:10us ? i ?*/
void delay_us(int i)
{
 int j,k;
 for(j=0;j<i;j++)
    for(k=0;k<5;k++);
}
/*??????,?????? P2.0 ? GND ???????*/


/*???? LCD ??*/
void transfer_command_lcd(int data1)
{
    char i;
    LCD_CS_LOW;
    LCD_RS_LOW;
    for(i=0;i<8;i++)
    {
        LCD_SCLK_LOW;
        delay_us(8); //?????
        if(data1&0x80) LCD_SID_HIGH;
        else LCD_SID_LOW;
        LCD_SCLK_HIGH;
        delay_us(8); //?????
        data1=data1<<1;
    }
    LCD_CS_HIGH;
}


/*???? LCD ??*/
void transfer_data_lcd(int data1)
{
    char i;
    LCD_CS_LOW;
    LCD_RS_HIGH;
    for(i=0;i<8;i++)
    {
        LCD_SCLK_LOW;
        delay_us(8); //?????
        if(data1&0x80) LCD_SID_HIGH;
        else LCD_SID_LOW;
        LCD_SCLK_HIGH;
        data1=data1<<1;
    }
    LCD_CS_HIGH;
}
/*LCD ?????*/
void initial_lcd(void)
{
    delay(30);
    LCD_RESET_LOW; /*?????*/
    delay(30);
    LCD_RESET_HIGH; /*????*/
    delay(30);
    delay(30);
    //////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x08); /*???*/
    delay_us(10);
    transfer_command_lcd(0x30); //???
    delay_us(50);

    transfer_command_lcd(0x08); //??? 1
    delay_us(10);
    transfer_command_lcd(0x30); //???
    delay_us(10);

    transfer_command_lcd(0x08); //??? 1
    delay_us(10);
    transfer_command_lcd(0x30); //???
    delay_us(10);


    transfer_command_lcd(0x08); //??? 1
    delay_us(10);
    transfer_command_lcd(0x01); //??
    delay_us(10);
    delay_us(10);
    delay_us(10);
    delay_us(10);
    delay_us(10);

    //////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x08); //??? 1
    delay_us(100);
    transfer_command_lcd(0x06); //Entry Mode Set
    delay_us(10);
    //////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x08); //??? 1
    delay_us(10);
    transfer_command_lcd(0x80); //Set DDRAM Address
    delay_us(10);

    /////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x09); //??? 2
    delay_us(10);
    transfer_command_lcd(0x06); //??????
    delay_us(10);
    /////////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x2D); //1/11 ???(Bais) 0x2F
    delay_us(10);
    ////////////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x26); //????,5X
    delay_us(10);
    ////////////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x37); //Select Regulator Volume Register
    delay_us(10);
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x4e); //?? LCD ???? 0x62 0x5a
    delay_us(10);
    /////////////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x82); //????
    delay(10);
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x86); //???? 2
    delay(10);
    transfer_command_lcd(0x0b); //??? 4
    delay_us(10);
    transfer_command_lcd(0x87); //???? 3
    delay(10);
    //////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    transfer_command_lcd(0x08); //??? 1
    delay_us(10);
    transfer_command_lcd(0x38); //???
    delay_us(10);
}

/*????*/
void clear_screen(void)
{
   transfer_command_lcd(0x01);
}

/*??????????*/
void display_char1(int y,int x,unsigned char *dp)
{
    transfer_command_lcd(0x80); //Set DDRAM Address
    transfer_command_lcd(0x10); //Set SEGRAM Address
    transfer_command_lcd(0x80+(y-1)*(0x10)+(x-1));
    while(*dp>1)
    {
        transfer_data_lcd(*dp);
        dp++;
        transfer_data_lcd(*dp);/* ???????????????*/
        dp++;
    }
}

/*? 16x16 ????*/
void write_CGRAM_16x16(unsigned char *dp)
{
    unsigned int i;
    // uint CGRAM_ADDRESS=0x80;
    transfer_command_lcd(0x0a); //? 3
    CGRAM_ADDRESS++;
    transfer_command_lcd(CGRAM_ADDRESS); //Set CGRAM Address
    for(i=0;i<32;i++)
    {
        transfer_data_lcd(*dp);
        dp++;
    }
}


/*? 192x96 ???*/
void write_CGRAM_192x96(unsigned int *dp)
{
    unsigned int i,j,k,m;
    unsigned int CGRAM_ADDRESS=0x80;
    transfer_command_lcd(0x0a); //??<??? 3>
    CGRAM_ADDRESS=0x80;
    for(m=0;m<6;m++)
    {
        for(i=0;i<12;i++)
        {
            transfer_command_lcd(CGRAM_ADDRESS+m*12+i); //?? CGRAM ??
            // dp=dp_temp+i*2+m*384;
            for(j=0;j<16;j++)
            {
                for(k=0;k<2;k++)
                {
                    transfer_data_lcd( *(dp+i*2+m*384+k+24*j) );
                }
            }
        }
    }
}

//??????
//void Display_CGRAM_192x96(unsigned int *dp)
//{
//    unsigned int i,j;
//    unsigned int CGRAM_order=0;
//    write_CGRAM_192x96(dp);
//    transfer_command_lcd(0x08); //??<??? 1>

//    for(j=0;j<6;j++)
//    {
//        for(i=0;i<12;i++)
//        {
//            transfer_command_lcd(0x80+0x10*j+i); //?? DDRAM ??
//            transfer_data_lcd( ((CGRAM_order+0xa0a0)>>8)&0x00ff );//? DDRAM ?????
//            transfer_data_lcd( (CGRAM_order+0xa0a0)&0x00ff );//? DDRAM ?????
//            CGRAM_order++;
//        }
//    }
//}

//??????
void Display_CGRAM_16x16(int y,int x,unsigned char *dp)
{
   //  unsigned int CGRAM_order=0;
    write_CGRAM_16x16(dp);
    CGRAM_order++;
    transfer_command_lcd(0x08); //??? 1
    transfer_command_lcd(0x80+(y-1)*(0x10)+(x-1)); //Set CGRAM Address
    transfer_data_lcd( ((CGRAM_order+0xa0a0)>>8)&0x00ff );//H
    transfer_data_lcd( (CGRAM_order+0xa0a0)&0x00ff );//L
}




