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
	int course = OUT;	//���ݒ�
	
	//��RA3 RA2 RA1 RA0��
	
	while(PORTAbits.RA4 || !flg)
		flg = PORTAbits.RA4;
		
	while(1){
		switch(~PORTA & 0x0F)	//�r�b�g���]
		{
			case 0b0110:
			case 0b1001:
				//���i
				PORTB = 0b10010000;
				__delay_ms(0.6);
    	   		PORTB=0b00000000;
       			__delay_ms(0.4);
       			break;
       			
			case 0b1110:
			case 0b1010:
			case 0b1100:
			case 0b1000:
				//������
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
				//�E����
				PORTB = 0b00010000;
				__delay_ms(1.2);
        		PORTB = 0b00000000;
       			__delay_ms(0.8);
       			course = LEFT;
				break;

			//���S�Z���T ���i
			case 0b0100:
				//��
				PORTB = 0b10010000;
				__delay_ms(0.6);

        		PORTB=0b00000000;
       			 __delay_ms(0.4);
       			// �\�z
       			course = RIGHT;	//�E�ɔ�яo��
				break;
				
			case 0b0010:
				//�E
				PORTB = 0b10010000;
				__delay_ms(0.6);

        		PORTB=0b00000000;
       			__delay_ms(0.4);
       			// �\�z
       			course = LEFT;	//���ɔ�яo��
				break;
				
			case 0b0000:
				//�R�[�X�A�E�g
				if(course == LEFT){	//�E����
					PORTB = 0b00010000;
					__delay_ms(1.6);

        			PORTB=0b00000000;
       				__delay_ms(0.4);
    			}else if(course == RIGHT){	//������
    				PORTB = 0b10000000;
					__delay_ms(1.6);
	
    	    		PORTB=0b00000000;
       				__delay_ms(0.4);
       			}else if(course == OUT){	//���߂͒��i
       				PORTB = 0b10010000;
					__delay_ms(0.6);
    	   			PORTB=0b00000000;
       				__delay_ms(0.4);
  				}     			
       			break;
       			
       		default:
       			//�p�X
       			/*
       			//���i
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