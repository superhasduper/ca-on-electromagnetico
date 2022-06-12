#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LONGITUD 21.8
#define SEN1 4

bool anterior=0;
long t1, t2;
double velocidad=0.00;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
 Serial.begin(9600);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
display.clearDisplay();
   
 pinMode(SEN1,INPUT);
 

}

void loop() {
  if(digitalRead(SEN1)!=anterior){
    anterior=digitalRead(SEN1);
    if(digitalRead(SEN1)==1){
      t1=micros();
    }
    else{
      t2=micros();
      
      mostrarvel();
    }
   }
   

digitalWrite(LED_BUILTIN,digitalRead(SEN1));


}

void mostrarvel()
{
  velocidad=(LONGITUD)/((t2-t1)/1000.0);
      Serial.println((t2-t1));
      
    display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(velocidad,4);
  display.display();    
      
  }
