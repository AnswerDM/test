#include "profiBus.h"
#include "main.h"



 VPC3_SYSTEM_STRUC         dp_sys;
 VPC3_STRUC *vpc3_ptr;
 UBYTE vpc3_result;//从.h中移过来的
 
 



extern void delay_ms(u16 nms);

void init_user_data(void)
{
	//initialization for configuration 
	dp_sys.din_bufsize = 32;   //dp_sys.inp_data_len;
	dp_sys.dout_bufsize = 0;   //do_sys.outp_data_len;
	
	dp_sys.cfg_bufsize = 1;    //0x44
	
	//initialization for prm
	dp_sys.prm_bufsize = 7;  //dp_prm_len
	dp_sys.prm_spec = 0;     //dp_prm_spec
	
	//initialzation for ident number
	dp_sys.inp_data_len = dp_ident_high;
	dp_sys.ind_low = dp_ident_low;
	
	//initialization for ssa
	dp_sys.ssa_bufsize = 0; //dp_ssa_len
	dp_sys.ssa_chg = 0xFF;
	
	//initialization for diagnostic
	dp_sys.diag_bufsize = 6; //dp_diag_len
	
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*   function:     initializing constant vpc3 values                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
DP_ERROR_CODE vpc3_set_constants(UBYTE slave_address)
{
	DP_ERROR_CODE result;
	
	result = DP_OK ;
	
	
	/*-----------------------------------------------------------------------*/
    /* initialize  control logic                                             */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->int_req1                = 0x00;
    vpc3_ptr->int_req2                = 0x00;
    vpc3_ptr->isreg.wr.int_ack1       = 0xFF;
    vpc3_ptr->isreg.wr.int_ack2       = 0xFF;
    vpc3_ptr->ctrl_reg.wr.mode_reg1_r = 0xFF;      // reset mode register 1

    /*-----------------------------------------------------------------------*/
    /* set modes of vpc3                                                     */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->mode_reg0_H = INIT_VPC3_MODE_REG_H;
    vpc3_ptr->mode_reg0_L = INIT_VPC3_MODE_REG_L;

    vpc3_ptr->ctrl_reg.wr.mode_reg2 = INIT_VPC3_MODE_REG_2;

    /*-----------------------------------------------------------------------*/
    /* set interrupt triggers                                                */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->isreg.wr.int_mask_H = ~(INIT_VPC3_IND_H);
    vpc3_ptr->isreg.wr.int_mask_L = ~(INIT_VPC3_IND_L);

    /*-----------------------------------------------------------------------*/
    /* set time-variables                                                    */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->ctrl_reg.wr.wd_baud_ctrl = 0x10;    // WD Timeout
    vpc3_ptr->ctrl_reg.wr.mintsdr      = 0x0B;    // Min Tsdr 11 BIT (11Bit .. 255Bit)

    /*-----------------------------------------------------------------------*/
    /* set variables for synch-mode                                          */
    /*-----------------------------------------------------------------------*/
    //vpc3_ptr->ctrl_reg.wr.sync_pw_reg = SYNCH_PULSEWIDTH;   // sync pulse width register
    //vpc3_ptr->ctrl_reg.wr.sync_group = 0x80;
    //vpc3_ptr->ctrl_reg.wr.sync_mode  = 0x00;

    /*-----------------------------------------------------------------------*/
    /* set user watchdog (dataexchange telegram counter)                     */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->user_wd_value[1] = (UBYTE)(USER_WD >> 8);
    vpc3_ptr->user_wd_value[0] = (UBYTE)(USER_WD);
    VPC3_RESET_USER_WD();

    /*-----------------------------------------------------------------------*/
    /* set pointer to FF                                                     */
    /*-----------------------------------------------------------------------*/
    //vpc3_ptr->fdl_sap_list_ptr = VPC3_SAP_CTRL_LIST_START;
    //vpc3_ptr->sap_ctrl_list[0] = 0xFF;

    /*-----------------------------------------------------------------------*/
    /* ssa support                                                           */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->real_no_add_change = ( dp_sys.ssa_bufsize == 0 ) ? 0xFF : 0x00;

    /*-----------------------------------------------------------------------*/
    /* set profibus ident number                                             */
    /*-----------------------------------------------------------------------*/
    vpc3_ptr->ident_high = 0x00;//(UBYTE)(IDENT_NR >> 8);
    vpc3_ptr->ident_low  = 0x08;//(UBYTE)(IDENT_NR);

    /*-----------------------------------------------------------------------*/
    /* set and check slave address                                           */
    /*-----------------------------------------------------------------------*/
    if( (slave_address < 126) && (slave_address != 0) )
    {
        vpc3_ptr->slave_addr = slave_address;
    }
    else
    {
        result = DP_ADDRESS_ERROR;
    }

    return result;
	
}

/********************************************************************************
*                                                                               *
*  UWORD assign_aux_buf (   UWORD PTR_ATTR *lens, UBYTE count,                  *
*                           UBYTE PTR_ATTR *assign,                             *
*                           UWORD PTR_ATTR *aux_len)                            *
*                                                                              *
*   function:      Calculate length of AUX buffers.                            *
*                                                                              *
*   parameter:     lens    : pointer of list to the buffer length              *
*                  count   : length of list (2..3)                             *
*                  assign  : Bit array, in which the assignments of the        *
*                            AUX-buffers1 and 2 are defined to the control     *
*                            buffers, SSA-Buf, PRM-Buf, Cfg-Buf                *
*                  aux_len : Pointer to a 2 byte field of aux-buffer length.   *
*   return value:  count of bytes used for aux buffers.                        *
*                                                                              *
********************************************************************************/
UWORD assign_aux_buf(UWORD *lens,UBYTE count,UBYTE *assign,UWORD *aux_len)
{
	  UWORD   min_len = 0xFFFF;     // calculated minimal length
    UBYTE   min_step = 0;         // step by calculated minimal length
    UBYTE   i,j;
    UBYTE   pos[3];               // memory for position of length
    UWORD   lensx[3];             // workarea for calculated length
    UBYTE   step;                 // counter
    UWORD   wtmp;                 // tmp-variable for calculated length
    UBYTE   tmp;                  // tmp-variable for calculated length
                                  // tmp-varaiable for sorted positions

    // check count
    if((count == 2) || (count == 3))
    {
        for(i = 0; i < count; i++)
        {
            // init memory for position of length
            pos[i] = i;
            // copy length into workarea for calculated length
            lensx[i] = lens[i];
            // put length to 8 Bit Segmentaddresses
            lensx[i] = (lensx[i] + SEG_OFFSET) & SEG_ADDWORD;
        }

        // sort length, highest length to index 0
        for(i = 0; i < count-1; i++)
        {
            for(j = i+1; j < count; j++)
            {
                if(lensx[i] < lensx[j])
                {
                    // found higher length
                    tmp = lensx[i];          // swap length
                    lensx[i] = lensx[j];
                    lensx[j] = tmp;
                    tmp = pos[i];            // swap position
                    pos[i] = pos[j];
                    pos[j] = tmp;
                }
            }
        }

        // delete zero length from list lensx
        for(i = count; i > 0; i--)
        {
            if(lensx[i-1] == 0)
            {
                count--;
            }
        }

        if( count == 0 )
        {
            min_len = 0;     // Error: no defined buffer length
        }

        // gradual length assign to aux-buffer
        for(step = 0; step < count; step++)
        {
            // get length for AUX-Buffer 1
            aux_len[0] = 0;

            for(i = step; i < count; i++)
            {
                if(aux_len[0] < lensx[i])
                {
                    aux_len[0] = lensx[i];
                }
            }

            aux_len[0] = aux_len[0] * (count - step + 1);

            // get length for AUX-Buffer 2
            aux_len[1] = 0;

            for(i = 0; i < step; i++)
            {
                if(aux_len[1] < lensx[i])
                {
                    aux_len[1] = lensx[i];
                }
            }

            aux_len[1] = aux_len[1] * (step + 1);

            if((aux_len[0] + aux_len[1]) < min_len)
            {
                // new minimal length found
                min_len = aux_len[0] + aux_len[1];
                min_step = step;
            }
        }

        // calculate length for AUX Buffer 1
        aux_len[0] = 0;

        for(i = min_step; i < count; i++)
        {
            if(aux_len[0] < lensx[i])
            {
                aux_len[0] = lensx[i];
            }
        }

        // put length, assigned for AUX buffer 1
        for(i = min_step; i < count; i++)
        {
            lens[pos[i]] = aux_len[0];
        }

        // calculate length of AUX-Buffer 2
        aux_len[1] = 0;

        for(i = 0; i < min_step; i++)
        {
            if (aux_len[1] < lensx[i])
            {
                aux_len[1] = lensx[i];
            }
        }

        *assign = 0;    // put all buffer to AUX-Buffer 1

        for(i = 0; i < min_step; i++)
        {
            lens[pos[i]] = aux_len[1];
            *assign |= 0x1 << pos[i];
        }

        //check here for VPC3+/B
        //handle Cfg-telegram only over AUX-Buffer 1
        if( *assign & 0x02 )
        {
            tmp = (*assign);
            *assign = ((~tmp)&0x07);
            //*assign &= 0x07;
            wtmp = aux_len[0];
            aux_len[0] = aux_len[1];
            aux_len[1] = wtmp;
        }

    }
    else
    {
        min_len = 0; // error
    }

    return min_len;
}




#define RBL_PRM                 0
#define RBL_CFG                 1
#define RBL_SSA                 2


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*  DP_ERROR_CODE vpc3_buf_init (void)                                       */
/*                                                                           */
/*   function:      Initializing VPC3 buffers.                               */
/*                                                                           */
/*   parameter:     none                                                     */
/*   return value:  DP_OK        : Buffer length OK                          */
/*                  ERROR        : defined in dp_error.h                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/


DP_ERROR_CODE vpc3_buf_init(void)
{
    DP_ERROR_CODE       result;
    UWORD               aux_buf_len[2];      // calculated length of AUX buffer
    UWORD               r_din_dout_buf_len;  // calculated length of real I/O Data length
    UWORD               real_buf_len[3];     // real length of AUX-Buffer
    UBYTE               aux_ass;             // Bit array, in which the assignments of AUX1/2 are defined

    result = DP_OK;

    /*-----------------------------------------------------------------------*/
    /* check buffer length                                                   */
    /*-----------------------------------------------------------------------*/
    if (dp_sys.dout_bufsize > 244)
    {
        result = DP_DOUT_LEN_ERROR;
    }

    else if(dp_sys.din_bufsize > 244)
    {
        result =  DP_DIN_LEN_ERROR;
    }

    else if((dp_sys.diag_bufsize < 6) || (dp_sys.diag_bufsize > 244))
    {
        result =  DP_DIAG_LEN_ERROR;
    }

    else if((dp_sys.prm_bufsize < 7) || (dp_sys.prm_bufsize > 244))
    {
        result =  DP_PRM_LEN_ERROR;
    }

    else if((dp_sys.cfg_bufsize < 1) || (dp_sys.cfg_bufsize > 244))
    {
        result =  DP_CFG_LEN_ERROR;
    }

    else if(dp_sys.ssa_bufsize != 0 && ((dp_sys.ssa_bufsize < 4) || (dp_sys.ssa_bufsize > 244)))
    {
        result = DP_SSA_LEN_ERROR;
    }

    if(result == DP_OK)//else
    {
        /*-------------------------------------------------------------------*/
        /* length of buffers ok, check memory consumption                    */
        /*-------------------------------------------------------------------*/
        if(vpc3_ptr->mode_reg0_H & VPC3_SPEC_PRM_BUF_MODE)
        {
            real_buf_len[RBL_PRM] = 0; /* prm-data goes directly into prm-buffer */
        }
        else
        {
            real_buf_len[RBL_PRM] = dp_sys.prm_bufsize; // prm-data goes over AUX-buffer
        }

        // length of cfg and ssa buffer
        real_buf_len[RBL_CFG] = dp_sys.cfg_bufsize;
        real_buf_len[RBL_SSA] = dp_sys.ssa_bufsize;

        /*-------------------------------------------------------------------*/
        /* calculate aux-buffer                                              */
        /*-------------------------------------------------------------------*/
        dp_sys.vpc3_used_dp_buf_mem = assign_aux_buf(&real_buf_len[0], 3, &aux_ass, &aux_buf_len[0]);

        /*-------------------------------------------------------------------*/
        /* check memory consumption                                          */
        /*-------------------------------------------------------------------*/
        r_din_dout_buf_len = ((dp_sys.dout_bufsize + SEG_OFFSET) & SEG_ADDWORD) + ((dp_sys.din_bufsize + SEG_OFFSET) & SEG_ADDWORD);
        // DIn DOut buffer
        dp_sys.vpc3_used_dp_buf_mem += r_din_dout_buf_len * 3;
        // add Read Config Buffer
        dp_sys.vpc3_used_dp_buf_mem += real_buf_len[RBL_CFG];
        // diagnose buffer
        dp_sys.vpc3_used_dp_buf_mem += ((dp_sys.diag_bufsize + SEG_OFFSET) & SEG_ADDBYTE) * 2;
        // prm buffer
        if(vpc3_ptr->mode_reg0_H & VPC3_SPEC_PRM_BUF_MODE)
        {
            // spec. PRM buffer
            real_buf_len[RBL_PRM] = (dp_sys.prm_bufsize + SEG_OFFSET) & SEG_ADDBYTE;
            dp_sys.vpc3_used_dp_buf_mem += real_buf_len[RBL_PRM];
            vpc3_ptr->len_spec_prm_buf = dp_sys.prm_bufsize;
        }
        else
        {
            vpc3_ptr->len_spec_prm_buf = 0;
        }

        if( dp_sys.vpc3_used_dp_buf_mem > sizeof (vpc3_ptr->dpbuff) )
        {
            // Error: user needs too much memory
            dp_sys.vpc3_used_dp_buf_mem = 0;
            result = DP_LESS_MEM_ERROR;
        }
        else
        {
            /*---------------------------------------------------------------*/
            /* set buffer pointer                                            */
            /*---------------------------------------------------------------*/
            vpc3_ptr->aux_buf_sel      = aux_ass;   // AUX-Puffer

            vpc3_ptr->din_buf_ptr[0]  = (UBYTE)VPC3_DP_BUF_START;  // user start address
		    vpc3_ptr->din_buf_ptr[1]  = vpc3_ptr->din_buf_ptr[0]  + (((dp_sys.din_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);
            vpc3_ptr->din_buf_ptr[2]  = vpc3_ptr->din_buf_ptr[1]  + (((dp_sys.din_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);

            //vpc3_ptr->dout_buf_ptr[0]   = vpc3_ptr->din_buf_ptr[2]  + (((dp_sys.din_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);
            //vpc3_ptr->dout_buf_ptr[1]   = vpc3_ptr->dout_buf_ptr[0]   + (((dp_sys.dout_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);
            //vpc3_ptr->dout_buf_ptr[2]   = vpc3_ptr->dout_buf_ptr[1]   + (((dp_sys.dout_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);

            vpc3_ptr->diag_buf_ptr[0]   = vpc3_ptr->din_buf_ptr[2]  + (((dp_sys.din_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);

            //vpc3_ptr->diag_buf_ptr[0]  = vpc3_ptr->dout_buf_ptr[2]   + (((dp_sys.dout_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);
            vpc3_ptr->diag_buf_ptr[1]  = vpc3_ptr->diag_buf_ptr[0]  + (((dp_sys.diag_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);

            vpc3_ptr->prm_buf_ptr      = vpc3_ptr->diag_buf_ptr[1]  + (((dp_sys.diag_bufsize + SEG_OFFSET) & SEG_ADDBYTE)>>SEG_MULDIV);

            vpc3_ptr->cfg_buf_ptr      = vpc3_ptr->prm_buf_ptr      + (real_buf_len[RBL_PRM]>>SEG_MULDIV);
            vpc3_ptr->read_cfg_buf_ptr = vpc3_ptr->cfg_buf_ptr      + (real_buf_len[RBL_CFG]>>SEG_MULDIV);

            vpc3_ptr->aux_buf_ptr[0]   = vpc3_ptr->read_cfg_buf_ptr + (real_buf_len[RBL_CFG]>>SEG_MULDIV);
            if( aux_buf_len[1] != 0 )
            {
                vpc3_ptr->aux_buf_ptr[1]   = vpc3_ptr->aux_buf_ptr[0]   + (aux_buf_len[0]>>SEG_MULDIV);
            }
            else
            {
                vpc3_ptr->aux_buf_ptr[1]   = 0;
            }

            if (real_buf_len[RBL_SSA] == 0)
            {
                // no ssa supported
                vpc3_ptr->ssa_buf_ptr = 0;         /* Dienst sperren */
            }
            else
            {
                // ssa supported
                if( aux_buf_len[1] != 0 )
                {
                    vpc3_ptr->ssa_buf_ptr = vpc3_ptr->aux_buf_ptr[1] + (aux_buf_len[1]>>SEG_MULDIV);
                }
                else
                {
                    vpc3_ptr->ssa_buf_ptr = vpc3_ptr->aux_buf_ptr[0] + (aux_buf_len[0]>>SEG_MULDIV);
                }
            }

            /*---------------------------------------------------------------*/
            /* set buffer length                                             */
            /*---------------------------------------------------------------*/
            vpc3_ptr->len_dout_buf    = dp_sys.dout_bufsize;//outp_data_len;
            vpc3_ptr->len_din_buf     = dp_sys.din_bufsize;//inp_data_len;

            vpc3_ptr->len_diag_buf[0] = dp_sys.diag_bufsize;                // length of Diag Buffers
            vpc3_ptr->len_diag_buf[1] = dp_sys.diag_bufsize;

            if(aux_buf_len[0] >= 244)
            {
                vpc3_ptr->len_ctrl_buf[0] = 244;      // Length AUX1-Buffer
            }
            else
            {
                vpc3_ptr->len_ctrl_buf[0] = aux_buf_len[0];      // Length AUX1-Buffer
            }

            if(aux_buf_len[1] >= 244)
            {
                vpc3_ptr->len_ctrl_buf[1] = 244;      // Length AUX1-Buffer
            }
            else
            {
                vpc3_ptr->len_ctrl_buf[1] = aux_buf_len[1];      // Length AUX1-Buffer
            }

            vpc3_ptr->len_cfg_data    = dp_sys.cfg_bufsize;
            vpc3_ptr->len_prm_data    = dp_sys.prm_bufsize;
            vpc3_ptr->len_ssa_buf     = dp_sys.ssa_bufsize;
        }
    }
    return result;
}//DP_ERROR_CODE vpc3_buf_init(void)



UWORD slave_address(void)
{
	 unsigned char slaveadd;//丁明加的，原程序在menu.c中
//   UWORD dp_slave_add;
	 slaveadd=DP_NUM; 	
//   dp_slave_add =slaveadd; //0x04;//从站地址号变量

//	return dp_slave_add;
	return slaveadd;

}
//void delay_us(unsigned int i)
//{
//	for(;i > 0;i --);

//}
 
void clr_vpc3_ram(void)
{
    UWORD i;

    uint32_t * vpc3_ram;

	vpc3_ram = (uint32_t  *)( 0xF016);


	for(i=0; i<0x1000; i++)
	{
	    *(vpc3_ram+i) = 0x0000;
    }
}




unsigned char vpc3_buf_check(void)
{
    UWORD i;
	UWORD xdata;
	UBYTE *vpc3_ram = (unsigned char *)(0xF000); 
    unsigned char  result;

	result = DP_OK;

    xdata = 0x00;
    for(i = 0x16; i < (0x800-0x16); i++)
    {
        *(vpc3_ram + i) = 0x02;
		xdata += 0x02;
		i++;
    }
    xdata = 0x00;
    for(i = 0x16; i < (0x800-0x16); i++)
    {
        if((*(vpc3_ram + i)) != 0x02)
		{
		    result = DP_SRAM_ERROR;
			xdata += 0x01;
			break;
        }
		
		i++;
    }
	//getdisplaynum(0,xdata * 10,10);
	//while(1);
	return result;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*   void init_dp(void)                                                      */
/*                                                                           */
/*   function:     initializing the vpc3+ controller                         */
/*                                                                           */
/*   parameter:    VPC3_INIT, VPC3_DP_INIT                                   */
/*   return value: errorcode (0 = no error)                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//UBYTE x;

void init_dp(void)
 {
   unsigned char *vpc3_ram;
	 DP_ERROR_CODE	init_dp_result;
   
   volatile UBYTE i;
	/*-----------------------------------------------------------------------*/
    /* init user data                                                        */
    /*-----------------------------------------------------------------------*/
   init_user_data();

	 init_dp_result = DP_NOK;
	/*-----------------------------------------------------------------------*/
    /* init user data                                                        */
    /*-----------------------------------------------------------------------*/
/*
     while(init_dp_result != DP_OK)
	 {
	   	PORTD |= 0x04;
  	 	delay_us(2000);
		PORTD &= 0xFB; 
    	
		init_dp_result = vpc3_buf_check();
		//getdisplaynum(0,init_dp_result * 10,10);
	 }
*/
	 /*-----------------------------------------------------------------------*/
    /* reset_vpc3+c                                                       */
    /*-----------------------------------------------------------------------*/
	init_dp_result = DP_OK;	

    //clr_vpc3_ram();
	
	 GPIO_SetBits(GPIOE,GPIO_Pin_12);
   delay_ms(2);
	 GPIO_ResetBits(GPIOE,GPIO_Pin_12); 
	
    if(init_dp_result == DP_OK)
    {
        /*-------------------------------------------------------------------*/
        /* clear VPC3                                                        */
        /*-------------------------------------------------------------------*/
		    clr_vpc3_ram();
        /*-------------------------------------------------------------------*/
        /* check VPC3 is in OFFLINE                                          */
        /*-------------------------------------------------------------------*/
        if( !VPC3_GET_OFF_PASS() )
        {
            /*---------------------------------------------------------------*/
            /* set constant values                                           */
            /*---------------------------------------------------------------*/
            init_dp_result = vpc3_set_constants( slave_address() );
            
			      if( init_dp_result == DP_OK )
            {
                /*-----------------------------------------------------------*/
                /* calculate length of input and output data using cfg-data  */
                /*-----------------------------------------------------------*/
                //init_dp_result = vpc3_calculate_inp_outp_len ( &cfg.cfg_data[0], cfg.length);
                if( init_dp_result == DP_OK )
                {
                    /*-------------------------------------------------------*/
                    /* initialize buffer structure                           */
                    /*-------------------------------------------------------*/
                    init_dp_result = vpc3_buf_init();
                    if ( init_dp_result == DP_OK )
                    {
                        /*---------------------------------------------------*/
                        /* set real configuration data                       */
                        /*---------------------------------------------------*/
                        VPC3_SET_READ_CFG_LEN(dp_sys.cfg_bufsize); 
                        /*---------------------------------------------------*/
                        /* set I/O length                                    */
                        /*---------------------------------------------------*/
						i = vpc3_ptr->read_cfg_buf_ptr;
						vpc3_ram = (UBYTE *)((((UWORD)(i)) << 4) + 0xF000);
                        *vpc3_ram = 0x5F;
                    }//if(DP_OK == error)
                }//if(DP_OK == error)
            }//if(DP_OK == error)
        }//if( !VPC3_GET_OFF_PASS() )
        else
        {
            init_dp_result = DP_NOT_OFFLINE_ERROR;
        }
    }//if(DP_OK == error)

    if( init_dp_result == DP_OK )
    {

        /*-----------------------------------------------------------------------*/
        /* start interrupt vector                                                */
		/* set microcontroller interrupt to falling edge                         */
		/* set microcontroller interrupt to high priority                        */
		/* enable microcontroller interrupt                                      */
        /*-----------------------------------------------------------------------*/
        __disable_irq();//丁明
        
        //todo: before startup the VPC3+, make here your own initialzations 
        if( ( (vpc3_ptr->ctrl_reg.rd.diag_buffer_sm) & 0x03 ) == 0x01)
		{
            vpc3_ptr->len_diag_buf[0] = 0x06;
			i = ( (UWORD)(vpc3_ptr->diag_buf_ptr[0]) ) << 4;
		}
		else if( ( (vpc3_ptr->ctrl_reg.rd.diag_buffer_sm) & 0x0C ) == 0x04)
		{
            vpc3_ptr->len_diag_buf[1] = 0x06;
			i = ( (UWORD)(vpc3_ptr->diag_buf_ptr[1]) ) << 4;
		}
		else
		{
			//
		}        

        /*-----------------------------------------------------------------------*/
        /* start vpc3                                                            */
        /*-----------------------------------------------------------------------*/
        vpc3_ptr->ctrl_reg.wr.mode_reg1_s = 0x01;
    }

 }

unsigned char check_dp(void)
{	
	unsigned char dp_status = vpc3_ptr->isreg.rd.status_L;
	dp_status &= 0x01;
	return dp_status;
}

