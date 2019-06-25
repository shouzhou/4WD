
#include <LCD1602.h>
#include <delay.h>

sbit LCD_RS = P2^3;             
sbit LCD_RW = P2^4;
sbit LCD_EN = P2^5;


uchar code  cdis1[ ] = {" Red Control "};
uchar code  cdis2[ ] = {"  IR-CODE: --H  "};
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};


/*******************************************************************/
/*                                                                 */
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*                                                                 */
/*******************************************************************/ 

bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }

/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/

void lcd_wcmd(uchar cmd)

{                          
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
   // cmd = ((cmd&0x01)<<7)|((cmd&0x02)<<5)|((cmd&0x04)<<3)|((cmd&0x08)<<1)|((cmd&0x10)>>1)|((cmd&0x20)>>3)|((cmd&0x40)>>5)|((cmd&0x80)>>7);
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}

/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/

void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
//	dat = ((dat&0x01)<<7)|((dat&0x02)<<5)|((dat&0x04)<<3)|((dat&0x08)<<1)|((dat&0x10)>>1)|((dat&0x20)>>3)|((dat&0x40)>>5)|((dat&0x80)>>7);
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}

/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/

void lcd_init()
{ 
    delayms(15);                   
    lcd_wcmd(0x38);      //16*2显示，5*7点阵，8位数据
    delayms(5);
    lcd_wcmd(0x38);         
    delayms(5);
    lcd_wcmd(0x38);         
    delayms(5);

    lcd_wcmd(0x0c);      //显示开，关光标
    delayms(5);
    lcd_wcmd(0x06);      //移动光标
    delayms(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delayms(5);
}

/*******************************************************************/
/*                                                                 */
/*  设定显示位置                                                   */
/*                                                                 */
/*******************************************************************/

void lcd_pos(uchar pos)
{                          
  lcd_wcmd(pos | 0x80);  //数据指针=80+地址变量
}

