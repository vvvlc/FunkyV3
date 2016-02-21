// the setup function runs once when you press reset or power the board

//#define OUTPUT_TEST

int mode=0;


void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  

#ifdef OUTPUT_TEST
  outputSetup();
#else
  inputSetup();
#endif
}

void loop() {
#ifdef OUTPUT_TEST
  outputLoop();
#else
  inputLoop();  
#endif
}

//sets all pins to output
//use diode to test all pins (use rezitor 330 to limit curent)
void outputSetup(){
  //DIGITAL  D2 (aka SDA), D4* (mapped to RFM FET), D6, D7, D8, D9, D11, D12
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

//ANALOG  A3, A4
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);

//SCL (not available),SDA 
  pinMode(2, OUTPUT);
  //pinMode(3, OUTPUT);

//SERIAL TX and RX are on Serial1  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);


//SPI as digital
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);

}

//sets all pins to output
//use diode to test all pins (use rezitor 330 to limit curent)
void inputSetup(){
  Serial.begin(9600);
  //DIGITAL  D2 (aka SDA), D4* (mapped to RFM FET), D6, D7, D8, D9, D11, D12
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);

//ANALOG  A3, A4
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

//SCL (not available),SDA 
  pinMode(2, INPUT);
  //pinMode(3, INPUT);

//SERIAL TX and RX are on Serial1  
  pinMode(0, INPUT);
  pinMode(1, INPUT);


//SPI as digital
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);

}


// like blink but on all pins
void outputLoop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)

  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)

  digitalWrite(A3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(A4, HIGH);   // turn the LED on (HIGH is the voltage level)
 
  digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)

  digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(15, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
   
  delay(1000);              // wait for a second

  digitalWrite(13, LOW);   // turn the LED on (LOW is the voltage level)
  
  digitalWrite(0, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(1, LOW);   // turn the LED on (LOW is the voltage level)

  digitalWrite(2, LOW);   // turn the LED on (LOW is the voltage level)

  digitalWrite(A3, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(A4, LOW);   // turn the LED on (LOW is the voltage level)
 
  digitalWrite(6, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(7, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(8, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(9, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(11, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(12, LOW);   // turn the LED on (LOW is the voltage level)

  digitalWrite(14, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(15, LOW);   // turn the LED on (LOW is the voltage level)
  digitalWrite(16, LOW);   // turn the LED on (LOW is the voltage level)
  
  delay(1000);              // wait for a second
}

/**
 * read from pin
 */
int readFromPin(int pin) {
  long start=millis();
  int val = 0;
  
  while (millis()-start<1000) {
    Serial.print("Pin:");
    Serial.print(pin);
    Serial.print(",");
    Serial.print(digitalRead(pin));
    Serial.println();
    if (digitalRead(pin)) {
      val=1;
    }
    delay(100);
  }
  return val;
}

int readFromPins(int pin) {
  int pins[]={0,1,2,A3,A4, 6,7,8,9,11,12,14,15,16,-1};
  long start=millis();
  int val = 0;
  
//  while (millis()-start<1000) {
    Serial.println("Pin:");
    for(int i=0;pins[i]!=-1;i++) {
      printd(pins[i]);
      Serial.print(" ");      
    }
    Serial.println();
    for(int i=0;pins[i]!=-1;i++) {
      printd(digitalRead(pins[i]));      
      Serial.print(" ");
    }
    Serial.println();
    delay(1500);
    
  //}
  return val;
}

void printd(int val) {
  if (val<100) Serial.print(" ");
  if (val<10) Serial.print(" ");
  Serial.print(val);
}

void blink(int count) {
  while(count-->0) {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);
  }
}

void testpin(int pin) {
  if (readFromPin(pin)) {
    //blink(pin);
  }
}

// like blink but on all pins
void inputLoop() {

  //testpin(0);   // turn the LED on (HIGH is the voltage level)
  readFromPins(0) ;

  /*
  testpin(0, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(1, HIGH);   // turn the LED on (HIGH is the voltage level)

  testpin(2, HIGH);   // turn the LED on (HIGH is the voltage level)

  testpin(A3, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(A4, HIGH);   // turn the LED on (HIGH is the voltage level)
 
  testpin(6, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(12, HIGH);   // turn the LED on (HIGH is the voltage level)

  testpin(14, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(15, HIGH);   // turn the LED on (HIGH is the voltage level)
  testpin(16, HIGH);   // turn the LED on (HIGH is the voltage level) 
*/
}
