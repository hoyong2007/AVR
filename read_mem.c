/*
 * HW.c
 *
 * Created: 2017-02-16 오전 5:39:31
 * Author : my
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


/*
	PORTA : write
		- A0 : CS
		- A1 : SK
		- A2 : DI
		- A3 : VCC
		- A4 : ORG -> on
		- A5 : GND
	PORTB : read
		- B0 : DO
*/
#define Tcss 0.2 // 0.05
#define Tskh 0.5 // 0.25
#define Tskl 0.5 // 0.25
#define Tcsh 0
#define Tdis 0.4 // 0.1
#define Tdih 0.4 // 0.1
#define Tpd0 0.25
#define Tpd1 0.25
#define Tdf 0.1
#define Tsv 0.25
#define Tdf 0.1


#define CS PORTA
#define SK PORTB
#define DI PORTC
#define Vc PORTD // + Or
// PORTE for UART
#define Gn PORTF
#define Do PORTG


void read_data(int i, char *data);

int input=0;

int main(void)
{
	char data[20];
	char ch=0;
    int i=0, j=0;
	
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UBRR0H = 0;
	UBRR0L = 103;
	
	DDRA = 0xff;	// out	cs
	DDRB = 0xff;	// out	sk
	DDRC = 0xff;	// out	di
	DDRD = 0xff;	// out	vcc
//	DDRE = 0xff;	// out	org
	DDRF = 0xff;	// out	gnd
	DDRG = 0x00;	// in	do
	Vc = 0xff;
	CS = 0x00;
	SK = 0x00;
	DI = 0x00;
	Vc = 0xff;
	Gn = 0x00;
	Do = 0x00;
	//Or = 1;
	while(1){
		for (i=0 ; i<=0b111111 ; i++){
			CS = 0x00;
			SK = 0x00;
			DI = 0x00;
			Vc = 0xff;
			Gn = 0x00;
			Do = 0x00;
			read_data(i, data);
	//		UDR0 = input;
	//		UDR0 = 66;//input;
			for (j=1, ch=0 ; j<17; j++){
					UDR0 = data[j]; //%'0')<<(9-i);
					_delay_ms(100);
				}
//		    _delay_ms(100);
	//		UDR0 = ch;
	//		_delay_ms(100);
	//		for ( ch=0 j<=17; j++){
	//			UDR0 = data[j]; //%'0')<<(17-i);
	//			_delay_ms(100);
	//		}
	//		UDR0 = ch;
		}
	}
}


void read_data(int i, char *data)
{
	
	DI = 1;
	_delay_us(Tdis-Tcss);
	CS = 1;
	_delay_us(Tcss);
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	DI = 1;
	_delay_us(Tdis);
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	DI = 0;
	_delay_us(Tdis);
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	UDR0 = 'A'+i;
	
	if (i & 0b100000){	//A5	- SK=0
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
		} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b010000){	//A4	- SK=1
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
		} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b001000){	//A3	- SK=0
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
		} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b000100){	//A2	- SK=1
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
		} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b000010){	//A1	- SK=0
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
		} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b000001){	//A0	- SK=1
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
		} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	DI = 0;
	_delay_us(0.2);
	
	for (i=0 ; i<17 ; i++){
		_delay_us(Tdis);
		if (PING == 0){		// d15
			data[i] = '0';
			} else{
			data[i] = '1';
		}
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	/*
	_delay_us(Tdis);
	if (PING == 0){		// d15
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	_delay_ms(100);
	UDR0 = '/';
	_delay_us(Tdis);
	if (PORTG == 0){		// d14
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d13
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d12
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d11
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d10
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d9
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d8
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
		
		
	_delay_us(Tdis);
	if (PORTG == 0){		// d7
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d6
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d5
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d4
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d3
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d2
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d1
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	
	_delay_us(Tdis);
	if (PORTG == 0){		// d0
		UDR0 = '0';
		} else{
		UDR0 = '1';
	}
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	*/
		
	/*
	for (i=15, input=0 ; i>=0 ; i--){
		_delay_us(Tdis);
		if (PING == 0){
			UDR0 = '0';
			} else{
			UDR0 = '1';
		}
		//		input += (PING << i);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	*/
}



/*
void read_data(int i)
{
	
	DI = 1;
	_delay_us(Tdis-Tcss);
	CS = 1;
	_delay_us(Tcss);
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	DI = 1;
	_delay_us(Tdis);
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	DI = 0;
	_delay_us(Tdis);
	SK = 1;
	_delay_us(Tdih);
	_delay_us(Tdis);
	SK = 0;
	_delay_us(Tdih);
	
	if (i & 0b100000){	//A5	- SK=0
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b010000){	//A4	- SK=1
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b001000){	//A3	- SK=0
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b000100){	//A2	- SK=1
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b000010){	//A1	- SK=0
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	if (i & 0b000001){	//A0	- SK=1
		DI = 1;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	} else {
		DI = 0;
		_delay_us(Tdis);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
	
	for (i=15, input=0 ; i>=0 ; i--){
		_delay_us(Tdis);
		if (PING == 0){
			UDR0 = '0';
		} else{
			UDR0 = PING;
		}
//		input += (PING << i);
		SK = 1;
		_delay_us(Tdih);
		_delay_us(Tdis);
		SK = 0;
		_delay_us(Tdih);
	}
}

*/