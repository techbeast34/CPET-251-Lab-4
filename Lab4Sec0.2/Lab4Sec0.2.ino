// Lab4 PWM_dim_LED_compact.ino
// Written By: C. Hochgraf
// Date: Feb 2017

  int sreg;
  unsigned long fadeValue=0;
//***********************************************************************************
void setup()
{  
  pinMode(9,OUTPUT);  // to drive led on pin 13
  pinMode(13,INPUT); // to receive digital signal from pin 9
  Serial.begin(9600);
  Serial.println(F("Lab 4: PWM_dim_LED_compact"));
  TCCR1A=0xA3; // configure registers for Timer 1 Mode 7 fast PWM 10bit, clock scale=8x
  TCCR1B=0x0A; // configure registers for Timer 1 Mode 7 fast PWM 10bit, clock scale=8x
  Serial.println();
  Serial.println("I'm ready to blink now. Attach a wire from pin 9 to 13");
}
//***********************************************************************************
void loop()
{ delay(10);
  fadeValue++;
  OCR1A=fadeValue; // load PWM compare register (OCR1A) with new PWM value (fadeValue)
  //OCR1A=512; // generates fixed PWM "analog voltage" of around 2.5 volts dc
  if (fadeValue>=1023) fadeValue=0; // PWM counts up to 10 bit value (1023)
} // Arduino loop()
