// Lab4 PWM_servo_compact.ino
// Written By: C. Hochgraf
// Date: Feb 2017

  unsigned long servoValue=0;
//***********************************************************************************
void setup()
{  
  pinMode(9,OUTPUT);  // to drive servo on pin 9
  Serial.begin(9600);
  Serial.println(F("Lab 4: PWM_servo_compact"));
  TCCR1A=0xB0;
  TCCR1B=0x13;
  ICR1=0x9C4;
  Serial.println();
  Serial.println("I'm ready to run a servo, attach one to pin 9");
}
//***********************************************************************************
void loop()
{ delay(100);
  servoValue++;
  OCR1A=72+servoValue; // load PWM compare register (OCR1A) with new PWM value (fadeValue)
  if (servoValue>=235) servoValue=0; // 
  // for HS-311 servo, min time= 0.575 ms to max time 2.460ms
  // 250 counts per ms, but divide by 2 due to phase correct = 125 counts per ms
} // Arduino loop()
