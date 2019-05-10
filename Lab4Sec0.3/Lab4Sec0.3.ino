// Lab4 PWM_motor_pos_neg_compact.ino
// Written By: C. Hochgraf
// Date: Feb 2017

  unsigned long fadeValue=0;
//***********************************************************************************
void setup()
{  
  pinMode(9,OUTPUT);  // motor lead +
  pinMode(10,OUTPUT);  // motor lead -
  Serial.begin(9600);
  Serial.println(F("Lab 4: PWM_motor_pos_neg_compact"));
  TCCR1A=0xB3; // configure registers for Timer 1 Mode 7 fast PWM 10bit, clock scale=8x
  TCCR1B=0x0A; // configure registers for Timer 1 Mode 7 fast PWM 10bit, clock scale=8x
  Serial.println();
  Serial.println("I'm ready to blink now. Attach 330 ohm resistor and back to back LEDs");
  Serial.println("(just like in lab 2) between pins 9 and 10");
}
//***********************************************************************************
void loop()
{ delay(20);
  fadeValue++;
  OCR1A=fadeValue; // load PWM compare register (OCR1A) with new PWM value (fadeValue)
  OCR1B=fadeValue;
  if (fadeValue>=1023) fadeValue=0; // PWM counts up to 10 bit value (1023)
} // Arduino loop()
