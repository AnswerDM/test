//#include "platform.h"

#include "stm32f10x.h"
#include "vl53l0x.h"
//#include "drivers/usart.h"

char IIC_Channel = 1;

unsigned char gbuf[16] = {0};

unsigned char vl53l0x_write_reg(unsigned char reg,
                                unsigned char length,
                                unsigned char * data)
{
    return iic_write(VL53L0X_Address, reg, length, data);
}

unsigned char vl53l0x_read_reg(unsigned char reg,
                                unsigned char length,
                                unsigned char * dat)
{
    return iic_read(VL53L0X_Address, reg, length, dat);
}

uint16_t VL53L0X_decode_vcsel_period(short vcsel_period_reg) {
  // Converts the encoded VCSEL period register value into the real
  // period in PLL clocks
  uint16_t vcsel_period_pclks = (vcsel_period_reg + 1) << 1;
  return vcsel_period_pclks;
}

void init_vl53l0x(void)
{
    unsigned char  temp = 0;
    vl53l0x_read_reg( VL53L0X_REG_IDENTIFICATION_REVISION_ID, 1, &temp);
    //printf( "Revision ID: %d \n", temp);
    vl53l0x_read_reg( VL53L0X_REG_IDENTIFICATION_MODEL_ID, 1, &temp);
    //printf( "Device ID: %d \n", temp);
    vl53l0x_read_reg(VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD, 1, &temp);
    //printf( "PRE_RANGE_CONFIG_VCSEL_PERIOD= %d\n", temp);
    //printf( "decode : %d\n", VL53L0X_decode_vcsel_period(temp) );
    
    vl53l0x_read_reg(VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD, 1, &temp);
    //printf( "FINAL_RANGE_CONFIG_VCSEL_PERIOD= %d\n", temp);
    //printf( "decode : %d\n", VL53L0X_decode_vcsel_period(temp) );
    
    temp = 0x01;
    vl53l0x_write_reg(VL53L0X_REG_SYSRANGE_START, 1, &temp);
}

unsigned char val_buf[20]  = {0};

signed short dist_1 = 0;
signed short dist_2 = 0;

void test(void)
{
    unsigned char val = 0;
    signed short dist = 0;
    int cnt = 0;
    while (cnt < 100) { // 1 second waiting time max
        iic_delay();
        vl53l0x_read_reg(VL53L0X_REG_RESULT_RANGE_STATUS, 1, &val);
        if (val & 0x01) break;
        cnt++;
    }
    //if (val & 0x01) printf("ready\n"); 
    //else printf("not ready");
    
    vl53l0x_read_reg(0x14, 12, val_buf);
    
    dist = val_buf[10] << 8  | val_buf[11];
		
		if(dist>1500||dist<100)
		{
			//dist = 0;
		}
		if(dist==-1||dist>=1500)
		{
			dist = 1500;
		}
	
		IIC_Channel == 1 ?  (dist_1 = dist) : (dist_2 = dist) ;

//    printf ("dist = %d \n", dist);
    
    
}



















////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                IIC Interface                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
unsigned char ack;


void init_iic_port(void)
{
	// SCL          PB10
	// SDA          PB11
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// SCL	        PB6
	// SDA          PB7
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void iic_delay(void)
{
	//delay_us(2);
	int i;
	for (i = 0; i < 12; i++)
	{
		;
	}
}

void iic_start(void)
{
    SDA_HIGH ;
    SCL_HIGH ;      //?????
    iic_delay() ;    //??
    SDA_LOW ;       //?????
    iic_delay() ;    //??
    SCL_LOW ;       //?????
}

void iic_stop(void)
{
    SDA_LOW ;
    SCL_HIGH;
    iic_delay();
    SDA_HIGH; 
    iic_delay(); 
}

void iic_send_ack(unsigned char ack)
{
    if(ack)
    {
        SDA_HIGH ;
    }
    else
    {
        SDA_LOW ;
    }           
    SCL_HIGH ;       
    iic_delay() ;   
    SCL_LOW ;          
    iic_delay() ;   
}

unsigned char iic_recv_ack(void)
{
    SDA_IN ;
    SCL_HIGH ;                     
    iic_delay() ;                 
    if(READ_SDA)  
    {
       ack = 1;
    }
    else
    {
        ack = 0;
    }
    SCL_LOW ;                       //?????
    SDA_OUT ;                       //??SDA???
    iic_delay() ;                    //??
    return ack ;

}

void iic_send_byte(unsigned char dat)
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        if((dat << i) & 0x80)   //????
        {    
			SDA_HIGH ;          //??SDA??
        }
		else
		{
		    SDA_LOW ;
        }
		iic_delay() ;            //??
        SCL_HIGH ;              //?????
        iic_delay() ;            //??
        SCL_LOW ;               //?????
    }
    iic_recv_ack();
}

unsigned char iic_recv_byte(void)
{
    unsigned char i,dat;
    SDA_HIGH ;                  //??????,??????
    iic_delay() ;                //??
    SDA_IN ;                    //??SDA???
    iic_delay() ;                //??
    for(i = 0; i < 8; i++)
    {
        dat <<= 1;              //????
        SCL_HIGH ;              //?????
        iic_delay() ;            //??
        if(READ_SDA)   			//??SDA????
            dat ++ ;
        SCL_LOW ;               //?????
        iic_delay() ;            //??
    }
    SDA_OUT ;                   //??SDA???
    return dat ;
}

unsigned char iic_read(unsigned char dev,
               unsigned char reg,
               unsigned char length,
               unsigned char * data)
{
    unsigned char i ;
    iic_start() ;
    iic_send_byte(dev) ;
    iic_send_byte(reg) ;
    iic_start() ;
    iic_send_byte(dev + 1) ;
    for(i = 0; i < length; i ++)
    {
        data[i] = iic_recv_byte() ;
        if(i == length-1)
            iic_send_ack(_NACK) ;
        else
            iic_send_ack(_ACK) ;
    }
    iic_stop() ;
    return 0 ;
}

unsigned char iic_write(unsigned char dev,
                        unsigned char reg,
                        unsigned char len,
                        unsigned char * dat)
{
    unsigned char i ;
    iic_start() ;
    iic_send_byte(dev) ;
    iic_send_byte(reg) ;
    for(i = 0; i < len; i ++)
    {
        iic_send_byte(dat[i]) ;
    }
    iic_stop() ;
    return 0 ;
}

