// If '#' is pressed then door is locked again
// If '0' is pressed then password is validated

#include <Password.h> 
#include <Keypad.h> 
#include <LiquidCrystal.h> 
int RS=A5, E=A4, D4=A3, D5=A2, D6=A1, D7=A0;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7); 
Password password = Password( "ABCD" );
int buz=13;
int led = 12;
int m1a=10;
int m1b=11;

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6};  //connect to the column pinouts of the keypad

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  lcd.begin(16, 2); // set up the LCD's number of columns and rows: 
  pinMode(buz,OUTPUT);
  pinMode(m1a,OUTPUT);
  pinMode(m1b,OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(buz, LOW);
  lcd.setCursor(0, 0);
  lcd.print("**Digital Door**");
  lcd.setCursor(0, 1);
  lcd.print("*Locking System*");
  delay(2000);
  lock();
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  keypad.getKey();
  
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  
  switch (keypad.getState()){
    case PRESSED:
        
    lcd.print("*");                     //print * when a key is perrsed(for security reasons)
        digitalWrite(buz, HIGH);        // buzz when a key is pressed
        delay(100);
        digitalWrite(buz, LOW);
    switch (eKey){
      case '0': checkPassword(); break;     // when '0' is pressed 
      case '#': lock(); break;
      default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()) // Arduino will evaluate the keypress with the Actual Password
  { 
    unlock();
  }
  else{
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("*****Wrong*****");
    lcd.setCursor(0, 1);
    lcd.print("***************");
    digitalWrite(buz, HIGH);
    delay(100);
    delay(1000);
    digitalWrite(buz, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("***Try Again***");
    delay(1000);
    lcd.clear();
    password.reset();
    lcd.blink();
    lcd.print("Enter Pass:");
  }
}
void lock() // Function For Lock The Door
{
  
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  
  delay(1000);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  digitalWrite(led, LOW);
  lcd.print("**Door Locked**");
  lcd.setCursor(0, 1);
  lcd.print("***************");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Etr Pas to Unlck");
  lcd.setCursor(0, 1);
  lcd.print("*****Again*****");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Pass:");
  lcd.blink();
    
}

void unlock() // Function For Unlock The Door
{
  lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("****Success****");
    lcd.setCursor(0, 1);
    lcd.print("***************");
    digitalWrite(buz, HIGH);
    digitalWrite(m1a,LOW);
    digitalWrite(m1b,HIGH);
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(m1a,LOW);
    digitalWrite(m1b,LOW);
    digitalWrite(buz, LOW);   
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.noBlink();
    lcd.print(" Press # key to");
    lcd.setCursor(0, 1);
    lcd.print("***Lock Again***");
    password.reset(); 
  
}

// End of program

