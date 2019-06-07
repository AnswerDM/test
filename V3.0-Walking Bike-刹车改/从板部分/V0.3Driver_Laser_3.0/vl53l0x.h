#ifndef _VL53L0X_H__
#define _VL53L0X_H__

extern char IIC_Channel;



#define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
#define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
#define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
#define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define VL53L0X_REG_SYSRANGE_START                  0x00
#define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
#define VL53L0X_REG_RESULT_RANGE_STATUS             0x14

#define VL53L0X_Address                             0x52



extern void init_vl53l0x(void);

void test(void);



////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                IIC Interface                               //
//     Channel  1                                                             //
// SCL	        PB10                                                          //
// SDA          PB11                                                          //
//     Channel  2                                                             //
// SCL	        PB6                                                           //
// SDA          PB7                                                           //
////////////////////////////////////////////////////////////////////////////////
/*--------------- define ---------------*/


#define SDA_OUT		\
do \
{ \
	     if(IIC_Channel==1){GPIOB->CRH&=0XFFFF0FFF;  GPIOB->CRH |= (3 << 12); } \
	else if(IIC_Channel==2){GPIOB->CRL&=0X0FFFFFFF;  GPIOB->CRL |= (3 << 28); } \
} \
while(0)


#define SDA_IN		\
do \
{ \
	     if(IIC_Channel==1){GPIOB->CRH&=0XFFFF0FFF;  GPIOB->CRH |= ((unsigned int)8 << 12);} \
	else if(IIC_Channel==2){GPIOB->CRL&=0X0FFFFFFF;  GPIOB->CRL |= ((unsigned int)8 << 28);} \
} \
while(0)

#define SDA_HIGH	\
do \
{ \
	     if(IIC_Channel==1){GPIO_SetBits(GPIOB, GPIO_Pin_11);} \
	else if(IIC_Channel==2){GPIO_SetBits(GPIOB, GPIO_Pin_7);} \
} \
while(0)
	
#define SDA_LOW		\
do \
{ \
	     if(IIC_Channel==1){GPIO_ResetBits(GPIOB, GPIO_Pin_11);} \
	else if(IIC_Channel==2){GPIO_ResetBits(GPIOB, GPIO_Pin_7);} \
} \
while(0)

#define SCL_HIGH	\
do \
{ \
	     if(IIC_Channel==1){GPIO_SetBits(GPIOB, GPIO_Pin_10);} \
	else if(IIC_Channel==2){GPIO_SetBits(GPIOB, GPIO_Pin_6);} \
} \
while(0)

#define SCL_LOW		\
do \
{ \
	     if(IIC_Channel==1){GPIO_ResetBits(GPIOB, GPIO_Pin_10);} \
	else if(IIC_Channel==2){GPIO_ResetBits(GPIOB, GPIO_Pin_6);} \
} \
while(0)

#define READ_SDA	IIC_Channel == 1 ?  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) : GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)


#define _ACK     0
#define _NACK    1

void init_iic_port(void);
extern void iic_delay(void) ;
extern void iic_start(void) ;
extern void iic_stop(void) ;
extern void iic_send_ack(unsigned char ack) ;
extern unsigned char iic_recv_ack(void) ;
extern void iic_send_byte(unsigned char dat) ;
extern unsigned char iic_recv_byte(void) ;

extern unsigned char iic_read(unsigned char dev,
               unsigned char reg,
               unsigned char length,
               unsigned char * data);

extern unsigned char iic_write(unsigned char dev,
                        unsigned char reg,
                        unsigned char len,
                        unsigned char * dat);



extern signed short dist_1 ;
extern signed short dist_2 ;

#endif
                        













