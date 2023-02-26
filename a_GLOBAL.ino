#include <WiFi.h>
#include <M5StickC.h>
#include <PinButton.h>
#include <WebServer.h>
#include <Preferences.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 27 // PIN LED
#define NUMPIXELS 1 // ilość LED

#define LED_BUILTIN 10

Preferences preferences;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setupmatrix() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setTextColor(0);
  matrix.setBrightness(20); // 20
  matrix.fillScreen(matrix.Color(0,0,0));
  }

//DON'T CHANGE THESE VARIABLES, YOU CAN CHANGE THEM IN THE WEB UI
String WIFI_SSID = "";
String WIFI_PASS = "";
String VMIX_IP = "";
String M_TALLY = "";
int VMIX_PORT = 8099; //USES THE TCP API PORT, THIS IS FIXED IN VMIX
int TALLY_NR = 1;

//Kolory
uint32_t black = matrix.Color(0, 0, 0);
uint32_t white = matrix.Color(255, 255, 255);
uint32_t red = matrix.Color(255, 0, 0);
uint32_t green = matrix.Color(0, 255, 0);
uint32_t blue = matrix.Color(0, 0, 255);
uint32_t yellow = matrix.Color(255, 255, 0);
uint32_t purple = matrix.Color(128, 0, 128);
uint32_t magenta = matrix.Color(255,0,255);
