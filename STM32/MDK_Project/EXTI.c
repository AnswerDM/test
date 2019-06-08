#include "exti.h"



//extern *vpc3_ptr;
void DP_EXTI_Init(void)
{
	
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

  //GPIOE.14 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource14);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn ;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}
	
void EXTI15_10_IRQnHandler(void)
{
		
    UBYTE *cfg_ptr;
	  UBYTE config_data_len, cfg_result, result;
	  UBYTE temp;
//   UBYTE *vpc3_ram = (UBYTE)0xF000;
    UWORD user_diag_buffer_ptr;
    UBYTE user_wd_state;
//   UBYTE user_global_ctrl_command;

    UBYTE store_mintsdr;
    UWORD  prm_ptr;
	  UBYTE  param_data_len, prm_result;
	  UBYTE  ii;
	
	if (EXTI_GetITStatus(EXTI_Line14) != RESET) 
	{
		
	  
/*
  if(VPC3_GET_IND_MAC_RESET())  //1) ??MAC_RESET
    {
	   //VPC3_POLL_IND_MAC_RESET();
	   VPC3_CON_IND_MAC_RESET();
	}
*/

  if(VPC3_GET_IND_GO_LEAVE_DATA_EX())    //2) ??(Go/Leave_DATA_EX)????????????,????????
	{  //=== Start or the end of the Data-Exchange-State ===
	   VPC3_CON_IND_GO_LEAVE_DATA_EX();    //confirm this indication
	}
  if(VPC3_GET_IND_NEW_GC_COMMAND())    //6) ?????Global Control Command????????
	{   //===  New Global Control Command ===
	   //user_global_ctrl_command = vpc3_ptr->gc_command;
	   VPC3_CON_IND_NEW_GC_COMMAND();  //confirm this indication
	}
  if(VPC3_GET_IND_NEW_PRM_DATA())    //9) ???????PRM_DATA,???????
	{   //=== New parameter  data ===
	    prm_result = 0xFF;
	   
	   do
		   { //Check parameter until no conflict behavior
		      prm_ptr = ( ( (UWORD)(vpc3_ptr->prm_buf_ptr) ) << 4 );
		      param_data_len = vpc3_ptr->len_prm_data;

		     //data_length_netto of parametration_telegram >7
		      if (param_data_len >= 7)  //??????
			  {
			      if (param_data_len > 244)  //amg_hmg define as 7(standard) + 18(user_prm_data) = 25
				   {
				       prm_result = vpc3_ptr->ctrl_reg.rd.user_prm_data_nok;
                   }
			       else
				   {
				       for (ii= 0; (ii<param_data_len) && (ii < 25); ii++)  // store in the interim buffer for the diagnostic
					   {
						   //
                       }
				       prm_result = vpc3_ptr->ctrl_reg.rd.user_prm_data_ok;
				   }
			   }
		      else
			      {
			        prm_result = vpc3_ptr->ctrl_reg.rd.user_prm_data_nok;
                  }

		    } while(prm_result == 0x01);

	    //store_mintsdr =  READ(prm_ptr+3);    //store the mintsdr for restart after baudrate search
	}
  if(VPC3_GET_IND_NEW_CFG_DATA())   //8) ???????CFG_DATA,????????
	{   //=== New Configuration data ===
	  

	   cfg_result = 0xFF;
	   result = 0xFF;

	   do   
		  {   //check configuration data until no conflict behavior m
		     cfg_ptr = (UBYTE *)(( ( (UWORD)(vpc3_ptr->cfg_buf_ptr) ) << 4 ) + 0xF000);  //pointer to the config_data_block
		     config_data_len = vpc3_ptr->len_cfg_data;

		      //In this example the only possible configurations are 0xF1 and 0xD1(4 Byte I/O) or 0xF0 and 0xD0(2 Byte I/O) are possible
		     if (config_data_len != 1)  //cfg_len_akt
			     {  
				    vpc3_ptr->ctrl_reg.wr.mode_reg1_r = 0x10;
				    cfg_result = vpc3_ptr->ctrl_reg.rd.user_cfg_data_nok;
                 }
		     else
			     {   //Length of the configuration data ok, check the configuratin bytes


//                     i = *(cfg_ptr);
					 //j = *(cfg_ptr+1);
/**/	
				     if ((*(cfg_ptr) == 0x5F))
					 { 
					     //cfg_akt = READ(cfg_ptr);
					     result = 0xFF;
					 }
				     else
				     {
					     result = 0x00;
                     }

			    /* if (result == DPS_CFG_UPDATE)
					 {
					     user_io_data_len_ptr = dps2_calculate_inp_outp_len (cfg_ptr, config_data_len);
					     if((user_io_data_len_ptr->inp_data_len != 0) || (user_io_data_len_ptr->outp_data_len != 0))
						 {
						     dps_set_io_data_len(user_io_data_len_ptr);
						 }
					     else
						 {
						     result = DPS_CFG_FAULT;
                         }
					 }*/
			         switch (result)
				     {/*
				         case DPS_CFG_OK:     WRITE(spc3_x1_w_mode_reg1_r_add, EN_CHG_CFG_BUFFER); 
						                      cfg_result = READ(spc3_user_cfg_data_ok_add);
										      break;
				         case DPS_CFG_OK:     WRITE(spc3_x1_w_mode_reg1_s_add, EN_CHG_CFG_BUFFER);
						                      WRITE(spc3_r_len_read_cfg_buf_add, ( READ(spc3_r_len_cfg_buf_add) ));
											  cfg_result = READ(spc3_user_cfg_data_ok_add);
											  break;*/
				         case 0x00:           vpc3_ptr->ctrl_reg.wr.mode_reg1_r = 0x10;
						                      cfg_result = vpc3_ptr->ctrl_reg.rd.user_cfg_data_nok;
											  break;
				         case 0xFF:           vpc3_ptr->ctrl_reg.wr.mode_reg1_r = 0x10;
						                      vpc3_ptr->len_read_cfg_data = vpc3_ptr->len_cfg_data;
											  cfg_result = vpc3_ptr->ctrl_reg.rd.user_cfg_data_ok;
											  break;
				     }
               }


		} while(result == 0x01);
	}
  if(VPC3_GET_IND_NEW_SSA_DATA())   //7) ???????SSA_DATA,????????
	{   //=== New Slave address received ===
/*	  char ch;
      UWORD addr_ptr;
      UWORD _dps2_x;
	  ch = READ(spc3_r_len_ssa_buf_add);
	  addr_ptr = ( ( (UWORD)READ(spc3_r_ssa_buf_ptr_add) ) << 3 );
	  //this_station = addr_ptr.new_address;
	  this_station = READ(addr_ptr);
      //real_no_add_chg = addr_ptr.no_add_chg; //store the new address and the bit real_no_add_chg for the next startup
	  real_no_add_chg = READ(addr_ptr+3);
      //_dps2_x = spc3.ssa_buffer_free_cmd;
	  _dps2_x = READ(spc3_r_ssa_buf_ptr_add);
    
	  WRITE(spc3_int_reg_ack_b1_add, 0x02); //confirm this indication*/
	}
  if(VPC3_GET_IND_WD_DP_TIMEOUT())  //4) ??(WD_DP_Control_Timeout)??????,???????
	{//=== Watchdog is run out ===
	 //Watchdog is run out. The SPC3 reset the PROFIBUS DP Statemachine
       user_wd_state = ( ( (vpc3_ptr->isreg.rd.status_L) >> 6 ) & 0x03 );
	//SX small weakness of the SPC3. Update of the diagnosis with 00, otherwise the bit "static diagnosis" would appear in the next startup
       if( ( (vpc3_ptr->ctrl_reg.rd.diag_buffer_sm) & 0x03 ) == 0x01 )
	   {
	      vpc3_ptr->len_diag_buf[0] = 6;   // test ,,should be 6
	   }
	   else
	   {
	      if( ( (vpc3_ptr->ctrl_reg.rd.diag_buffer_sm) & 0x0c ) == 0x04 )
		  {
		     vpc3_ptr->len_diag_buf[1] = 6;
		  }
	   }
       if(((vpc3_ptr->ctrl_reg.rd.diag_buffer_sm) & 0x03) == 0x01)
	   {
	      //vpc3_ram |= vpc3_ptr
		  //WRITE((((UWORD)READ(spc3_r_diag_buf_ptr0_add))<<3), 0x00);
	   }
	   else
	   {
	      if((((vpc3_ptr->ctrl_reg.rd.diag_buffer_sm) & 0x0c) == 0x04))
		  {
		    // WRITE((((UWORD)READ(spc3_r_diag_buf_ptr1_add))<<3), 0x00);
		  }
	   }
       
	   //DPS2_DIAG_UPDATE();
    
	  temp = (vpc3_ptr->ctrl_reg.rd.new_diag_buf_cmd) & 0x03;
	  switch(temp)
	  {
		 case 1:   //buffer with Index 0
		 {
			user_diag_buffer_ptr = (((UWORD)(vpc3_ptr->diag_buf_ptr[0]))<<4);
		 }
		 case 2:   //buffer with Index 1
		 {
			user_diag_buffer_ptr = (((UWORD)(vpc3_ptr->diag_buf_ptr[1]))<<4);
		 }
		 default:
		 {
			//no buffer
//			return SPC3_NIL;
		 }
	  }

      vpc3_ptr->isreg.wr.int_ack1 = 0x08;  //confirm this indication
	}
  if(VPC3_GET_IND_USER_TIMER_CLOCK()) //5) ?????????(user_Timer_clock)????,???????
	{   //==== Timer tick received ====
	   vpc3_ptr->isreg.wr.int_mask_L = 0x10;
//	   WRITE(spc3_x1_w_mode_reg1_s_add, RES_USER_WD);
	}

    if(VPC3_GET_IND_BAUDRATE_DETECT())  //3) ??(Baudrate_Detect)SPC3????????????,????????
	{   //==== Baudrate found  ====

	//If the baudrate has lost and again found in the state WAIT_CFG, DATA_EX the SPC3 would answer to the next telegramms
	//with his default mintsdr. But he should answer in the meantime parametrized mindstr

	  if ( ( ( ( (vpc3_ptr->isreg.rd.status_L) >> 4 ) & 0x03 ) ==  0x01 ) ||  ( ( ( (vpc3_ptr->isreg.rd.status_L) >> 4 ) & 0x03 )  ==  0x02 ) )
	    {
		  vpc3_ptr->ctrl_reg.wr.mintsdr = store_mintsdr;
        }
	  vpc3_ptr->isreg.wr.int_ack1 = 0x04;
	}
/*
  if(READ(spc3_int_reg_com_b1_add) & 0x10)  //10) ?????
    {
	   WRITE(spc3_int_reg_ack_b1_add, 0x10);
	}
*/


  vpc3_ptr->ctrl_reg.wr.mode_reg1_s = 0x02;
		
	
	 EXTI_ClearITPendingBit(EXTI_Line14);//清除中断标志
//	 EXTI_ClearFlag(EXTI_Line2); //清除中断标志
//----------------------------------------------------------------------------------	
   }
}

