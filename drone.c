/*
 * trial.c
 *
 * Created: 2017-02-06 오후 2:09:07
 * Author : my
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void putstr(char *str)
{
	int i;
	for (i=0 ; str[i]!='\0' ; i++){
		UDR0 = str[i];
		_delay_ms(100);
	}
	UDR0 = UCSR0A + '0';
}

/*
int main()
{
	int i=0;
	char str[] = "Hello world!\n";
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UBRR0H = 0;
	UBRR0L = 103;
	while(1){
		putstr(str);
		_delay_ms(1000);
	}
}
*/
// T : 0.6 off -> 0.3 on
// F : 0.3 off -> 0.3 off
void True()
{
	int i;
	PORTA = 0x00;
	_delay_us(600);
	for (i=0 ; i<12 ; i++){
		PORTA = 0x00;
		_delay_us(12.5);
		PORTA = 0x01;
		_delay_us(12.5);
	}
}

void False()
{
	int i;
	PORTA = 0x00;
	_delay_us(300);
	for (i=0 ; i<12 ; i++){
		PORTA = 0x00;
		_delay_us(12.5);
		PORTA = 0x01;
		_delay_us(12.5);
	}
}

void up()
{
	int i;
	for (i=0 ; i<40 ; i++){
		PORTA = 0x00;
		_delay_us(12.5);
		PORTA = 0x01;
		_delay_us(12.5);
	}
	for (i=0 ; i<7; i++){
		True();
	}
	for (i=0 ; i<5; i++){
		False();
	}
	True();
	for (i=0 ; i<5; i++){
		False();
	}
	for (i=0 ; i<6; i++){
		True();
	}
	for (i=0 ; i<2; i++){
		False();
	}
	True();
	for (i=0 ; i<2; i++){
		False();
	}
	True();
	True();
	False();
}

void stop()
{
	int i;
	for (i=0 ; i<40 ; i++){
		PORTA = 0x00;
		_delay_us(12.5);
		PORTA = 0x01;
		_delay_us(12.5);
	}
//	PORTA = 0x01;
//	_delay_ms(1);
	for (i=0 ; i<6; i++){
		False();
	}
	True();
	for (i=0 ; i<5; i++){
		False();
	}
	True();
	for (i=0 ; i<5; i++){
		False();
	}
	for (i=0 ; i<6; i++){
		True();
	}
	for (i=0 ; i<2; i++){
		False();
	}
	True();
	for (i=0 ; i<4; i++){
		False();
	}
	True();
}

int main(void)
{
    DDRA = 0xff;
	
	while(1){
		up();
		_delay_ms(100);
		stop();
		_delay_ms(100);
	}
//	DDRB = 0xff;
//	PORTB = 0x00;
}

