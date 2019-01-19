/*
	高速コース用
	動作電圧 5.0V程度が良い
	右モーター不調 -> 電池ボックス後方移動で解決

	進行方向・センサ位置
	↑RA3 RA2 RA1 RA0↑
*/
#include<XC.h>
#include<pic16f84a.h>

#pragma config FOSC=HS
#pragma config WDTE=OFF
#pragma config PWRTE=ON
#define _XTAL_FREQ 10000000

// コースアウト判定用
#define LEFT 1
#define RIGHT 2
#define	OUT	3

void main(void){
	TRISA = 0x1F;
	TRISB = 0x00;
	int flg = 0;		// スタート用フラグ
	int course = OUT;	// コースアウト記憶用 仮設定
	
	while(PORTAbits.RA4 || !flg)	// スタートスイッチが押されるまで待機
		flg = PORTAbits.RA4;
		
	// スタート
	while(1){
		switch(~PORTA & 0x0F)	// 光センサ値のビット反転 (黒で1 -> 白で1)
		{
			// 両端・中央2つが白
			case 0b0110:
			case 0b1001:
				// 直進
				PORTB = 0b10010000;
				__delay_ms(0.5);
    	   		PORTB=0b00000000;
       			__delay_ms(0.3);
       			break;
       		
       		// 左センサが白
			case 0b1110:
			case 0b1010:
			case 0b1100:
			case 0b1000:
				// 左旋回
				PORTB = 0b10000000;
				__delay_ms(1.4);
        		PORTB = 0b00000000;
       			__delay_ms(0.6);
       			// はみ出した場合
       			course = RIGHT;		// 最後に左センサ反応:右に飛び出し
				break;
			
			// 右センサが白
			case 0b0111:
			case 0b0101:
			case 0b0011:
			case 0b0001:
				// 右旋回
				PORTB = 0b00010000;
				__delay_ms(1.4);
        		PORTB = 0b00000000;
       			__delay_ms(0.6);
       			course = LEFT;		// 最後に右センサ反応:左に飛び出し
				break;

			// 中心センサ
			case 0b0100:
				// 左側が白 少し左旋回
				PORTB = 0b10010000;
				__delay_ms(0.2);
				PORTB = 0b10000000;
				__delay_ms(0.02);
        		PORTB = 0b00000000;
       			 __delay_ms(0.15);
       			// 予想
       			course = RIGHT;		// 右に飛び出す
				break;
				
			case 0b0010:
				//右側が白 少し右旋回
				PORTB = 0b10010000;
				__delay_ms(0.2);
				PORTB = 0b00010000;
				__delay_ms(0.02);
        		PORTB = 0b00000000;
       			__delay_ms(0.15);
       			// 予想
       			course = LEFT;		// 左に飛び出す
				break;
				
			// コースアウト
			case 0b0000:
				if(course == LEFT){		// 左飛び出し
					// 右旋回
					PORTB = 0b00010000;
					__delay_ms(1.4);
        			PORTB = 0b00000000;
       				__delay_ms(0.6);
    			}else if(course == RIGHT){		// 右飛び出し
    				// 左旋回
					PORTB = 0b10000000;
					__delay_ms(1.4);
        			PORTB = 0b00000000;
       				__delay_ms(0.6);
       			}else if(course == OUT){	// 初めは直進
       				PORTB = 0b10010000;
					__delay_ms(0.7);
    	   			PORTB = 0b00000000;
       				__delay_ms(0.4);
  				}     			
       			break;
       			
			// その他
       		default:
       			// 惰行
       			break;
  		}
 	}
	
 	PORTB = 0x00;
 	return;
}				