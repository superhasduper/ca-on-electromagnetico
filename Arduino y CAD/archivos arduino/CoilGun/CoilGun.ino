#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <VL53L0X.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

VL53L0X sensor;

void setup() {
Serial.begin(9600);
Wire.begin();
    
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.display();
  delay(1000);
    sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(100000);
  //sensor.startContinuous();
}

void loop() {

  display.clearDisplay();
  
  display.setCursor(11,0);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print("Distancia");
  
  display.setCursor(47,29);
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE); 
  display.print(sensor.readRangeSingleMillimeters());
  display.display();
  delay(100);
  
}
