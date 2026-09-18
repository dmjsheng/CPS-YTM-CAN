/*Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_EUART_H__
#define __CPS32K21X_EUART_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


    
/*------------------------------------------------------------------------------
addtogroup EUART_Register_Masks EUART Register Masks
------------------------------------------------------------------------------*/
/* PARAM Bit Fields */
#define EUART_PARAM_TXFIFO_Mask               0xFFu
#define EUART_PARAM_TXFIFO_Pos                0u
#define EUART_PARAM_TXFIFO_WIDTH              8u
#define EUART_PARAM_TXFIFO(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_PARAM_TXFIFO_Pos))&EUART_PARAM_TXFIFO_Mask)
#define EUART_PARAM_RXFIFO_Mask               0xFF00u
#define EUART_PARAM_RXFIFO_Pos                8u
#define EUART_PARAM_RXFIFO_WIDTH              8u
#define EUART_PARAM_RXFIFO(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_PARAM_RXFIFO_Pos))&EUART_PARAM_RXFIFO_Mask)
    /* GLOBAL Bit Fields */
#define EUART_GLOBAL_RST_Mask                 0x2u
#define EUART_GLOBAL_RST_Pos                  1u
#define EUART_GLOBAL_RST_WIDTH                1u
#define EUART_GLOBAL_RST(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_GLOBAL_RST_Pos))&EUART_GLOBAL_RST_Mask)
    /* PINCFG Bit Fields */
#define EUART_PINCFG_TRGSEL_Mask              0x3u
#define EUART_PINCFG_TRGSEL_Pos               0u
#define EUART_PINCFG_TRGSEL_WIDTH             2u
#define EUART_PINCFG_TRGSEL(x)                (((uint32_t)(((uint32_t)(x))<<EUART_PINCFG_TRGSEL_Pos))&EUART_PINCFG_TRGSEL_Mask)
    /* BAUD Bit Fields */
#define EUART_BAUD_SBR_Mask                   0x1FFFu
#define EUART_BAUD_SBR_Pos                    0u
#define EUART_BAUD_SBR_WIDTH                  13u
#define EUART_BAUD_SBR(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_SBR_Pos))&EUART_BAUD_SBR_Mask)
#define EUART_BAUD_SBNS_Mask                  0x2000u
#define EUART_BAUD_SBNS_Pos                   13u
#define EUART_BAUD_SBNS_WIDTH                 1u
#define EUART_BAUD_SBNS(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_SBNS_Pos))&EUART_BAUD_SBNS_Mask)
#define EUART_BAUD_RXEDGIE_Mask               0x4000u
#define EUART_BAUD_RXEDGIE_Pos                14u
#define EUART_BAUD_RXEDGIE_WIDTH              1u
#define EUART_BAUD_RXEDGIE(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_RXEDGIE_Pos))&EUART_BAUD_RXEDGIE_Mask)
#define EUART_BAUD_LBKDIE_Mask                0x8000u
#define EUART_BAUD_LBKDIE_Pos                 15u
#define EUART_BAUD_LBKDIE_WIDTH               1u
#define EUART_BAUD_LBKDIE(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_LBKDIE_Pos))&EUART_BAUD_LBKDIE_Mask)
#define EUART_BAUD_RESYNCDIS_Mask             0x10000u
#define EUART_BAUD_RESYNCDIS_Pos              16u
#define EUART_BAUD_RESYNCDIS_WIDTH            1u
#define EUART_BAUD_RESYNCDIS(x)               (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_RESYNCDIS_Pos))&EUART_BAUD_RESYNCDIS_Mask)
#define EUART_BAUD_BOTHEDGE_Mask              0x20000u
#define EUART_BAUD_BOTHEDGE_Pos               17u
#define EUART_BAUD_BOTHEDGE_WIDTH             1u
#define EUART_BAUD_BOTHEDGE(x)                (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_BOTHEDGE_Pos))&EUART_BAUD_BOTHEDGE_Mask)
#define EUART_BAUD_MATCFG_Mask                0xC0000u
#define EUART_BAUD_MATCFG_Pos                 18u
#define EUART_BAUD_MATCFG_WIDTH               2u
#define EUART_BAUD_MATCFG(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_MATCFG_Pos))&EUART_BAUD_MATCFG_Mask)
#define EUART_BAUD_RIDMAE_Mask                0x100000u
#define EUART_BAUD_RIDMAE_Pos                 20u
#define EUART_BAUD_RIDMAE_WIDTH               1u
#define EUART_BAUD_RIDMAE(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_RIDMAE_Pos))&EUART_BAUD_RIDMAE_Mask)
#define EUART_BAUD_RDMAE_Mask                 0x200000u
#define EUART_BAUD_RDMAE_Pos                  21u
#define EUART_BAUD_RDMAE_WIDTH                1u
#define EUART_BAUD_RDMAE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_RDMAE_Pos))&EUART_BAUD_RDMAE_Mask)
#define EUART_BAUD_TDMAE_Mask                 0x800000u
#define EUART_BAUD_TDMAE_Pos                  23u
#define EUART_BAUD_TDMAE_WIDTH                1u
#define EUART_BAUD_TDMAE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_TDMAE_Pos))&EUART_BAUD_TDMAE_Mask)
#define EUART_BAUD_OSR_Mask                   0x1F000000u
#define EUART_BAUD_OSR_Pos                    24u
#define EUART_BAUD_OSR_WIDTH                  5u
#define EUART_BAUD_OSR(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_OSR_Pos))&EUART_BAUD_OSR_Mask)
#define EUART_BAUD_M10_Mask                   0x20000000u
#define EUART_BAUD_M10_Pos                    29u
#define EUART_BAUD_M10_WIDTH                  1u
#define EUART_BAUD_M10(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_M10_Pos))&EUART_BAUD_M10_Mask)
#define EUART_BAUD_MAEN2_Mask                 0x40000000u
#define EUART_BAUD_MAEN2_Pos                  30u
#define EUART_BAUD_MAEN2_WIDTH                1u
#define EUART_BAUD_MAEN2(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_MAEN2_Pos))&EUART_BAUD_MAEN2_Mask)
#define EUART_BAUD_MAEN1_Mask                 0x80000000u
#define EUART_BAUD_MAEN1_Pos                  31u
#define EUART_BAUD_MAEN1_WIDTH                1u
#define EUART_BAUD_MAEN1(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_BAUD_MAEN1_Pos))&EUART_BAUD_MAEN1_Mask)
    /* STAT Bit Fields */
#define EUART_STAT_MA2F_Mask                  0x4000u
#define EUART_STAT_MA2F_Pos                   14u
#define EUART_STAT_MA2F_WIDTH                 1u
#define EUART_STAT_MA2F(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_STAT_MA2F_Pos))&EUART_STAT_MA2F_Mask)
#define EUART_STAT_MA1F_Mask                  0x8000u
#define EUART_STAT_MA1F_Pos                   15u
#define EUART_STAT_MA1F_WIDTH                 1u
#define EUART_STAT_MA1F(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_STAT_MA1F_Pos))&EUART_STAT_MA1F_Mask)
#define EUART_STAT_PF_Mask                    0x10000u
#define EUART_STAT_PF_Pos                     16u
#define EUART_STAT_PF_WIDTH                   1u
#define EUART_STAT_PF(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_STAT_PF_Pos))&EUART_STAT_PF_Mask)
#define EUART_STAT_FE_Mask                    0x20000u
#define EUART_STAT_FE_Pos                     17u
#define EUART_STAT_FE_WIDTH                   1u
#define EUART_STAT_FE(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_STAT_FE_Pos))&EUART_STAT_FE_Mask)
#define EUART_STAT_NF_Mask                    0x40000u
#define EUART_STAT_NF_Pos                     18u
#define EUART_STAT_NF_WIDTH                   1u
#define EUART_STAT_NF(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_STAT_NF_Pos))&EUART_STAT_NF_Mask)
#define EUART_STAT_OR_Mask                    0x80000u
#define EUART_STAT_OR_Pos                     19u
#define EUART_STAT_OR_WIDTH                   1u
#define EUART_STAT_OR(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_STAT_OR_Pos))&EUART_STAT_OR_Mask)
#define EUART_STAT_IDLE_Mask                  0x100000u
#define EUART_STAT_IDLE_Pos                   20u
#define EUART_STAT_IDLE_WIDTH                 1u
#define EUART_STAT_IDLE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_STAT_IDLE_Pos))&EUART_STAT_IDLE_Mask)
#define EUART_STAT_RDRF_Mask                  0x200000u
#define EUART_STAT_RDRF_Pos                   21u
#define EUART_STAT_RDRF_WIDTH                 1u
#define EUART_STAT_RDRF(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_STAT_RDRF_Pos))&EUART_STAT_RDRF_Mask)
#define EUART_STAT_TC_Mask                    0x400000u
#define EUART_STAT_TC_Pos                     22u
#define EUART_STAT_TC_WIDTH                   1u
#define EUART_STAT_TC(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_STAT_TC_Pos))&EUART_STAT_TC_Mask)
#define EUART_STAT_TDRE_Mask                  0x800000u
#define EUART_STAT_TDRE_Pos                   23u
#define EUART_STAT_TDRE_WIDTH                 1u
#define EUART_STAT_TDRE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_STAT_TDRE_Pos))&EUART_STAT_TDRE_Mask)
#define EUART_STAT_RAF_Mask                   0x1000000u
#define EUART_STAT_RAF_Pos                    24u
#define EUART_STAT_RAF_WIDTH                  1u
#define EUART_STAT_RAF(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_STAT_RAF_Pos))&EUART_STAT_RAF_Mask)
#define EUART_STAT_LBKDE_Mask                 0x2000000u
#define EUART_STAT_LBKDE_Pos                  25u
#define EUART_STAT_LBKDE_WIDTH                1u
#define EUART_STAT_LBKDE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_STAT_LBKDE_Pos))&EUART_STAT_LBKDE_Mask)
#define EUART_STAT_BRK13_Mask                 0x4000000u
#define EUART_STAT_BRK13_Pos                  26u
#define EUART_STAT_BRK13_WIDTH                1u
#define EUART_STAT_BRK13(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_STAT_BRK13_Pos))&EUART_STAT_BRK13_Mask)
#define EUART_STAT_RWUID_Mask                 0x8000000u
#define EUART_STAT_RWUID_Pos                  27u
#define EUART_STAT_RWUID_WIDTH                1u
#define EUART_STAT_RWUID(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_STAT_RWUID_Pos))&EUART_STAT_RWUID_Mask)
#define EUART_STAT_RXINV_Mask                 0x10000000u
#define EUART_STAT_RXINV_Pos                  28u
#define EUART_STAT_RXINV_WIDTH                1u
#define EUART_STAT_RXINV(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_STAT_RXINV_Pos))&EUART_STAT_RXINV_Mask)
#define EUART_STAT_MSBF_Mask                  0x20000000u
#define EUART_STAT_MSBF_Pos                   29u
#define EUART_STAT_MSBF_WIDTH                 1u
#define EUART_STAT_MSBF(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_STAT_MSBF_Pos))&EUART_STAT_MSBF_Mask)
#define EUART_STAT_RXEDGIF_Mask               0x40000000u
#define EUART_STAT_RXEDGIF_Pos                30u
#define EUART_STAT_RXEDGIF_WIDTH              1u
#define EUART_STAT_RXEDGIF(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_STAT_RXEDGIF_Pos))&EUART_STAT_RXEDGIF_Mask)
#define EUART_STAT_LBKDIF_Mask                0x80000000u
#define EUART_STAT_LBKDIF_Pos                 31u
#define EUART_STAT_LBKDIF_WIDTH               1u
#define EUART_STAT_LBKDIF(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_STAT_LBKDIF_Pos))&EUART_STAT_LBKDIF_Mask)
    /* CTRL Bit Fields */
#define EUART_CTRL_PT_Mask                    0x1u
#define EUART_CTRL_PT_Pos                     0u
#define EUART_CTRL_PT_WIDTH                   1u
#define EUART_CTRL_PT(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_PT_Pos))&EUART_CTRL_PT_Mask)
#define EUART_CTRL_PE_Mask                    0x2u
#define EUART_CTRL_PE_Pos                     1u
#define EUART_CTRL_PE_WIDTH                   1u
#define EUART_CTRL_PE(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_PE_Pos))&EUART_CTRL_PE_Mask)
#define EUART_CTRL_ILT_Mask                   0x4u
#define EUART_CTRL_ILT_Pos                    2u
#define EUART_CTRL_ILT_WIDTH                  1u
#define EUART_CTRL_ILT(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_ILT_Pos))&EUART_CTRL_ILT_Mask)
#define EUART_CTRL_WAKE_Mask                  0x8u
#define EUART_CTRL_WAKE_Pos                   3u
#define EUART_CTRL_WAKE_WIDTH                 1u
#define EUART_CTRL_WAKE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_WAKE_Pos))&EUART_CTRL_WAKE_Mask)
#define EUART_CTRL_M_Mask                     0x10u
#define EUART_CTRL_M_Pos                      4u
#define EUART_CTRL_M_WIDTH                    1u
#define EUART_CTRL_M(x)                       (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_M_Pos))&EUART_CTRL_M_Mask)
#define EUART_CTRL_RSRC_Mask                  0x20u
#define EUART_CTRL_RSRC_Pos                   5u
#define EUART_CTRL_RSRC_WIDTH                 1u
#define EUART_CTRL_RSRC(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_RSRC_Pos))&EUART_CTRL_RSRC_Mask)
#define EUART_CTRL_DOZEEN_Mask                0x40u
#define EUART_CTRL_DOZEEN_Pos                 6u
#define EUART_CTRL_DOZEEN_WIDTH               1u
#define EUART_CTRL_DOZEEN(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_DOZEEN_Pos))&EUART_CTRL_DOZEEN_Mask)
#define EUART_CTRL_LOOPS_Mask                 0x80u
#define EUART_CTRL_LOOPS_Pos                  7u
#define EUART_CTRL_LOOPS_WIDTH                1u
#define EUART_CTRL_LOOPS(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_LOOPS_Pos))&EUART_CTRL_LOOPS_Mask)
#define EUART_CTRL_IDLECFG_Mask               0x700u
#define EUART_CTRL_IDLECFG_Pos                8u
#define EUART_CTRL_IDLECFG_WIDTH              3u
#define EUART_CTRL_IDLECFG(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_IDLECFG_Pos))&EUART_CTRL_IDLECFG_Mask)
#define EUART_CTRL_M7_Mask                    0x800u
#define EUART_CTRL_M7_Pos                     11u
#define EUART_CTRL_M7_WIDTH                   1u
#define EUART_CTRL_M7(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_M7_Pos))&EUART_CTRL_M7_Mask)
#define EUART_CTRL_MA2IE_Mask                 0x4000u
#define EUART_CTRL_MA2IE_Pos                  14u
#define EUART_CTRL_MA2IE_WIDTH                1u
#define EUART_CTRL_MA2IE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_MA2IE_Pos))&EUART_CTRL_MA2IE_Mask)
#define EUART_CTRL_MA1IE_Mask                 0x8000u
#define EUART_CTRL_MA1IE_Pos                  15u
#define EUART_CTRL_MA1IE_WIDTH                1u
#define EUART_CTRL_MA1IE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_MA1IE_Pos))&EUART_CTRL_MA1IE_Mask)
#define EUART_CTRL_SBK_Mask                   0x10000u
#define EUART_CTRL_SBK_Pos                    16u
#define EUART_CTRL_SBK_WIDTH                  1u
#define EUART_CTRL_SBK(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_SBK_Pos))&EUART_CTRL_SBK_Mask)
#define EUART_CTRL_RWU_Mask                   0x20000u
#define EUART_CTRL_RWU_Pos                    17u
#define EUART_CTRL_RWU_WIDTH                  1u
#define EUART_CTRL_RWU(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_RWU_Pos))&EUART_CTRL_RWU_Mask)
#define EUART_CTRL_RE_Mask                    0x40000u
#define EUART_CTRL_RE_Pos                     18u
#define EUART_CTRL_RE_WIDTH                   1u
#define EUART_CTRL_RE(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_RE_Pos))&EUART_CTRL_RE_Mask)
#define EUART_CTRL_TE_Mask                    0x80000u
#define EUART_CTRL_TE_Pos                     19u
#define EUART_CTRL_TE_WIDTH                   1u
#define EUART_CTRL_TE(x)                      (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_TE_Pos))&EUART_CTRL_TE_Mask)
#define EUART_CTRL_ILIE_Mask                  0x100000u
#define EUART_CTRL_ILIE_Pos                   20u
#define EUART_CTRL_ILIE_WIDTH                 1u
#define EUART_CTRL_ILIE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_ILIE_Pos))&EUART_CTRL_ILIE_Mask)
#define EUART_CTRL_RIE_Mask                   0x200000u
#define EUART_CTRL_RIE_Pos                    21u
#define EUART_CTRL_RIE_WIDTH                  1u
#define EUART_CTRL_RIE(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_RIE_Pos))&EUART_CTRL_RIE_Mask)
#define EUART_CTRL_TCIE_Mask                  0x400000u
#define EUART_CTRL_TCIE_Pos                   22u
#define EUART_CTRL_TCIE_WIDTH                 1u
#define EUART_CTRL_TCIE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_TCIE_Pos))&EUART_CTRL_TCIE_Mask)
#define EUART_CTRL_TIE_Mask                   0x800000u
#define EUART_CTRL_TIE_Pos                    23u
#define EUART_CTRL_TIE_WIDTH                  1u
#define EUART_CTRL_TIE(x)                     (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_TIE_Pos))&EUART_CTRL_TIE_Mask)
#define EUART_CTRL_PEIE_Mask                  0x1000000u
#define EUART_CTRL_PEIE_Pos                   24u
#define EUART_CTRL_PEIE_WIDTH                 1u
#define EUART_CTRL_PEIE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_PEIE_Pos))&EUART_CTRL_PEIE_Mask)
#define EUART_CTRL_FEIE_Mask                  0x2000000u
#define EUART_CTRL_FEIE_Pos                   25u
#define EUART_CTRL_FEIE_WIDTH                 1u
#define EUART_CTRL_FEIE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_FEIE_Pos))&EUART_CTRL_FEIE_Mask)
#define EUART_CTRL_NEIE_Mask                  0x4000000u
#define EUART_CTRL_NEIE_Pos                   26u
#define EUART_CTRL_NEIE_WIDTH                 1u
#define EUART_CTRL_NEIE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_NEIE_Pos))&EUART_CTRL_NEIE_Mask)
#define EUART_CTRL_ORIE_Mask                  0x8000000u
#define EUART_CTRL_ORIE_Pos                   27u
#define EUART_CTRL_ORIE_WIDTH                 1u
#define EUART_CTRL_ORIE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_ORIE_Pos))&EUART_CTRL_ORIE_Mask)
#define EUART_CTRL_TXINV_Mask                 0x10000000u
#define EUART_CTRL_TXINV_Pos                  28u
#define EUART_CTRL_TXINV_WIDTH                1u
#define EUART_CTRL_TXINV(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_TXINV_Pos))&EUART_CTRL_TXINV_Mask)
#define EUART_CTRL_TXDIR_Mask                 0x20000000u
#define EUART_CTRL_TXDIR_Pos                  29u
#define EUART_CTRL_TXDIR_WIDTH                1u
#define EUART_CTRL_TXDIR(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_TXDIR_Pos))&EUART_CTRL_TXDIR_Mask)
#define EUART_CTRL_R9T8_Mask                  0x40000000u
#define EUART_CTRL_R9T8_Pos                   30u
#define EUART_CTRL_R9T8_WIDTH                 1u
#define EUART_CTRL_R9T8(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_R9T8_Pos))&EUART_CTRL_R9T8_Mask)
#define EUART_CTRL_R8T9_Mask                  0x80000000u
#define EUART_CTRL_R8T9_Pos                   31u
#define EUART_CTRL_R8T9_WIDTH                 1u
#define EUART_CTRL_R8T9(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_CTRL_R8T9_Pos))&EUART_CTRL_R8T9_Mask)
    /* DATA Bit Fields */
#define EUART_DATA_R0T0_Mask                  0x1u
#define EUART_DATA_R0T0_Pos                   0u
#define EUART_DATA_R0T0_WIDTH                 1u
#define EUART_DATA_R0T0(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R0T0_Pos))&EUART_DATA_R0T0_Mask)
#define EUART_DATA_R1T1_Mask                  0x2u
#define EUART_DATA_R1T1_Pos                   1u
#define EUART_DATA_R1T1_WIDTH                 1u
#define EUART_DATA_R1T1(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R1T1_Pos))&EUART_DATA_R1T1_Mask)
#define EUART_DATA_R2T2_Mask                  0x4u
#define EUART_DATA_R2T2_Pos                   2u
#define EUART_DATA_R2T2_WIDTH                 1u
#define EUART_DATA_R2T2(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R2T2_Pos))&EUART_DATA_R2T2_Mask)
#define EUART_DATA_R3T3_Mask                  0x8u
#define EUART_DATA_R3T3_Pos                   3u
#define EUART_DATA_R3T3_WIDTH                 1u
#define EUART_DATA_R3T3(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R3T3_Pos))&EUART_DATA_R3T3_Mask)
#define EUART_DATA_R4T4_Mask                  0x10u
#define EUART_DATA_R4T4_Pos                   4u
#define EUART_DATA_R4T4_WIDTH                 1u
#define EUART_DATA_R4T4(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R4T4_Pos))&EUART_DATA_R4T4_Mask)
#define EUART_DATA_R5T5_Mask                  0x20u
#define EUART_DATA_R5T5_Pos                   5u
#define EUART_DATA_R5T5_WIDTH                 1u
#define EUART_DATA_R5T5(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R5T5_Pos))&EUART_DATA_R5T5_Mask)
#define EUART_DATA_R6T6_Mask                  0x40u
#define EUART_DATA_R6T6_Pos                   6u
#define EUART_DATA_R6T6_WIDTH                 1u
#define EUART_DATA_R6T6(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R6T6_Pos))&EUART_DATA_R6T6_Mask)
#define EUART_DATA_R7T7_Mask                  0x80u
#define EUART_DATA_R7T7_Pos                   7u
#define EUART_DATA_R7T7_WIDTH                 1u
#define EUART_DATA_R7T7(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R7T7_Pos))&EUART_DATA_R7T7_Mask)
#define EUART_DATA_R8T8_Mask                  0x100u
#define EUART_DATA_R8T8_Pos                   8u
#define EUART_DATA_R8T8_WIDTH                 1u
#define EUART_DATA_R8T8(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R8T8_Pos))&EUART_DATA_R8T8_Mask)
#define EUART_DATA_R9T9_Mask                  0x200u
#define EUART_DATA_R9T9_Pos                   9u
#define EUART_DATA_R9T9_WIDTH                 1u
#define EUART_DATA_R9T9(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_DATA_R9T9_Pos))&EUART_DATA_R9T9_Mask)
#define EUART_DATA_IDLINE_Mask                0x800u
#define EUART_DATA_IDLINE_Pos                 11u
#define EUART_DATA_IDLINE_WIDTH               1u
#define EUART_DATA_IDLINE(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_DATA_IDLINE_Pos))&EUART_DATA_IDLINE_Mask)
#define EUART_DATA_RXEMPT_Mask                0x1000u
#define EUART_DATA_RXEMPT_Pos                 12u
#define EUART_DATA_RXEMPT_WIDTH               1u
#define EUART_DATA_RXEMPT(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_DATA_RXEMPT_Pos))&EUART_DATA_RXEMPT_Mask)
#define EUART_DATA_FRETSC_Mask                0x2000u
#define EUART_DATA_FRETSC_Pos                 13u
#define EUART_DATA_FRETSC_WIDTH               1u
#define EUART_DATA_FRETSC(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_DATA_FRETSC_Pos))&EUART_DATA_FRETSC_Mask)
#define EUART_DATA_PARITYE_Mask               0x4000u
#define EUART_DATA_PARITYE_Pos                14u
#define EUART_DATA_PARITYE_WIDTH              1u
#define EUART_DATA_PARITYE(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_DATA_PARITYE_Pos))&EUART_DATA_PARITYE_Mask)
#define EUART_DATA_NOISY_Mask                 0x8000u
#define EUART_DATA_NOISY_Pos                  15u
#define EUART_DATA_NOISY_WIDTH                1u
#define EUART_DATA_NOISY(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_DATA_NOISY_Pos))&EUART_DATA_NOISY_Mask)
    /* MATCH Bit Fields */
#define EUART_MATCH_MA1_Mask                  0x3FFu
#define EUART_MATCH_MA1_Pos                   0u
#define EUART_MATCH_MA1_WIDTH                 10u
#define EUART_MATCH_MA1(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_MATCH_MA1_Pos))&EUART_MATCH_MA1_Mask)
#define EUART_MATCH_MA2_Mask                  0x3FF0000u
#define EUART_MATCH_MA2_Pos                   16u
#define EUART_MATCH_MA2_WIDTH                 10u
#define EUART_MATCH_MA2(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_MATCH_MA2_Pos))&EUART_MATCH_MA2_Mask)
    /* MODIR Bit Fields */
#define EUART_MODIR_TXCTSE_Mask               0x1u
#define EUART_MODIR_TXCTSE_Pos                0u
#define EUART_MODIR_TXCTSE_WIDTH              1u
#define EUART_MODIR_TXCTSE(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_TXCTSE_Pos))&EUART_MODIR_TXCTSE_Mask)
#define EUART_MODIR_TXRTSE_Mask               0x2u
#define EUART_MODIR_TXRTSE_Pos                1u
#define EUART_MODIR_TXRTSE_WIDTH              1u
#define EUART_MODIR_TXRTSE(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_TXRTSE_Pos))&EUART_MODIR_TXRTSE_Mask)
#define EUART_MODIR_TXRTSPOL_Mask             0x4u
#define EUART_MODIR_TXRTSPOL_Pos              2u
#define EUART_MODIR_TXRTSPOL_WIDTH            1u
#define EUART_MODIR_TXRTSPOL(x)               (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_TXRTSPOL_Pos))&EUART_MODIR_TXRTSPOL_Mask)
#define EUART_MODIR_RXRTSE_Mask               0x8u
#define EUART_MODIR_RXRTSE_Pos                3u
#define EUART_MODIR_RXRTSE_WIDTH              1u
#define EUART_MODIR_RXRTSE(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_RXRTSE_Pos))&EUART_MODIR_RXRTSE_Mask)
#define EUART_MODIR_TXCTSC_Mask               0x10u
#define EUART_MODIR_TXCTSC_Pos                4u
#define EUART_MODIR_TXCTSC_WIDTH              1u
#define EUART_MODIR_TXCTSC(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_TXCTSC_Pos))&EUART_MODIR_TXCTSC_Mask)
#define EUART_MODIR_TXCTSSRC_Mask             0x20u
#define EUART_MODIR_TXCTSSRC_Pos              5u
#define EUART_MODIR_TXCTSSRC_WIDTH            1u
#define EUART_MODIR_TXCTSSRC(x)               (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_TXCTSSRC_Pos))&EUART_MODIR_TXCTSSRC_Mask)
#define EUART_MODIR_RTSWATER_Mask             0x300u
#define EUART_MODIR_RTSWATER_Pos              8u
#define EUART_MODIR_RTSWATER_WIDTH            2u
#define EUART_MODIR_RTSWATER(x)               (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_RTSWATER_Pos))&EUART_MODIR_RTSWATER_Mask)
#define EUART_MODIR_TNP_Mask                  0x30000u
#define EUART_MODIR_TNP_Pos                   16u
#define EUART_MODIR_TNP_WIDTH                 2u
#define EUART_MODIR_TNP(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_TNP_Pos))&EUART_MODIR_TNP_Mask)
#define EUART_MODIR_IREN_Mask                 0x40000u
#define EUART_MODIR_IREN_Pos                  18u
#define EUART_MODIR_IREN_WIDTH                1u
#define EUART_MODIR_IREN(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_MODIR_IREN_Pos))&EUART_MODIR_IREN_Mask)
    /* FIFO Bit Fields */
#define EUART_FIFO_RXFIFOSIZE_Mask            0x7u
#define EUART_FIFO_RXFIFOSIZE_Pos             0u
#define EUART_FIFO_RXFIFOSIZE_WIDTH           3u
#define EUART_FIFO_RXFIFOSIZE(x)              (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXFIFOSIZE_Pos))&EUART_FIFO_RXFIFOSIZE_Mask)
#define EUART_FIFO_RXFE_Mask                  0x8u
#define EUART_FIFO_RXFE_Pos                   3u
#define EUART_FIFO_RXFE_WIDTH                 1u
#define EUART_FIFO_RXFE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXFE_Pos))&EUART_FIFO_RXFE_Mask)
#define EUART_FIFO_TXFIFOSIZE_Mask            0x70u
#define EUART_FIFO_TXFIFOSIZE_Pos             4u
#define EUART_FIFO_TXFIFOSIZE_WIDTH           3u
#define EUART_FIFO_TXFIFOSIZE(x)              (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_TXFIFOSIZE_Pos))&EUART_FIFO_TXFIFOSIZE_Mask)
#define EUART_FIFO_TXFE_Mask                  0x80u
#define EUART_FIFO_TXFE_Pos                   7u
#define EUART_FIFO_TXFE_WIDTH                 1u
#define EUART_FIFO_TXFE(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_TXFE_Pos))&EUART_FIFO_TXFE_Mask)
#define EUART_FIFO_RXUFE_Mask                 0x100u
#define EUART_FIFO_RXUFE_Pos                  8u
#define EUART_FIFO_RXUFE_WIDTH                1u
#define EUART_FIFO_RXUFE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXUFE_Pos))&EUART_FIFO_RXUFE_Mask)
#define EUART_FIFO_TXOFE_Mask                 0x200u
#define EUART_FIFO_TXOFE_Pos                  9u
#define EUART_FIFO_TXOFE_WIDTH                1u
#define EUART_FIFO_TXOFE(x)                   (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_TXOFE_Pos))&EUART_FIFO_TXOFE_Mask)
#define EUART_FIFO_RXIDEN_Mask                0x1C00u
#define EUART_FIFO_RXIDEN_Pos                 10u
#define EUART_FIFO_RXIDEN_WIDTH               3u
#define EUART_FIFO_RXIDEN(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXIDEN_Pos))&EUART_FIFO_RXIDEN_Mask)
#define EUART_FIFO_RXFLUSH_Mask               0x4000u
#define EUART_FIFO_RXFLUSH_Pos                14u
#define EUART_FIFO_RXFLUSH_WIDTH              1u
#define EUART_FIFO_RXFLUSH(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXFLUSH_Pos))&EUART_FIFO_RXFLUSH_Mask)
#define EUART_FIFO_TXFLUSH_Mask               0x8000u
#define EUART_FIFO_TXFLUSH_Pos                15u
#define EUART_FIFO_TXFLUSH_WIDTH              1u
#define EUART_FIFO_TXFLUSH(x)                 (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_TXFLUSH_Pos))&EUART_FIFO_TXFLUSH_Mask)
#define EUART_FIFO_RXUF_Mask                  0x10000u
#define EUART_FIFO_RXUF_Pos                   16u
#define EUART_FIFO_RXUF_WIDTH                 1u
#define EUART_FIFO_RXUF(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXUF_Pos))&EUART_FIFO_RXUF_Mask)
#define EUART_FIFO_TXOF_Mask                  0x20000u
#define EUART_FIFO_TXOF_Pos                   17u
#define EUART_FIFO_TXOF_WIDTH                 1u
#define EUART_FIFO_TXOF(x)                    (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_TXOF_Pos))&EUART_FIFO_TXOF_Mask)
#define EUART_FIFO_RXEMPT_Mask                0x400000u
#define EUART_FIFO_RXEMPT_Pos                 22u
#define EUART_FIFO_RXEMPT_WIDTH               1u
#define EUART_FIFO_RXEMPT(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_RXEMPT_Pos))&EUART_FIFO_RXEMPT_Mask)
#define EUART_FIFO_TXEMPT_Mask                0x800000u
#define EUART_FIFO_TXEMPT_Pos                 23u
#define EUART_FIFO_TXEMPT_WIDTH               1u
#define EUART_FIFO_TXEMPT(x)                  (((uint32_t)(((uint32_t)(x))<<EUART_FIFO_TXEMPT_Pos))&EUART_FIFO_TXEMPT_Mask)
    /* WATER Bit Fields */
#define EUART_WATER_TXWATER_Mask              0x3u
#define EUART_WATER_TXWATER_Pos               0u
#define EUART_WATER_TXWATER_WIDTH             2u
#define EUART_WATER_TXWATER(x)                (((uint32_t)(((uint32_t)(x))<<EUART_WATER_TXWATER_Pos))&EUART_WATER_TXWATER_Mask)
#define EUART_WATER_TXCOUNT_Mask              0x700u
#define EUART_WATER_TXCOUNT_Pos               8u
#define EUART_WATER_TXCOUNT_WIDTH             3u
#define EUART_WATER_TXCOUNT(x)                (((uint32_t)(((uint32_t)(x))<<EUART_WATER_TXCOUNT_Pos))&EUART_WATER_TXCOUNT_Mask)
#define EUART_WATER_RXWATER_Mask              0x30000u
#define EUART_WATER_RXWATER_Pos               16u
#define EUART_WATER_RXWATER_WIDTH             2u
#define EUART_WATER_RXWATER(x)                (((uint32_t)(((uint32_t)(x))<<EUART_WATER_RXWATER_Pos))&EUART_WATER_RXWATER_Mask)
#define EUART_WATER_RXCOUNT_Mask              0x7000000u
#define EUART_WATER_RXCOUNT_Pos               24u
#define EUART_WATER_RXCOUNT_WIDTH             3u
#define EUART_WATER_RXCOUNT(x)                (((uint32_t)(((uint32_t)(x))<<EUART_WATER_RXCOUNT_Pos))&EUART_WATER_RXCOUNT_Mask)

/*------------------------------------------------------------------------------
end of group EUART_Register_Masks
------------------------------------------------------------------------------*/

/** 
  * @brief UART Init Structure definition  
  */ 
typedef struct
{
    uint32_t SysclkFreq;      /*!< Specifies the system clock frequency (unit : Hz).
                                   This parameter can be a value of @ref SYSCLK_FREQUENCY */
    
    uint32_t BaudRate;        /*!< This member configures the EUART communication baud rate.
                                   This parameter can be a value of @ref EUART_BaudRate */
                                   
	uint16_t WordLength; 	  /*!< Specifies the number of data bits transmitted or received in a frame.
                                   This parameter can be a value of @ref EUART_Word_Length */
	
	uint16_t StopBits;   	  /*!< Specifies the number of stop bits transmitted.
                                   This parameter can be a value of @ref EUART_Stop_Bits */
	
    uint16_t ParitySel;       /*!< Specifies the parity mode.
                                   This parameter can be a value of @ref EUART_Parity */
 
    uint16_t WorkMode;        /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                   This parameter can be a value of @ref USART_Mode */
    
    uint16_t IDLE_Type;       /*!< Specifies the type of IDLE level.
                                   This parameter can be a value of @ref IDLE_Level_Type */
} EUART_InitTypeDef;


/** @defgroup SYSCLK_FREQUENCY 
  * @{
  */ 
#define SYSCLK_FREQ_48Mz       (48000000U)
#define SYSCLK_FREQ_40Mz       (40000000U)
#define SYSCLK_FREQ_32Mz       (32000000U)
#define SYSCLK_FREQ_24Mz       (24000000U)
#define SYSCLK_FREQ_16Mz       (16000000U)


/** @defgroup EUART_BaudRate 
  * @{
  */ 
#define EUART_BaudRate_9600         (9600U)     /*!< communication baud rate : 9600 */
#define EUART_BaudRate_19200        (19200U)    /*!< communication baud rate : 19200 */
#define EUART_BaudRate_38400        (38400U)    /*!< communication baud rate : 38400 */
#define EUART_BaudRate_115200       (115200U)   /*!< communication baud rate : 115200 */


/** @defgroup EUART_Word_Length 
  * @{
  */ 
#define WordLength_7bit        ((uint16_t)0x01)   /*!< 数据位7bit */
#define WordLength_8bit        ((uint16_t)0x02)   /*!< 数据位8bit */
#define WordLength_9bit        ((uint16_t)0x03)   /*!< 数据位9bit */
#define WordLength_10bit       ((uint16_t)0x04)   /*!< 数据位10bit */


/** @defgroup EUART_Stop_Bits 
  * @{
  */ 
#define StopBits_1bit        ((uint16_t)0x01)   /*!< 停止位1bit */
#define StopBits_2bit        ((uint16_t)0x02)   /*!< 停止位2bit */


/** @defgroup EUART_Parity 
  * @{
  */ 
#define Parity_None       ((uint16_t)0x00)    /*!< 无校验 */
#define Parity_Odd        ((uint16_t)0x01)    /*!< 奇校验 */
#define Parity_Even       ((uint16_t)0x02)    /*!< 偶校验 */


/** @defgroup EUART_WorkMode 
  * @{
  */
#define WorkMode_None     ((uint16_t)0x00)   /*!< 工作模式为None, 禁止接收和发送功能 */
#define WorkMode_Rx       ((uint16_t)0x01)   /*!< 工作模式为接收模式 */
#define WorkMode_Tx       ((uint16_t)0x02)   /*!< 工作模式为发送模式 */
#define WorkMode_TxRx     ((uint16_t)0x03)   /*!< 工作模式为发送接收模式 */


/** @defgroup IDLE_Level_Type 
  * @{
  */ 
#define IDLE_TYPE_AfterStop       ((uint32_t)(0x01UL << 2))   /*!< 空闲字符计数在停止位之后开始 */
#define IDLE_TYPE_AfterStart      (0)                         /*!< 空闲字符计数在开始位之后开始 */


/** @defgroup LIN间隔字符长度选择
  * @{
  */ 
#define LIN_BRK_Char_9to13        (0)                          /*!< 间隔字符的长度为 9 到 13 位 */
#define LIN_BRK_Char_12to15       ((uint32_t)(0x01UL << 26))   /*!< 间隔字符的长度为 12 到 15 位 */


/*  四舍五入宏定义   */
#define SHE_4_5_RU(floatVal) 	((int)(((floatVal) - (int)(floatVal)) * 10) >= 5) ? ((int)(floatVal) + 1) : (int)(floatVal)

/*  空闲字符数定义    */
#define EUART_IDLECFG_1bit        (0)                         /*!< 1位空闲字符 */
#define EUART_IDLECFG_2bit        ((uint32_t)(0x01UL << 8))   /*!< 2位空闲字符 */
#define EUART_IDLECFG_4bit        ((uint32_t)(0x02UL << 8))   /*!< 4位空闲字符 */
#define EUART_IDLECFG_8bit        ((uint32_t)(0x03UL << 8))   /*!< 8位空闲字符 */
#define EUART_IDLECFG_16bit       ((uint32_t)(0x04UL << 8))   /*!< 16位空闲字符 */
#define EUART_IDLECFG_32bit       ((uint32_t)(0x05UL << 8))   /*!< 32位空闲字符 */
#define EUART_IDLECFG_64bit       ((uint32_t)(0x06UL << 8))   /*!< 64位空闲字符 */
#define EUART_IDLECFG_128bit      ((uint32_t)(0x07UL << 8))   /*!< 128位空闲字符 */

/**-----------------------------------------------------------------------------
EUART标志位定义
------------------------------------------------------------------------------*/
/*---------------------- EUARTx_STAT Register Flag bit define ----------------*/
#define EUART_STAT_FLAG_LBKDIF         ((uint32_t)(0x01UL << 31))     /*!< LIN 间隔检测中断标志 (W1C) */
#define EUART_STAT_FLAG_RXEDGIF        ((uint32_t)(0x01UL << 30))     /*!< RXD 引脚有效边沿中断标志 (W1C) */
#define EUART_STAT_FLAG_RAF            ((uint32_t)(0x01UL << 24))     /*!< 接收有效标志 (RO) */
#define EUART_STAT_FLAG_TDRE           ((uint32_t)(0x01UL << 23))     /*!< 发送数据寄存器空标志 (RO) */
#define EUART_STAT_FLAG_TC             ((uint32_t)(0x01UL << 22))     /*!< 发送完成标志 (RO) */
#define EUART_STAT_FLAG_RDRF           ((uint32_t)(0x01UL << 21))     /*!< 接收数据寄存器满标志 (RO) */
#define EUART_STAT_FLAG_IDLE           ((uint32_t)(0x01UL << 20))     /*!< 空闲电平标志 (W1C) */
#define EUART_STAT_FLAG_OR             ((uint32_t)(0x01UL << 19))     /*!< 接收溢出标志 (W1C) */
#define EUART_STAT_FLAG_NF             ((uint32_t)(0x01UL << 18))     /*!< 噪声标志 (W1C) */
#define EUART_STAT_FLAG_FE             ((uint32_t)(0x01UL << 17))     /*!< 帧错误标志 (W1C) */
#define EUART_STAT_FLAG_PF             ((uint32_t)(0x01UL << 16))     /*!< 奇偶校验错误标志 (W1C) */
#define EUART_STAT_FLAG_MA1F           ((uint32_t)(0x01UL << 15))     /*!< Match1 标志 (W1C) */
#define EUART_STAT_FLAG_MA2F           ((uint32_t)(0x01UL << 14))     /*!< Match2 标志 (W1C) */

/*---------------------- EUARTx_DATA Register Flag bit define ----------------*/
#define EUART_DATA_FLAG_NOISY          ((uint32_t)(0x01UL << 15))     /*!< 当前接收到的数据字段 DATA[R9： R0]中包含噪声 (RO) */
#define EUART_DATA_FLAG_PARITYE        ((uint32_t)(0x01UL << 14))     /*!< 当前接收到的数据字段 DATA[R9： R0]中存在奇偶校验错误 (RO) */
#define EUART_DATA_FLAG_RXEMPT         ((uint32_t)(0x01UL << 12))     /*!< 接收缓冲空 (RO) */
#define EUART_DATA_FLAG_IDLINE         ((uint32_t)(0x01UL << 11))     /*!< 空闲电平 (RO) */

/*---------------------- EUARTx_FIFO Register Flag bit define ----------------*/
#define EUART_FIFO_FLAG_TXEMPT         ((uint32_t)(0x01UL << 23))     /*!< 发送缓冲区/FIFO 空 (RO) */
#define EUART_FIFO_FLAG_RXEMPT         ((uint32_t)(0x01UL << 22))     /*!< 接收缓冲区/FIFO 空 (RO) */
#define EUART_FIFO_FLAG_TXOF           ((uint32_t)(0x01UL << 17))     /*!< 发送缓冲区溢出标志 (RW) */
#define EUART_FIFO_FLAG_RXUF           ((uint32_t)(0x01UL << 16))     /*!< 接收缓冲区下溢标志 (RW) */


/** @defgroup EUARTx interrupt_sources 
  * @{
  */
#define EUART_IT_LBKDIE       ((uint32_t)(0x05))               /*!< LIN 间隔检测中断使能 */
#define EUART_IT_RXEDGIE      ((uint32_t)(0x0A))               /*!< RX 输入的有效边沿中断使能 */
#define EUART_IT_ORIE         ((uint32_t)(0x01UL << 27))       /*!< 溢出中断使能 */ 
#define EUART_IT_NEIE         ((uint32_t)(0x01UL << 26))       /*!< 噪声错误中断使能 */ 
#define EUART_IT_FEIE         ((uint32_t)(0x01UL << 25))       /*!< 帧错误中断使能 */ 
#define EUART_IT_PEIE         ((uint32_t)(0x01UL << 24))       /*!< 奇偶校验错误中断使能 */ 
#define EUART_IT_TIE          ((uint32_t)(0x01UL << 23))       /*!< 发送数据寄存器空中断使能 */ 
#define EUART_IT_TCIE         ((uint32_t)(0x01UL << 22))       /*!< 发送完成中断使能 */ 
#define EUART_IT_RIE          ((uint32_t)(0x01UL << 21))       /*!< 接收中断使能 */ 
#define EUART_IT_ILIE         ((uint32_t)(0x01UL << 20))       /*!< 空闲电平中断使能 */ 
#define EUART_IT_MA1IE        ((uint32_t)(0x01UL << 15))       /*!< Match1 中断使能 */
#define EUART_IT_MA2IE        ((uint32_t)(0x01UL << 14))       /*!< Match2 中断使能 */
#define EUART_IT_TXOFE        ((uint32_t)(0x01UL << 9))        /*!< 发送 FIFO 溢出中断使能, EUARTx_FIFO.TXOFE */
#define EUART_IT_RXUFE        ((uint32_t)(0x01UL << 8))        /*!< 接收 FIFO 下溢中断使能, EUARTx_FIFO.RXUFE */

    
/* Exported functions --------------------------------------------------------*/
void EUART_DeInit(EUART_TypeDef* EUARTx);
void EUART_Soft_Reset(EUART_TypeDef* EUARTx);
void EUART_StructInit(EUART_InitTypeDef* EUART_InitStruct);    
void EUART_Init(EUART_TypeDef* EUARTx, EUART_InitTypeDef* EUART_InitStruct);
void EUART_Tx_Cmd(EUART_TypeDef* EUARTx, FunctionalState NewState);    
void EUART_Rx_Cmd(EUART_TypeDef* EUARTx, FunctionalState NewState);
void EUART_LIN_BreakDetect_Cmd(EUART_TypeDef* EUARTx, FunctionalState NewState);
void EUART_BRK13_CharLenght_Config(EUART_TypeDef* EUARTx, uint32_t CharLen);
void EUART_IDLE_Type_Config(EUART_TypeDef* EUARTx, uint32_t ILT_Sel);    
void EUART_IDLE_Char_Config(EUART_TypeDef* EUARTx, uint32_t idle_char);
void EUART_Transmit_Data(EUART_TypeDef* EUARTx, uint8_t SendData);  
void EUART_Transmit_String(EUART_TypeDef* EUARTx, uint8_t *strData);
uint8_t EUART_Receive_Data(EUART_TypeDef* EUARTx);
uint8_t EUART_Recevie_RB8(EUART_TypeDef* EUARTx);
uint8_t EUART_Recevie_RB9(EUART_TypeDef* EUARTx);
FlagStatus EUART_STAT_Get_FlagStatus(EUART_TypeDef* EUARTx, uint32_t EUART_Flag);
FlagStatus EUART_DATA_Get_FlagStatus(EUART_TypeDef* EUARTx, uint32_t EUART_Flag);
FlagStatus EUART_FIFO_Get_FlagStatus(EUART_TypeDef* EUARTx, uint32_t EUART_Flag);
void EUART_STAT_ClearFlag(EUART_TypeDef* EUARTx, uint32_t EUART_Flag);
void EUART_FIFO_ClearFlag(EUART_TypeDef* EUARTx, uint32_t EUART_Flag);
void EUART_ITConfig(EUART_TypeDef* EUARTx, uint32_t EUART_IT, FunctionalState NewState);


#ifdef __cplusplus
}
#endif


#endif   /* __CPS32K21X_EUART_H__ */



