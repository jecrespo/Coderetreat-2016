//Coderetreat-2016
//Juego de la vida: https://es.wikipedia.org/wiki/Juego_de_la_vida

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

int delayval = 1000; // delay
boolean universo [8][8];  //leds encendidos y apagados
boolean universo_siguiente [8][8];  //leds encendidos y apagados
int num_iteracion = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Coderetreat-2016");
  Serial.println("Juego de la vida");
  Serial.println("-----------------");

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.
  inicializa_universo();
  delay(delayval);
}

void loop() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (int x = 0; x < NUMMATRIZ_X; x++) {
    for (int y = 0; y < NUMMATRIZ_Y; y++) {
      int circundantes = cacular_circundantes(x, y);
      if (universo[x][y] == 1) {
        if ((circundantes < 2) || (circundantes > 3)) {
          universo_siguiente[x][y] = 0;
          pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 0));
          Serial.print("Mueren la celda: ");
          Serial.print(x);
          Serial.print(" , ");
          Serial.println(y);
        }
      }
      else {
        if ((circundantes == 3)) {
          universo_siguiente[x][y] = 1;
          pixels.setPixelColor(num_led (x, y), pixels.Color(25, 0, 0));
          Serial.print("Nace la celda: ");
          Serial.print(x);
          Serial.print(" , ");
          Serial.println(y);
        }
      }
    }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  num_iteracion++;
  Serial.print("Iteracion: ");
  Serial.println(num_iteracion);
  actualiza_universo();
  delay(delayval);
}

int num_led (int x, int y) { //devuelve el nº led segun cooordenadas la posicion 0,0 es el pin 1
  int pin = x + (y * 8);
  return pin;
}

int cacular_circundantes (int x, int y) {
  int num_circundantes = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      num_circundantes += universo[i][j];
    }
  }
  return num_circundantes;
}

void inicializa_universo() {  //inicializa el universo tal y como quieres que empiece
  Serial.println("Inicializado");
  for (int x = 0; x < NUMMATRIZ_X; x++) {
    for (int y = 0; y < NUMMATRIZ_Y; y++) {
      if (x > 3) {
        universo[x][y] = 1;
        universo_siguiente[x][y] = 1;
        pixels.setPixelColor(num_led (x, y), pixels.Color(25, 0, 0));
      }
      else {
        universo[x][y] = 0;
        universo_siguiente[x][y] = 0;
        pixels.setPixelColor(num_led (x, y), pixels.Color(0, 0, 0));
      }
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }
}

void actualiza_universo() {
  for (int x = 0; x < NUMMATRIZ_X; x++) {
    for (int y = 0; y < NUMMATRIZ_Y; y++) {
      universo[x][y] = universo_siguiente[x][y];
    }
  }
}

