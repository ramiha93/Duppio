#include <LiquidCrystal.h>


LiquidCrystal lcd(12,11,5,4,3,2);
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 6;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 8;             //Set up a speaker on a PWM pin (digital 9, 10, or 11)
int run = 0;
int sec = 0;
int bytteLydPin = 9;
int switchState = 1;
int antTrykk = 0;
int onOff = 7;
int switchStateAvPaa = 0;
int whatSound = 1;


void setup() {
  lcd.begin(16,2);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  pinMode(bytteLydPin, INPUT); 
  pinMode(onOff, INPUT);
  lcd.setCursor(4,0);
  lcd.print("STARTING");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
  on();


}


void loop(){

  digitalWrite(bytteLydPin, HIGH);
  switchState = digitalRead(bytteLydPin);

  if(switchState == LOW){   
    delay(100);
    byttLyd(antTrykk);
    antTrykk++;
    Serial.print(antTrykk);
    if(antTrykk >=5){
      antTrykk =0;
    }
  }
  
  lcd.setCursor(5,0);
  lcd.print("NEI PUZ");
  lcd.setCursor(6,2);
  lcd.print("IS ON");
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
  digitalWrite(ledPin, HIGH);  // turn LED ON
  alarm(whatSound);

    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      lcd.setCursor(5,0);
      lcd.print("Motion");
      lcd.setCursor(4,2);
      lcd.print("Detected");
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF  
      if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}


void alarm(int whatSound){

  if(whatSound == 1){
    lcd.clear();
    tone(pinSpeaker, 600);
    lcd.setCursor(5,0);
    lcd.print("MOTION");
    lcd.setCursor(4,2);
    lcd.print("DETECTED");
    delay(100);
    noTone(pinSpeaker);
    delay(100);
    lcd.clear();
 
  }

  if(whatSound == 2){
    lcd.clear();
    tone(pinSpeaker, 1500);
    lcd.setCursor(5,0);
    lcd.print("MOTION");
    lcd.setCursor(4,2);
    lcd.print("DETECTED");
    delay(50);
    noTone(pinSpeaker);
    delay(100);
    lcd.clear();
 
  }


  if(whatSound == 3){
    lcd.clear();
    tone(pinSpeaker, 900);
    lcd.setCursor(5,0);
    lcd.print("MOTION");
    lcd.setCursor(4,2);
    lcd.print("DETECTED");
    delay(25);
    tone(pinSpeaker, 450);
    delay(25);
    noTone(pinSpeaker);
    delay(10);
    lcd.clear();
 
  }


  if(whatSound == 4){
    lcd.clear();
    tone(pinSpeaker,10000);
    lcd.setCursor(5,0);
    lcd.print("MOTION");
    lcd.setCursor(4,2);
    lcd.print("DETECTED");
    delay(100);
    noTone(pinSpeaker);
    delay(100);
    lcd.clear();
 
  }
}


void on(){
  tone(pinSpeaker, 261);
  delay(180);
  tone(pinSpeaker, 523);
  delay(200);
  noTone(pinSpeaker);
}

void byttLyd(int ant){
  int tall = ant; 
  lcd.clear();
if(tall == 0){
  lcd.setCursor(4,0);
  lcd.print("STANDARD");
  lcd.setCursor(5,2);
  lcd.print("ALARM");
  delay(1500);
  lcd.clear();
  whatSound = 1;
}

if(tall == 1){
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("BEEP");
  lcd.setCursor(5,2);
  lcd.print("ALARM");
  delay(2000);
  lcd.clear();
  whatSound =2;
}
if(tall == 3){
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("PHONE");
  lcd.setCursor(5,2);
  lcd.print("ALARM");
  delay(2000);
  lcd.clear();
  whatSound = 3;
}

if(tall == 4){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("NIGHTMARE");
  delay(2000);
  lcd.clear();
  whatSound = 4;
}
}
