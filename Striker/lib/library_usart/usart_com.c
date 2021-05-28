#include "include_lib.h"
#include "usart_com.h"

char ReceivedByte[250]; // For Receive Data
int state; // Status
int i,o,u;
float pdc; //

char ReceivedByte2[250]; // For Receive Data
int state2; // Status
int i2; //

char ReceivedByte6[250]; // For Receive Data
int state6; // Status
int i6; //

int Header=0, Data1=0, Data2=0, Data3=0, Data4=0, Data5=0, Data6=0, Data7=0; //, Header;
int refbox = 0, refbox2=0; //, Header;
int Header_5 = 0, Data1_5 = 0, Data2_5 = 0; //, Header;
int ModeGerdy;

char ReceivedByte5[250]; // For Receive Data
int state5; // Status
int i5; //

char ReceivedByte4[250]; // For Receive Data
int state4; // Status
int i4; //

float YawErrorBS[7];


char *pry1;
char *pry2;
char *pry3;
char *pry4;
char *pry5;
char *pry6;
int p = 1;
int p2 = 1;
int p3 = 1;
int p4 = 1;
int p5 = 1;
int p6 = 1;

char rcv1, xsatu1;
char rcv2, xsatu2;
char rcv3, xsatu3;
char rcv4, xsatu4;
char rcv5, xsatu5;
char rcv6, xsatu6;
char zsatu1[50];
char DATAzsatu1[50];
char zsatu2[50];
char DATAzsatu2[50];
char zsatu3[50];
char DATAzsatu3[50];
char zsatu4[50];
char DATAzsatu4[50];
char zsatu5[50];
char DATAzsatu5[50];
char zsatu6[50];
char DATAzsatu6[50];

int check1;
int check2;
int check3;
int check4;
int check5;
int check6;
//------------------------------------------------------//

//----------------------------------------------------USART INIT--------------------------------------------------------//

void USArt1_1_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // enable APB1 peripheral clock for USART1
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // Connect USART1 pins to AF
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    /* Configure USART2 pins:  PD.5 Tx, PD.6 Rx */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure USART
    USART_InitStructure.USART_BaudRate = BaudRateUSART1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART2 receive interrupt

    NVIC_InitTypeDef  NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;            // we want to configure the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;// this sets the priority group of the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;           // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                      // the USART2 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);                                                      // the properties are passed to the NVIC_Init function which takes care of the low level stuff

	USART_Cmd(USART1, ENABLE);
}

void USArt1_2_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // enable APB1 peripheral clock for USART2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    // enable APB1 peripheral clock for GPIOA
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // Connect USART2 pins to AF
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

    /* Configure USART2 pins:  PD.5 Tx, PD.6 Rx */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // Configure USART
    USART_InitStructure.USART_BaudRate = BaudRateUSART2;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_2;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // enable the USART2 receive interrupt
    //USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);

    NVIC_InitTypeDef  NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;            // we want to configure the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                      // the USART2 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);                                                      // the properties are passed to the NVIC_Init function which takes care of the low level stuff

//     Enable USART2
    USART_Cmd(USART2, ENABLE);
}

void USArt1_3_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    // enable APB1 peripheral clock for USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    // enable APB1 peripheral clock for GPIOD
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // Connect USART3 pins to AF
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

    /* Configure USART3 pins:  PD.8 Tx, PD.9 Rx */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // Configure USART
    USART_InitStructure.USART_BaudRate = BaudRateUSART3;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_2;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // enable the USART2 receive interrupt
    //USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

    NVIC_InitTypeDef  NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;            // we want to configure the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;// this sets the priority group of the USART2 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                      // the USART2 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);                                                      // the properties are passed to the NVIC_Init function which takes care of the low level stuff

//     Enable USART3
    USART_Cmd(USART3, ENABLE);
}

void UART_4_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

    // enable APB1 peripheral clock for UART4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
    // enable APB1 peripheral clock for GPIOC
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // Connect USART2 pins to AF
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

    /* Configure USART2 pins:  PC.10 Tx, PC.11 Rx */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Configure USART
	USART_InitStructure.USART_BaudRate = BaudRateUSART4;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);

	//***************************Usart Interupt init****************************************************************************************//
	NVIC_InitTypeDef  NVIC_InitStructure;
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt
	//USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;                // we want to configure the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;// this sets the priority group of the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;               // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                  // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);                                                  // the properties are passed to the NVIC_Init function which takes care of the low level stuff
	//**************************************************************************************************************************************//

	// Enable USART4
	USART_Cmd(UART4, ENABLE);
}

void UART_5_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	// enable APB2 peripheral clock for UART5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	// enable APB1 peripheral clock for GPIOC & GPIOD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// Connect UART5 pins to AF
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

	/* Configure UART5 pins:  PC.12 Tx */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure UART5 pins:  PD.2 Rx */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// Configure USART
	USART_InitStructure.USART_BaudRate = BaudRateUSART5;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure);


	//***************************Usart Interupt init****************************************************************************************//
	NVIC_InitTypeDef  NVIC_InitStructure;
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt
	//USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;                // we want to configure the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;// this sets the priority group of the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;               // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                  // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);                                                  // the properties are passed to the NVIC_Init function which takes care of the low level stuff
	//**************************************************************************************************************************************//

	// Enable UART5
	USART_Cmd(UART5, ENABLE);
}

void USART_6_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;


    // enable APB2 peripheral clock for USART6
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
    // enable APB1 peripheral clock for GPIOA
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);


    // Connect USART6 pins to AF
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);


    /* Configure USART6 pins:  PC.6 Tx, PC.7 Rx */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Configure USART
    USART_InitStructure.USART_BaudRate = BaudRateUSART6;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_2;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART6, &USART_InitStructure);

    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE); // enable the USART6 receive interrupt
//    USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;            // we want to configure the USART6 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;// this sets the priority group of the USART6 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;           // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                      // the USART2 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure);                                                      // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    // Enable USART6
    USART_Cmd(USART6, ENABLE);
}
//----------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------USART SEND FUNCTION------------------------------------------------------//
// Send USART1
void USART1_send(int c)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Wait empty
    USART_SendData(USART1, c); // Send char
}

// Send string data USART1
void USART1_sendString(char *ptr, int end_cmd)
{
    while (*ptr != 0)
    {
        USART1_send(*ptr);
        ptr++;
    }

    if(end_cmd == 0)
    {
        USART1_send(0x0A); // send LineFeed
        USART1_send(0x0D); // send CariageReturn
    }
    else if(end_cmd == 1)
    {
        USART1_send(0x0D); // send CariageReturn
        USART1_send(0x0A); // send LineFeed
    }
    else if(end_cmd == 2)
    {
        USART1_send(0x0A); // send LineFeed
    }
    else if(end_cmd == 3)
    {
        USART1_send(0x0D); // send CariageReturn
    }
}

void USART2_send(int c)
{
    USART_ClearFlag(USART2,USART_FLAG_TXE);

    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait empty
    USART_SendData(USART2, c); // Send char


}

void USART2_sendString(char *ptr, int end_cmd)
{
    while (*ptr != 0)
    {
        USART2_send(*ptr);
        ptr++;
    }

    if(end_cmd == 0)
    {
        USART2_send(0x0A); // send LineFeed
        USART2_send(0x0D); // send CariageReturn
    }
    else if(end_cmd == 1)
    {
        USART2_send(0x0D); // send CariageReturn
        USART2_send(0x0A); // send LineFeed
    }
    else if(end_cmd == 2)
    {
        USART2_send(0x0A); // send LineFeed
    }
    else if(end_cmd == 3)
    {
        USART2_send(0x0D); // send CariageReturn
    }
}

void UART4_send(int c)
{
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET); // Wait empty
	USART_SendData(UART4, c); // Send char
}
void USART4_send(){
	int posisi_robot;
	if (Program_Untuk == ORION) posisi_robot = T_ORION.Keadaan_Robot ;
	else if (Program_Untuk == HYDRA) posisi_robot = T_HYDRA.Keadaan_Robot ;
	cetak(UART4,"12,%d,%d,%d,1,1,1,1\r",(int)X_Oddo_cm[5],(int)Y_Oddo_cm[5],(int)posisi_robot);
	cetak(UART5,"12,%d,%d,%d,1,1,1,1\r",(int)X_Oddo_cm[5],(int)Y_Oddo_cm[5],(int)posisi_robot);
}

void UART4_sendString(char *ptr, int end_cmd)
{
	while (*ptr != 0)
	{
		UART4_send(*ptr);
		ptr++;
	}

	if(end_cmd == 0)
	{
		UART4_send(0x0A); // send LineFeed
		UART4_send(0x0D); // send CariageReturn
	}
	else if(end_cmd == 1)
	{
		UART4_send(0x0D); // send CariageReturn
		UART4_send(0x0A); // send LineFeed
	}
	else if(end_cmd == 2)
	{
		UART4_send(0x0A); // send LineFeed
	}
	else if(end_cmd == 3)
	{
		UART4_send(0x0D); // send CariageReturn
	}
}

void UART5_send(int c)
{
	while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET); // Wait empty
	USART_SendData(UART5, c); // Send char
}

void UART5_sendString(char *ptr, int end_cmd)
{
	while (*ptr != 0)
	{
		UART5_send(*ptr);
		ptr++;
	}

	if(end_cmd == 0)
	{
		UART5_send(0x0A); // send LineFeed
		UART5_send(0x0D); // send CariageReturn
	}
	else if(end_cmd == 1)
	{
		UART5_send(0x0D); // send CariageReturn
		UART5_send(0x0A); // send LineFeed
	}
	else if(end_cmd == 2)
	{
		UART5_send(0x0A); // send LineFeed
	}
	else if(end_cmd == 3)
	{
		UART5_send(0x0D); // send CariageReturn
	}
}

void USART6_send(int c)
{
    USART_ClearFlag(USART6,USART_FLAG_TXE);

    while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET); // Wait empty
    USART_SendData(USART6, c); // Send char
}

// Send string data USART6
void USART6_sendString(char *ptr, int end_cmd)
{
    while (*ptr != 0)
    {
        USART6_send(*ptr);
        ptr++;
    }

    if(end_cmd == 0)
    {
        USART6_send(0x0A); // send LineFeed
        USART6_send(0x0D); // send CariageReturn
    }
    else if(end_cmd == 1)
    {
        USART6_send(0x0D); // send CariageReturn
        USART6_send(0x0A); // send LineFeed
    }
    else if(end_cmd == 2)
    {
        USART6_send(0x0A); // send LineFeed
    }
    else if(end_cmd == 3)
    {
        USART6_send(0x0D); // send CariageReturn
    }
}

//------------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------USART RECEIVE FUNCTION-----------------------------------------------------//
// USART Receive
char USART1_receive(char px)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET); // Wait char
    px=USART_ReceiveData(USART1);

    return px;
}
// Receive Data
void USART1_receiveData(uint16_t in)
{
    if (i < data_buffer)
    {
        if (state == empty)
        {
            if ((in >= first_char) && (in <= last_char))
            {
                ReceivedByte[i] = in;
                i++;
            }
            if (in == end_char)
            {
                ReceivedByte[i] = in;
                state = start;
            }
        }
    }
    else
    {
        state = full;
    }
}
// For Receive
void USART1_Rx_Int(uint16_t in)
{
    USART1_receiveData(in);

}
// Receive String Data
int USART1_receiveString(char *ptr)
{
    int take_in = empty;
    uint8_t n, in;

    if (state == start)
    {
        take_in = start;

        n = 0;
        do
        {
            in = ReceivedByte[n];
            if (in != end_char)
            {

                ptr[n] = in;
                n++;
            }
        } while (in != end_char);

        ptr[n] = 0x00; // 0

        ReceivedByte[0] = end_char;
        i = 0;
        state = empty;
    }
    else if (state == full)
    {
        take_in = full;
        ReceivedByte[0] = end_char;
        i = 0;
        state = empty;
    }

    return (take_in);
}

// USART Receive
char USART2_receive(char px)
{
    while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET); // Wait char
    px=USART_ReceiveData(USART2);

    return px;
}
// Receive Data
void USART2_receiveData(uint16_t in2)
{
    if (i2 < data_buffer2)
    {
        if (state2 == empty2)
        {
            if ((in2 >= first_char2) && (in2 <= last_char2))
            {
                ReceivedByte2[i2] = in2;
                i2++;
            }
            if (in2 == end_char2)
            {
                ReceivedByte2[i2] = in2;
                state2 = start2;
            }
        }
    }
    else
    {
        state2 = full2;
    }
}


// For Receive
void USART2_Rx_Int(uint16_t in2)
{
    USART2_receiveData(in2);
}

// Receive String Data
int USART2_receiveString(char *ptr2)
{
    int take_in2 = empty2;
    uint8_t n2, in2;

    if (state2 == start2)
    {
        take_in2 = start2;
        // imu_filter = 90;

        n2 = 0;
        do
        {
            in2 = ReceivedByte2[n2];
            if (in2 != end_char2)
            {

                ptr2[n2] = in2;
                n2++;
            }
        } while (in2 != end_char2);

        ptr2[n2] = 0x00; // 0

        ReceivedByte2[0] = end_char2;
        i2 = 0;
        state2 = empty2;
    }
    else if (state2 == full2)
    {
        take_in2 = full2;
        ReceivedByte2[0] = end_char2;
        i2 = 0;
        state2 = empty2;
    }

    return (take_in2);
}

void USART3_receiveData(uint16_t in)
{
    if (i < data_buffer)
    {
        if (state == empty)
        {
            if ((in >= first_char) && (in <= last_char))
            {
                ReceivedByte[i] = in;
                i++;
            }
            if (in == end_char)
            {
                ReceivedByte[i] = in;
                state = start;
            }
        }
    }
    else
    {
        state = full;
    }
}

void USART3_Rx_Int(uint16_t in)
{
    USART3_receiveData(in);

}
// Receive String Data
int USART3_receiveString(char *ptr)
{
    int take_in = empty;
    uint8_t n, in;

    if (state == start)
    {
        take_in = start;

        n = 0;
        do
        {
            in = ReceivedByte[n];
            if (in != end_char)
            {

                ptr[n] = in;
                n++;
            }
        } while (in != end_char);

        ptr[n] = 0x00; // 0

        ReceivedByte[0] = end_char;
        i = 0;
        state = empty;
    }
    else if (state == full)
    {
        take_in = full;
        ReceivedByte[0] = end_char;
        i = 0;
        state = empty;
    }

    return (take_in);
}

char UART4_receive(char px)
{
	while(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET); // Wait char
	px=USART_ReceiveData(UART4);

	return px;
}

void UART4_receiveData(uint16_t in4)
{
	if (i4 < data_buffer)
	{
		if (state4 == empty4)
		{
			if ((in4 >= first_char4) && (in4 <= last_char4))
			{
				ReceivedByte4[i4] = in4;
				i4++;
			}
			if (in4 == end_char4)
			{
				ReceivedByte4[i4] = in4;
				state4 = start4;
			}
		}
	}
	else
	{
		state4 = full4;
	}
}

// For Receive
void UART4_Rx_Int(uint16_t in4)
{
	UART4_receiveData(in4);
}

int UART4_receiveString(char *ptr4)
{
	int take_in4 = empty4;
	uint8_t n4, in4;

	if (state4 == start4)
	{
		take_in4 = start4;

		n4 = 0;
		do
		{
			in4 = ReceivedByte4[n4];
			if (in4 != end_char4)
			{

				ptr4[n4] = in4;
				n4++;
			}
		} while (in4 != end_char4);

		ptr4[n4] = 0x00; // 0

		ReceivedByte4[0] = end_char4;
		i4 = 0;
		state4 = empty4;
	}
	else if (state4 == full4)
	{
		take_in4 = full4;
		ReceivedByte4[0] = end_char4;
		i4 = 0;
		state4 = empty4;
	}

	return (take_in4);
}

char UART5_receive(char px)
{
	while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET); // Wait char
	px=USART_ReceiveData(UART5);

	return px;
}
void UART5_receiveData(uint16_t in5)
{
	if (i5 < data_buffer)
	{
		if (state5 == empty5)
		{
			if ((in5 >= first_char5) && (in5 <= last_char5))
			{
				ReceivedByte5[i5] = in5;
				i5++;
			}
			if (in5 == end_char5)
			{
				ReceivedByte5[i5] = in5;
				state5 = start5;
			}
		}
	}
	else
	{
		state5 = full5;
	}
}
// For Receive
void UART5_Rx_Int(uint16_t in5)
{
	UART5_receiveData(in5);
}
int UART5_receiveString(char *ptr5)
{
	int take_in5 = empty5;
	uint8_t n5, in5;

	if (state5 == start5)
	{
		take_in5 = start5;

		n5 = 0;
		do
		{
			in5 = ReceivedByte5[n5];
			if (in5 != end_char5)
			{

				ptr5[n5] = in5;
				n5++;
			}
		} while (in5 != end_char5);

		ptr5[n5] = 0x00; // 0

		ReceivedByte5[0] = end_char5;
		i5 = 0;
		state5 = empty5;
	}
	else if (state5 == full5)
	{
		take_in5 = full5;
		ReceivedByte5[0] = end_char5;
		i5 = 0;
		state5 = empty5;
	}

	return (take_in5);
}

char USART6_receive(char px)
{
    while(USART_GetFlagStatus(USART6, USART_FLAG_RXNE) == RESET); // Wait char
    px=USART_ReceiveData(USART6);

    return px;
}

// Receive Data
void USART6_receiveData(uint16_t in6)
{
    if (i6 < data_buffer6)
    {
        if (state6 == empty6)
        {
            if ((in6 >= first_char6) && (in6 <= last_char6))
            {
                ReceivedByte6[i6] = in6;
                i6++;
            }
            if (in6 == end_char6)
            {
                ReceivedByte6[i6] = in6;
                state6 = start6;
            }
        }
    }
    else
    {
        state6 = full6;
    }
}
// For Receive
void USART6_Rx_Int(uint16_t in6)
{
    USART6_receiveData(in6);

}
// Receive String Data
int USART6_receiveString(char *ptr6)
{
    int take_in6 = empty6;
    uint8_t n6, in6;

    if (state6 == start6)
    {
        take_in6 = start6;

        n6 = 0;
        do
        {
            in6 = ReceivedByte6[n6];
            if (in6 != end_char6)
            {

                ptr6[n6] = in6;
                n6++;
            }
        } while (in6 != end_char6);

        ptr6[n6] = 0x00; // 0

        ReceivedByte6[0] = end_char6;
        i6 = 0;
        state6 = empty6;
    }
    else if (state6 == full6)
    {
        take_in6 = full6;
        ReceivedByte6[0] = end_char6;
        i6 = 0;
        state6 = empty6;
    }

    return (take_in6);
}

//----------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------IRQ HANDLER--------------------------------------------------------//

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
        xsatu2 = USART2->DR;
    }
    USART2_Rx_Int(xsatu2);

    check2 = USART2_receiveString(zsatu2);
    
    if (check2 == start)
    {
    	strcpy(DATAzsatu2, zsatu2);
    	pry2 = strtok(zsatu2, ",");
    	while (pry2 != '\0' && p2 <= 3 )
    	{
    		if (p2 == 1)
    		{
    			kalibrasi_imu = atof(pry2);
    		}
    		else if (p2 == 2)
    		{
    			imu_asli = atof(pry2);
    		}
    		else if (p2 == 3)
    		{
    			imu_filter = atof(pry2);
    			imu_real = imu_filter;
    			imu_filter -= (reset_imu + start_hadap);
    		}
    		pry2 = strtok ('\0', ",");
    		p2++;
    	}
    	if (p2 >= 4)p2 = 1;
    }
}

void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    { 
        xsatu3 = USART3->DR;
    }
    USART3_Rx_Int(xsatu3);

    check3 = USART3_receiveString(zsatu3);

    if (check3 == start)
    {
        strcpy(DATAzsatu3, zsatu3);

        pry3 = strtok(zsatu3, ",");

        while (pry3 != '\0' && p3 <= 5 )
        {
            if (p3 == 1)
            {
            	Tuas_Switch1 = atof(pry3);	//limit_switch atas
            }
            else if (p3 == 2)
            {
            	Tuas_Switch2 = atof(pry3);	//limit_switch bawah
            }
            else if (p3 == 3)
            {
            	Tuas_Pot = atof(pry3);		//resistor geser
            }
            else if (p3 == 4)
            {
            	Griper_Pot1 = atof(pry3);	//gripper kanan
            }
            else if (p3 == 5)
            {
            	Griper_Pot2 = atof(pry3);	//gripper kiri
            }
            pry3 = strtok ('\0', ",");

            p3++;
        }
        if (p3 == 6) p3 = 1;

    }
}

void UART4_IRQHandler(void)
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) == SET)
	{
		xsatu4 = UART4->DR;
	}

	UART4_Rx_Int(xsatu4);
	check4 = UART4_receiveString(zsatu4);

	if (check4 == start4)
	{
		strcpy(DATAzsatu4, zsatu4);
		pry4 = strtok(zsatu4, ",");
		while (pry4 != '\0' && p4 <= 6 )
		{
			if (p4 == 1)
			{
				Header = atof(pry4);
			}
			else if (p4 == 2)
			{
				Data1 = atof(pry4);
			}
			else if (p4 == 3)
			{
				Data2 = atof(pry4);
			}
			else if (p4 == 4)
			{
				Data3 = atof(pry4);
			}
			else if (p4 == 5)
			{
				Data4 = atof(pry4);
			}
			else if (p4 == 6)
			{
				Data5 = atof(pry4);
			}
			pry4 = strtok ('\0', ",");
			p4++;
		}
		if (p4 >= 7)p4 = 1;
	}
//	Data_MiniPC_Identification();
//	Parsing_Data();
	Parsing_Data_Online();

}

void UART5_IRQHandler(void)
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) == SET)
	{
		xsatu5 = UART5->DR;
	}

	UART5_Rx_Int(xsatu5);
	check5 = UART5_receiveString(zsatu5);

	if (check5 == start5)
	{
		strcpy(DATAzsatu5, zsatu5);
		pry5 = strtok(zsatu5, ",");
		while (pry5 != '\0' && p5 <= 6 )
		{
			if (p5 == 1)
			{
				Header = atof(pry5);
			}
			else if (p5 == 2)
			{
				Data1 = atof(pry5);
			}
			else if (p5 == 3)
			{
				Data2 = atof(pry5);
			}
			else if (p5 == 4)
			{
				Data3 = atof(pry5);
			}
			else if (p5 == 5)
			{
				Data4 = atof(pry5);
			}
			else if (p5 == 6)
			{
				Data5 = atof(pry5);
			}
			pry5 = strtok ('\0', ",");
			p5++;
		}
		if (p5 >= 7)p5 = 1;
	}

//	Data_MiniPC_Identification();
//	Parsing_Data();
	Parsing_Data_Online();
}

void USART6_IRQHandler(void)
{
    if (USART_GetITStatus(USART6, USART_IT_RXNE) == SET)
    {
        xsatu6 = USART6->DR;
    }

    USART6_Rx_Int(xsatu6);
    check6 = USART6_receiveString(zsatu6);

    if (check6 == start6)
    {
        strcpy(DATAzsatu6, zsatu6);
        pry6 = strtok(zsatu6, ",");
		while (pry6 != '\0' && p6 <= 5 )
		{
			if (p6 == 1)
			{
				Header = atof(pry6);
			}
			else if (p6 == 2)
			{
				Data1 = atof(pry6);
			}
			else if (p6 == 3)
			{
				Data2 = atof(pry6);
			}
			else if (p6 == 4)
			{
				Data3 = atof(pry6);
			}
			else if (p6 == 5)
			{
				Data4 = atof(pry6);
			}
			else if (p6 == 6)
			{
				Data5 = atof(pry6);
			}
			pry6 = strtok ('\0', ",");
			p6++;
		}
		if (p6 >= 7)p6 = 1;
    }
//	Data_MiniPC_Identification();
}

void cetak(USART_TypeDef* USARTx, const char *pFormat, ... )
{
    va_list ap;
    char pStr[100];

    va_start(ap, pFormat);
    vsprintf(pStr, pFormat, ap);
    va_end(ap);

    int i=0;
    int n = strlen(pStr);
    for(i=0;i<n;i++)
    {
        USART_SendData(USARTx, (uint8_t)pStr[i]);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
    }
}
