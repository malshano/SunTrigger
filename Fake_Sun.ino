#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
int LEDpin = 13; //7
int hourset[]={12,14,00};  // holds alarm values 
int houroff[] = {12,15,00};
Adafruit_SSD1306 display(OLED_RESET);

bool alarmstatus = false;

RTC_DS3231 rtc;

void setup () {
  pinMode(LEDpin, OUTPUT);                                //LED pin is the pin the TIP transistor is Connected to
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1500);
  display.clearDisplay();
  Wire.begin();
  rtc.begin();

  if (rtc.lostPower()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));       // Date and time is set to the computers date and time
  }
        Serial.println(hourset[0]);
}

void loop () {
  DateTime now = rtc.now();
  TimeDisplay();            // Displays the time for one second  x 5 = 5 seonds before switching screens,
  TimeDisplay(); 
  TimeDisplay();

  
if (now.hour() == hourset[0] && now.minute() == hourset[1] ) {  // reads the alarm array if it is equal to the time then the alarm tuns on. Seconds cannot be set because of alarm chek being done every 3 seconds
  alarmstatus = "ON"  ;                                        // toggles boolean on - so that the light stays on
  Serial.println("ALARM ON");

}
if (now.hour() == houroff[0] && now.minute() == houroff[1]) {  // reads the alarm array to tiuurn alarm off
  alarmstatus = "OFF" ;                                        // Toggles boolean off at sunset 
        Serial.println("ALARM OFF");
}

if (alarmstatus =="ON"){                                      // Checks boolean and turns alarm on or off
    digitalWrite(LEDpin, HIGH); 
  }
  else if(alarmstatus =="OFF"){
    digitalWrite(LEDpin, LOW); 
  }
  
  
  AlarmDisplay();                                         // Displays the alarm display on OLED with sunrise and sunset times               

}

void AlarmDisplay(){
    display.clearDisplay();
  display.setTextSize(1);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(10,6);                           
  display.println("Sun Rise");
  display.drawRect(0,0,display.width()/2,display.height(), WHITE); // draws recangular border - (start coordinates x,y, width of box, height of box)



  display.setTextSize(0.5);                            
  display.setTextColor(WHITE,BLACK);
    display.setCursor(9,16); 
  display.print(hourset[0]);
  display.print(':');  
  display.print(hourset[1]);
    display.print(':'); 
  display.print(hourset[2]);
 // display.display();
/////////////////////
  display.setTextSize(1);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(73,6);                           
  display.println("Sun Set");
  display.drawRect((display.width()/2),0,display.width()/2,display.height(), WHITE);   // draws recangular border - (start coordinates x,y, width of box, height of box)



  display.setTextSize(0.5);                            
  display.setTextColor(WHITE,BLACK);
    display.setCursor(73,16); 
  display.print(houroff[0]);
  display.print(':');  
  display.print(houroff[1]);
    display.print(':'); 
  display.print(houroff[2]);
  display.display();
///////////////////////////
  
  delay(5000);
  display.clearDisplay();
  
  }

void TimeDisplay()
{
    DateTime now = rtc.now();
    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC); 
    Serial.println();
    delay(1000);


                            
  display.setTextSize(2);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(20,1);                           
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  
  display.setTextSize(0.5);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(15,20);
  display.print(now.day(), DEC);

  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.year(), DEC);
  
  display.drawRect(75,19,50,13, WHITE);

  display.setTextSize(0.5);                            
  display.setTextColor(WHITE,BLACK);
  display.setCursor(77,21);
  display.print(rtc.getTemperature());
  display.print(" C");

  
  display.display();
  display.clearDisplay();
 
  
  }
