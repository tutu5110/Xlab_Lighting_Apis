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

int  m_blue;
int  m_red;
int  m_green;


void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif  
Serial.begin(9600);                
m_blue = 0;
m_red = 0;
m_green = 0;
pixels.begin(); // This initializes the NeoPixel library.
  
//  for(int i=0;i<NUMPIXELS;i++){
//    
//    pixels.setPixelColor(i, pixels.Color(0,15,0)); // Moderately bright green color.
//    
//    pixels.show(); // This sends the updated pixel color to the hardware.
//    
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
  fadeInColor(1,23,25,25,true,1);
  
}

void loop() {

 // changeColor(1,23,25,25);


}


/********* Single Panel Functions *************/

void fadeInColor(int quad, int r, int g, int b){
   int _time = 5;
  int _start = quad - 1;
  if(_start < 0 ) _start = 0;
  _start = _start * PXQUADS;
  int _end = quad * PXQUADS;
  //initialize
  uint32_t color = pixels.getPixelColor(_start);
  for(int i = _start; i < _end; i ++){
     color = pixels.getPixelColor(i);
      m_red = (color >> 16) & 0xff;
      m_green = (color >> 8) & 0xff;
      m_blue = color & 0xff;
      m_red+=1;
      m_green+=1;
      m_blue+=1;
      pixels.setPixelColor(i, pixels.Color(confine(m_red,r),confine(m_green,g),confine(m_blue,b)));
       delay(_time);
   }
    pixels.show();
}

boolean fadeInColor(int quad, int r, int g, int b, boolean animated, int index){
  if(index == 0){
    index = (quad -1) * PXQUADS;
  }
  int _time = 5;
  int _start = quad - 1;
  if(_start < 0 ) _start = 0;
  _start = _start * PXQUADS;
  int _end = quad * PXQUADS;
   uint32_t colorCu = pixels.getPixelColor(_start);
   //check last color
      uint32_t color = pixels.getPixelColor(_end);
     
    //if sequence is completed
  if(index > _end)
      return true;

     
  for(int i = _start; i < index; i ++){
       //get previous
      color = pixels.getPixelColor(i);
      m_red = (color >> 16) & 0xff;
      m_green = (color >> 8) & 0xff;
      m_blue = color & 0xff;  
      m_red+=2;
      m_green+=2;
      m_blue+=2;
      pixels.setPixelColor(i, pixels.Color(confine(m_red,r),confine(m_green,g),confine(m_blue,b)));
       delay(_time);
   }
    pixels.show();
    
    if(m_red >= r)
      index ++;
      
    fadeInColor(1,23,25,25,true,index);

}


// Change led color in a quad of the loop, without animation.
void changeColor(int quad, int r, int g, int b){
  changeColor(quad,r,g,b,false);
}

// Change led color in a quad of the loop, with animation.
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
   }
    pixels.show();
}

// confines a range of numbers
int confine(int num, int upperlimit){
  if(num > upperlimit)
    return upperlimit;
   return num;
}
