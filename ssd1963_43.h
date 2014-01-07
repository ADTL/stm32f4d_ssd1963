#ifndef WF43ATIBEDB
#define WF43ATIBEDB

void Send_WF43_Byte(unsigned char data);
void Write_WF43_C(unsigned char command, unsigned char args);
void Write_WF43_D(unsigned char command);
void SSD1963_init(void);
void FULL_ON(unsigned long dat);
void WindowSet(unsigned int s_x,unsigned int e_x,unsigned int s_y,unsigned int e_y);
void Write_Command(unsigned char command);
void SendData(uint32_t color);
void FillWin(unsigned long dat,unsigned short x, unsigned short y, unsigned short w, unsigned short h);
void ShowTest(void);
void TFT_putChar(unsigned short x, unsigned short y, char c);
void TFT_printf(unsigned short x, unsigned short y, char *arg_list, ...);
void SSD1963_lowlevelinit(void);
void SSD1963_reset_init(void);

#endif
