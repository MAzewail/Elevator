// C++ code
//
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

byte pins[8]={7,8,9,10,11,12,13};
byte disp[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1} // 9
};
float reading = 0.0,force=0.0;
long d=0,t=0;
byte buttonstate=0;
bool button_reading=0;

void presNum(byte num){
  for(int i=0;i<sizeof(pins);i++)
    digitalWrite(*(pins+i),*(*(disp+num)+i)); 
}

void setup()
{
  for(int i=0;i<8;i++)
    pinMode(pins[i],OUTPUT);
  for(int i=0;i<7;i++)
    pinMode(i,INPUT);
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Loading ......");
  delay(1000);
  lcd.clear();
  presNum(7);
}

void loop()
{
  for(byte ii=1;ii<10;ii++){
    button_reading = digitalRead((ii>6)?(ii+7):ii);
    if(button_reading)buttonstate=ii*button_reading;
  }
  presNum(buttonstate);
  reading =(analogRead(A3)/466.)*100;
  lcd.home();
  if(reading < 50.0)
  lcd.print("Available load");
  else
  lcd.print("Over loaded    ");
  
  lcd.setCursor(5,1);
  lcd.print(String(reading)+" %  ");


}