//// Lab4_BlinkUsingDelay
//// Written By: C. Hochgraf
//// Date: Feb 2017
//
//unsigned long numberOfLoopsRun=0;
////***********************************************************************************
//void setup() {
//  pinMode(13,OUTPUT); 
//  Serial.begin(9600);
//  Serial.println(F("Lab 4: BlinkUsingDelay"));
//  Serial.println(F("I'm ready to blink now."));
//}
////***********************************************************************************
//void loop() { 
//  digitalWrite(13,HIGH);
//  delay(1000);
//  digitalWrite(13,LOW);
//  delay(1000);  
//  Serial.print(F("The number of times loop code has run is: "));
//  Serial.println(numberOfLoopsRun);
//  numberOfLoopsRun++;
//} // Arduino loop()

// Lab4_BlinkUsingTimer1
// Written By: C. Hochgraf
// Date: Feb 2017

unsigned long numberOfLoopsRun=0;
//***********************************************************************************
void setup()
{  
  pinMode(9,OUTPUT);  // to drive led on pin 13
  pinMode(13,INPUT); // to receive digital signal from pin 9
  Serial.begin(9600);
  Serial.println(F("Lab 4: BlinkUsingTimer1"));
  TCCR1A=0x50; // Configures timer to CTC mode 4 with OCR1A as top
  TCCR1B=0x0D; // toggles pin 9 every one second
  OCR1A=0x3D09; // one second interval
  Serial.println("I'm ready to blink now. Attach a wire from pin 9 to 13");
}
//***********************************************************************************
void loop()
{
  // every time numberOfLoopsRun is a multiple of 10000, print the number of loops run so far
  if ((numberOfLoopsRun % 10000)==0) { 
    Serial.print(F("The number of times loop code has run is: "));
    Serial.println(numberOfLoopsRun);
  }
  numberOfLoopsRun++;
} // Arduino loop()
