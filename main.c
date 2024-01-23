// main.c
//
// A simple blinky program for ATtiny85
// Connect red LED at pin 2 (PB3)
//
// electronut.in

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// Function prototypes
static void setup_io(void);
static void setup_interrupts(void);
static void setup_timer(void);
static void setup_usi(void);
static void initialize(void);

// Interrupt service routines
ISR(PCINT1_vect)
{
    // Read pins PB:5, PB:4, PB:3, PB:1
    uint8_t status = PINB & 0b00111010;
    reti();
}

ISR(PCINT3_vect, ISR_ALIASOF(PCINT1_vect));
ISR(PCINT4_vect, ISR_ALIASOF(PCINT1_vect));
ISR(PCINT5_vect, ISR_ALIASOF(PCINT1_vect));


/// @brief main.c initialization of the ATtiny85
/// @param  void
/// @return int
int main (void)
{
  // set PB3 to be output
	DDRB = 0b00000101;
  while (1) {

    // flash# 1:
    // set PB3 high
    PORTB = 0b00001000;
    _delay_ms(20);
    // set PB3 low
    PORTB = 0b00000000;
    _delay_ms(20);

    // flash# 2:
    // set PB3 high
    PORTB = 0b00001000;
    _delay_ms(200);
    // set PB3 low
    PORTB = 0b00000000;
    _delay_ms(200);
  }

  return 1;
}

static void setup_io(void){
  // PB4 is output, 3:0 are input
  DDRB = 0b00000101;

}

void setup_interrupts(void){
  // Enable pin change interrupt on PB0
  GIMSK |= (1 << PCIE);
  PCMSK |= (1 << PCINT5) | (1 << PCINT4) | (1 << PCINT3) | (1 << PCINT1);
  sei();
}

static void setup_usi(void){
    // Enable 2 wire mode
    USICR = (1 << USIWM1);
}