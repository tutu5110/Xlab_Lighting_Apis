/******    APIs for XLAB Light Panels  ******/
/******    Jing Qian **********/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN        6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS  24
#define NOQUADS    4
#define NOPANELS   1
#define PXQUADS NUMPIXELS/NOQUADS
#define DISPWIDTH 13
#define DISPHEIGHT 13
#define PXPERSTRIP = 24

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
int  gcounter;
int m = DISPWIDTH;
int l = DISPHEIGHT;
unsigned long pxArr[DISPWIDTH * DISPHEIGHT];
unsigned long ledIndex[24];

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif  
  Serial.begin(9600);                
  m_blue = 0;
  m_red = 0;
  m_green = 0;
  pixels.begin(); // This initializes the NeoPixel library.
  //assign pxarr
  for(int i = 0 ; i < 3; i ++){
    int tmp = (i % 24);

  }
  initializeLedIndex();
  
  int r = 100;
  int g = 35;
  int b = 55;
  long rgb = rgb232(r,g,b);
  Serial.println("rgb here");
  Serial.println(rgb);
  
  Serial.println("r is ");
  Serial.println((rgb >> 16) & 0xff);
  
    Serial.println("g is ");
  Serial.println((rgb >> 8) & 0xff);
  
    Serial.println("b is ");
  Serial.println(rgb & 0xff);
  
  for(int i = 0; i < 24; i ++){
    ledIndex[i] = rgb;
  }
  
  for(int i=0;i<NUMPIXELS;i++){
    
    pixels.setPixelColor(i, pixels.Color((ledIndex[i] >> 16) & 0xff,(ledIndex[i] >> 8) & 0xff, ledIndex[i] & 0xff)); // Moderately bright green color.
    
    pixels.show(); // This sends the updated pixel color to the hardware.
    
    delay(delayval); // Delay for a period of time (in milliseconds).

  }
//Serial.println(gcounter);
 // fadeToColor(1,35,35,45,true);

//Serial.println(gcounter);
//fadeToColor(2,23,25,25,true);
//Serial.println(gcounter);
//fadeToColor(3,23,25,25,true);
//Serial.println(gcounter);
//fadeToColor(4,23,25,25,true);
//Serial.println(gcounter);
//
//changeColor(1,23,25,25,true);
//changeColor(2,23,25,25,true);
//changeColor(3,23,25,25,true);
}

void loop() {

}


/********* Single Panel Functions *************/

void updateAllPixels(){
    
}

void fadeToColor(int quad, int r, int g, int b){
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
      m_red = getColorIncrement(m_red,r);
      m_green = getColorIncrement(m_green,g);
      m_blue = getColorIncrement(m_blue,b);
      pixels.setPixelColor(i, pixels.Color(confine(m_red,r),confine(m_green,g),confine(m_blue,b)));
       delay(_time);
   }
    pixels.show();
}


boolean fadeToColor(int quad, int r, int g, int b, boolean animated){
  int _time = 15;  
  int _start = quad - 1;
  if(_start < 0 ) _start = 0;
  _start = _start * PXQUADS;
  int _end = quad * PXQUADS;
  int index = (_end - _start) * 30;
  int lightCount = _start;
  uint32_t color = pixels.getPixelColor(_end);
  
  for(int i = 0; i < index; i ++){
      color = pixels.getPixelColor(lightCount);
      m_red = (color >> 16) & 0xff;
      m_green = (color >> 8) & 0xff;
      m_blue = color & 0xff;  
      m_red  = getColorChange(m_red,r);
      m_green = getColorChange(m_green,g);
      m_blue = getColorChange(m_blue,b);
      pixels.setPixelColor(lightCount, pixels.Color(m_red,m_green,m_blue));
      if(i % 30 == 0){
        lightCount ++;
       }
      delay(_time);
      pixels.show();
   }
}

int getColorChange(int a, int b){
if(a>b)
   a -= 2;
 else
   a += 2;
 a = confine(a,b);
 return a;
}

// Change led color in a quad of the loop, without animation.
void changeColor(int quad, int r, int g, int b){
  changeColor(quad,r,g,b,false);
}

// Change led color in a quad of the loop, with animation.
void changeColor(int quad, int r, int g, int b, boolean animated){
  int _time = 50;
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

int getBeginIndex(int quad){
  return (quad-1) * PXQUADS+1;
}
// confines a range of numbers
int confine(int num, int upperlimit){
  if(num > upperlimit)
    return upperlimit;
   return num;
}

int getColorIncrement(int a, int b){
  if(a>b){
    a = a - 2;
     return a;
  }
   else{
     a = a +2;
     return a;
   }
}


void initializeLedIndex(){
  ledIndex[0] = pxArr[6];
  ledIndex[1] = pxArr[7];
  ledIndex[23] = pxArr[5];
  ledIndex[22] = pxArr[4+DISPWIDTH];
  ledIndex[3] = pxArr[8+DISPWIDTH];
  ledIndex[21] = pxArr[3+DISPWIDTH*2];
  ledIndex[20] = pxArr[2+DISPWIDTH*2];
  ledIndex[3] = pxArr[9+DISPWIDTH*2];
  ledIndex[4] = pxArr[10+DISPWIDTH*2];
  ledIndex[19] = pxArr[1+DISPWIDTH*4];
  ledIndex[5] = pxArr[11+DISPWIDTH*4];
  
}

long rgb232(unsigned int r, unsigned int g, unsigned int b)
{
 // long res = 0L;
  long red = r;
  return (red << 16) | (g << 8) | b;
  Serial.println("function");
  Serial.println(red<<16);
 // return res;
}
