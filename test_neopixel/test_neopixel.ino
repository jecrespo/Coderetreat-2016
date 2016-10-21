// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64
#define NUMMATRIZ_X 8
#define NUMMATRIZ_Y 8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 250; // delay for half a second

void setup() {
  Serial.begin(9600);
  Serial.println("Empezamos...");
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for (int i = 0; i < NUMPIXELS + 6; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 50, 0)); // Moderately bright green color.
    pixels.setPixelColor(i - 1, pixels.Color(50, 0, 0));  //red
    pixels.setPixelColor(i - 2, pixels.Color(0, 0, 50));  //blue
    pixels.setPixelColor(i - 3, pixels.Color(50, 50, 0)); //yellow
    pixels.setPixelColor(i - 4, pixels.Color(50, 0, 50)); //purple
    pixels.setPixelColor(i - 5, pixels.Color(0, 50, 50));
    pixels.setPixelColor(i - 6, pixels.Color(0, 0, 0));

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
  }

  for (int y = 0; y < NUMMATRIZ_Y; y++) {
    for (int x = 0; x < NUMMATRIZ_X; x++) {
      pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 25));
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(100); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 0));
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(100);
    }
  }

  boolean leds [8][8];  //leds encendidos y apagados

  for (int y = 0; y < NUMMATRIZ_Y; y++) { //inicializo a 0 todo
    for (int x = 0; x < NUMMATRIZ_X; x++) {
      leds[x][y] = 0;
      pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 0));
    }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  for (int y = 3; y < 5; y++) { //inicializo la semilla, en este caso los centrales
    for (int x = 3; x < 5; x++) {
      leds[x][y] = 1;
      pixels.setPixelColor(num_led (x, y), pixels.Color(25, 0, 0));
    }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(2000);

  for (int z = 0; z < 10; z++) { //10 iteraciones
    for (int y = 0; y < NUMMATRIZ_Y; y++) {
      for (int x = 0; x < NUMMATRIZ_X; x++) {
        if (leds[x][y] == 1) {
          leds[x][y] = 0;
          pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 0));
          if (x <= 3) {
            leds[x - 1][y] = 1;
            pixels.setPixelColor(num_led (x - 1, y), pixels.Color(25, 0, 0));
          }
          if (x >= 4) {
            leds[x + 1][y] = 1;
            pixels.setPixelColor(num_led (x + 1, y), pixels.Color(25, 0, 0));
          }
          if (y <= 3) {
            leds[x][y - 1] = 1;
            pixels.setPixelColor(num_led (x , y - 1), pixels.Color(25, 0, 0));
          }
          if (y >= 4) {
            leds[x][y + 1] = 1;
            pixels.setPixelColor(num_led (x, y + 1), pixels.Color(25, 0, 0));
          }
        }
      }
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    Serial.print("Iteracion: ");
    Serial.println(z);
    delay(2000);
  }
  for (int y = 0; y < NUMMATRIZ_Y; y++) { //inicializo a 0 todo
    for (int x = 0; x < NUMMATRIZ_X; x++) {
      leds[x][y] = 0;
      pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 0));
    }
  }
}

int num_led (int x, int y) { //devuelve el nº led segun cooordenadas la posicion 0,0 es el pin 1
  int pin = x + (y * 8);
  return pin;
}
