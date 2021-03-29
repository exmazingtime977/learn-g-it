#include <mega32.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 8000000UL
#define eq     12
#define jaam   13
#define taqsim 14
#define zarb   15
#define menha  16
int key = 111;
int flag = 13;
int j = 13;
int on = 0;
int k = 1;
void command (unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_print(char *p);
unsigned char adad[15];
int encr_decr(void){
    while(on == 0){
    if (flag == j) k = 1;
    if (flag != j) { 
    k = 2;
    flag = j;
    }  
    command(0XC0);//Forced the cursor to the first position of second line.  
    if (k == 1){
        key = key - 1;
        lcd_print("Descending");
        }
        
    if (k == 2){  
        key = key + 1;
        lcd_print("Ascending");
        }
    }
return (k);
}
char keyboard_read(void){

    //step 1 ofoghi A
    PORTB.4=0;
    delay_ms(5);
    if(PINB.0 == 0) key= 7;
    if(PINB.1 == 0) key= 8;
    if(PINB.2 == 0) key= 9;
    //if(PINB.3==0) key= '/';
    PORTB.4=1;
    //step 2 ofoghi B
    PORTB.5 = 0;
    delay_ms(5);
    if(PINB.0 == 0) key = 4;
    if(PINB.1 == 0) key = 5;
    if(PINB.2 == 0) key = 6;
    if(PINB.3 == 0) flag = 1; //zarb varedshode
    PORTB.5 = 1;
    //step 3 ofoghi C
    PORTB.6 = 0;
    delay_ms(5);
    if(PINB.0 == 0) key = 1;
    if(PINB.1 == 0) key = 2;
    if(PINB.2 == 0) key = 3;
    //if(PINB.3==0) key='-';
    PORTB.6 = 1;
    //step 4 ofoghi D
    PORTB.7 = 0;
    delay_ms(5);
    if(PINB.0 == 0) on = 1;
    if(PINB.1 == 0) key = 0;
    //if(PINB.2==0) key='=';
    //if(PINB.3==0) key='+';
    PORTB.4 = 1;   
    
return key;
}

void main (void){
    DDRB = 0xF0;
    DDRC = 0XFF;//This register is used for selecting the R/S and R/W pin.
	DDRD = 0XFF;//This register is used to give the data or commands.
	command(0x38);//Activated 2 lines in 8-bit mode.
	command(0X0F);//Display is ON, cursor is blinking.
	command(0x01);//Clearing the display.
        while(1){
        command(0X80);//Forced the cursor to first position of first line.           
        keyboard_read(); 
        //tabe kam ya ziad shodan ra tashkhis bede
        encr_decr();   
        sprintf(adad,"%d",key);   
        lcd_print(adad);
        delay_ms(1000);
        command(0X80);//Forced the cursor to first position of first line.           
        lcd_print(adad);
        delay_ms(1000);
        on = 0;   
        command(0X01);//Clearing the display.
	    delay_ms(1000);
}}
void command (char cmd)
{
	PORTC = 0X02;
	PORTD = cmd;
	PORTC = 0X00;
	delay_ms(15);
}
void lcd_data(char data)
{
	PORTC = 0X03;
	PORTD = data;
	PORTC = 0X01;
	delay_ms(15);
}
void lcd_print(char *p)
{
	while(*p)
	{
		lcd_data(*p++);
	}
}
