#ifndef USART_COM_H
#define USART_COM_H

//----------------------VARIABEL USART------------------//
#define BaudRateUSART1	19200;
#define BaudRateUSART2	19200;
#define BaudRateUSART3	19200;
#define BaudRateUSART4	38400;
#define BaudRateUSART5	38400;
#define BaudRateUSART6	38400;

/* Variable for USART func */
#define data_buffer 50 // For array data [i]
#define empty 0 // Empty
#define start 1 // Ready
#define full 2 // Full

#define  first_char  0x20  // Space
#define  last_char   0x7E  // '~'
#define  end_char    0x0D // CR

/* Variable for USART2 func */
#define data_buffer2 50 // For array data [i]
#define empty2 0 // Empty
#define start2 1 // Ready
#define full2 2 // Full

#define  first_char2  0x20  // Space
#define  last_char2   0x7E  // '~'
#define  end_char2    0x0D // CR
// #define  end_char2    0x0A // CR


/* Variable for USART6 func */
#define data_buffer6 50 // For array data [i]
#define empty6 0 //Empty
#define start6 1 // Ready
#define full6 2 // Full

#define  first_char6  0x20  // Space
#define  last_char6   0x7E  // '~'
#define  end_char6    0x0D // CR

/* Variable for USART5 func */
#define data_buffer5 50 // For array data [i]
#define empty5 0 //Empty
#define start5 1 // Ready
#define full5 2 // Full

#define  first_char5  0x20  // Space
#define  last_char5   0x7E  // '~'
#define  end_char5    0x0D // CR

/* Variable for USART4 func */
#define data_buffer4 50 // For array data [i]
#define empty4 0 //Empty
#define start4 1 // Ready
#define full4 2 // Full

#define  first_char4  0x20  // Space
#define  last_char4   0x7E  // '~'
#define  end_char4    0x0D // CR

extern char ReceivedByte[250]; // For Receive Data
extern int state; // Status
extern int i,o,u;
extern float pdc; //

extern char ReceivedByte2[250]; // For Receive Data
extern int state2; // Status
extern int i2; //

extern char ReceivedByte6[250]; // For Receive Data
extern int state6; // Status
extern int i6; //

extern int Header, Data1, Data2, Data3, Data4, Data5, Data6, Data7; //, Header;
extern int refbox, refbox2; //, Header;
extern int Header_5 , Data1_5 , Data2_5; //, Header;
extern int ModeGerdy;

extern char ReceivedByte5[250]; // For Receive Data
extern int state5; // Status
extern int i5; //

extern char ReceivedByte4[250]; // For Receive Data
extern int state4; // Status
extern int i4; //

extern float YawErrorBS[7];


extern char *pry1;
extern char *pry2;
extern char *pry3;
extern char *pry4;
extern char *pry5;
extern char *pry6;
extern int p;
extern int p2;
extern int p3;
extern int p4;
extern int p5;
extern int p6;

extern char rcv1, xsatu1;
extern char rcv2, xsatu2;
extern char rcv3, xsatu3;
extern char rcv4, xsatu4;
extern char rcv5, xsatu5;
extern char rcv6, xsatu6;
extern char zsatu1[50];
extern char DATAzsatu1[50];
extern char zsatu2[50];
extern char DATAzsatu2[50];
extern char zsatu3[50];
extern char DATAzsatu3[50];
extern char zsatu4[50];
extern char DATAzsatu4[50];
extern char zsatu5[50];
extern char DATAzsatu5[50];
extern char zsatu6[50];
extern char DATAzsatu6[50];

extern int check1;
extern int check2;
extern int check3;
extern int check4;
extern int check5;
extern int check6;
//------------------------------------------------------//

//----------------USART INIT----------------------------//
void USArt1_1_Init(void);
void USArt1_2_Init(void);
void USArt1_3_Init(void);
void UART_4_Init(void);
void UART_5_Init(void);
void USART_6_Init(void);
//------------------------------------------------------//

//----------------USART SEND FUNCTION-------------------//
void USART1_send(int c);
void USART1_sendString(char *ptr, int end_cmd);

void USART2_send(int c);
void USART2_sendString(char *ptr, int end_cmd);

void USART4_send();
void UART4_send(int c);
void UART4_sendString(char *ptr, int end_cmd);

void UART5_send(int c);
void UART5_sendString(char *ptr, int end_cmd);

void USART6_send(int c);
void USART6_sendString(char *ptr, int end_cmd);

//-------------USART RECEIVE FUNCTION- -----------------//
char USART1_receive(char px);
void USART1_receiveData(uint16_t in);
void USART1_Rx_Int(uint16_t in);
int USART1_receiveString(char *ptr);

char USART2_receive(char px);
void USART2_receiveData(uint16_t in2);
void USART2_Rx_Int(uint16_t in2);
int USART2_receiveString(char *ptr2);

void USART3_receiveData(uint16_t in);
void USART3_Rx_Int(uint16_t in);
int USART3_receiveString(char *ptr);

char UART4_receive(char px);
void UART4_receiveData(uint16_t in4);
void UART4_Rx_Int(uint16_t in4);
int UART4_receiveString(char *ptr4);

char UART5_receive(char px);
void UART5_receiveData(uint16_t in5);
void UART5_Rx_Int(uint16_t in5);
int UART5_receiveString(char *ptr5);

char USART6_receive(char px);
void USART6_receiveData(uint16_t in6);
void USART6_Rx_Int(uint16_t in6);
int USART6_receiveString(char *ptr6);
//------------------------------------------------------//

//-------------------IRQ HANDLER------------------------//
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART6_IRQHandler(void);
//------------------------------------------------------//

void cetak(USART_TypeDef* USARTx, const char *pFormat, ... );

#endif
