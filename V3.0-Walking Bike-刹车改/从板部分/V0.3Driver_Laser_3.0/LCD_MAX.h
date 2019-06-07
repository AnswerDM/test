#ifndef _LCD_MAX_H_
#define _LCD_MAX_H_

#include <MAIN.h>


//PB12  LCD_SCLK
#define LCD_SCLK_HIGH    GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LCD_SCLK_LOW     GPIO_ResetBits(GPIOB, GPIO_Pin_12)
//PB14  LCD_RS
#define LCD_RS_HIGH      GPIO_SetBits(GPIOB, GPIO_Pin_14)
#define LCD_RS_LOW       GPIO_ResetBits(GPIOB, GPIO_Pin_14)
//PB13  LCD_SDA
#define LCD_SID_HIGH     GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define LCD_SID_LOW      GPIO_ResetBits(GPIOB, GPIO_Pin_13)
//PA8   LCD_CS
#define LCD_CS_HIGH      GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define LCD_CS_LOW       GPIO_ResetBits(GPIOA, GPIO_Pin_8)
//PB15  LCD_RES
#define LCD_RESET_HIGH      GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define LCD_RESET_LOW       GPIO_ResetBits(GPIOB, GPIO_Pin_15)



//#define ROM_CS_HIGH      ROM_PORT |= (1<<ROM_CS_bit)
//#define ROM_CS_LOW       ROM_PORT &= ~(1<<ROM_CS_bit)//?? IC ???? Rom_CS ???? IC ? CS#

//#define ROM_IN_HIGH      ROM_PORT |= (1<<ROM_IN_bit)
//#define ROM_IN_LOW       ROM_PORT &= ~(1<<ROM_IN_bit)//?? IC ???? Rom_CS ???? IC ? CS#

//#define ROM_SCK_HIGH      ROM_PORT |= (1<<ROM_SCK_bit)
//#define ROM_SCK_LOW       ROM_PORT &= ~(1<<ROM_SCK_bit)//?? IC ????:Rom_SCK ???? IC ? SCK


//#define ROM_OUT           ROM_PIN&(1<<ROM_OUT_bit)

extern unsigned int CGRAM_order;
extern unsigned int CGRAM_ADDRESS;

extern void initial_lcd(void);
extern void clear_screen(void);
extern void LCD_port_init(void);
extern void Display_CGRAM_16x16(int y,int x,unsigned char *dp);
extern void display_char1(int y,int x,unsigned char *dp);
extern void Display_CGRAM_192x96(unsigned int *dp);
#endif
