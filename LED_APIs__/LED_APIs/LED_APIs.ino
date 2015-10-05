/****** APIs for XLAB Light Panels ******/
/****** Jing Qian **********/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN 6
#define NUMPIXELS 96
#define NOQUADS 4
#define NOPANELS  1
#define PXQUADS NUMPIXELS/NOQUADS
#define DISPWIDTH 13
#define DISPHEIGHT 13
#define PXPERSTRIP  24
#define NOPACKAGES  7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 5;
unsigned int a = 0;
unsigned int quadrant;
int m_blue;
int m_red;
int m_green;
int gcounter;
int m = DISPWIDTH;
int l = DISPHEIGHT;
int lastUpdate = 0;
int ACounter = 0;
int currentPackage = 1;
boolean sections[NOPACKAGES];
boolean gReadyToUpdate = false;
boolean pause = false;
//unsigned long pxArr[DISPWIDTH * DISPHEIGHT];
unsigned long ledIndex[NUMPIXELS];
String tmp;
char val;
boolean animating = false;
boolean readyUpdate = false;
void setup()
{
    #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    m_blue = 0;
    m_red = 0;
    m_green = 0;
    pixels.begin();
    int r = 12;
    int g = 12;
    int b = 22;
    long rgb = get32Color(r,g,b);
    for(int i = 0; i < NUMPIXELS; i ++)
    {
        ledIndex[i] = rgb;
    }
  //  AssignRandomColor();
   // initializeLedIndex();
    for(int i=0;i<NUMPIXELS;i++)
    {
        pixels.setPixelColor(i, pixels.Color((ledIndex[i] >> 16) & 0xff,(ledIndex[i] >> 8) & 0xff, ledIndex[i] & 0xff)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).
    }
    Serial.begin(115200); // RFID reader SOUT pin connected to Serial RX pin at 2400bps
    Serial.setTimeout(500);
   // fadeToColor(1,0,0,0,true);
    establishContact(); // send a byte to establish contact until receiver responds
}
void loop()
{
    
   if (Serial.available() > 0) { // If data is available to read,
    tmp = Serial.readStringUntil('\0'); // read it and store it in val
        
     // Serial.println(tmp);
  //  Serial.println(tmp.length());
    if(!pause)
       AssembleData(tmp);
//     Serial.flush();
    delay(0);
     } 
    else {
    Serial.println("FA"); //send back a hello world
    delay(1);
    }
    
    if(animating)
    {
       // fadeToColor(1,0,0,0,true);
        animating = false;
    }
    
   // updateAllPixels();
}
