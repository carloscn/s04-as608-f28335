
#ifndef INC_SCI_H_
#define INC_SCI_H_


#define SCI_FREQ     100E3
#define SCI_PRD      (LSPCLK_FREQ/(SCI_FREQ*8))-1


void scia_fifo_init();
void scib_fifo_init();
void scic_fifo_init();
extern void    SCI_INIT( void );
extern void scib_msg(char * msg);
extern void scib_xmit(int a);
extern void scia_msg(char * msg);
extern void scia_xmit(int a);
extern void scic_msg(char * msg);
extern void scic_xmit(int a);
extern void scia_send_temp(float *a);
// Prototype statements for functions found within this file.
__interrupt void sciaRxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);
__interrupt void scicRxFifoIsr(void);
// Global variables

#endif /* INC_SCI_H_ */
