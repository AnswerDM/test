#include "buzz.h"





//----- (080024CE) --------------------------------------------------------
void buzz_ctrl_all()
{
  signed int i; // r0@6

  if ( (flag_unknown_2_bak_094 != 1) || flag_unknown_2_086 )
  {
    if ( (!flag_unknown_2_bak_094) && (flag_unknown_2_086 == 1) )
    {//������������ ��ͯģʽ ����
      buzz_type_0B2 = 1;
      for ( i = 0; i < 200; i = (u8)(i + 1) )
      {
        while ( !time1_ok_05A )
          ;
        time1_ok_05A = 0;
      }
      buzz_type_0B2 = 0;
    }
  }
  else
  {
    buzz_power_on_type_08B = 0;
    flag_buzz_poweron_08A = 0;
  }
  flag_unknown_2_bak_094 = flag_unknown_2_086;
	/*************���������������*******************/
  if ( flag_buzz_poweron_08A )
  {//time
    if ( flash_para4_050 == flash_para3_054 )
    {
      if ( flag_unknown_2_086 )
      {
        buzz_type_0B2 = 0;
      }
      else if ( flag_unknown_3_087 )
      {
        buzz_type_0B2 = 3;
      }
      else if ( flag_dormancy_reset_039 )
      {//��ѹ�ȶ���־
        if ( !flag_buzz_ok_1_084 )
        {
          buzz_type_0B2 = 3;//�ε�һ��
          if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
          {
            cycle_buzz_cnt1_08C = 0;
            flag_buzz_ok_1_084 = 1;
            buzz_type_0B2 = 0;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
      }
      else
      {
        if ( (flag_charging_085 != 1) || flag_pa12_ok_last_08D )
        {
          if ( (!flag_charging_085) && (flag_pa12_ok_last_08D == 1) )
            flag_buzz_unknown2_091 = 1;
        }
        else
        {
          flag_buzz_unknown1_090 = 1;//����buzz���
        }
        if ( ((flag_mpu2_online2_1D2 == 1) 
							&& (!flag_mpu2_online2_last_08E)
							&& (!flag_mpu3_online2_1D3)) 
					|| ((!flag_mpu2_online2_1D2) 
							&& (!flag_mpu3_online2_last_08F) 
							&& (flag_mpu3_online2_1D3 == 1)) )
							flag_buzz_unknown3_092 = 1;
        if ( ((!flag_mpu2_online2_1D2) 
							&& (flag_mpu2_online2_last_08E == 1) 
							&& (!flag_mpu3_online2_1D3) 
							&& (!flag_mpu3_online2_last_08F))
          || ((!flag_mpu2_online2_1D2) 
							&& (!flag_mpu2_online2_last_08E) 
							&& (flag_mpu3_online2_last_08F == 1) 
							&& (!flag_mpu3_online2_1D3)) )
							flag_buzz_unknown4_093 = 1;
        flag_pa12_ok_last_08D = flag_charging_085;
        flag_mpu2_online2_last_08E = flag_mpu2_online2_1D2;
        flag_mpu3_online2_last_08F = flag_mpu3_online2_1D3;
        if ( flag_unknown_8_188 )
        {
          if ( buzz_power_on_type_08B )
          {//����
            buzz_type_0B2 = 0;
            cycle_buzz_cnt1_08C = 0;
            buzz_power_on_type_08B = 0;
            flag_unknown_8_188 = 0;
          }
          else
          {
            buzz_type_0B2 = 1;
            if ( (signed int)cycle_buzz_cnt1_08C >= 200 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown1_090 )//����buzz���
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 2;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown1_090 = 0;//����buzz���
            }
          }
          else
          {
            buzz_type_0B2 = 1;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown2_091 )
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 1;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown2_091 = 0;
            }
          }
          else
          {
            buzz_type_0B2 = 2;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown3_092 )
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 2;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown3_092 = 0;
            }
          }
          else
          {
            buzz_type_0B2 = 1;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_buzz_unknown4_093 )
        {
          if ( buzz_power_on_type_08B )
          {
            if ( buzz_power_on_type_08B == 1 )
            {
              buzz_type_0B2 = 1;
              if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
              {
                cycle_buzz_cnt1_08C = 0;
                buzz_power_on_type_08B = 2;
              }
              else
              {
                ++cycle_buzz_cnt1_08C;
              }
            }
            else
            {
              buzz_type_0B2 = 0;
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 0;
              flag_buzz_unknown4_093 = 0;
            }
          }
          else
          {
            buzz_type_0B2 = 2;
            if ( (signed int)cycle_buzz_cnt1_08C >= 80 )
            {
              cycle_buzz_cnt1_08C = 0;
              buzz_power_on_type_08B = 1;
            }
            else
            {
              ++cycle_buzz_cnt1_08C;
            }
          }
        }
        else if ( flag_charging_mpu_online_20C || flag_vol_lower_031 )
        {//���ʱ ����̤�� ���ߵ�ѹ�� ����
          if ( (signed int)cycle_buzz_cnt1_08C >= 100 )
          {
            cycle_buzz_cnt1_08C = 0;
            if(buzz_type_0B2 == 0) buzz_type_0B2 = 1;
						else buzz_type_0B2 = 0;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
        else if ( error_vice_20D )
        {
          if ( (signed int)cycle_buzz_cnt1_08C >= 100 )
          {
            cycle_buzz_cnt1_08C = 0;
            if ( buzz_type_0B2 )
              buzz_type_0B2 = 0;
            else
              buzz_type_0B2 = 2;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
        else if ( flag_two_motor_dir_20E )
        {
          if ( (signed int)cycle_buzz_cnt1_08C >= 100 )
          {
            cycle_buzz_cnt1_08C = 0;
            if ( buzz_type_0B2 )
              buzz_type_0B2 = 0;
            else
              buzz_type_0B2 = 3;
          }
          else
          {
            ++cycle_buzz_cnt1_08C;
          }
        }
        else
        {
          buzz_type_0B2 = 0;
        }
      }
    }
  }
	/********�������ȿ���***********/
  else if ( buzz_power_on_type_08B )
  {//�����ǿ����е�����
		//��ʱ���� �ı俪������
    if ( buzz_power_on_type_08B == 1 )
    {//����
      buzz_type_0B2 = 2;
      if ( (signed int)cycle_buzz_cnt1_08C >= 80 )//ԭ���������80
      {
        cycle_buzz_cnt1_08C = 0;
        buzz_power_on_type_08B = 2;
      }
      else
      {
        ++cycle_buzz_cnt1_08C;
      }
    }
    else if ( buzz_power_on_type_08B == 2 )
    {
      buzz_type_0B2 = 3;
      if ( (signed int)cycle_buzz_cnt1_08C >= 80 )//ԭ���������80
      {
        cycle_buzz_cnt1_08C = 0;
        buzz_power_on_type_08B = 3;
      }
      else
      {
        ++cycle_buzz_cnt1_08C;
      }
    }
    else
    {
      buzz_type_0B2 = 0;
      cycle_buzz_cnt1_08C = 0;
      buzz_power_on_type_08B = 0;
      flag_buzz_poweron_08A = 1;//������־ �����������
    }
  }
  else
  {
    buzz_type_0B2 = 1;
    if ( (signed int)cycle_buzz_cnt1_08C >= 80 )//ԭ���������80
    {
      cycle_buzz_cnt1_08C = 0;
      buzz_power_on_type_08B = 1;
    }
    else
    {
      ++cycle_buzz_cnt1_08C;
    }
  }
}

//----- (08002AEA) --------------------------------------------------------
void buzz_ctrl()
{//����������״̬
  if (( buzz_type_0B2 == 1 )&& (!buzz_cnt_095))
  {
    buzz_total_096 = 6;
  }
  else if ( (buzz_type_0B2 == 2)&& (!buzz_cnt_095 ) )
  {
    buzz_total_096 = 5;
  }
  else if ( (buzz_type_0B2 == 3) && (!buzz_cnt_095) )
  {
    buzz_total_096 = 4;
  }
	
  if ( buzz_cnt_095 >= (signed int)buzz_total_096 )
  {
    buzz_cnt_095 = 0;
    if ( buzz_on_097 )
    {
      buzz_on_097 = 0;
      GPIO_SetBits(GPIOA, 16);//����
    }
    else
    {
      buzz_on_097 = 1;
      GPIO_ResetBits(GPIOA, 16);
    }
  }
  else
  {
    ++buzz_cnt_095;
  }
}


