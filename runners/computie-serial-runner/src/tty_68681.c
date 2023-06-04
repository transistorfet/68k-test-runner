
#include <stdint.h>

// MC68681 Register Addresses
#define MR1A_MR2A_ADDR      ((volatile uint8_t *) 0x700001)
#define SRA_RD_ADDR         ((volatile uint8_t *) 0x700003)
#define CSRA_WR_ADDR        ((volatile uint8_t *) 0x700003)
#define CRA_WR_ADDR         ((volatile uint8_t *) 0x700005)
#define TBA_WR_ADDR         ((volatile uint8_t *) 0x700007)
#define RBA_RD_ADDR         ((volatile uint8_t *) 0x700007)

#define MR1B_MR2B_ADDR      ((volatile uint8_t *) 0x700011)
#define SRB_RD_ADDR         ((volatile uint8_t *) 0x700013)
#define CSRB_WR_ADDR        ((volatile uint8_t *) 0x700013)
#define CRB_WR_ADDR         ((volatile uint8_t *) 0x700015)
#define TBB_WR_ADDR         ((volatile uint8_t *) 0x700017)
#define RBB_RD_ADDR         ((volatile uint8_t *) 0x700017)

#define ACR_WR_ADDR         ((volatile uint8_t *) 0x700009)
#define CTUR_WR_ADDR        ((volatile uint8_t *) 0x70000D)
#define CTLR_WR_ADDR        ((volatile uint8_t *) 0x70000F)
#define START_RD_ADDR       ((volatile uint8_t *) 0x70001D)
#define STOP_RD_ADDR        ((volatile uint8_t *) 0x70001F)

#define IPCR_RD_ADDR        ((volatile uint8_t *) 0x700009)
#define OPCR_WR_ADDR        ((volatile uint8_t *) 0x70001B)
#define INPUT_RD_ADDR       ((volatile uint8_t *) 0x70001B)
#define OUT_SET_ADDR        ((volatile uint8_t *) 0x70001D)
#define OUT_RESET_ADDR      ((volatile uint8_t *) 0x70001F)

#define ISR_RD_ADDR         ((volatile uint8_t *) 0x70000B)
#define IMR_WR_ADDR         ((volatile uint8_t *) 0x70000B)
#define IVR_WR_ADDR         ((volatile uint8_t *) 0x700019)


// MC68681 Command Numbers
#define CMD_RESET_MR                    0x10
#define CMD_RESET_RX                    0x20
#define CMD_RESET_TX                    0x30
#define CMD_RESET_ERROR                 0x40
#define CMD_ENABLE_TX_RX                0x05
#define CMD_ENABLE_RX                   0x01
#define CMD_DISABLE_RX                  0x02
#define CMD_ENABLE_TX                   0x04
#define CMD_DISABLE_TX                  0x08
#define CMD_START_BREAK                 0x60
#define CMD_STOP_BREAK                  0x70


// MC68681 Default Configuration Values
#define MR1A_MODE_A_REG_1_CONFIG        0b10010011    // RxRTS Enabled, 8 bits, No Parity
#define MR2A_MODE_A_REG_2_CONFIG        0b00000111    // Normal mode, CTS Disabled, 1 stop bit
//#define CSRA_CLK_SELECT_REG_A_CONFIG  0b10111011    // 9600 bps @ 3.6864MHz (19200 @ 7.3728 MHz)
//#define ACR_AUX_CONTROL_REG_CONFIG    0b11111000    // Set2, External Clock / 16, IRQs disabled
#define CSRA_CLK_SELECT_REG_A_CONFIG    0b11001100    // 38400 bps @ 3.6864MHz
#define ACR_AUX_CONTROL_REG_CONFIG      0b01111000    // Set1, External Clock / 16, IRQs disabled except IP3


// Status Register Bits (SRA/SRB)
#define SR_RECEIVED_BREAK               0x80
#define SR_FRAMING_ERROR                0x40
#define SR_PARITY_ERROR                 0x20
#define SR_OVERRUN_ERROR                0x10
#define SR_TX_EMPTY                     0x08
#define SR_TX_READY                     0x04
#define SR_RX_FULL                      0x02
#define SR_RX_READY                     0x01


// Interrupt Status/Mask Bits (ISR/IVR)
#define ISR_INPUT_CHANGE                0x80
#define ISR_CH_B_BREAK_CHANGE           0x40
#define ISR_CH_B_RX_READY_FULL          0x20
#define ISR_CH_B_TX_READY               0x10
#define ISR_TIMER_CHANGE                0x08
#define ISR_CH_A_BREAK_CHANGE           0x04
#define ISR_CH_A_RX_READY_FULL          0x02
#define ISR_CH_A_TX_READY               0x01

#define delay(count)        ({ int c = count; while (--c > 0) { asm volatile (""); } })

extern int putchar(int);

int init_tty(void) {
    asm volatile("or.w    #0x0700, %sr");

    *CRA_WR_ADDR = CMD_DISABLE_RX | CMD_DISABLE_TX;
    asm volatile("nop\n");
    *CRA_WR_ADDR = CMD_RESET_MR;

    *MR1A_MR2A_ADDR = MR1A_MODE_A_REG_1_CONFIG;
    *MR1A_MR2A_ADDR = MR2A_MODE_A_REG_2_CONFIG;
    *CSRA_WR_ADDR = CSRA_CLK_SELECT_REG_A_CONFIG;
    *ACR_WR_ADDR = ACR_AUX_CONTROL_REG_CONFIG;

    *CRA_WR_ADDR = CMD_RESET_ERROR;
    asm volatile("nop\n");
    *CRA_WR_ADDR = CMD_RESET_RX;
    asm volatile("nop\n");
    *CRA_WR_ADDR = CMD_RESET_TX;
    asm volatile("nop\n");
    *CRA_WR_ADDR = CMD_ENABLE_TX_RX;

    *MR1B_MR2B_ADDR = MR1A_MODE_A_REG_1_CONFIG;
    *MR1B_MR2B_ADDR = MR2A_MODE_A_REG_2_CONFIG;
    *CSRB_WR_ADDR = CSRA_CLK_SELECT_REG_A_CONFIG;
    *ACR_WR_ADDR = ACR_AUX_CONTROL_REG_CONFIG;

    *CRB_WR_ADDR = CMD_RESET_ERROR;
    asm volatile("nop\n");
    *CRB_WR_ADDR = CMD_RESET_RX;
    asm volatile("nop\n");
    *CRB_WR_ADDR = CMD_RESET_TX;
    asm volatile("nop\n");
    *CRB_WR_ADDR = CMD_ENABLE_TX_RX;

    // Disable interrupts
    *IMR_WR_ADDR = 0x00;

    // Turn ON Test LED
    *OPCR_WR_ADDR = 0x00;
    *OUT_SET_ADDR = 0xF0;
    *OUT_RESET_ADDR = 0xF0;

    // This slight delay prevents garbled output being sent during the welcome message
    delay(100);

    // Assert CTS
    *OUT_SET_ADDR = 0x01;

    putchar('\n');
    putchar('\n');

    return 0;
}

int getchar(void) {
    char in;
    char status;

    // Assert CTS
    *OUT_SET_ADDR = 0x01;
    while (1) {
        status = *SRA_RD_ADDR;
        if (status & SR_RX_READY) {
            // De-Assert CTS
            *OUT_RESET_ADDR = 0x01;
            return *RBA_RD_ADDR;
        }

        // Debugging - Set LEDs to the upper status bits of channel A
        if (in & 0xF0) {
            *OUT_SET_ADDR = in;
            *OUT_RESET_ADDR = (~in & 0xF0);
        }
    }
}

int putchar(int ch) {
    while (!(*SRA_RD_ADDR & SR_TX_READY)) { }
    *TBA_WR_ADDR = (char) ch;
    return ch;
}

int getchar_b(void) {
    char in;
    char status;

    // Assert CTS
    *OUT_SET_ADDR = 0x02;
    while (1) {
        status = *SRB_RD_ADDR;
        if (status & SR_RX_READY) {
            // De-Assert CTS
            *OUT_RESET_ADDR = 0x02;
            return *RBB_RD_ADDR;
        }

        // Debugging - Set LEDs to the upper status bits of channel A
        if (in & 0xF0) {
            *OUT_SET_ADDR = in;
            *OUT_RESET_ADDR = (~in & 0xF0);
        }
    }
}

int putchar_b(int ch) {
    while (!(*SRB_RD_ADDR & SR_TX_READY)) { }
    *TBB_WR_ADDR = (char) ch;
    return ch;
}

