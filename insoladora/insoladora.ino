/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin X)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int Start_Stop = 9;
const int botonMENOS =  10;
const int botonMAS =  11;

bool valSS = 1;
bool valSS_ant = 1;

bool valMAS = 1;
bool valMAS_ant = 1;

bool valMENOS = 1;
bool valMENOS_ant = 1;

unsigned int contador=0;
bool estado = 0;

unsigned int minutos=0;
unsigned int segundos=0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(Start_Stop, INPUT);
  pinMode(botonMAS, INPUT);
  pinMode(botonMENOS, INPUT);

  cli();//stop interrupts
  
  // Print a message to the LCD.
  lcd.print("hello, world!");
  lcd.setCursor(2, 1);
  lcd.print(":");

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz 
  if(estado){ 
      contador--;
      if(contador==0) estado =0;
  }
}

void loop() {

  valSS = digitalRead(Start_Stop);
  if(!valSS){
    if(valSS_ant){
      valSS_ant=valSS;
      estado=(!estado);
    }
  }
  valSS_ant=valSS;

  valMAS = digitalRead(botonMAS);
  if(!valMAS){
    if(valMAS_ant){
      valMAS_ant=valMAS;
      contador+=10;
    }
  }
  valMAS_ant=valMAS;

  valMENOS = digitalRead(botonMENOS);
  if(!valMENOS){
    if(valMENOS_ant){
      valMENOS_ant=valMENOS;
      contador-=10;
      if(contador<=0) contador=0;
    }
  }
  valMENOS_ant=valMENOS;

  minutos=contador/60;
  segundos=contador%60;
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  if(minutos<10){
    lcd.setCursor(0, 1);
    lcd.print("0");
    lcd.setCursor(1, 1);
  }
  else 
    lcd.setCursor(0, 1);
  lcd.print(minutos);

  if(segundos<10){
    lcd.setCursor(3, 1);
    lcd.print("0");
    lcd.setCursor(4, 1);
  }
  else 
    lcd.setCursor(3, 1);
  lcd.print(segundos);

  lcd.setCursor(8, 1);
  lcd.print(estado);
}

