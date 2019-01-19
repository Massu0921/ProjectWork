/*
	�����R�[�X�p
	����d�� 5.0V���x���ǂ�
	�E���[�^�[�s�� -> �d�r�{�b�N�X����ړ��ŉ���

	�i�s�����E�Z���T�ʒu
	��RA3 RA2 RA1 RA0��
*/
#include<XC.h>
#include<pic16f84a.h>

#pragma config FOSC=HS
#pragma config WDTE=OFF
#pragma config PWRTE=ON
#define _XTAL_FREQ 10000000

// �R�[�X�A�E�g����p
#define LEFT 1
#define RIGHT 2
#define	OUT	3

void main(void){
	TRISA = 0x1F;
	TRISB = 0x00;
	int flg = 0;		// �X�^�[�g�p�t���O
	int course = OUT;	// �R�[�X�A�E�g�L���p ���ݒ�
	
	while(PORTAbits.RA4 || !flg)	// �X�^�[�g�X�C�b�`���������܂őҋ@
		flg = PORTAbits.RA4;
		
	// �X�^�[�g
	while(1){
		switch(~PORTA & 0x0F)	// ���Z���T�l�̃r�b�g���] (����1 -> ����1)
		{
			// ���[�E����2����
			case 0b0110:
			case 0b1001:
				// ���i
				PORTB = 0b10010000;
				__delay_ms(0.5);
    	   		PORTB=0b00000000;
       			__delay_ms(0.3);
       			break;
       		
       		// ���Z���T����
			case 0b1110:
			case 0b1010:
			case 0b1100:
			case 0b1000:
				// ������
				PORTB = 0b10000000;
				__delay_ms(1.4);
        		PORTB = 0b00000000;
       			__delay_ms(0.6);
       			// �͂ݏo�����ꍇ
       			course = RIGHT;		// �Ō�ɍ��Z���T����:�E�ɔ�яo��
				break;
			
			// �E�Z���T����
			case 0b0111:
			case 0b0101:
			case 0b0011:
			case 0b0001:
				// �E����
				PORTB = 0b00010000;
				__delay_ms(1.4);
        		PORTB = 0b00000000;
       			__delay_ms(0.6);
       			course = LEFT;		// �Ō�ɉE�Z���T����:���ɔ�яo��
				break;

			// ���S�Z���T
			case 0b0100:
				// �������� ����������
				PORTB = 0b10010000;
				__delay_ms(0.2);
				PORTB = 0b10000000;
				__delay_ms(0.02);
        		PORTB = 0b00000000;
       			 __delay_ms(0.15);
       			// �\�z
       			course = RIGHT;		// �E�ɔ�яo��
				break;
				
			case 0b0010:
				//�E������ �����E����
				PORTB = 0b10010000;
				__delay_ms(0.2);
				PORTB = 0b00010000;
				__delay_ms(0.02);
        		PORTB = 0b00000000;
       			__delay_ms(0.15);
       			// �\�z
       			course = LEFT;		// ���ɔ�яo��
				break;
				
			// �R�[�X�A�E�g
			case 0b0000:
				if(course == LEFT){		// ����яo��
					// �E����
					PORTB = 0b00010000;
					__delay_ms(1.4);
        			PORTB = 0b00000000;
       				__delay_ms(0.6);
    			}else if(course == RIGHT){		// �E��яo��
    				// ������
					PORTB = 0b10000000;
					__delay_ms(1.4);
        			PORTB = 0b00000000;
       				__delay_ms(0.6);
       			}else if(course == OUT){	// ���߂͒��i
       				PORTB = 0b10010000;
					__delay_ms(0.7);
    	   			PORTB = 0b00000000;
       				__delay_ms(0.4);
  				}     			
       			break;
       			
			// ���̑�
       		default:
       			// �čs
       			break;
  		}
 	}
	
 	PORTB = 0x00;
 	return;
}				