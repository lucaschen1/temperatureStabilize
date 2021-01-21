
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

double currentTemperature = 50;
double alterTemperature ();
String isStabilized();
const double constantTemperature = 50;
unsigned long timeInRange = 0;
bool inRange = false;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
tft.reset();
tft.fillScreen(WHITE);
uint16_t identifier = tft.readID();
tft.begin(identifier);
tft.setRotation(0);

}

void loop() {
  // put your main code here, to run repeatedly:
alterTemperature();
Serial.println(currentTemperature);

tft.setCursor(100, 120);
tft.setTextColor(BLUE);
tft.setTextSize(2);
tft.print(currentTemperature);
delay(500);
tft.fillScreen(WHITE);

isStabilized();
Serial.println(isStabilized());

tft.setCursor(70, 150);
tft.setTextSize(2);
tft.print(isStabilized());

}


double alterTemperature () {
  if (random(0, 2)){
    currentTemperature += 0.1;
  }
  else{
    currentTemperature -= 0.1;
  }
  
  delay(1000);
  return currentTemperature;
  
}

String isStabilized (){
  if ((currentTemperature <= constantTemperature + 1) && (currentTemperature >= constantTemperature - 1)){
    if (inRange == false){
      inRange = true;
      timeInRange = millis();
    }
    if (inRange == true){
      if (millis() - timeInRange > 3000){
        return "Stabilized";
        
        tft.setCursor(100, 150);
        tft.setTextColor(GREEN);
        tft.setTextSize(2);
        tft.print("Stabilized");
        
      }
      return "notStabilized";

       tft.setCursor(100, 150);
        tft.setTextColor(RED);
        tft.setTextSize(2);
        tft.print("notStabilized");
        
    }
    }  
          
    if (!(currentTemperature <= constantTemperature + 1) && (currentTemperature >= constantTemperature - 1)){
      inRange = false;
      return "notStabilized";

      tft.setCursor(100, 150);
        tft.setTextColor(RED);
        tft.setTextSize(2);
        tft.print("notStabilized");
        
    }  
  }






  
 
