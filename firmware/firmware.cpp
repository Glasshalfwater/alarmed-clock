#include <Arduino.h>
#include <Adafruit_GFX.h> // graphics library 
#include <SPI.h> 
#include <TFT_eSPI> // Because updated screen is a TFT over SPI, albeit board supports a range of inputs
 
#define CS 0
#define RST 1
#define DC 2
#define MOSI 3
#define SCK 4
#define LED 5
#define MISO 6

#define BUZZER_PIN 19

#define sw1 7
#define sw2 8
#define sw3 9

// Fix setColRowStart() by exposing it via a subclass
class MyST7789 : public Adafruit_ST7789 {
public:
  MyST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst)
    : Adafruit_ST7789(cs, dc, mosi, sclk, rst) {}
  void setOffsets(uint8_t col, uint8_t row) {
    _colstart = _colstart2 = col;
    _rowstart = _rowstart2 = row;
  }
};

MyST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// setup() runs ONCE when the board powers on
void setup() {
  Serial.begin(115200); // lets the board talk to your computer EDIT: 115200 is a common baud rate, works for ESP32S3 Plus as well

  pinMode(TFT_BL, OUTPUT); // Set the backlight pin mode, or just wire it to 3.3V
  digitalWrite(TFT_BL, LOW); // Turns the backlight ON, for some reason this screen is active Low, so setting it to LOW is really HIGH

  tft.init(76, 284); // Our panel size (portrait)
  tft.setOffsets(82, 18); // Offsets for the weird resolution
  tft.invertDisplay(false); // Invert the colors (This display is flipped from normal)
  tft.setRotation(1); // Landscape, if it's upside down use 3!
  Serial.println("TFT Initialized!");

  tft.fillScreen(ST77XX_BLACK); // clear the screen

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(6);
  tft.setCursor(0,0); // Where the text is drawn, 0,0 is top left
  tft.print(42); // Show whatever you want! Draws from the top left of the text/number/shape 
}

// Current iteration plan: display time, then rest for 30 secs, sync up again, and repeat. Of course, becomes active upon button inputs, touchscreen inputs, WIFi connection, etc.
// Will implement after math final in late fall/early winter

void loop() {
  tft.drawString("hello, world, welcome to this wip", 15, 15, 2);
}
