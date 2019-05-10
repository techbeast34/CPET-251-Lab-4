// homework 4 part 2
#define LED_PIN 10
enum{LED_ON,LED_OFF};
int state = LED_ON, 
prevState = !state;
boolean isNewState;

void setup() {
  DDRB |= 0x04; // setting PD10 OUTPUT
  DDRB &= 0xDF;
  // setting timer1 to NORMAL mode with pre scale value 256
  TCCR1A = 0x00;
  TCCR1B = 0x04;
}

void loop() {
  isNewState = (state != prevState); 
  prevState = state;
  switch(state) {
    case LED_ON:
        PORTB |= 0x04; // turn LED ON
        TCNT1 = 31250;
        while ((TIFR1 & 0x01) == 0); //wait for 250ms
        state = LED_OFF;
        TIFR1 |= 0x01; // clear the flag
        break;
    case LED_OFF:
        PORTB &= 0xFB; // turn LED OFF
        TCNT1 = 31250;
        while ((TIFR1 & 0x01) == 0); //wait for 750ms
        state = LED_ON;
        TIFR1 |= 0x01; // clear the flag
        break;
    default: state = LED_ON;
  }
}
