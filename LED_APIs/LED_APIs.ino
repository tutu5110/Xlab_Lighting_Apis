/* XLab Lighting Main Software.
***************************
** written by Jing Qian ***
*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
#define NUMPIXELS 96
#define NOQUADS 4
#define NOPANELS  1
#define PXQUADS NUMPIXELS/NOQUADS
#define DISPWIDTH 13
#define DISPHEIGHT 13
#define PXPERSTRIP  24
#define NOPACKAGES  4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 5;
int PACKAGESIZE = 1;
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
boolean firstContact = false;
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
    int r = 3;
    int g = 5;
    int b = 6;
    long rgb = get32Color(r,g,b);
    for(int i = 0; i < NUMPIXELS; i ++)
    {
        ledIndex[i] = rgb;
    }
    for(int i=0;i<NUMPIXELS;i++)
    {
        // give panels a light blue for preview
        pixels.setPixelColor(i, pixels.Color((ledIndex[i] >> 16) & 0xff,(ledIndex[i] >> 8) & 0xff, ledIndex[i] & 0xff)); 
        // This sends the updated pixel color to the hardware.
        pixels.show(); 
        // Delay for a period of time (in milliseconds).
        delay(delayval); 
    }
    //  Begin Serials.
    Serial.begin(115200);
    //  Set Serial timeout.
    Serial.setTimeout(1000);
    //  Establish Contact
    establishContact(); 
}

void loop()
{
    // If data is available to read,
    if (Serial.available() > 0) { 
    // read it and store it in val
    tmp = Serial.readStringUntil('\0');
     if(!pause)
      AssembleData(tmp);    
      delay(1);
     } else {
      // Constantly Communicating With Java/Processing end to make sure the connection stays alive.
      Serial.println("ready");
      delay(1);
    }

    if(animating)
    {
       // fadeToColor(1,0,0,0,true);
        animating = false;
    }
}
