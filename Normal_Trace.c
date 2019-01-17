#include<XC.h>
#include<pic16f84a.h>

#pragma config FOSC=HS
#pragma config WDTE=OFF
#pragma config PWRTE=ON
#define _XTAL_FREQ 10000000

#define LEFT 1
#define RIGHT 2
#define	OUT	3

void main(void){
	TRISA = 0x1F;
	TRISB = 0x00;
	int flg = 0;
	int course = OUT;	//仮設定
	
	//↑RA3 RA2 RA1 RA0↑
	
	while(PORTAbits.RA4 || !flg)
		flg = PORTAbits.RA4;
		
	while(1){
		switch(~PORTA & 0x0F)	//ビット反転
		{
			case 0b0110:
			case 0b1001:
				//直進
				PORTB = 0b10010000;
				__delay_ms(0.6);
    	   		PORTB=0b00000000;
       			__delay_ms(0.4);
       			break;
       			
			case 0b1110:
			case 0b1010:
			case 0b1100:
			case 0b1000:
				//左旋回
				PORTB = 0b10000000;
				__delay_ms(1.2);

        		PORTB=0b00000000;
       			__delay_ms(0.8);
       			course = RIGHT;
				break;
			
			case 0b0111:
			case 0b0101:
			case 0b0011:
			case 0b0001:
				//右旋回
				PORTB = 0b00010000;
				__delay_ms(1.2);
        		PORTB = 0b00000000;
       			__delay_ms(0.8);
       			course = LEFT;
				break;

			//中心センサ 直進
			case 0b0100:
				//左
				PORTB = 0b10010000;
				__delay_ms(0.6);

        		PORTB=0b00000000;
       			 __delay_ms(0.4);
       			// 予想
       			course = RIGHT;	//右に飛び出す
				break;
				
			case 0b0010:
				//右
				PORTB = 0b10010000;
				__delay_ms(0.6);

        		PORTB=0b00000000;
       			__delay_ms(0.4);
       			// 予想
       			course = LEFT;	//左に飛び出す
				break;
				
			case 0b0000:
				//コースアウト
				if(course == LEFT){	//右旋回
					PORTB = 0b00010000;
					__delay_ms(1.6);

        			PORTB=0b00000000;
       				__delay_ms(0.4);
    			}else if(course == RIGHT){	//左旋回
    				PORTB = 0b10000000;
					__delay_ms(1.6);
	
    	    		PORTB=0b00000000;
       				__delay_ms(0.4);
       			}else if(course == OUT){	//初めは直進
       				PORTB = 0b10010000;
					__delay_ms(0.6);
    	   			PORTB=0b00000000;
       				__delay_ms(0.4);
  				}     			
       			break;
       			
       		default:
       			//パス
       			/*
       			//直進
				PORTB = 0b10010000;
				__delay_ms(0.6);
    	   		PORTB=0b00000000;
       			__delay_ms(0.4);
       			*/
       			break;
  		}
 	}
 	PORTB = 0x00;
 	return;
}				