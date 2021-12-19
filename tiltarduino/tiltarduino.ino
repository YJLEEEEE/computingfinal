#include <Adafruit_NeoPixel.h>              // 네오픽셀 라이브러리를 불러옴
#define PIN 6
#define LEDNUM 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRB + NEO_KHZ800);  // 네오픽셀 객체 불러옴

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  strip.setBrightness(50);  
  
  Serial.begin(9600);
  pinMode(7,INPUT);
  digitalWrite(7, HIGH);
}

void loop() {

    theaterChaseRainbow(70);
  rainbow(10);
  // put your main code here, to run repeatedly:
  //int value = 0;
  if(digitalRead(7) == LOW)
  {
     Serial.println("Stand");
  }
  else
  {
    Serial.println("lean");
  }
  delay(70);
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  for (int a = 0; a < 30; a++) { 
    for (int b = 0; b < 3; b++) {
      strip.clear();         
      for (int c = b; c < strip.numPixels(); c += 3) {        
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color);
      }
      strip.show();                
      delay(wait);                 
      firstPixelHue += 65536 / 90; 
    }
  }
}

void rainbow(int wait) {  
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());      
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}
