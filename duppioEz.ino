#include <LiquidCrystal.h>


LiquidCrystal lcd(12,11,5,4,3,2);
 
const int inputPin = 6;     //Motion sensor
const int onOff = 7;        //Pushbutton to turn Duppio on and off
const int pinSpeaker = 8;   //Speaker
const int bytteLydPin = 9;  //Pushbutton to change the chosen sound
const int ledPin = 13;      //LED only used for earlier testing phases, which indicates whether Duppio is on/off and if motion is detected

int pirState = LOW;         //State of the motion sensor component (LOW = no motion / HIGH = motion detected)
int val = 0;                //Variable for reading the pin status
int switchState = 1;        //Variable that checks when the pushbutton "bytteLydPin" is pressed
int antTrykk = 0;           //Counter variable that determines the value of "whatSound" 
int whatSound = 1;          //Variable that determins which sound to release (value "1" is default when Duppio turns on)


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(pinSpeaker, OUTPUT);
  pinMode(bytteLydPin, INPUT); 
  pinMode(onOff, INPUT);

  lcd.begin(16,2);
  lcd.setCursor(4,0);
  lcd.print("STARTING");
  delay(3000);  //A short delay to prolong the text's presence 
  lcd.clear();
  Serial.begin(9600);
  on();
}


/*
 * Everything occurs in the "loop" method and
 * this is also where all the other methods will be called upon.
 */
void loop(){

  digitalWrite(bytteLydPin, HIGH);
  switchState = digitalRead(bytteLydPin);

  //Counter that tells how many times the pushbutton "bytteLydPin" has been pressed.
  //It serves the purpose of allowing the changing of released sound from Duppio when something is detected.
  //(Counter resets if Duppio is set to turn off)
  if(switchState == LOW){   
    delay(100);
    antTrykk++;
    byttLyd(antTrykk);
    Serial.print(antTrykk);
    if(antTrykk >= 4){
      antTrykk = 0;
    }
  }

  //Output message on LCD display
  lcd.setCursor(5,0);
  lcd.print("NEI PUZ");
  lcd.setCursor(6,2);
  lcd.print("IS ON");

  val = digitalRead(inputPin);    //Reads the motion detector's value
    
  if (val == HIGH) {              //Checks if the motion detector gives the input: HIGH
    digitalWrite(ledPin, HIGH);   //turn LED ON (was used for earlier testing phases)
    alarm(whatSound);
    
      if (pirState == LOW) {
        //Prints a message in the LCD (used for earlier tests)
        Serial.println("Motion detected!");
        lcd.setCursor(5,0);
        lcd.print("Motion");
        lcd.setCursor(4,2);
        lcd.print("Detected");
        pirState = HIGH;
      }
      
  } else {
    digitalWrite(ledPin, LOW);  //turn LED OFF  
      
    if (pirState == HIGH){
    //Prints a message in the LCD (used for earlier tests)
    Serial.println("Motion ended!");
    pirState = LOW;
    }  
  }
}


/*
 * This method uses "whatSound" as parameter to determine which if-sentence should be used.
 * There is an if sentence for each tone (1, 2, 3, 4) that also outputs a message on the LCD.
 * The program will pass through the same tone as long as motion is being detected and the chosen sounds hasn't been changed (with a small delay).
 * 
 */
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


/*
 * This method causes a short sound notification once Duppio turns on.
 */
void on(){
  tone(pinSpeaker, 261);
  delay(180);
  tone(pinSpeaker, 523);
  delay(200);
  noTone(pinSpeaker);
}

/*
 * Takes "ant" as a parameter then according to the value "ant" has,
 * a message will be shown on the LCD aswell as the value of "whatSound" will be changed.
 * The value of "whatSound" will be used as a parameter in the method "alarm".
 */
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
    whatSound = 2;
  }
  
  if(tall == 2){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("PHONE");
    lcd.setCursor(5,2);
    lcd.print("ALARM");
    delay(2000);
    lcd.clear();
    whatSound = 3;
  }

  if(tall == 3){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("NIGHTMARE");
    delay(2000);
    lcd.clear();
    whatSound = 4;
  }
}
