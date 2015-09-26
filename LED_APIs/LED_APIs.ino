/******    APIs for XLAB Light Panels  ******/
/******    Jing Qian **********/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24
#define NOQUADS   4
#define NOPANELS   1
#define PXQUADS NUMPIXELS/NOQUADS

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 30; // delay for half a second

unsigned int a = 0;

unsigned int quadrant;

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif  

pixels.begin(); // This initializes the NeoPixel library.
  
  for(int i=0;i<NUMPIXELS;i++){
    
    pixels.setPixelColor(i, pixels.Color(0,15,0)); // Moderately bright green color.
    
    pixels.show(); // This sends the updated pixel color to the hardware.
    
    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}

void loop() {

  changeColor(1,23,25,25);
}


/********* Single Panel Functions *************/

void fadeInColor(int quad, int r, int g, int b){
  
}

void fadeInColor(int quad, int r, int g, int b, boolean animated){
}

void changeColor(int quad, int r, int g, int b){
  changeColor(quad,r,g,b,false);
}
void changeColor(int quad, int r, int g, int b, boolean animated){
  int _time = 10;
  int _start = quad - 1;
  if(_start < 0 ) _start = 0;
  _start = _start * PXQUADS;
  int _end = quad * PXQUADS;
  for(int i = _start; i < _end; i ++){
      pixels.setPixelColor(i, pixels.Color(r,g,b));
      if(animated){
        pixels.show();
        delay(_time);
       }
       pixels.show();
  }
}
