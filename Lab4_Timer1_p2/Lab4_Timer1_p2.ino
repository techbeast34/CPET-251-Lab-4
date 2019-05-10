// Lab4_Timer1_p1
// Written By: C. Hochgraf
// Date: Feb 2017

// declare variables
  enum {TC1_PCFC_DC90_D10};
  int state, sreg;
//***********************************************************************************
void setup()
{  
  Serial.begin(9600);
  Serial.println(F("Lab 4: Hardware Timers"));
}
//***********************************************************************************
void loop()
{
  // loop() is only executed once because each state contains an infinite loop.
  state = TC1_PCFC_DC90_D10;
 
  switch(state)
  {
    //-------------------------------------------------------------------------------
    case TC1_PCFC_DC90_D10:
      // Create 90% duty cycle square wave using Timer 1.
      
      Serial.println(F("Print out all the default Timer1 settings"));
      Serial.println(F("The settings are all stored in registers"));
      Serial.println(F("Later, you will change the values in the registers"));
      Serial.println();
      Serial.println(F("First, what is in the Timer 1 Control Registers?"));
      
      printTimer1Registers();
      delay(8000);
     
      // you can comment out the printWGM function below when you are ready
      Serial.println(F("you can comment out the printing of WGM values to save time"));
      //printWGMCOMCS1Values();
     
      Serial.println();
      delay(1000);
      Serial.println(F("Initializing Timer1 in PCFC mode, toggling OC1B on d10"));
      
      sreg = SREG; /* Save global interrupt flag */
      cli(); // temporarily stop interrupts while setting register values
      TCCR1A = 0; // set to defaults as good practice
      TCCR1B = 0; // set to defaults as good practice
      TCCR1A  = (0 << WGM11)|(0 << WGM10);    // first part of setup for PCFC PWM (mode 8)
      TCCR1B  = (1 << WGM13)|(0 << WGM12);    // second part of setup for PCFC PWM (mode 8)
      TCCR1A |= (1 << COM1B1)|(1 << COM1B0);  // non-inverting PWM on channel B: PORTB2, UNOd10 
      TCCR1A |= (1 << COM1A1)|(0 << COM1A0);  // non-inverting PWM on channel A: PORTB1, UNOd9

      TCCR1A |= 0x20;
      TCCR1A &= 0xEF;
      

      
    
      //This setup COM1A (10) COM1B (11), gives d9 to be inverted from d10 if OCR1A=OCR1B. 
      // WGM mode 8 (1000) has ICR1 as top.
   
      //TCCR1B |= (1 << CS12)|(0 << CS11)|(1 << CS10); // clock prescale = 1024 -> 15.625 kHz
      //TCCR1B |= (1 << CS12)|(0 << CS11)|(0 << CS10); // clock prescale = 256 -> 62.5 kHz
      TCCR1B |= (0 << CS12)|(1 << CS11)|(1 << CS10); // clock prescale = 64 -> 250 kHz
      ICR1 = 10000;  // period   ICR1=10000 gives visible blips
      OCR1A = 625;  //  =10000/16 = 625
      OCR1B = 625;  //  =10000/16 = 625 
      sei(); // reenable interrupts  
      SREG = sreg; /* Restore global interrupt flag */
      //did it work right? check by printing registers
      printTimer1Registers();
      //delay(10000);
      pinMode(9,OUTPUT);  // to drive led on pin 13
      pinMode(10,OUTPUT); 
      pinMode(13,INPUT); // to receive digital signal from pin 9
      Serial.println();
      Serial.println("I'm ready to blink now. Attach a wire from pin 9 to 13");
      while(true) {; // dwell forever 
         }
      break;     
  } // switch(state)
} // Arduino loop()

//==============================================================================
void printWGMCOMCS1Values(void) {
    Serial.println();
    delay(8000);
    Serial.println(F("Second, what are these WGM values? Try printing as decimals"));
    Serial.println();
    Serial.print(F("WGM10    DECIMAL: ")); Serial.println(WGM10, DEC);
    Serial.print(F("WGM11    DECIMAL: ")); Serial.println(WGM11, DEC);
    Serial.print(F("WGM12    DECIMAL: ")); Serial.println(WGM12, DEC);
    Serial.print(F("WGM13    DECIMAL: ")); Serial.println(WGM13, DEC);
 
    delay(8000);
    Serial.println();
    Serial.println(F("The WGM values are #defines that tell you how far"));
    delay(1000);
    Serial.println(F("to shift a bit value to have it land at the right place "));
    delay(1000);
    Serial.println(F("in the register. "));
    Serial.println();
   
    delay(2000);
    Serial.println(F("Now print the COM1B values."));
    Serial.println(F("Thes are #defines that tell you how far"));
    Serial.println(F("to shift a bit value to have it land at the right place "));

    Serial.println();
    Serial.print(F("COM1B0    DECIMAL: ")); Serial.println(COM1B0, DEC);
    Serial.print(F("COM1B1    DECIMAL: ")); Serial.println(COM1B1, DEC);
    Serial.println();
    delay(8000);
    Serial.println(F("Now print the CS values that help with setting the "));
    Serial.println(F("clock prescaler value (clock divider). "));
    Serial.println();
    delay(2000);
    
    Serial.print(F("CS10    DECIMAL: ")); Serial.println(CS10, DEC);
    Serial.print(F("CS11    DECIMAL: ")); Serial.println(CS11, DEC); 
    Serial.print(F("CS12    DECIMAL: ")); Serial.println(CS12, DEC);
    Serial.println();
    delay(8000);
  };
//==============================================================================
void printHex8(byte data) { // prints 8-bit data in hex with leading zeroes
  Serial.print("0x"); 
  if (data<0x10) {Serial.print("0");} 
  Serial.print(data,HEX); 
}

//==============================================================================
void printHex16(uint16_t data) { // prints 16-bit data in hex with leading zeroes
  Serial.print("0x"); 
  uint8_t MSB=byte(data>>8);
  uint8_t LSB=byte(data);
  if (MSB<0x10) {Serial.print("0");} Serial.print(MSB,HEX);  
  if (LSB<0x10) {Serial.print("0");} Serial.print(LSB,HEX); 
  
}
//==============================================================================
void printBinaryByte(byte value) { // prints 8-bit data in binary with leading 0's  
  Serial.print("B");
  for (byte bitmask = 0x80; bitmask; bitmask >>= 1) {
        Serial.print((bitmask & value) ? '1' : '0');
    }
}
//==============================================================================
void printBinaryWord(unsigned int value) { // prints 16-bit data in binary with leading 0's  
  Serial.print("B");
  for (unsigned int bitmask = 0x8000; bitmask; bitmask >>= 1) {
        Serial.print((bitmask & value) ? '1' : '0');
    }
}

//==============================================================================
void printRegister16InDecHexBin(unsigned int registerName) {
  Serial.print(F("Binary:  ")); printBinaryWord(registerName); Serial.print("\t");
  Serial.print(F("Hex:     ")); printHex16(registerName); Serial.print("\t");
  Serial.print(F("Decimal: ")); Serial.println(registerName);
}

//==============================================================================
void printRegister8InDecHexBin(unsigned int registerName) {
  Serial.print(F("Binary:  ")); printBinaryByte(registerName); Serial.print("\t\t");
  Serial.print(F("Hex:     ")); printHex8(registerName); Serial.print("\t");
  Serial.print(F("Decimal: ")); Serial.println(registerName);
}

//==============================================================================
void printTimer1Registers() {
  Serial.print(F("TCCR1A: ")); printRegister8InDecHexBin(TCCR1A);
  Serial.print(F("TCCR1B: ")); printRegister8InDecHexBin(TCCR1B);
  Serial.print(F("OCR1A:  ")); printRegister16InDecHexBin(OCR1A);
  Serial.print(F("OCR1B:  ")); printRegister16InDecHexBin(OCR1B);
  Serial.print(F("ICR1:   ")); printRegister16InDecHexBin(ICR1); 
  Serial.print(F("TIMSK1: ")); printRegister8InDecHexBin(TIMSK1);  
}
