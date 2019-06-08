#ifndef __PROFIBUS_H
#define __PROFIBUS_H

#include "stm32f10x.h"
#include "GPIO_Init.h"


extern unsigned char DP_NUM;

// VPC3_SYSTEM_STRUC         dp_sys;
// VPC3_STRUC *vpc3_ptr;
// UBYTE vpc3_result;//从.h中移过来的

#define UBYTE unsigned char
#define UWORD unsigned int	

#define cfg_simple  	 0x01
#define cfg_special 	 0x02

#define dp_cfg_len  	 0x01

#define dp_cfg_data 	 0xF1

#define dp_cfg_low  	 0x1F
#define dp_cfg_high    0x2F

#define dp_prm_len     0x20
#define dp_prm_spec    0x00

#define dp_ident_high  0x05
#define dp_ident_low   0x9B

#define dp_ssa_len     0x00
#define dp_ssa_chg     0xFF

#define dp_diag_len    0x06

/*-----------------------------------------------------------------------*/
/* general slave parameter                                               */
/*-----------------------------------------------------------------------*/
#define IDENT_NR                    ((UWORD)0x0008)	// PROFIBUS Ident Number
#define USER_WD                     ((UWORD)0x01FF) // User Watchdog
                                                    // set watchdog greater than 0x00FF, if serial printouts used
													// The UserWatchdog is only active in DataExchange. The UserWatchdog
													// isn't timebased, it's a counter of DataExchange-telegrams.													 	
/*-----------------------------------------------------------------------*/
/* define buffer length                                                  */
/*-----------------------------------------------------------------------*/
#define DIN_BUFSIZE                 ((UBYTE)0x20)   // Length of the DIn Buffer (Data Slave to Master)                0..244
#define DOUT_BUFSIZE                ((UBYTE)0x20)   // Length of the DOut Buffer     (Data Master to Slave)           0..244
#define PRM_BUFSIZE                 ((UBYTE)0x40)   // Length of the Parameter Buffer                                 7..244
#define DIAG_BUFSIZE                ((UBYTE)0x40)   // Length of the Diagnosis Buffer                                 6..244
#define CFG_BUFSIZE                 ((UBYTE)0x40)   // Length of the Configuration Buffer                             1..244
#define SSA_BUFSIZE                 ((UBYTE)0x00)   // Length of the Input Data in the Set_Slave_Address-Buffer 0 and 4..244
                                                    // 0: SetSlaveAddress will be deactivated!

/*-----------------------------------------------------------------------*/
/* settings for MSAC_C1                                                  */
/*-----------------------------------------------------------------------*/
#define C1_LEN                      ((UBYTE)0x30)   // Length of the MSAC_C1 Data
                                                    // The parameter specifies the maximum length of user data including
                                                    // Function_Num, Slot_number, Index, Length, transferred on the
                                                    // MSAC_1 communication channel.
                                                    // Type: Unsigned8 (0 .. 244)

/*-----------------------------------------------------------------------*/
/* settings for MSAC_C1 Alarm                                            */
/*-----------------------------------------------------------------------*/
#define DP_ALARM_OVER_SAP50                         // Alarm Acknowledge over SAP50

/*-----------------------------------------------------------------------*/
/* settings for MSAC_C2                                                  */
/*-----------------------------------------------------------------------*/
#define DP_MSAC_C2_Time                             // enables time control for msac-c2
#define C2_NUM_SAPS                 ((UBYTE)0x03)   // Number of MSAC_C2 connections
#define C2_LEN                      ((UBYTE)0x34)   // Length of MSAC_C2 Data
                                                    // The parameter specifies the maximum length of an Initiate Request
                                                    // PDU including the Function_Num to the Resource Manager.
                                                    // The parameter specifies the maximum length of user data including
                                                    // Function_Num, Slot_number, Index, Length, transferred on the
                                                    // MSAC_2 communication channel.
                                                    // Type: Unsigned8 (0,52.. 244)
#define C2_FEATURES_SUPPORTED_1     ((UBYTE)0x01)   // default: 0x01, Read and Write supported
#define C2_FEATURES_SUPPORTED_2     ((UBYTE)0x00)   // default: 0x00
#define C2_PROFILE_FEATURES_1       ((UBYTE)0x00)   // default: 0x00, vendor or profile specific
#define C2_PROFILE_FEATURES_2       ((UBYTE)0x00)   // default: 0x00, vendor or profile specific
#define C2_PROFILE_NUMBER           ((UWORD)0x0000) // default: 0x0000, vendor or profile specific

/*-----------------------------------------------------------------------*/
/* settings for DPV2 - Isochron Mode                                     */
/*-----------------------------------------------------------------------*/
#define SYNCH_PULSEWIDTH            ((UBYTE)0xFF)   // Width of Synchpulse in 1/12?

/*-----------------------------------------------------------------------*/
/* settings for DPV2 - DXB Subscriber                                    */
/*-----------------------------------------------------------------------*/
#define MAX_LINK_SUPPORTED          ((UBYTE)0x05)   // Number of Links
#define MAX_DATA_PER_LINK           ((UBYTE)0x10)   // maximal Number of Data per Link

/*---------------------------------------------------------------------------*/
/* set hardware modes                                                        */
/*---------------------------------------------------------------------------*/
#define DP_VPC3_4KB_MODE							// (only VPC3+B, VPC3+C)


/*-----------------------------------------------------------------------*/
/* ModeRegister0 (7..0) ( page 15 )                                      */
/*-----------------------------------------------------------------------*/
//
//  bit  7       6      5        4         3       2       1          0
//  --------------------------------------------------------------------------
//  | Freeze | Sync | Early | Int_Pol | MinTSDR | Res | Dis_Stop | Dis_Start |
//  |  supp. | supp.|  RDY  |         |         |     | Control  | Control   |
//  --------------------------------------------------------------------------
//       1       1      0        0         0       0       0          0        = 0xC0 // Default
//
#define INIT_VPC3_MODE_REG_L        ((UBYTE)0xC0)   // 0xC0

/*-----------------------------------------------------------------------*/
/* ModeRegister0 (15..8) ( page 15 )                                     */
/*-----------------------------------------------------------------------*/
//
//  bit15      14       13           12           11           10         9         8
//  ------------------------------------------------------------------------------------
//  | Res | PrmCmd | Spec_Clear | Spec_Prm |  SetExtPrm  | User_Time | EOI_Time |  DP  |
//  |     |  Supp  |    Mode    | Buf_Mode |     Supp    |    Base   |   Base   | Mode |
//  ------------------------------------------------------------------------------------
//     0       0        1            0              0           1         1         1   = 0x27 // Default
//
#define INIT_VPC3_MODE_REG_H       ((UBYTE)0x05) //((UBYTE)0x27)   // 0x05


/*-----------------------------------------------------------------------*/
/* ModeRegister2 (7..0) ( page 19 )   (only VPC3+B, VPC3+C)              */
/*-----------------------------------------------------------------------*/
//
//  bit  7          6          5        4       3          2          1            0
//  --------------------------------------------------------------------------------------
//  |  4KB  |   No_Check   | SYNC_  | SYNC_ | DX_Int_ | DX_Int_ |  No_Check_  | NEW_GC_  |
//  |  Mode | Prm_Reserved |  Pol   |  ENA  |  Port   |  Mode   | GC_RESERVED | Int_Mode |
//  --------------------------------------------------------------------------------------
//       1          0          0        0       0          0          0            1        = 0x01 or 0x81
//
//#ifdef DP_VPC3_4KB_MODE
    #define INIT_VPC3_MODE_REG_2    ((UBYTE)0x80)
//#else
//    #define INIT_VPC3_MODE_REG_2    ((UBYTE)0x01)
//#endif

/*---------------------------------------------------------------------------*/
/* set interrupt indications                                                 */
/*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Interrupt Mask Register (7..0) ( page 23 )                            */
/*-----------------------------------------------------------------------*/
//  bit7       6          5           4             3             2          1         0
//  ----------------------------------------------------------------------------------------
//  | DXB | New_Ext  | DXB_LINK | User_Timer |    WD_DP     | Baud_Rate | Go/Leave |  MAC  |
//  | OUT | PRM_Data |  ERROR   |   Clock    | Mode_Timeout |   detect  |  DataEx  | Reset |
//  ----------------------------------------------------------------------------------------
//     1       0          1           1             1             1          1         0      = 0xBE // Default
//
#define INIT_VPC3_IND_L  0x0E//0xBE

/*-----------------------------------------------------------------------*/
/* Interrupt Mask Register (15..8) ( page 23 )                           */
/*-----------------------------------------------------------------------*/
//  bit  15         14       13        12            11       10       9         8
//  -----------------------------------------------------------------------------------
//  | REQ_PDU | POLL_END | DX_OUT | Diag_Buffer | New_PRM | NewCfg | NewSSA |  NewGC  |
//  |   Ind   |    Ind   |        |   Changed   |   Data  |  Data  |  Data  | Command |
//  -----------------------------------------------------------------------------------
//       1          1        1          1            1        1        0         0      = 0xFC // Default
//
#define INIT_VPC3_IND_H  0x0F//0xFC

/*---------------------------------------------------------------------------*/
/* end of user defines                                                       */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* !!!!! do not edit this calculating part !!!!!                             */
/*---------------------------------------------------------------------------*/
// == Segmentation VPC3+ ===============================================================
#ifdef DP_VPC3_4KB_MODE
    // 16 Byte segmentation
    #define SEG_OFFSET              ((UBYTE)0x0F)
    #define SEG_MULDIV              ((UBYTE)0x04)
    #define SEG_ADDBYTE             ((UWORD)0xFFF0)
    #define SEG_ADDWORD             ((UWORD)0xFFF0)
#else
    // 8 Byte segmentation
    #define SEG_OFFSET              ((UBYTE)0x07)
    #define SEG_MULDIV              ((UBYTE)0x03)
    #define SEG_ADDBYTE             ((UWORD)0xF8)
    #define SEG_ADDWORD             ((UWORD)0xFFF8)
#endif


// == Calculating FDL list =============================================================
#if ( (defined DP_MSAC_C1) || (defined DP_MSAC_C2) )
   #define DP_FDL
#endif

#if (DP_C1_SAPS & DP_C1_USE_RD_WR_SAP)
    #define DP_TEMP_X1              1
#else
    #define DP_TEMP_X1              0
#endif

#if (DP_C1_SAPS & DP_C1_USE_ALARM_SAP )
   #define DP_TEMP_X2               1
   #define SAP_50
#else
   #define DP_TEMP_X2               0
#endif

#ifdef DP_MSAC_C1
    #define DP_TEMP_X (DP_TEMP_X1 + DP_TEMP_X2)
#else
    #define DP_TEMP_X               0
#endif

#ifdef DP_MSAC_C2
    #define DP_MAX_SAPS             (DP_TEMP_X + DP_C2_NUM_SAPS + 1 )

#else
    #define DP_MAX_SAPS             DP_TEMP_X
#endif

#define DP_ORG_LENGTH               0x40 // organizational parameter

//#if (defined (DP_FDL))
   //#define FDL_SAP_MAX DP_MAX_SAPS
   /* length of vpc3-sap-list */
   //#define SAP_LENGTH          (((FDL_SAP_MAX*7)+SEG_OFFSET) & SEG_ADDBYTE)
//#else
   #define SAP_LENGTH               0x10
//#endif

//#ifdef DP_VPC3_4KB_MODE
    #define ASIC_RAM_LENGTH         0x1000
    //#define ASIC_USER_RAM           (ASIC_RAM_LENGTH - DP_ORG_LENGTH - SAP_LENGTH)
//#else
   // #define ASIC_RAM_LENGTH         0x800
    #define ASIC_USER_RAM           (ASIC_RAM_LENGTH - DP_ORG_LENGTH - SAP_LENGTH)
//#endif

/*-----------------------------------------------------------------------------------------------------------*/
/* 1.0 vpc3+                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 1.1 register structure of vpc3+                                           */
/*---------------------------------------------------------------------------*/
typedef struct
{
                                        // address  register
                                        // -------------------------------------------------------------------
    UBYTE int_req1;                     // 000H     Interrupt request register 1
    UBYTE int_req2;                     // 001H     Interrupt request register 2

    union
    {
        struct
        {                               // [read]
            UBYTE int_reg1;             // 002H     Interrupt register 1
            UBYTE int_reg2;             // 003H     Interrupt register 2
            UBYTE status_L;             // 004H     status register b0..b7
            UBYTE status_H;             // 005H     status register b8..b15
        }rd;

        struct
        {                               // [write]
            UBYTE int_ack1;             // 002H     Interrupt acknowledge register 1
            UBYTE int_ack2;             // 003H     Interrupt acknowledge register 2
            UBYTE int_mask_L;           // 004H     Interrupt mask register b0..b7
            UBYTE int_mask_H;           // 005H     Interrupt mask register b8..b15
        }wr;
    } isreg;


    UBYTE mode_reg0_L;                  // 006H     mode register0 b0..b7
    UBYTE mode_reg0_H;                  // 007H     mode register0 b8..b15

    union
    {
        struct
        {                               //          [read]
            UBYTE din_buffer_sm;        // 008H     buffer assignment of the DP_DIN_BUFFER state machine
            UBYTE new_din_buf_cmd;      // 009H     the user makes a new DP_DIN_BUFFER available in the N state
            UBYTE dout_buffer_sm;       // 00AH     buffer assignment of the DP_DOUT_BUFFER state machine
            UBYTE next_dout_buf_cmd;    // 00BH     the user fetches the last DP_DOUT_BUFFER from the N state
            UBYTE diag_buffer_sm;       // 00CH     buffer assignment for DP_DIAG_BUFFER state machine
            UBYTE new_diag_buf_cmd;     // 00DH     the user makes a new DP_DIAG_BUFFER available to the VPC3+
            UBYTE user_prm_data_ok;     // 00EH     positive acknowledge for received user parameter data
            UBYTE user_prm_data_nok;    // 00FH     negative acknowledge for received user parameter data
            UBYTE user_cfg_data_ok;     // 010H     positive acknowledge for received config data
            UBYTE user_cfg_data_nok;    // 011H     negative acknowledge for received config data
            UBYTE dxbout_buffer_sm;     // 012H     buffer assignment of the DXB_OUT_BUFFER state machine
            UBYTE next_dxb_buf_cmd;     // 013H     the user fetches the last DXB_OUT_BUFFER
            UBYTE ssa_buf_free_cmd;     // 014H     the user has fetched data from ssa buffer and enables buffer again
            UBYTE mode_reg1;            // 015H     current value of mode_reg1
        } rd;

        struct
        {                               //          [write]
            UBYTE mode_reg1_s;          // 008H     set b0..b7 in mode_reg1
            UBYTE mode_reg1_r;          // 009H     reset b0..b7 in mode_reg1
            UBYTE wd_baud_ctrl;         // 00AH     root value for baud rate monitoring
            UBYTE mintsdr;              // 00BH     MinTsdr time
            UBYTE mode_reg2;            // 00CH     set b0..b7 in mode_reg2
            UBYTE sync_pw_reg;          // 00DH     sync pulse width register
            UBYTE sync_mode;            // 00EH
            UBYTE sync_group;           // 00FH
            UBYTE controlbyte_mask;     // 010H
            UBYTE groupselect_mask;     // 011H
            UBYTE reserved_12;          // 012H
            UBYTE reserved_13;          // 013H
            UBYTE reserved_14;          // 014H
            UBYTE reserved_15;          // 015H
        } wr;
   }ctrl_reg;

   UBYTE slave_addr;                    // 016H     setup VPC3+ station address
   UBYTE fdl_sap_list_ptr;              // 017H     pointer fdl_sap_list
   UBYTE user_wd_value[2];              // 018H     user watchdog value b0..b7
                                        // 019H     user watchdog value b8..b15
   UBYTE len_dout_buf;                  // 01AH     length of dout buffers
   UBYTE dout_buf_ptr[3];               // 01BH     segment base address of dout_buffer [0]
                                        // 01CH     segment base address of dout_buffer [1]
                                        // 01DH     segment base address of dout_buffer [2]
   UBYTE len_din_buf;                   // 01EH     length of din buffers
   UBYTE din_buf_ptr[3];                // 01FH     segment base address of din_buffer [0]
                                        // 020H     segment base address of din_buffer [1]
                                        // 021H     segment base address of din_buffer [2]
   UBYTE len_dxb_out_buf;               // 022H     length of dxb buffers
   UBYTE dxb_out_buf_ptr1;              // 023H     segment base address of dxbout_buffer1
   UBYTE len_diag_buf[2];               // 024H     length of diag buffers [0]
                                        // 025H     length of diag buffers [1]
   UBYTE diag_buf_ptr[2];               // 026H     segment base address of diag_buffer [0]
                                        // 027H     segment base address of diag_buffer [1]
   UBYTE len_ctrl_buf[2];               // 028H     length of aux buffer 1
                                        // 029H     length of aux buffer 2
   UBYTE aux_buf_sel;                   // 02AH     assignment for aux buffers 1/2
   UBYTE aux_buf_ptr[2];                // 02BH     segment base address of aux buffer 1
                                        // 02CH     segment base address of aux buffer 2
   UBYTE len_ssa_buf;                   // 02DH     length of SET_SLAVE_ADDRESS buffer
   UBYTE ssa_buf_ptr;                   // 02EH     segment base address of SET_SLAVE_ADDRESS buffer
   UBYTE len_prm_data;                  // 02FH     max. length of input data in SET_PRM buffer
   UBYTE prm_buf_ptr;                   // 030H     segment base address of SET_PRM buffer
   UBYTE len_cfg_data;                  // 031H     length of input data in the CHECK_CONFIG buffer
   UBYTE cfg_buf_ptr;                   // 032H     segment base address of CHECK_CONFIG buffer
   UBYTE len_read_cfg_data;             // 033H     length of input data in the GET_CONFIG buffer
   UBYTE read_cfg_buf_ptr;              // 034H     segment base address of GET_CONFIG buffer
   UBYTE len_dxb_link_table_buf;        // 035H     length of dxb link table buffer
   UBYTE dxb_link_table_buf_ptr;        // 036H     segment base address of dxb link table buffer
   UBYTE len_dxb_link_status_buf;       // 037H     length of dxb link status buffer
   UBYTE dxb_link_status_buf_ptr;       // 038H     segment base address of dxb link status buffer
   UBYTE real_no_add_change;            // 039H     address changes
   UBYTE ident_low;                     // 03AH     IDENT_LOW
   UBYTE ident_high;                    // 03BH     IDENT_HIGH
   UBYTE gc_command;                    // 03CH     last global control command
   UBYTE len_spec_prm_buf;              // 03DH     length of SPEC_PRM buffer
   UBYTE dxb_out_buf_ptr2;              // 03EH     segment base address of dxbout_buffer2
   UBYTE dxb_out_buf_ptr3;              // 03FH     segment base address of dxbout_buffer3

   UBYTE sap_ctrl_list[0x10];//[SAP_LENGTH];     // 040H     SAP CONTROL BLOCK LIST

   UBYTE dpbuff[0x800];//[ASIC_USER_RAM];       // VPC3: 040H...7F0H: ram area for dp buffers
                                        // SPC3: 040H...5F0H
}VPC3_STRUC;




// -- dp system structure -----------------------------------------------------
typedef struct
{
    UBYTE               cfg_len;
	  UBYTE               outp_data_len;              // calculated output length (data from DP-Master to VPC3)
    UBYTE               inp_data_len;               // calculated input length  (data from VPC3 to DP-Master)

	UBYTE               prm_spec;

	UBYTE               ssa_chg;


    UWORD               vpc3_used_dp_buf_mem;       // consumed user_memory
    UBYTE               ind_high;                   // interrupt indication high byte
    UBYTE               ind_low;                    // interrupt indication low byte
    UBYTE               vpc3_con;                   // dummy

    UBYTE               din_bufsize;                // Length of the DIn Buffer (Data Slave to Master)                0..244
    UBYTE               dout_bufsize;               // Length of the DOut Buffer     (Data Master to Slave)           0..244
    UBYTE               prm_bufsize;                // Length of the Parameter Buffer                                 7..244
    UBYTE               diag_bufsize;               // Length of the Diagnosis Buffer                                 6..244
    UBYTE               cfg_bufsize;                // Length of the Configuration Buffer                             1..244
    UBYTE               ssa_bufsize;                // Length of the Input Data in the Set_Slave_Address-Buffer 0 and 4..244

    UBYTE               c2_num_saps;                // Number of MSAC_C2 connections
    UBYTE               c2_len;                     // Length of MSAC_C2 Data

   // C1_STRUC            c1;
  //  AL_STRUC            al;
  //  T_ISOCHRON          iso_m;

  //  VPC3_UNION_DIAG_PTR diag_buf_ptr;               // pointer to actual diagnosis buffer
} VPC3_SYSTEM_STRUC;

     // global system structure



/*---------------------------------------------------------------------------*/
/* 1.2 literals for interrupt register                                       */
/*---------------------------------------------------------------------------*/
//low Byte
#define VPC3_INT_MAC_RESET              ((UBYTE)0x01)  // VPC3 in offline state
#define VPC3_INT_GO_LEAVE_DATA_EX       ((UBYTE)0x02)  // VPC3 has entered or left DATA_EX
#define VPC3_INT_BAUDRATE_DETECT        ((UBYTE)0x04)  // VPC3 has detected Baudrate
#define VPC3_INT_WD_DP_TIMEOUT          ((UBYTE)0x08)  // DP watchdog timeout
#define VPC3_INT_USER_TIMER_CLOCK       ((UBYTE)0x10)  // time base for USER_TIMER_CLOCKS has run out
#define VPC3_INT_DXB_LINK_ERROR         ((UBYTE)0x20)  // subscriber link error
#define VPC3_INT_NEW_EXT_PRM_DATA       ((UBYTE)0x40)  // New EXT_PRM_DATA received
#define VPC3_INT_DXB_OUT                ((UBYTE)0x80)  // NEW subscriber data received

//high Byte
#define VPC3_INT_NEW_GC_COMMAND         ((UBYTE)0x01)  // New Global control command received
#define VPC3_INT_NEW_SSA_DATA           ((UBYTE)0x02)  // New SSA_DATA received
#define VPC3_INT_NEW_CFG_DATA           ((UBYTE)0x04)  // New check_config received
#define VPC3_INT_NEW_PRM_DATA           ((UBYTE)0x08)  // New prm_data received
#define VPC3_INT_DIAG_BUF_CHANGED       ((UBYTE)0x10)  // diag_buffer has been changed
#define VPC3_INT_DX_OUT                 ((UBYTE)0x20)  // New DOut_data received
#define VPC3_INT_POLL_END_IND           ((UBYTE)0x40)  // DPV1
#define VPC3_INT_FDL_IND                ((UBYTE)0x80)  // DPV1

// -- events for interrupt event handler --------------------------------------
#define VPC3_EV_MAC_RESET               ((UWORD)0x0001)
#define VPC3_EV_GO_LEAVE_DATA_EX        ((UWORD)0x0002)
#define VPC3_EV_BAUDRATE_DETECT         ((UWORD)0x0004)
#define VPC3_EV_WD_DP_TIMEOUT           ((UWORD)0x0008)
#define VPC3_EV_USER_TIMER_CLOCK        ((UWORD)0x0010)
#define VPC3_EV_DXB_LINK_ERROR          ((UWORD)0x0020)
#define VPC3_EV_NEW_EXT_PRM_DATA        ((UWORD)0x0040)
#define VPC3_EV_DXB_OUT                 ((UWORD)0x0080)
#define VPC3_EV_NEW_GC_COMMAND          ((UWORD)0x0100)
#define VPC3_EV_NEW_SSA_DATA            ((UWORD)0x0200)
#define VPC3_EV_NEW_CFG_DATA            ((UWORD)0x0400)
#define VPC3_EV_NEW_PRM_DATA            ((UWORD)0x0800)
#define VPC3_EV_DIAG_BUF_CHANGED        ((UWORD)0x1000)
#define VPC3_EV_DX_OUT                  ((UWORD)0x2000)
#define VPC3_EV_RESERVED                ((UWORD)0x4000)
#define VPC3_EV_NEW_INPUT_DATA          ((UWORD)0x8000)

/*---------------------------------------------------------------------------*/
/* 1.3 literals for status register                                          */
/*---------------------------------------------------------------------------*/
#define VPC3_PASS_IDLE                  ((UBYTE)0x01)
#define VPC3_DIAG_FLAG                  ((UBYTE)0x04)
#define WAIT_PRM                        ((UBYTE)0x00)
#define WAIT_CFG                        ((UBYTE)0x10)
#define DATA_EX                         ((UBYTE)0x20)
#define DP_ERROR                        ((UBYTE)0x30)
#define BAUD_SEARCH                     ((UBYTE)0x00)
#define BAUD_CONTROL                    ((UBYTE)0x40)
#define DP_MODE                         ((UBYTE)0x80)
#define WD_ERROR                        ((UBYTE)0xC0)

#define BAUDRATE_MASK                   ((UBYTE)0x0F)
#define BAUDRATE_12MBAUD                ((UBYTE)0x00)
#define BAUDRATE_6MBAUD                 ((UBYTE)0x01)
#define BAUDRATE_3MBAUD                 ((UBYTE)0x02)
#define BAUDRATE_1_5MBAUD               ((UBYTE)0x03)
#define BAUDRATE_500KBAUD               ((UBYTE)0x04)
#define BAUDRATE_187_50KBAUD            ((UBYTE)0x05)
#define BAUDRATE_93_75KBAUD             ((UBYTE)0x06)
#define BAUDRATE_45_45KBAUD             ((UBYTE)0x07)
#define BAUDRATE_19_20KBAUD             ((UBYTE)0x08)
#define BAUDRATE_9_60KBAUD              ((UBYTE)0x09)
#define BAUDRATE_AFTER_RESET            ((UBYTE)0xFF)

#define AT_MASK                         ((UBYTE)0xF0)
#define AT_VPC3                         ((UBYTE)0x00)
#define AT_VPC3B                        ((UBYTE)0xB0)
#define AT_VPC3C                        ((UBYTE)0xC0)
/*---------------------------------------------------------------------------*/
/* 1.4 literals for mode register 0                                          */
/*---------------------------------------------------------------------------*/
//low Byte
#define VPC3_DIS_START_CTRL             ((UBYTE)0x01)
#define VPC3_DIS_STOP_CTRL              ((UBYTE)0x02)
#define VPC3_FDL_DBB                    ((UBYTE)0x04)
#define VPC3_MINTSDR                    ((UBYTE)0x08)
#define VPC3_INT_POL_HIGH               ((UBYTE)0x10)
#define VPC3_EARLY_RDY                  ((UBYTE)0x20)
#define VPC3_SYNC_SUPP                  ((UBYTE)0x40)
#define VPC3_FREEZE_SUPP                ((UBYTE)0x80)

//high Byte
#define VPC3_DP_MODE                    ((UBYTE)0x01)
#define VPC3_EOI_TBASE_1ms              ((UBYTE)0x02)
#define VPC3_USR_TBASE_10ms             ((UBYTE)0x04)
#define VPC3_WD_TEST                    ((UBYTE)0x08)
#define VPC3_SPEC_PRM_BUF_MODE          ((UBYTE)0x10)
#define VPC3_SPEC_CLR_MODE              ((UBYTE)0x20)

/*---------------------------------------------------------------------------*/
/* 1.5 literals for mode register 1                                          */
/*---------------------------------------------------------------------------*/
#define VPC3_START                      ((UBYTE)0x01)
#define VPC3_EOI                        ((UBYTE)0x02)
#define VPC3_GO_OFFLINE                 ((UBYTE)0x04)
#define VPC3_USER_LEAVE_MASTER          ((UBYTE)0x08)
#define VPC3_EN_CHG_CFG_BUFFER          ((UBYTE)0x10)
#define VPC3_RES_USER_WD                ((UBYTE)0x20)

/*---------------------------------------------------------------------------*/
/* 1.6 literals for mode register 2                                          */
/*---------------------------------------------------------------------------*/
#define VPC3_GC_INT_MODE                ((UBYTE)0x01)
#define VPC3_NO_CHECK_GC_RESERVED       ((UBYTE)0x02)
#define VPC3_DX_INT_MODE                ((UBYTE)0x04)
#define VPC3_DX_INT_PORT                ((UBYTE)0x08)
#define VPC3_SYNC_ENA                   ((UBYTE)0x10)
#define VPC3_SYNC_POL                   ((UBYTE)0x20)
#define VPC3_NO_CHECK_PRM_RESERVED      ((UBYTE)0x40)
#define VPC3_4KB_MODE                   ((UBYTE)0x80)


/*---------------------------------------------------------------------------*/
/* 1.7 basic macros for VPC3+                                                */
/*---------------------------------------------------------------------------*/
// Startaddress of User-Area in VPC3-Format -----------------------------------
#define VPC3_DP_BUF_START (0x40>>4)//(UBYTE)(((VPC3_ADR)&p_Vpc3->dpbuffer - (VPC3_ADR)VPC3_ASIC_ADDRESS) >> SEG_MULDIV)
// Startaddress of FDL-List-Area in VPC3-Format -------------------------------
#define VPC3_SAP_CTRL_LIST_START (UBYTE)(((VPC3_ADR)&p_Vpc3->sap_ctrl_list - (VPC3_ADR)VPC3_ASIC_ADDRESS) >> SEG_MULDIV)
// set HW-Mode ----------------------------------------------------------------
#define VPC3_SET_HW_MODE_HIGH(MODE_HIGH) p_Vpc3->mode_reg0_H = MODE_HIGH
#define VPC3_SET_HW_MODE_LOW(MODE_LOW)   p_Vpc3->mode_reg0_L = MODE_LOW
// set interrupt indications --------------------------------------------------
#define VPC3_SET_INDICATIONS_HIGH(IND_HIGH) p_Vpc3->isreg.wr.int_mask_H = IND_HIGH
#define VPC3_SET_INDICATIONS_LOW(IND_LOW)   p_Vpc3->isreg.wr.int_mask_L = IND_LOW
// -- Set Slave-Adresse -------------------------------------------------------
#define VPC3_SET_STATION_ADDRESS(ADDRESS) p_Vpc3->slave_addr = ADDRESS
#define VPC3_GET_STATION_ADDRESS()        p_Vpc3->slave_addr
// -- Set min_TSDR ------------------------------------------------------------
#define VPC3_SET_MINTSDR(MINTSDR) p_Vpc3->ctrl_reg.wr.mintsdr = MINTSDR
// -- Set Baud Control --------------------------------------------------------
#define VPC3_SET_BAUD_CNTRL(VALUE) p_Vpc3->ctrl_reg.wr.wd_baud_ctrl = VALUE
//-- Ident-Nummer -------------------------------------------------------------
//-- Set Ident-Number ---------------------------------------------------------
#define VPC3_SET_IDENT_NUMBER_LOW(NR) p_Vpc3->ident_low = NR
#define VPC3_SET_IDENT_NUMBER_HIGH(NR) p_Vpc3->ident_high = NR
// -- address change service --------------------------------------------------
#define VPC3_SET_ADD_CHG_DISABLE() p_Vpc3->real_no_add_change  = 0xFF
#define VPC3_SET_ADD_CHG_ENABLE()  p_Vpc3->real_no_add_change  = 0x00
//-- start VPC3 ---------------------------------------------------------------
#define START_VPC3__() vpc3_ptr->ctrl_reg.wr.mode_reg1_s = VPC3_START
#define RESET_START_VPC3() p_Vpc3->ctrl_reg.wr.mode_reg1_r = VPC3_START
//-- set VPC3 offline ---------------------------------------------------------
#define GO_OFFLINE_VPC3()  p_Vpc3->ctrl_reg.wr.mode_reg1_s = VPC3_GO_OFFLINE
// -- read State of DP-State Machine ------------------------------------------
#define VPC3_GET_DP_STATE() (vpc3_ptr->isreg.rd.status_L & 0x30)
// -- read WD-State Machine ---------------------------------------------------
#define VPC3_GET_WD_STATE() (p_Vpc3->isreg.rd.status_L & 0xC0)
// -- read Baud-Rate ----------------------------------------------------------
#define VPC3_GET_BAUDRATE() (p_Vpc3->isreg.rd.status_H & BAUDRATE_MASK)
// -- read ASIC-Type ----------------------------------------------------------
#define VPC3_GET_ASIC_TYPE() (p_Vpc3->isreg.rd.status_H & AT_MASK)
// -- read VPC3-Offline/Passiv-Idle-State -------------------------------------
#define VPC3_GET_OFF_PASS()  (vpc3_ptr->isreg.rd.status_L & VPC3_PASS_IDLE)
// -- set DP StateMachine to WAIT_PRM -----------------------------------------
#define VPC3_SET_USER_LEAVE_MASTER() p_Vpc3->ctrl_reg.wr.mode_reg1_s = VPC3_USER_LEAVE_MASTER
// -- User-Watchdog -----------------------------------------------------------
#define VPC3_SET_USER_WD_VALUE_HIGH(VALUE_HIGH) p_Vpc3->user_wd_value[1] = VALUE_HIGH
#define VPC3_SET_USER_WD_VALUE_LOW(VALUE_LOW)   p_Vpc3->user_wd_value[0] = VALUE_LOW
// -- Reset User-Watchdog -----------------------------------------------------
#define VPC3_RESET_USER_WD() vpc3_ptr->ctrl_reg.wr.mode_reg1_s = VPC3_RES_USER_WD

// -- read out reasons for indications ( vpc3_isr() ) --------------------------
#define VPC3_GET_IND_MAC_RESET()        (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_MAC_RESET)
#define VPC3_GET_IND_GO_LEAVE_DATA_EX() (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_GO_LEAVE_DATA_EX)
#define VPC3_GET_IND_BAUDRATE_DETECT()  (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_BAUDRATE_DETECT)
#define VPC3_GET_IND_WD_DP_TIMEOUT()    (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_WD_DP_TIMEOUT)
#define VPC3_GET_IND_USER_TIMER_CLOCK() (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_USER_TIMER_CLOCK)
#define VPC3_GET_IND_DXB_LINK_ERROR()   (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_DXB_LINK_ERROR)
#define VPC3_GET_IND_NEW_EXT_PRM_DATA() (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_NEW_EXT_PRM_DATA)
#define VPC3_GET_IND_DXB_OUT()          (vpc3_ptr->isreg.rd.int_reg1 & VPC3_INT_DXB_OUT)
#define VPC3_GET_IND_NEW_GC_COMMAND()   (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_NEW_GC_COMMAND)
#define VPC3_GET_IND_NEW_SSA_DATA()     (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_NEW_SSA_DATA)
#define VPC3_GET_IND_NEW_CFG_DATA()     (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_NEW_CFG_DATA)
#define VPC3_GET_IND_NEW_PRM_DATA()     (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_NEW_PRM_DATA)
#define VPC3_GET_IND_DIAG_BUF_CHANGED() (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_DIAG_BUF_CHANGED)
#define VPC3_GET_IND_DX_OUT()           (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_DX_OUT)
#define VPC3_GET_IND_POLL_END_IND()     (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_POLL_END_IND)
#define VPC3_GET_IND_FDL_IND()          (vpc3_ptr->isreg.rd.int_reg2 & VPC3_INT_FDL_IND)

// -- Acknowledging the indication -------------------------------------------
#define VPC3_CON_IND_MAC_RESET()        vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_MAC_RESET
#define VPC3_CON_IND_GO_LEAVE_DATA_EX() vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_GO_LEAVE_DATA_EX
#define VPC3_CON_IND_BAUDRATE_DETECT()  vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_BAUDRATE_DETECT
#define VPC3_CON_IND_WD_DP_TIMEOUT()    vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_WD_DP_TIMEOUT
#define VPC3_CON_IND_USER_TIMER_CLOCK() vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_USER_TIMER_CLOCK
#define VPC3_CON_IND_DXB_LINK_ERROR()   vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_DXB_LINK_ERROR
#define VPC3_CON_IND_NEW_EXT_PRM_DATA() vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_NEW_EXT_PRM_DATA
#define VPC3_CON_IND_DXB_OUT()          vpc3_ptr->isreg.wr.int_ack1 = VPC3_INT_DXB_OUT
#define VPC3_CON_IND_NEW_GC_COMMAND()   vpc3_ptr->isreg.wr.int_ack2 = VPC3_INT_NEW_GC_COMMAND
#define VPC3_CON_IND_NEW_SSA_DATA()     vpc3_ptr->isreg.wr.int_ack2 = VPC3_INT_NEW_SSA_DATA
#define VPC3_CON_IND_DIAG_BUF_CHANGED() vpc3_ptr->isreg.wr.int_ack2 = VPC3_INT_DIAG_BUF_CHANGED
#define VPC3_CON_IND_DX_OUT()           vpc3_ptr->isreg.wr.int_ack2 = VPC3_INT_DX_OUT
#define VPC3_CON_IND_POLL_END_IND()     vpc3_ptr->isreg.wr.int_ack2 = VPC3_INT_POLL_END_IND
#define VPC3_CON_IND_FDL_IND()          vpc3_ptr->isreg.wr.int_ack2 = VPC3_INT_FDL_IND

// -- Ending the Indication ---------------------------------------------------
#define VPC3_SET_EOI() p_Vpc3->ctrl_reg.wr.mode_reg1_s  = VPC3_EOI

// poll read out reasons for indications --------------------------------------
#define VPC3_POLL_IND_MAC_RESET()           (vpc3_ptr->int_req1 & VPC3_INT_MAC_RESET)
#define VPC3_POLL_IND_BAUDRATE_DETECT()     (vpc3_ptr->int_req1 & VPC3_INT_BAUDRATE_DETECT)
#define VPC3_POLL_IND_USER_TIMER_CLOCK()    (vpc3_ptr->int_req1 & VPC3_INT_USER_TIMER_CLOCK)
#define VPC3_POLL_IND_GO_LEAVE_DATA_EX()    (vpc3_ptr->int_req1 & VPC3_INT_GO_LEAVE_DATA_EX)
#define VPC3_POLL_IND_WD_DP_MODE_TIMEOUT()  (vpc3_ptr->int_req1 & VPC3_INT_WD_DP_MODE_TIMEOUT)
#define VPC3_POLL_IND_NEW_EXT_PRM_DATA()    (vpc3_ptr->int_req1 & VPC3_INT_NEW_EXT_PRM_DATA)
#define VPC3_POLL_IND_NEW_GC_COMMAND()      (vpc3_ptr->int_req2 & VPC3_INT_NEW_GC_COMMAND)
#define VPC3_POLL_IND_NEW_SSA_DATA()        (vpc3_ptr->int_req2 & VPC3_INT_NEW_SSA_DATA)
#define VPC3_POLL_IND_NEW_CFG_DATA()        (vpc3_ptr->int_req2 & VPC3_INT_NEW_CFG_DATA)
#define VPC3_POLL_IND_NEW_PRM_DATA()        (vpc3_ptr->int_req2 & VPC3_INT_NEW_PRM_DATA)
#define VPC3_POLL_IND_DIAG_BUFFER_CHANGED() (vpc3_ptr->int_req2 & VPC3_INT_DIAG_BUF_CHANGED)
#define VPC3_POLL_IND_DX_OUT()              (vpc3_ptr->int_req2 & VPC3_INT_DX_OUT)
#define VPC3_POLL_IND_POLL_END_IND()        (vpc3_ptr->int_req2 & VPC3_INT_POLL_END_IND)
#define VPC3_POLL_IND_FDL_IND()             (vpc3_ptr->int_req2 & VPC3_INT_FDL_IND)

#define VPC3_SET_IRR_1(IRR_BYTE)            (vpc3_ptr->int_req1 |= IRR_BYTE)
#define VPC3_SET_IRR_2(IRR_BYTE)            (vpc3_ptr->int_req2 |= IRR_BYTE)



#define DP_LOCK_IND()                                                            \
{                                                                                \
      vpc3_ptr->isreg.wr.int_mask_H = 0xFF;                                        \
                                                                                 \
      vpc3_ptr->isreg.wr.int_mask_L = 0xFF;                                        \
}


#define DP_UNLOCK_IND()                                                          \
{                                                                                \
      vpc3_ptr->isreg.wr.int_mask_H = dp_sys.ind_high;                             \
                                                                                 \
      vpc3_ptr->isreg.wr.int_mask_L = dp_sys.ind_low;                              \
}

/*-----------------------------------------------------------------------------------------------------------*/
/* 2.0 parameter telegram                                                                                    */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 2.1 structure of prm data                                                 */
/*---------------------------------------------------------------------------*/

/*
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
|      7       |      6     |       5       |           4           |      3     |     2     |         1        |          0        |
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
|   Lock_Req   | Unlock_Req |   Sync_Req    |       Freeze_Req      |    WD_On   |     0     |         0        |          0        |
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
| WD_Fact_1 (1 bis 255)                                                                                                             |
|-----------------------------------------------------------------------------------------------------------------------------------|
| WD_Fact_2 (1 bis 255)                                                                                                             |
|-----------------------------------------------------------------------------------------------------------------------------------|
| Min. Station Delay Responder (min Tsdr)                                                                                           |
|-----------------------------------------------------------------------------------------------------------------------------------|
| Ident_Number (high)                                                                                                               |
|-----------------------------------------------------------------------------------------------------------------------------------|
| Ident_Number (low)                                                                                                                |
|-----------------------------------------------------------------------------------------------------------------------------------|
| Group_Ident                                                                                                                       |
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
| DPV1_Enable  | Fail_Safe  | Publisher_En  |       reserved        |  res       |  WD_Base  | Dis_Stop_Control | Dis_Start_Control |
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
| En_Pull_Plug | En_Process | En_Diagnostic | En_Manufacturer_Spec. | En_Status  | En_Update |    reserviert    | Chk_Cfg_Mode      |
|    Alarm     |    Alarm   |    Alarm      |         Alarm         |   Alarm    |   Alarm   |                  |                   |
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
|   PrmCmd     |  reserved  |   reserved    |       IsoM_Req        | Prm_Struct |                 Alarm_Mode                       |
|--------------|------------|---------------|-----------------------|------------|-----------|------------------|-------------------|
|                                                            User_Prm_Data                                                          |
|-----------------------------------------------------------------------------------------------------------------------------------|
*/

typedef struct
{
    UBYTE station_state;
    UBYTE wd_fact_1;
    UBYTE wd_fact_2;
    UBYTE mintsdr;
    UBYTE pno_ident_high;
    UBYTE pno_ident_low;
    UBYTE group_ident;
    UBYTE dpv1_status_1;
    UBYTE dpv1_status_2;
    UBYTE dpv1_status_3;

    UBYTE user_data;
}STRUC_PRM;
#define VPC3_STRUC_PRM_PTR  STRUC_PRM PTR_ATTR *

/*---------------------------------------------------------------------------*/
/* 2.1 literals for Station State                                            */
/*---------------------------------------------------------------------------*/
#define STATION_STATE_WD_ON             ((UBYTE)0x08)

/*---------------------------------------------------------------------------*/
/* 2.2 literals for DPV1 Status 1                                            */
/*---------------------------------------------------------------------------*/
#define DPV1_STATUS_1_RESERVED_1        ((UBYTE)0x03)
#define DPV1_STATUS_1_WD_BASE_1MS       ((UBYTE)0x04)
#define DPV1_STATUS_1_RESERVED_2        ((UBYTE)0x08)
#define DPV1_STATUS_1_RESERVED_3        ((UBYTE)0x10)
#define DPV1_STATUS_1_PUBLISHER_ENABLE  ((UBYTE)0x20)
#define DPV1_STATUS_1_FAIL_SAFE         ((UBYTE)0x40)
#define DPV1_STATUS_1_DPV1_ENABLE       ((UBYTE)0x80)

/*---------------------------------------------------------------------------*/
/* 2.3 literals for DPV1 Status 2                                            */
/*---------------------------------------------------------------------------*/
#define DPV1_STATUS_2_CHECK_CFG_MODE    ((UBYTE)0x01)
#define CHECK_CFG                       ((UBYTE)0x00)
#define NO_CHECK_CFG                    ((UBYTE)0x01)
#define DPV1_STATUS_2_RESERVED_4        ((UBYTE)0x02)

#define ALARM_TYPE_UPDATE_VALUE         ((UBYTE)0x04)
#define ALARM_TYPE_STATUS_VALUE         ((UBYTE)0x08)
#define ALARM_TYPE_MANUFACTURER_VALUE   ((UBYTE)0x10)
#define ALARM_TYPE_DIAGNOSTIC_VALUE     ((UBYTE)0x20)
#define ALARM_TYPE_PROCESS_VALUE        ((UBYTE)0x40)
#define ALARM_TYPE_PULLPLUG_VALUE       ((UBYTE)0x80)

#define DPV1_STATUS_2_ALARM_TYPE_MASK   (   ALARM_TYPE_UPDATE_VALUE       \
                                          | ALARM_TYPE_STATUS_VALUE       \
                                          | ALARM_TYPE_MANUFACTURER_VALUE \
                                          | ALARM_TYPE_DIAGNOSTIC_VALUE   \
                                          | ALARM_TYPE_PROCESS_VALUE      \
                                          | ALARM_TYPE_PULLPLUG_VALUE     \
                                        )
#define ALARM_TYPE_NONE_VALUE           ((UBYTE)0x00)
#define ALARM_TYPE_ALL_VALUE            ((UBYTE)0xFF)

/*---------------------------------------------------------------------------*/
/* 2.4 literals for DPV1 Status 3                                            */
/*---------------------------------------------------------------------------*/
#define DPV1_STATUS_3_ALARM_MODE_MASK   ((UBYTE)0x07)
#define DPV1_STATUS_3_PRM_STRUCTURE     ((UBYTE)0x08)
#define DPV1_STATUS_3_ISOM_REQUEST      ((UBYTE)0x10)
#define DPV1_STATUS_3_RESERVED_UNUSED5  ((UBYTE)0x70)
#define DPV1_STATUS_3_PRM_CMD           ((UBYTE)0x80)

/*---------------------------------------------------------------------------*/
/* 2.5 general defines for prm data                                          */
/*---------------------------------------------------------------------------*/
#define PRM_LEN_NORM                    ((UBYTE)0x07)
#define PRM_LEN_DPV1                    ((UBYTE)0x0A)

/*---------------------------------------------------------------------------*/
/* 2.6 literals for structured prm data                                      */
/*---------------------------------------------------------------------------*/
#define PBC_PRMCMD                      ((UBYTE)0x02)
#define PBC_DXB_LINKTABLE               ((UBYTE)0x03)
#define PBC_ISOCHRON                    ((UBYTE)0x04)
#define PBC_DXB_SUBSCRIBERTABLE         ((UBYTE)0x07)
#define PBC_TIME_AR                     ((UBYTE)0x08)
#define PBC_USER_PRM_DATA               ((UBYTE)0x81)

typedef struct
{
    UBYTE len;
    UBYTE command;
    UBYTE slot_nr;
    UBYTE index;
    UBYTE user_data;
}STRUC_PRM_BLOCK;
#define VPC3_STRUC_PRM_BLOCK_PTR  STRUC_PRM_BLOCK PTR_ATTR *

/*---------------------------------------------------------------------------*/
/* 2.7 returncodes prm data                                                  */
/*---------------------------------------------------------------------------*/
#define VPC3_PRM_FINISHED               ((UBYTE)0x00)
#define VPC3_PRM_CONFLICT               ((UBYTE)0x01)
#define VPC3_PRM_NOT_ALLOWED            ((UBYTE)0x03)

/*---------------------------------------------------------------------------*/
/* 2.8 macros for prm data                                                   */
/*---------------------------------------------------------------------------*/
// read length of prm-Data --------------------------------------------------
#define VPC3_GET_PRM_LEN()  p_Vpc3->len_prm_data
// get pointer to prm-buffer ------------------------------------------------
#define VPC3_GET_PRM_BUF_PTR() (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->prm_buf_ptr << SEG_MULDIV)+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
// acknowledge prm-data -----------------------------------------------------
#define VPC3_SET_PRM_DATA_OK()      p_Vpc3->ctrl_reg.rd.user_prm_data_ok
#define VPC3_SET_PRM_DATA_NOT_OK()  p_Vpc3->ctrl_reg.rd.user_prm_data_nok


/*-----------------------------------------------------------------------------------------------------------*/
/* 3.0 configuration telegram                                                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 3.1 standard format of cfg byte                                           */
/*---------------------------------------------------------------------------*/
//
//        MSB                         LSB
//       +---+---+---+---+---+---+---+---+
//Bit-No | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//       +---+---+---+---+---+---+---+---+
//         |   |   |   |   |   |   |   |      meaning:
//         |   |   |   |   |   |   |   |
//         |   |   |   |   +---+---+---+----  length of data
//         |   |   |   |                      00 1 byte resp. 1 word
//         |   |   |   |                      .
//         |   |   |   |                      .
//         |   |   |   |                      15 16 byte resp. 16 words
//         |   |   |   |
//         |   |   |   |
//         |   |   +---+--------------------  input/output
//         |   |                              00 specific identifier formats
//         |   |                              01 input
//         |   |                              10 output
//         |   |                              11 input-output
//         |   |
//         |   +----------------------------  length format 1)
//         |                                   0 byte byte structure
//         |                                   1 word word structure
//         |
//         +--------------------------------  consistency over
//                                             0 byte or word
//                                             1 whole length
//

/*---------------------------------------------------------------------------*/
/* 3.2 special format of cfg byte                                            */
/*---------------------------------------------------------------------------*/
//
//        MSB                         LSB
//       +---+---+---+---+---+---+---+---+
//Bit-No | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//       +---+---+---+---+---+---+---+---+
//         |   |   |   |   |   |   |   |      meaning:
//         |   |   |   |   |   |   |   |
//         |   |   |   |   |   |   |   |
//         |   |   |   |   +---+---+---+----- length of manufacturer
//         |   |   |   |                      specific data 2)
//         |   |   |   |
//         |   |   +---+--------------------- fixed to 00
//         |   |
//         +---+----------------------------- input/output
//                                            00 free place
//                                            01 it follows 1 length byte for inputs
//                                            10 it follows 1 length byte for outputs
//                                            11 it follows - 1 length byte for outputs
//                                                          - 1 length byte for inputs
//
// -----------------------------------------------------------------------------
// 2) The length information of the manufacturer specific data shall be interpreted as follows:
//
// In case of Chk_Cfg:
//
//   0             No manufacturer specific data follow; no data in Real_Cfg_Data.
//   1 to 14       Manufacturer specific data of specified length follow;
//                 these shall be identical with the data in Real_Cfg_Data.
//   15            No manufacturer specific data follow;
//                 the verification can be omitted
//
// In case of DDLM_Get_Cfg :
//
//   0             No manufacturer specific data follow
//   1 to 14       Manufacturer specific data with specified length follow
//   15            Not allowed

// The structure of the length bytes is as follows:
//
//        MSB                         LSB
//       +---+---+---+---+---+---+---+---+
//Bit-No | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//       +---+---+---+---+---+---+---+---+
//         |   |   |   |   |   |   |   |      meaning:
//         |   |   |   |   |   |   |   |
//         |   |   +---+---+---+---+---+----- length of inputs/outputs
//         |   |                              00 1 byte resp. 1 word
//         |   |                              .
//         |   |                              .
//         |   |                              63 64 byte resp. 64 words
//         |   |
//         |   +----------------------------- Length format 3)
//         |                                   0 byte byte structure
//         |                                   1 word word structure
//         |
//         +--------------------------------- consistency over
//                                             0 byte or word
//                                             1 whole length

/*---------------------------------------------------------------------------*/
/* 3.3 literals for cfg-bytes                                                */
/*---------------------------------------------------------------------------*/
#define VPC3_CFG_IS_BYTE_FORMAT         ((UBYTE)0x30)
#define VPC3_CFG_BF_LENGTH              ((UBYTE)0x0f)
#define VPC3_CFG_LENGTH_IS_WORD_FORMAT  ((UBYTE)0x40)
#define VPC3_CFG_BF_INP_EXIST           ((UBYTE)0x10)
#define VPC3_CFG_BF_OUTP_EXIST          ((UBYTE)0x20)
#define VPC3_CFG_SF_OUTP_EXIST          ((UBYTE)0x80)
#define VPC3_CFG_SF_INP_EXIST           ((UBYTE)0x40)
#define VPC3_CFG_SF_LENGTH              ((UBYTE)0x3f)

/*---------------------------------------------------------------------------*/
/* 3.4 returncodes cfg data                                                  */
/*---------------------------------------------------------------------------*/
#define VPC3_CFG_FINISHED               ((UBYTE)0x00)
#define VPC3_CFG_CONFLICT               ((UBYTE)0x01)
#define VPC3_CFG_NOT_ALLOWED            ((UBYTE)0x03)

/*---------------------------------------------------------------------------*/
/* 3.5 literals for chk config data                                          */
/*---------------------------------------------------------------------------*/
#define VPC3_CFG_OK                     ((UBYTE)0x00)
#define VPC3_CFG_FAULT                  ((UBYTE)0x01)
#define VPC3_CFG_UPDATE                 ((UBYTE)0x02)

/*---------------------------------------------------------------------------*/
/* 3.6 macros for cfg data                                                   */
/*---------------------------------------------------------------------------*/
// read length of cfg-buffers ----------------------------------------------
#define VPC3_GET_READ_CFG_LEN()   p_Vpc3->len_read_cfg_data
#define VPC3_GET_CFG_LEN()        p_Vpc3->len_cfg_data
// set length of cfg-data --------------------------------------------------
#define VPC3_SET_READ_CFG_LEN(LEN)  vpc3_ptr->len_read_cfg_data = LEN
// get pointer to cfg-buffers ----------------------------------------------
#define VPC3_GET_READ_CFG_BUF_PTR() (vpc3_ptr->read_cfg_buf_ptr)
#define VPC3_GET_CFG_BUF_PTR()      (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->cfg_buf_ptr << SEG_MULDIV     )+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
// acknowledge cfg-data ----------------------------------------------------
#define VPC3_SET_CFG_DATA_OK()     vpc3_cfg_data_ok()
#define VPC3_SET_CFG_DATA_UPDATE() vpc3_cfg_data_update()
#define VPC3_SET_CFG_DATA_NOT_OK() vpc3_cfg_data_not_ok()

/*---------------------------------------------------------------------------*/
/* 3.7 structure for real cfg data                                           */
/*---------------------------------------------------------------------------*/
// -- cfg structure -----------------------------------------------------------
typedef struct
{
    UBYTE length;
//    UBYTE cfg_data[CFG_BUFSIZE];
} CFG_STRUCT;


/*-----------------------------------------------------------------------------------------------------------*/
/* 4.0 input / output                                                                                        */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 4.1 structure for calculated input-/output-length                         */
/*---------------------------------------------------------------------------*/
typedef struct
{
   UBYTE inp_data_len;               // calculated input length  (VPC3->DP-Master)
   UBYTE outp_data_len;              // calculated output length (DP-Master->VPC3)
}  VPC3_IO_DATA_LEN;

/*---------------------------------------------------------------------------*/
/* 4.2 states for output buffer                                              */
/*---------------------------------------------------------------------------*/
#define VPC3_NEW_DOUT_BUF               ((UBYTE)0x04)
#define VPC3_DOUT_BUF_CLEARED           ((UBYTE)0x08)

/*---------------------------------------------------------------------------*/
/* 4.3 macros for input buffer                                               */
/*---------------------------------------------------------------------------*/
#define VPC3_INPUT_UPDATE()             p_Vpc3->ctrl_reg.rd.new_din_buf_cmd


/*-----------------------------------------------------------------------------------------------------------*/
/* 5.0 set slave address                                                                                     */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 5.1 structure                                                             */
/*---------------------------------------------------------------------------*/
typedef struct
{
    UBYTE address;
    UBYTE ident_high;
    UBYTE ident_low;
    UBYTE no_add_chg;
    UBYTE user_data;
}STRUC_SSA_BLOCK;
#define VPC3_STRUC_SSA_BLOCK_PTR  STRUC_SSA_BLOCK PTR_ATTR *

/*---------------------------------------------------------------------------*/
/* 5.2 macros                                                                */
/*---------------------------------------------------------------------------*/
// -- read length of set-slave-address ----------------------------------------
#define VPC3_GET_SSA_LEN()  p_Vpc3->len_ssa_buf
// -- get pointer to ssa buffer -----------------------------------------------
#define VPC3_GET_SSA_BUF_PTR() (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->ssa_buf_ptr << SEG_MULDIV)+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
// -- acknowledge ssa commando ------------------------------------------------
#define VPC3_FREE_SSA_BUF() p_Vpc3->ctrl_reg.rd.ssa_buf_free_cmd


/*-----------------------------------------------------------------------------------------------------------*/
/* 6.0 global control telegram                                                                               */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 6.1 defines for GLOBAL CONTROL                                            */
/*---------------------------------------------------------------------------*/
#define GC_OPERATE                      ((UBYTE)0x00)
#define GC_CLEAR                        ((UBYTE)0x02)

/*---------------------------------------------------------------------------*/
/* 6.2 macros for global control                                             */
/*---------------------------------------------------------------------------*/
// -- read Global-Control-Command ---------------------------------------------
#define VPC3_GET_GC_COMMAND() p_Vpc3->gc_command


/*-----------------------------------------------------------------------------------------------------------*/
/* 7.0 diagnostic telegram                                                                                   */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 7.1 defines                                                               */
/*---------------------------------------------------------------------------*/
#define EXT_DIAG_RESET                  ((UBYTE)0x00)
#define EXT_DIAG_SET                    ((UBYTE)0x01)
#define STAT_DIAG_RESET                 ((UBYTE)0x00)
#define STAT_DIAG_SET                   ((UBYTE)0x02)
#define EXT_STAT_DIAG_SET               ((UBYTE)0x03)
#define DIAG_WAIT_FOR_ALARM             ((UBYTE)0x80)

#define DIAG_REV_SIGN                   ((UBYTE)0xC0)
#define DIAG_KEN_SIGN                   ((UBYTE)0x40)
#define DIAG_CHN_SIGN                   ((UBYTE)0x80)
#define DIAG_DEV_SIGN                   ((UBYTE)0x00)

#define DIAG_TYPE_MASK                  ((UBYTE)0xC0)
#define DIAG_TYPE_DEV                   ((UBYTE)0x00)
#define DIAG_TYPE_KEN                   ((UBYTE)0x40)
#define DIAG_TYPE_CHN                   ((UBYTE)0x80)
#define DIAG_TYPE_REV                   ((UBYTE)0xC0)

#define DIAG_NORM_DIAG_SIZE             ((UBYTE)0x06)
#define DIAG_TYPE_CHN_SIZE              ((UBYTE)0x03)
#define DIAG_TYPE_REV_SIZE              ((UBYTE)0x01)

#define STATUS_DIAG_HEAD_SIZE           ((UBYTE)0x04)
#define STATUS_TYPE_SIGN                ((UBYTE)0x80)
#define STATUS_TYPE_STATUS_MESSAGE      ((UBYTE)0x01)
#define STATUS_TYPE_MODUL_STATUS        ((UBYTE)0x02)
#define STATUS_TYPE_PRM_COMMAND_ACK     ((UBYTE)0x1E)
#define STATUS_TYPE_H_STATUS_MESSAGE    ((UBYTE)0x1F)
#define STATUS_TYPE_MANU_MIN            ((UBYTE)0x20)
#define STATUS_TYPE_MANU_MAX            ((UBYTE)0x7E)

#define ALARM_TYPE_SIGN                 ((UBYTE)0x00)
#define ALARM_DIAG_HEAD_SIZE            ((UBYTE)0x04)

/*---------------------------------------------------------------------------*/
/* 7.2 structures                                                            */
/*---------------------------------------------------------------------------*/
// -- revision diagnosis data -------------------------------------------------
typedef struct
{
    UBYTE   sign_revision;
} STRUC_REV_DIAG;

// -- slot signed diagnosis data ----------------------------------------------
typedef struct
{
    UBYTE   sign_len;
    UBYTE   slots[1];
} STRUC_KEN_DIAG;

//defines for channel related diagnostic
//        MSB                         LSB
//       +---+---+---+---+---+---+---+---+
//Bit-No | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//       +---+---+---+---+---+---+---+---+
//         |   |   |   |   |   |   |   |    meaning:
//         |   |   |   |   |   |   |   |
//         |   |   |   +---+---+---+---+--- error type
//         |   |   |
//         +---+---+----------------------- channel type

//channel type of statuscode
#define STATUS_1BIT                     ((UBYTE)0x20)
#define STATUS_2BIT                     ((UBYTE)0x40)
#define STATUS_4BIT                     ((UBYTE)0x60)
#define STATUS_BYTE                     ((UBYTE)0x80)
#define STATUS_WORD                     ((UBYTE)0xA0)
#define STATUS_DWORD                    ((UBYTE)0xC0)

//error type of statuscode (PROFIBUS NORM)
#define STATUS_SHORT_CIRCUIT            ((UBYTE)0x01)
#define STATUS_UNDERVOLTAGE             ((UBYTE)0x02)
#define STATUS_OVERVOLTAGE              ((UBYTE)0x03)
#define STATUS_OVERLOAD                 ((UBYTE)0x04)
#define STATUS_OVERTEMPERATURE          ((UBYTE)0x05)
#define STATUS_LINE_BREAK               ((UBYTE)0x06)
#define STATUS_UPPER_LIMIT_VALUE        ((UBYTE)0x07)
#define STATUS_LOWER_LIMIT_VALUE        ((UBYTE)0x08)
#define STATUS_ERROR                    ((UBYTE)0x09)
#define STATUS_RESERVED_10              ((UBYTE)0x0A)
#define STATUS_RESERVED_11              ((UBYTE)0x0B)
#define STATUS_RESERVED_12              ((UBYTE)0x0C)
#define STATUS_RESERVED_13              ((UBYTE)0x0D)
#define STATUS_RESERVED_14              ((UBYTE)0x0E)
#define STATUS_RESERVED_15              ((UBYTE)0x0F)

//manufacturer specific between 16 and 31
//Siemens Error Codes
#define STATUS_PRM_ERROR                ((UBYTE)0x10)
#define STATUS_VOLTAGE                  ((UBYTE)0x11)
#define STATUS_FUSE_ERROR               ((UBYTE)0x12)
#define STATUS_GND_ERROR                ((UBYTE)0x13)
#define STATUS_REF_ERROR                ((UBYTE)0x14)
#define STATUS_UNKNOWN_ERROR            ((UBYTE)0x1B)

//defines for channel number in/out
#define CH_NUMBER_INOUT                 ((UBYTE)0xC0)
#define CH_NUMBER_OUT                   ((UBYTE)0x80)
#define CH_NUMBER_IN                    ((UBYTE)0x40)

// -- channel diagnosis data --------------------------------------------------
typedef struct
{
    UBYTE   sign_ident;
    UBYTE   number;
    UBYTE   status_code;
} STRUC_CHN_DIAG;

// -- device diagnosis data ---------------------------------------------------
typedef struct
{
    UBYTE   sign_len;
    UBYTE   user_data[9];
} STRUC_DEV_DIAG;

// -- status message data (coded as device diagnosis (see above) --------------
typedef struct
{
    UBYTE   sign_len;           // equal to DIAG_DEV_SIGN
    UBYTE   status_type;
    UBYTE   slot_number;
    UBYTE   specifier;
    UBYTE   user_data;
} STRUC_STATUS_DIAG;

// alarm data (coded as device diagnosis (see above) --------------------------
typedef struct
{
    UBYTE   sign_len;           // equal to DIAG_DEV_SIGN */
    UBYTE   alarm_type;
    UBYTE   slot_number;
    UBYTE   specifier;
    UBYTE   user_data;
} STRUC_ALARM_DIAG;

typedef union
{
    STRUC_REV_DIAG     rev;
    STRUC_KEN_DIAG     ken;
    STRUC_CHN_DIAG     chn;
    STRUC_DEV_DIAG     dev;
    STRUC_STATUS_DIAG  status;
    STRUC_ALARM_DIAG   alarm;
} UNION_DIAG;
#define VPC3_DIAG_PTR   UNION_DIAG PTR_ATTR *

//typedef union
//{
////    VPC3_DIAG_PTR       struc_ptr;
////    VPC3_UNSIGNED8_PTR  byte_ptr;

//} VPC3_UNION_DIAG_PTR;

/*---------------------------------------------------------------------------*/
/* 7.3 macros                                                                */
/*---------------------------------------------------------------------------*/
// get pointer to diag-buffers ----------------------------------------------
#define VPC3_GET_DIAG1_PTR() (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->diag_buf_ptr[0] << SEG_MULDIV)+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
#define VPC3_GET_DIAG2_PTR() (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->diag_buf_ptr[1] << SEG_MULDIV)+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
//-- Control diagnostics buffer ------------
#define VPC3_GET_DIAG_FLAG()  (p_Vpc3->isreg.rd.status_L & VPC3_DIAG_FLAG)


/*-----------------------------------------------------------------------------------------------------------*/
/* 8.0 subscriber                                                                                            */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 8.1 structures                                                            */
/*---------------------------------------------------------------------------*/
typedef struct
{
    UBYTE       publisher_addr;
    UBYTE       link_status;
} DXB_STATUS;

typedef struct
{
    UBYTE       header;
    UBYTE       status_type;
    UBYTE       slot_number;
    UBYTE       status_specifier;
//    DXB_STATUS  link_status[MAX_LINK_SUPPORTED];
} VPC3_DXB_LINK_STATUS;
#define VPC3_DXB_LINK_STATUS_PTR  VPC3_DXB_LINK_STATUS PTR_ATTR *

typedef struct
{
    UBYTE       publisher_addr;
    UBYTE       publisher_length;
    UBYTE       sample_offset;
    UBYTE       sample_length;
} DXB_LINK_TABLE;

//typedef struct
//{
////    DXB_LINK_TABLE  link_table_entry[MAX_LINK_SUPPORTED];
//} VPC3_DXB_LINK_TABLE;
#define VPC3_DXB_LINK_TABLE_PTR  VPC3_DXB_LINK_TABLE PTR_ATTR *

typedef struct
{
    UBYTE       publisher_addr;
    UBYTE       publisher_length;
    UBYTE       sample_offset;
    UBYTE       dest_slot_number;
    UBYTE       offset_data_area;
    UBYTE       sample_length;
} DXB_SUBSCRIBER_TABLE;

typedef struct
{
    UBYTE                   version;
//    DXB_LINK_TABLE          link_table_entry[MAX_LINK_SUPPORTED];
} PRM_DXB_LINK_TABLE;
#define PRM_DXB_LINK_TABLE_PTR  PRM_DXB_LINK_TABLE PTR_ATTR *

typedef struct
{
    UBYTE                   version;
//    DXB_SUBSCRIBER_TABLE    subscriber_table_entry[MAX_LINK_SUPPORTED];
} PRM_SUBSCRIBER_TABLE;
#define PRM_SUBSCRIBER_TABLE_PTR  PRM_SUBSCRIBER_TABLE PTR_ATTR *

typedef struct
{
    UBYTE       publisher_addr;
    UBYTE       sample_length;
    UBYTE       sample_data;
} VPC3_DXB_OUT;
#define VPC3_DXB_OUT_PTR  VPC3_DXB_OUT PTR_ATTR *


/*---------------------------------------------------------------------------*/
/* 8.2 macros                                                                */
/*---------------------------------------------------------------------------*/
#define VPC3_GET_DXB_LINK_STATUS_BUF_PTR()  (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->dxb_link_status_buf_ptr << SEG_MULDIV)+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
#define VPC3_GET_DXB_LINK_STATUS_LEN()      p_Vpc3->len_dxb_link_status_buf
#define VPC3_SET_DXB_LINK_STATUS_LEN(value) p_Vpc3->len_dxb_link_status_buf = value

#define VPC3_GET_DXB_LINK_TABLE_BUF_PTR()   (VPC3_UNSIGNED8_PTR)(((VPC3_ADR)(p_Vpc3->dxb_link_table_buf_ptr << SEG_MULDIV)+((VPC3_ADR)VPC3_ASIC_ADDRESS)))
#define VPC3_GET_DXB_LINK_TABLE_LEN()       p_Vpc3->len_dxb_link_table_buf
#define VPC3_SET_DXB_LINK_TABLE_LEN(value)  p_Vpc3->len_dxb_link_table_buf = value


/*-----------------------------------------------------------------------------------------------------------*/
/* 9.0 isochron mode                                                                                         */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 9.2 defines                                                               */
/*---------------------------------------------------------------------------*/
#define PLL_OFFLINE                     ((UBYTE)0x01)
#define PLL_WAIT_SYNCH                  ((UBYTE)0x02)
#define PLL_WAIT_DELAY                  ((UBYTE)0x04)
#define PLL_RUN                         ((UBYTE)0x08)
#define PLL_RUN_PLL                     ((UBYTE)0x10)

/*---------------------------------------------------------------------------*/
/* 9.2 structures                                                            */
/*---------------------------------------------------------------------------*/
typedef struct
{
//    ULONG   T_BASE_DP;
    UWORD   T_DP;
    UBYTE   T_MAPC;
//    ULONG   T_BASE_IO;
    UWORD   T_I;
    UWORD   T_O;
//    ULONG   T_DX;
    UWORD   T_PLL_W;
    UWORD   T_PLL_D;
} T_ISOCHRON;


/*-----------------------------------------------------------------------------------------------------------*/
/* 10.0 fdl layer                                                                                            */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 10.1 SAPs (service access points) for MSAC1                               */
/*---------------------------------------------------------------------------*/
#define DP_C1_ALARM_SAP_NR              ((UBYTE)0x32)
#define DP_C1_RD_WR_SAP_NR              ((UBYTE)0x33)

/*---------------------------------------------------------------------------*/
/* 10.2 SAPs (service access points) for MSAC2                               */
/*---------------------------------------------------------------------------*/
#define MSAC_C2_MAX_INPUT_ITEMS         ((UBYTE)((2*DP_C2_NUM_SAPS)+1)) // number of elements in the input queue
#define MSAC_C2_SAP_NR_LOW              ((UBYTE)0x00)                   // lowest possible SAP for MSAC_C2
#define MSAC_C2_SAP_NR_HIGH             ((UBYTE)0x30)                   // highest possible SAP for MSAC_C2 (dp_mode =1)

/*---------------------------------------------------------------------------*/
/* 10.3 structure of a FDL-indication-response-buffer-head                   */
/*---------------------------------------------------------------------------*/
// -- defines for buffer-control-byte ----------------------------------------
#define PCNTRL_USER                     ((UBYTE)0x80)  // 1: buffer in user
#define PCNTRL_IND                      ((UBYTE)0x40)  // 1: indication occured
#define PCNTRL_RESP                     ((UBYTE)0x20)  // 1: response provided
#define PCNTRL_INUSE                    ((UBYTE)0x10)  // 1: buffer in use

// -- structure of a FDL-indication-response-buffer-head ---------------------
typedef struct
{
    UBYTE cntrl;        // buffer-control
    UBYTE max_len;      // max ind-buffer-length
    UBYTE len;          // actual ind-response-length
    UBYTE fc;           // ind-response-function-code
} FDL_BUF_HEAD;
#define FDL_BUF_HEAD_PTR FDL_BUF_HEAD PTR_ATTR *
#define sizeof_FDL_BUF_HEAD             ((UBYTE)0x04)

/*---------------------------------------------------------------------------*/
/* 10.4 structure of a FDL-sap-entry                                         */
/*---------------------------------------------------------------------------*/
typedef struct
{
    UBYTE  resp_s__sap_nr;
    UBYTE  req_sa;
    UBYTE  access__req_ssap;
    UBYTE  event__serv_sup;
    UBYTE  ind_ptr[2];
    UBYTE  resp_ptr;
} FDL_SAP_CNTRL;
#define FDL_SAP_CNTRL_PTR FDL_SAP_CNTRL PTR_ATTR *
#define sizeof_FDL_SAP_CNTRL   ((UBYTE)0x07)

/*---------------------------------------------------------------------------*/
/* 10.5 structure of a sap-control-block                                     */
/*---------------------------------------------------------------------------*/
// -- defines for FDL SAP TYPE -----------------------------------------------
typedef enum
{
    FDL_RM_SAP      = ((UBYTE)0x00),
    FDL_MSAC_C1_SAP = ((UBYTE)0x01),
    FDL_MSAC_C2_SAP = ((UBYTE)0x02)
} FDL_SAP_TYPE;

// -- defines for FDL STATE --------------------------------------------------
typedef enum
{
    ENABLED          =  ((UBYTE)0x00),
    DIS_RUNNING      =  ((UBYTE)0x01),
    DISABLED         =  ((UBYTE)0x02),
    DISABLED_FOR_RM  =  ((UBYTE)0x03),
    DISABLED_IN_RM   =  ((UBYTE)0x04)
} FDL_STATE;

typedef struct
{
//    FDL_BUF_HEAD_PTR  ind_ptr[2];       // ind-buffer-address uP-formatted
 //   FDL_BUF_HEAD_PTR  resp_ptr;         // resp-buffer-address uP-formatted

//    FDL_SAP_CNTRL_PTR sap_ptr;          // pointer to VPC3-SAP uP-formatted
//    FDL_SAP_CNTRL     sap;              // content of VPC3-sap

    UBYTE             vpc3_ind_ptr[2];  // ind-buffer-address VPC3-formatted
    FDL_STATE         state;

    UBYTE             sap_nr;
    UBYTE             req_ssap;
    FDL_SAP_TYPE      sap_type;
    UBYTE             ind_buf_len;
    UBYTE             resp_buf_len;
    UBYTE             serv_sup;
    UBYTE             req_sa;
} FDL_SAP_HEADER;


/*---------------------------------------------------------------------------*/
/* 10.6 structure of a indication- or response-buffer                        */
/*---------------------------------------------------------------------------*/
typedef struct
{
    UBYTE data_len;       // length of netto-data
    UBYTE fc;             // function-code
    UBYTE user_data[246]; // netto-data
} IND_RESP_BUF;
#define IND_RESP_BUF_PTR        IND_RESP_BUF PTR_ATTR *
#define MSAC_C2_DATA_BUF        IND_RESP_BUF
#define MSAC_C2_DATA_BUF_PTR    MSAC_C2_DATA_BUF PTR_ATTR *

/*---------------------------------------------------------------------------*/
/* 10.7 structure of the immediate-response-pdu of the FDL-RM-SAP            */
/*---------------------------------------------------------------------------*/
typedef struct
{
    UBYTE opcode;
    UBYTE sap_nr;
    UBYTE poll_to_high;
    UBYTE poll_to_low;
} rm_answer;

/*---------------------------------------------------------------------------*/
/* 10.8 global structure of FDL state machine                                */
/*---------------------------------------------------------------------------*/
// -- defines for resource manager state -------------------------------------
typedef enum
{
    RM_LOCKED       = ((UBYTE)0x01),    // do not treat rm-sap (channel not opened)
    RM_LOADABLE     = ((UBYTE)0x02),    // load rm-sap (immediate response was sent or channel was opened)
    RM_LOADED       = ((UBYTE)0x03)     // do not load rm-sap (immediate-response not sent yet)
} FDL_RM_STATE;


#define FDL_RM_BUF_LENGTH           ((UBYTE)0x04)
#define FDL_DPV2_SEC_BUF_LENGTH     ((UBYTE)0x04)

/*---------------------------------------------------------------------------*/
/* 10.9 function-codes                                                       */
/*---------------------------------------------------------------------------*/
#define SS_ALL                      ((UBYTE)0x00)
#define SS_SDN_L                    ((UBYTE)0x01)
#define SS_SDN_H                    ((UBYTE)0x02)
#define SS_SDN_LH                   ((UBYTE)0x03)
#define SS_SDN_SRD_LH               ((UBYTE)0x04)
#define SS_SDA_L                    ((UBYTE)0x05)
#define SS_SDA_H                    ((UBYTE)0x06)
#define SS_SDA_LH                   ((UBYTE)0x07)
#define SS_SRD_DDB                  ((UBYTE)0x08)
#define SS_SRD_L                    ((UBYTE)0x09)
#define SS_SRD_H                    ((UBYTE)0x0A)
#define SS_SRD_LH                   ((UBYTE)0x0B)
#define SS_DDB_REQ                  ((UBYTE)0x0C)
#define SS_DDB_RES_L                ((UBYTE)0x0D)
#define SS_DDB_RES_H                ((UBYTE)0x0E)
#define SS_DDB_RES_LH               ((UBYTE)0x0F)

#define FC_RESP_L                   ((UBYTE)0x08)
#define FC_RESP_H                   ((UBYTE)0x0A)

#define DEFAULT_SAP                 ((UBYTE)0x40)
#define SAP_ALL                     ((UBYTE)0x7F)
#define SA_ALL                      ((UBYTE)0x7F)

/*---------------------------------------------------------------------------*/
/* 10.A returncodes of FDL-services                                          */
/*---------------------------------------------------------------------------*/
#define FDL_OK                      ((UBYTE)0x00)
#define FDL_SNI                     ((UBYTE)0x01)
#define FDL_IUSE                    ((UBYTE)0x02)
#define FDL_IVP                     ((UBYTE)0x03)
#define FDL_ACT                     ((UBYTE)0x04)
#define FDL_DACT                    ((UBYTE)0x05)
#define FDL_SND                     ((UBYTE)0x06)
#define FDL_NUIB                    ((UBYTE)0x07)
#define FDL_UBLEN                   ((UBYTE)0x08)
#define FDL_FPTR                    ((UBYTE)0x09)
#define FDL_NRB                     ((UBYTE)0x0A)
#define FDL_NURB                    ((UBYTE)0x0B)
#define FDL_SBNI                    ((UBYTE)0x0C)
#define FDL_RLEN                    ((UBYTE)0x0D)
#define FDL_SBUF                    ((UBYTE)0x0E)
#define FDL_SDA                     ((UBYTE)0x0F)
#define FDL_NRD                     ((UBYTE)0x40)
#define FDL_OPEN_ERR                ((UBYTE)0xAA)
#define FDL_CLOSE_ERR               ((UBYTE)0xAB)

#define FDL_RR                      ((UBYTE)0x10)    // do not change
#define FDL_RS                      ((UBYTE)0x20)    // do not change

#define FDL_PRIMARY_BUF             ((UBYTE)0x01)
#define FDL_SECONDARY_BUF           ((UBYTE)0x02)

/*---------------------------------------------------------------------------*/
/* 10.B helpful macros                                                       */
/*---------------------------------------------------------------------------*/
#define _INIT_FDL_BUF_HEAD(FDL_PTR, LEN)                                \
{                                                                       \
  (FDL_PTR)->cntrl   = 0;                                               \
  (FDL_PTR)->len     = 0;                                               \
  (FDL_PTR)->fc      = 0;                                               \
  (FDL_PTR)->max_len = (LEN);                                           \
}//#define _INIT_FDL_BUF_HEAD(FDL_PTR, LEN)

#define copy_sap_parameter__(_dest, _src)                               \
{                                                                       \
  FDL_SAP_CNTRL PTR_ATTR * dest = (_dest);                              \
  FDL_SAP_CNTRL PTR_ATTR * src =  (_src);                               \
                                                                        \
  dest->resp_s__sap_nr    =  src->resp_s__sap_nr;                       \
  dest->req_sa            =  src->req_sa;                               \
  dest->access__req_ssap  =  src->access__req_ssap;                     \
  dest->event__serv_sup   =  src->event__serv_sup;                      \
  dest->ind_ptr[0]        =  src->ind_ptr[0];                           \
  dest->ind_ptr[1]        =  src->ind_ptr[1];                           \
  dest->resp_ptr          =  src->resp_ptr;                             \
}//#define copy_sap_parameter__(_dest, _src)

#define incr_vpc3_up_ptr__(_buf_size)                                   \
{                                                                       \
  vpc3_seg_adr += (UBYTE)((_buf_size)>>SEG_MULDIV);                     \
  vpc3_ptr = &vpc3_ptr[(_buf_size)];                                    \
}//#define incr_vpc3_up_ptr__(_buf_size)

#define SWAP_WORD(w) ((((w)&0x00ff)*0x100) + (((w)>>8)&0x00ff))


/*-----------------------------------------------------------------------------------------------------------*/
/* 11.0 DPV1                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* 11.1 return codes for DPV1 services                                       */
/*---------------------------------------------------------------------------*/
typedef enum
{
    DPV1_OK     = ((UBYTE)0x00),      //must be the same as for return no_error
    DPV1_NOK    = ((UBYTE)0x81),      //negative response
    DPV1_DELAY  = ((UBYTE)0x82),      //user give pdu later back
    DPV1_ABORT  = ((UBYTE)0x83)       //user want abort the connection
} DPV1_RET_VAL;

/*----------------------------------------------------------------------------*/
/* 11.2 errorcodes of DPV1 for ERROR_DECODE                                   */
/*----------------------------------------------------------------------------*/
#define DPV1_ERRDC_DPV1                 ((UBYTE)0x80) // Error_decode, DPV1 fixed value
#define DPV1_ERRDC_FMS                  ((UBYTE)0xFE) // Error_decode, FMS  fixed value
#define DPV1_ERRDC_HART                 ((UBYTE)0xFF) // Error_decode, HART fixed value

/*----------------------------------------------------------------------------*/
/* 11.3 errorcodes of DPV1 for ERROR_CODE_1                                   */
/*----------------------------------------------------------------------------*/
// error_class
#define DPV1_ERRCL_APPLICATION          ((UBYTE)0xA0)
#define DPV1_ERRCL_ACCESS               ((UBYTE)0xB0)
#define DPV1_ERRCL_RESSOURCE            ((UBYTE)0xC0)
#define DPV1_ERRCL_USER                 ((UBYTE)0xD0)
// error_code for  DPV1_ERRCL_APPLICATION
#define DPV1_ERRCL_APP_READ             ((UBYTE)0x00)
#define DPV1_ERRCL_APP_WRITE            ((UBYTE)0x01)
#define DPV1_ERRCL_APP_MODULE           ((UBYTE)0x02)
#define DPV1_ERRCL_APP_VERSION          ((UBYTE)0x08)
#define DPV1_ERRCL_APP_NOTSUPP          ((UBYTE)0x09)
#define DPV1_ERRCL_APP_USER             ((UBYTE)0x0A)
// error_code for  DPV1_ERRCL_ACCESS
#define DPV1_ERRCL_ACC_INV_INDEX        ((UBYTE)0x00)
#define DPV1_ERRCL_ACC_WRITE_LEN        ((UBYTE)0x01)
#define DPV1_ERRCL_ACC_INV_SLOT         ((UBYTE)0x02)
#define DPV1_ERRCL_ACC_TYPE             ((UBYTE)0x03)
#define DPV1_ERRCL_ACC_INV_AREA         ((UBYTE)0x04)
#define DPV1_ERRCL_ACC_STATE            ((UBYTE)0x05)
#define DPV1_ERRCL_ACC_ACCESS           ((UBYTE)0x06)
#define DPV1_ERRCL_ACC_INV_RANGE        ((UBYTE)0x07)
#define DPV1_ERRCL_ACC_INV_PARAM        ((UBYTE)0x08)
#define DPV1_ERRCL_ACC_INV_TYPE         ((UBYTE)0x09)
#define DPV1_ERRCL_ACC_USER             ((UBYTE)0x0A)
// error_code for  DPV1_ERRCL_RESOURCE
#define DPV1_ERRCL_RES_READ_CONSTRAIN   ((UBYTE)0x00)
#define DPV1_ERRCL_RES_WRITE_CONSTRAIN  ((UBYTE)0x01)
#define DPV1_ERRCL_RES_BUSY             ((UBYTE)0x02)
#define DPV1_ERRCL_RES_UNAVAIL          ((UBYTE)0x03)
#define DPV1_ERRCL_RES_USER             ((UBYTE)0x08)
// error_code for  msac_c1_transmit_delay
#define DPV1_NO_VALID_SAP               ((UBYTE)0x01)
#define DPV1_ERR_INV_PARAM              ((UBYTE)0x02)
#define DPV1_ERR_NO_JOB                 ((UBYTE)0x03)

/*----------------------------------------------------------------------------*/
/* 11.4 coding of abort                                                       */
/*----------------------------------------------------------------------------*/
/* subnet */
#define MSAC_C2_SUBNET_NO               ((UBYTE)0x00)
#define MSAC_C2_SUBNET_LOCAL            ((UBYTE)0x01)
#define MSAC_C2_SUBNET_REMOTE           ((UBYTE)0x02)
/* instance */
#define MSAC_C2_INSTANCE_FDL            ((UBYTE)0x00)
#define MSAC_C2_INSTANCE_MSAC_C2        ((UBYTE)0x10)
#define MSAC_C2_INSTANCE_USER           ((UBYTE)0x20)
#define MSAC_C2_INSTANCE_RESERVED       ((UBYTE)0x30)
/* reason */
#define MSAC_C2_ABT_SE                  ((UBYTE)0x01)   // sequence error
#define MSAC_C2_ABT_FE                  ((UBYTE)0x02)   // invalid request PDU received
#define MSAC_C2_ABT_TO                  ((UBYTE)0x03)   // timeout of the connection
#define MSAC_C2_ABT_RE                  ((UBYTE)0x04)   // invalid response PDU received
#define MSAC_C2_ABT_IV                  ((UBYTE)0x05)   // invalid service from USER
#define MSAC_C2_ABT_STO                 ((UBYTE)0x06)   // Send_Timeout requested was too small
#define MSAC_C2_ABT_IA                  ((UBYTE)0x07)   // invalid additional address information
#define MSAC_C2_ABT_OC                  ((UBYTE)0x08)   // waiting for FDL_DATA_REPLY.con
#define MSAC_C2_ABT_RES                 ((UBYTE)0x0F)   // resource error

/*----------------------------------------------------------------------------*/
/* 11.5 Function Codes for DPV1                                               */
/*----------------------------------------------------------------------------*/
#define DPV1_FC_ERROR                   ((UBYTE)0x80)
#define DPV1_FC_INITIATE                ((UBYTE)0x57)
#define DPV1_FC_ABORT                   ((UBYTE)0x58)
#define DPV1_FC_READ                    ((UBYTE)0x5E)
#define DPV1_FC_WRITE                   ((UBYTE)0x5F)
#define DPV1_FC_ALARM_ACK               ((UBYTE)0x5C)
#define DPV1_FC_IDLE                    ((UBYTE)0x48)
#define DPV1_FC_TRANSPORT               ((UBYTE)0x51)
#define DPV1_FC_RM                      ((UBYTE)0x56)
// mask for function code
#define MSAC_C2_FN_MASK                 ((UBYTE)0x1F)
#define MSAC_C2_FN_CONNECT              ((UBYTE)0x17)
#define MSAC_C2_FN_DATA                 ((UBYTE)0x11)
#define MSAC_C2_FN_DISCONNECT           ((UBYTE)0x18)
#define MSAC_C2_FN_IDLE                 ((UBYTE)0x08)
#define MSAC_C2_FN_DS_READ              ((UBYTE)0x1E)
#define MSAC_C2_FN_DS_WRITE             ((UBYTE)0x1F)

/*----------------------------------------------------------------------------*/
/* 11.6 general defines for DPV1                                              */
/*----------------------------------------------------------------------------*/
#define MSAC_C2_TIMEOUT_12MBAUD         ((UWORD)0x0064)
#define MSAC_C2_TIMEOUT_6MBAUD          ((UWORD)0x0064)
#define MSAC_C2_TIMEOUT_3MBAUD          ((UWORD)0x0064)
#define MSAC_C2_TIMEOUT_1_5MBAUD        ((UWORD)0x0064)
#define MSAC_C2_TIMEOUT_500KBAUD        ((UWORD)0x00C8)
#define MSAC_C2_TIMEOUT_187_50KBAUD     ((UWORD)0x0190)

#define MSAC_C2_MIN_POLL_TIMEOUT        ((UWORD)0x0001)
#define MSAC_C2_MAX_POLL_TIMEOUT        ((UWORD)0x7FFF)

#define MSAC_C2_MIN_PDU_LEN             ((UBYTE)0x04)
#define MSAC_C2_LEN_DISCONNECT_PDU      ((UBYTE)0x04)
#define MSAC_C2_LEN_IDLE_PDU            ((UBYTE)0x02)
#define MSAC_C2_LEN_RESSOURCE_PDU       ((UBYTE)0x04)
#define MSAC_C2_MIN_CC_PDU_SIZE         ((UBYTE)0x10)
#define MSAC_C2_MAX_PDU_SIZE            ((UBYTE)0xF0)
#define MSAC_C2_MIN_CR_PDU_SIZE         ((UBYTE)0x14)

#define MSAC_C2_MAX_PDU                 ((UBYTE)0xF4)   // PDU with DPV1-Header (4Byte) + 240 User Data
#define MSAC_C2_LEN_INITIATE_RES_HEAD   ((UBYTE)0x0C)   // Initiate response, no addr_data[]
#define DPV1_LEN_NEG_RESPONSE           ((UBYTE)0x04)   // Negative Response PDU
#define DPV1_LEN_HEAD_DATA              ((UBYTE)0x04)   // Fct,Slot,Index,Len

#define MSAC_C2_FUNCTION_NUM_EXTENSION  ((UBYTE)0x40)
#define MSAC_C2_ERROR_FRAME             ((UBYTE)0xC0)
#define DPV1_ERROR_BIT_RESPONSE         ((UBYTE)0x80)

#define MSAC_C2_IND_RECV                ((UBYTE)0x01)   // indication receive
#define MSAC_C2_RESP_SENT               ((UBYTE)0x02)   // response sent
#define MSAC_C2_IND_DISABLE_DONE        ((UBYTE)0x10)   // ind_disable_done

#define MSAC_C2_FC_SRD_L                ((UBYTE)0x0C)
#define VPC3_MSAC_C1_CLOSE_FAILED       ((UBYTE)0x90)

typedef enum
{
    MSAC_C2_RESP_DIRECTION = ((UBYTE)0x01),
    MSAC_C2_REQ_DIRECTION  = ((UBYTE)0x02)
} MSAC2_DIRECTION;

/*----------------------------------------------------------------------------*/
/* 11.7 structures for DPV1                                                   */
/*----------------------------------------------------------------------------*/
typedef struct
{
    UBYTE function_num;
    UBYTE slot_num;
    UBYTE index;
    UBYTE length;
    UBYTE pdu_data[1];
}DPV1_PDU;

typedef struct
{
    UBYTE function_num;
    UBYTE slot_num;
    UBYTE index;
    UBYTE length;
    UBYTE pdu_data[1];
}DPV1_READ_PDU;

typedef struct
{
    UBYTE function_num;
    UBYTE slot_num;
    UBYTE index;
    UBYTE length;
    UBYTE pdu_data[1];
}DPV1_WRITE_PDU;

typedef struct
{
    UBYTE function_num;
    UBYTE err_decode;
    UBYTE err_code1;
    UBYTE err_code2;
}DPV1_NEG_RES_PDU;

typedef struct _MSAC_C2_TRANSPORT_PDU
{
    UBYTE  function_num;
    UBYTE  slot_num;
    UBYTE  index;
    UBYTE  length;
    UBYTE  pdu_data[1];
}MSAC_C2_TRANSPORT_PDU;

typedef struct
{
    UBYTE  function_num;
    UBYTE  reserved1;
    UBYTE  reserved2;
    UBYTE  reserved3;
    UWORD  send_timeout;
    UBYTE  features_supported1;
    UBYTE  features_supported2;
    UBYTE  profile_features_supported1;
    UBYTE  profile_features_supported2;
    UWORD  profile_ident_nummer;
    UBYTE  s_type;
    UBYTE  s_len;
    UBYTE  d_type;
    UBYTE  d_len;
    UBYTE  addr_data[20];  /* len is defined by S_len or D_len !! */
}MSAC_C2_INITIATE_REQ_PDU;
#define MSAC_C2_INITIATE_REQ_PDU_PTR   MSAC_C2_INITIATE_REQ_PDU PTR_ATTR *

typedef struct _MSAC_C2_INITIATE_SUB_PARAM
{
    UBYTE  api;
    UBYTE  reserved;
    UBYTE  net_addr[6];
    UBYTE  mac_addr[1]; /* len is defined by S_len or D_len !! */
}MSAC_C2_INITIATE_SUB_PARAM;

typedef struct _MSAC_C2_INITIATE_RES_PDU
{
    UBYTE  function_num;
    UBYTE  max_len_data_unit;
    UBYTE  features_supported1;
    UBYTE  features_supported2;
    UBYTE  profile_features_supported1;
    UBYTE  profile_features_supported2;
    UWORD  profile_ident_nummer;
    UBYTE  s_type;
    UBYTE  s_len;
    UBYTE  d_type;
    UBYTE  d_len;
    UBYTE  addr_data[1]; /* len is defined by S_len and D_len !! */
}MSAC_C2_INITIATE_RES_PDU;

typedef struct _MSAC_C2_ABORT_PDU
{
    UBYTE  function_num;
    UBYTE  subnet;
    UBYTE  instance_reason;
    UBYTE  reserved; /* MSAC_C2 + 1 Byte, no additional Detail */
}MSAC_C2_ABORT_PDU;

typedef struct
{
    UBYTE function_num;
    UBYTE slot_num;
    UBYTE alarm_type;
    UBYTE specifier;
}MSAC_C1_ALARM_ACK_PDU;
#define ALARM_ACK_REQ_PTR MSAC_C1_ALARM_ACK_PDU PTR_ATTR *

typedef union
{
    UBYTE                     ubyte_ptr;
    DPV1_READ_PDU             read;
    DPV1_WRITE_PDU            write;
    MSAC_C1_ALARM_ACK_PDU     alarm;
    MSAC_C2_TRANSPORT_PDU     transport;
    MSAC_C2_INITIATE_REQ_PDU  initiate_req;
    MSAC_C2_ABORT_PDU         abort;
    MSAC_C2_INITIATE_RES_PDU  initiate_res;
    DPV1_NEG_RES_PDU          neg;
    DPV1_PDU                  response;
}DPV1_UNION_PDU;

#define DPV1_PTR   DPV1_UNION_PDU PTR_ATTR *

typedef struct
{
  UBYTE                       opcode;
  UBYTE                       reserved1;
  UWORD                       reserved2;
  UWORD                       poll_time_out;
  UWORD                       features_supported;
  UWORD                       profile_features_supported;
  UWORD                       profile_ident_number;
}MSAC_C2_CR_BUF;
#define MSAC_C2_CR_BUF_PTR            MSAC_C2_CR_BUF PTR_ATTR *

typedef struct
{
  UBYTE                       opcode;
  UBYTE                       max_pdu_size;
  UWORD                       features_supported;
  UWORD                       profile_features_supported;
  UWORD                       profile_ident_number;
}MSAC_C2_CC_BUF;
#define MSAC_C2_CC_BUF_PTR            MSAC_C2_CC_BUF PTR_ATTR *

typedef struct
{
  UBYTE                       opcode;
  UBYTE                       location;
  UBYTE                       reason_code;
  UBYTE                       reserved;
}MSAC_C2_DR_BUF;
#define MSAC_C2_DR_BUF_PTR            MSAC_C2_DR_BUF PTR_ATTR *

typedef struct
{
  UBYTE                       opcode;
  UBYTE                       slot;
  UBYTE                       index;
  UBYTE                       length;
}MSAC_C2_DE_BUF;
#define MSAC_C2_DE_BUF_PTR            MSAC_C2_DE_BUF PTR_ATTR *

typedef struct
{
  UBYTE                       opcode;
  UBYTE                       reserved;
}MSAC_C2_WAIT_BUF;
#define MSAC_C2_WAIT_BUF_PTR      MSAC_C2_WAIT_BUF PTR_ATTR *

// input queue element
typedef struct
{
//  MSAC_C2_DATA_BUF_PTR  buf_ptr;
  UBYTE                 ret_value;
  UBYTE                 sap_nr;
  UBYTE                 fdl_code;
}MSAC_C2_REC_QUEUE;
#define MSAC_C2_REC_QUEUE_PTR    MSAC_C2_REC_QUEUE PTR_ATTR *

// reserve queue for ind disable buffer
typedef struct
{
  UBYTE                 data_len;                              // length of netto-data
  UBYTE                 fc;                                    // function-code
  UBYTE                 user_data[MSAC_C2_LEN_DISCONNECT_PDU]; // netto-data
}MSAC_C2_RES_IND_QUEUE;

//defines for MSAC_C2 connection state
typedef enum
{
    MSAC_C2_CS_CLOSE_CHANNEL    = ((UBYTE)0x01),    // initialization state
    MSAC_C2_CS_AWAIT_CONNECT    = ((UBYTE)0x04),    // first state
    MSAC_C2_CS_AWAIT_IND        = ((UBYTE)0x05),    // state after successfull connect
    MSAC_C2_CS_PROVIDE_IND      = ((UBYTE)0x06),
    MSAC_C2_CS_PROVIDE_RESP     = ((UBYTE)0x07),
    MSAC_C2_CS_DISABLE_CONNECT  = ((UBYTE)0x08)
} MSAC2_CONN_STATE;

//defines for MSAC_C2 error codes
typedef enum
{
    MSAC_C2_EC_OK               = ((UBYTE)0x00),    //  without errors
    MSAC_C2_EC_USER_ERR         = ((UBYTE)0x01),    //  invalid response data
    MSAC_C2_EC_INV_S_D_LEN_ERR  = ((UBYTE)0x03),    //  S,D-len error
    MSAC_C2_EC_REQ_TIMEOUT      = ((UBYTE)0x05),    //  req_time_out
    MSAC_C2_EC_DC_BY_USER       = ((UBYTE)0x0D),    //  user response is disconnect
    MSAC_C2_EC_DC_BY_MASTER     = ((UBYTE)0x0E),    //  master request is disconnect
    MSAC_C2_EC_REMOTE_ERROR     = ((UBYTE)0x10)     //  invalid pdu from the master
} MSAC2_ERROR_CODE;

//defines for MSAC_C2 user_break
typedef enum
{
    MSAC_C2_UB_NO_BREAK         = ((UBYTE)0x00),
    MSAC_C2_UB_BREAK            = ((UBYTE)0x01)
} MSAC2_USER_BREAK;


#define MSAC_C2_CONNECT_ITEM_PTR  MSAC_C2_CONNECT_ITEM PTR_ATTR *

// -- defines for MSAC2 - Timer -----------------------------------------------------
#define MSAC_C2_TIMER_OK                ((UBYTE)10)
#define MSAC_C2_TIMER_ALREADY_STOPPED   ((UBYTE)20)
#define MSAC_C2_TIMER_ALREADY_RUNS      ((UBYTE)30)

typedef struct
{
  UWORD  time_act;
  UBYTE  running;
} MSAC_C2_TIMER;

#define MSAC_C1_IND_DS_READ             ((UBYTE)0x01)
#define MSAC_C1_IND_DS_WRITE            ((UBYTE)0x02)
#define MSAC_C1_IND_ALARM_QUIT          ((UBYTE)0x04)
#define MSAC_C1_IND_ALARM_QUIT_SAP50    ((UBYTE)0x08)

/*----------------------------------------------------------------------------*/
/* 11.8 defines for ALARM                                                     */
/*----------------------------------------------------------------------------*/
// max length of alarm-fifo
#define ALARM_MAX_FIFO                  ((UBYTE)0x20)
// defines for Status-Types
#define STATUS_MESSAGE                  ((UBYTE)0x81)
#define MODUL_STATUS                    ((UBYTE)0x82)

#define SET_ALARM_AL_STATE_CLOSED       ((UBYTE)0x01)
#define SET_ALARM_SEQ_NR_ERROR          ((UBYTE)0x02)
#define SET_ALARM_SPECIFIER_ERROR       ((UBYTE)0x03)
#define SET_ALARM_LIMIT_EXPIRED         ((UBYTE)0x04)
#define SET_ALARM_PENDING               ((UBYTE)0x05)
#define SET_ALARM_ALARMTYPE_NOTSUPP     ((UBYTE)0x06)
#define SET_ALARM_OK                    ((UBYTE)0x00)

#define SET_STATUS_NOT_ENABLED          ((UBYTE)0x01)
#define SET_STATUS_OK                   ((UBYTE)0x00)

// defines for alarm-type
#define ALARM_TYPE_MAX                  ((UBYTE)0x07)

#define ALARM_TYPE_DIAGNOSTIC           ((UBYTE)0x01)
#define ALARM_TYPE_PROCESS              ((UBYTE)0x02)
#define ALARM_TYPE_PULL                 ((UBYTE)0x03)
#define ALARM_TYPE_PLUG                 ((UBYTE)0x04)
#define ALARM_TYPE_STATUS               ((UBYTE)0x05)
#define ALARM_TYPE_UPDATE               ((UBYTE)0x06)
#define ALARM_TYPE_MANU_MIN             ((UBYTE)0x20)
#define ALARM_TYPE_MANU_MAX             ((UBYTE)0x7E)

// defines for sequence_mode
#define SEQC_MODE_TOTAL_00              ((UBYTE)0x00)
#define SEQC_MODE_OFF                   ((UBYTE)0x01)
#define SEQC_MODE_TOTAL_02              ((UBYTE)0x02)
#define SEQC_MODE_TOTAL_04              ((UBYTE)0x04)
#define SEQC_MODE_TOTAL_08              ((UBYTE)0x08)
#define SEQC_MODE_TOTAL_12              ((UBYTE)0x0C)
#define SEQC_MODE_TOTAL_16              ((UBYTE)0x10)
#define SEQC_MODE_TOTAL_24              ((UBYTE)0x18)
#define SEQC_MODE_TOTAL_32              ((UBYTE)0x20)

// defines for specifier
#define SPEC_GENERAL                    ((UBYTE)0x00)
#define SPEC_APPEARS                    ((UBYTE)0x01)
#define SPEC_DISAPPEARS                 ((UBYTE)0x02)

#define SPEC_MASK                       ((UBYTE)0x03)
#define SPEC_SEQ_START                  ((UBYTE)0x03)   //use it to shift the sequence number down to bit 0 or up to bit 3
#define MAX_SEQ_NR                      ((UBYTE)0x20)
#define SEQUENCE_NUMBER_ALL             ((UBYTE)0xFF)
#define SEQ_NR_MASK                     ((UBYTE)0xF8)

#define SPEC_ADD_ACK                    ((UBYTE)0x04)

#define szAlarmHeader                   ((UBYTE)0x04)

/*----------------------------------------------------------------------------*/
/* 11.9 structure of ALARM                                                    */
/*----------------------------------------------------------------------------*/
typedef struct
{
//  DPL_STRUC_LIST_CB list_head;

  UBYTE                 header;
  UBYTE                 type;
  UBYTE                 slot;
  UBYTE                 spec;
  UBYTE                 user_data_len;
  UBYTE                 callback;
//  VPC3_UNSIGNED8_PTR    user_data_ptr;
}ALARM_STATUS_PDU;

/*-----------------------------------------------------------------------------------------------------------*/
/* 12.0 global system structure                                                                              */
/*-----------------------------------------------------------------------------------------------------------*/
//defines for MSAC1 Operation Mode
typedef enum
{
    DP_OPMODE_V0        = ((UBYTE)0x00),
    DP_OPMODE_V1        = ((UBYTE)0x01)
} MSAC1_OPMODE;

//defines for MSAC1 Start State
typedef enum
{
    DP_SS_IDLE          = ((UBYTE)0x00),
    DP_SS_STOP          = ((UBYTE)0x01),
    DP_SS_START_AGAIN   = ((UBYTE)0x02),
    DP_SS_RUN           = ((UBYTE)0x03)
} MSAC1_START_STATE;

// -- structures --------------------------------------------------------------
typedef struct
{
    UBYTE               DX_Entered;
    UBYTE               Fdl_Closing;
    MSAC1_OPMODE        Operation_Mode;             // DP/DPV1
    UBYTE               active_Job;
    MSAC1_START_STATE   Start_State;
    UBYTE               event;
} C1_STRUC;

#define AL_STATE_CLOSED                 ((UBYTE)0x10)
#define AL_STATE_OPEN                   ((UBYTE)0x11)

#define AL_TYPE_MAX                     ((UBYTE)0x07)   // dpv1 draft specification - do not use cast !
#define AL_SEQUENCE_MAX                 ((UBYTE)0x20)   // dpv1 draft specification - do not use cast !

//defines for sequence_status
#define AL_SEQUENCE_STATUS_SIZE         ((UBYTE)(((ALARM_TYPE_MAX * MAX_SEQ_NR)+7)/8))

#define AL_ALARM_STATUS_ACTION_SET      ((UBYTE)0x11)
#define AL_ALARM_STATUS_ACTION_CHECK    ((UBYTE)0x49)
#define AL_ALARM_STATUS_ACTION_RESET    ((UBYTE)0x57)

typedef struct
{
//    DPL_STRUC_LIST_CB queue_new;
//    DPL_STRUC_LIST_CB queue_ack;

    UBYTE       state;
    UBYTE       enabled;    //DPV1_STATUS 2, indicates the type of alarms
    UBYTE       mode;       //DPV1_STATUS 3

    UBYTE       type_status;
    UBYTE       sequence_status[ AL_SEQUENCE_STATUS_SIZE ];

    UBYTE       sequence;   //FALSE: only one alarm of a specific ALARM_TYPE can be active at one time
                            //TRUE : several alarms (2 to 32) of the same or different ALARM_TYPE can be
                            //       active at one time
    UBYTE       limit;      //contains the maximum number of alarms
                            //allowed by the actual master-slave connection
    UBYTE       count;      //contains the number of alarms, which have been sent
} AL_STRUC;


/************************** Global-Control-command **************************/

  #define DPS2_GET_GC_COMMAND() spc3.r_gc_command

/******************************* User-Watchdog *******************************/

  #define DPS2_SET_USER_WD_VALUE(VALUE) spc3.r_user_wd_value = SWAP_W(VALUE);
  #define DPS2_RESET_USER_WD()  spc3.x1.w.mode_reg1_s = RES_USER_WD;

/***************************** general macros *****************************/

  #define SPC3_GET_WD_STATE() ((spc3.is_reg.status[_IML] >> 6) & 0x03)
  #define SPC3_GET_BAUD() (spc3.is_reg.status[_IMH] & 0x0f)
  #define SPC3_GET_OFF_PASS()  (spc3.is_reg.status[_IML] & SPC3_OFFLINE_PASS)
  #define SPC3_GET_ACCESS_VIOLATION()  (spc3.is_reg.status[_IML] & ACCESS_VIOLATION)
  #define SPC3_SET_BAUD_CNTRL(VAL) spc3.x1.w.wd_baud_ctrl_val = VAL;
  #define SPC3_GET_FREE_MEM(FREE_MEM) dps2_get_free_mem(FREE_MEM)
  #define DPS2_GET_DP_STATE() ((spc3.is_reg.status[_IML] >> 4) & 0x03)


typedef enum
{
    _DP_USER    = 0x10,
    _DP_IF      = 0x20,
    _DP_ISR     = 0x30,
    _DP_FDL     = 0x40,
    _DP_C1      = 0x50,
    _DP_C2      = 0x60

}   DP_ERROR_FILE;


typedef struct
{
    UBYTE                   function;
    UBYTE                   error_code;
    UWORD                   detail;
    UBYTE                   cn_id;
}   VPC3_STRUC_ERRCB;

extern VPC3_STRUC_ERRCB   vpc3_errcb;

/*-----------------------------------------------------------------------------------------------------------*/
/* 13.0 ERROR defines                                                                                        */
/*-----------------------------------------------------------------------------------------------------------*/
typedef enum
{
    DP_FATAL_ERROR                  = 0x00, // fatal error

    DP_OK                           = 0x01, // OK
    DP_NOK                          = 0x02, // OK

    DP_NOT_OFFLINE_ERROR            = 0x10, // VPC3 is not in OFFLINE state
    DP_ADDRESS_ERROR                = 0x11, // Slave Address Error
    DP_CALCULATE_IO_ERROR           = 0x12,

    DP_DOUT_LEN_ERROR               = 0x13,
    DP_DIN_LEN_ERROR                = 0x14,
    DP_DIAG_LEN_ERROR               = 0x15,
    DP_PRM_LEN_ERROR                = 0x16,
    DP_SSA_LEN_ERROR                = 0x17,
    DP_CFG_LEN_ERROR                = 0x18,
    DP_LESS_MEM_ERROR               = 0x19,
    DP_LESS_MEM_FDL_ERROR           = 0x1A,

    DP_PRM_ENTRY_ERROR              = 0x20,
    DP_PRM_DXB_MAX_LINK_ERROR       = 0x21,
    DP_PRM_DXB_ERROR                = 0x22,
    DP_CFG_ENTRY_ERROR              = 0x23,
    DP_CFG_UPDATE_ERROR             = 0x24,
    DP_PRM_DPV1_STATUS              = 0x25,
    DP_PRM_BLOCK_ERROR              = 0x26,
    DP_PRM_ALARM_ERROR              = 0x27,
    DP_PRMCMD_LEN_ERROR             = 0x28,
    DP_PRM_SOLL_IST_ERROR           = 0x29,
    DP_PRM_DXB_WD_ERROR             = 0x2A,

    DP_DIAG_BUFFER_ERROR            = 0x30,
    DP_DIAG_SEQUENCE_ERROR          = 0x31,
    DP_DIAG_OLD_DIAG_NOT_SEND_ERROR = 0x32,
    DP_DIAG_NOT_POSSIBLE_ERROR      = 0x33,
    DP_DIAG_NO_BUFFER_ERROR         = 0x34,
    DP_DIAG_BUFFER_LENGTH_ERROR     = 0x35,
    DP_DIAG_CONTROL_BYTE_ERROR      = 0x36,

    C2_DATA_LEN_ERROR               = 0x80,
    C2_DATA_POLL_TIMEOUT_ERROR      = 0x81,
    C2_DATA_SAP_ERROR               = 0x82,
    C2_NO_CONN_RESOURCE             = 0x83,
    C2_INV_LOWER_LAYER              = 0x84,
    C2_ENABLED_ERROR                = 0x85,
    C2_RESOURCE_ERROR               = 0x86,
    C2_INV_CN_ID                    = 0x87,
    C2_USER_ERR                     = 0x88,

    SSC_MAX_DATA_PER_LINK           = 0x90,

    DP_EEPROM_ERROR                 = 0xF1, // Hardware errors
    DP_VPC3_ERROR                   = 0xF4,
    DP_SRAM_ERROR                   = 0xFF

}   DP_ERROR_CODE;



#define OFFSET 0xF000




extern UBYTE *vpc3_ram;


void init_dp(void);

#endif
