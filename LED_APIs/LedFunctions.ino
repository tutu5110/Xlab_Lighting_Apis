/* XLab Lighting Panel API Functions
***************************
High Level APIs:

Func: AssembleData - Assemble Packages sent from Serial sender. 

Func: fadeToColor - fade a section of led to destination color

Func: changeToColor - change to destination color without fading.

** written by Jing Qian ***

*/

/**********************************************/
 /********* All Panel Functions *************/
 
void AssembleData(String SerialPackageData)
{
   // Sanity Check, make sure you know the data length before continue
   int SDataLength = 196;
   if(SerialPackageData.length() != SDataLength){
     return;
   }
   //  How many data per package;
   int NumDataPoints = 24;
   //  Create Variables to prepare serial data for "splitting", namely, install them into arrays
   char str[SerialPackageData.length()];
   SerialPackageData.toCharArray(str, SerialPackageData.length());
   const char s[2] = ",";
   boolean inputData = false;
   int multi = 0;
   char *token;
   int lct = 0;
   int ledIndexCt = 0;
   String zz = "";
   token = strtok(str, s);
   // Frist result should be P1,or P2, or ...Pn, the ID of package
   long result = atol(token);
   while( token != NULL ) 
   {
      printf( " %s\n", token );
      token = strtok(NULL, s);
      result = atol(token);
       if(inputData == false){
        inputData = true;
        sections[result] = true;
        multi = result;
       } else{
         ledIndexCt = (lct + (multi * NumDataPoints));
         if(ledIndexCt < NUMPIXELS){
            ledIndex[ledIndexCt] = result;   
            lct++;
         }
      }
   }
   //  Reset the counters
   multi = 0;
   lct = 0;
   free(token);
   //  check if all packages has been sent
   for(int i = 0 ; i < NOPACKAGES; i ++){
     if(sections[i])
     {
        gReadyToUpdate = true;
     } else {
       gReadyToUpdate = false;
       break;
     }
   }
   
   if(gReadyToUpdate){
     updateAllPixels();
     // reset all sections
     for(int i = 0 ; i < NOPACKAGES; i ++){
      sections[i] = false;
     }
     // reset updater
      gReadyToUpdate =  false;
   }
 }
 
 /**********************************************/
 /********* Single Panel Functions *************/
 
/* Change led color in a quad of the loop, with animation. */ 
boolean fadeToColor(int quad, int r, int g, int b, boolean animated){
  int _time = 25;  
  int _start = quad - 1;
  if(_start < 0 ) _start = 0;
  _start = _start * PXQUADS;
  int _end = quad * PXQUADS;
  int index = (_end - _start) * 30;
  int lightCount = 0;
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
    // When counter > 30, move to next led in the strip
    if(i % 30 == 0){
      lightCount ++;
    }
    delay(_time);
    pixels.show();
  }
}

/* DEPLETED */ 
void fadeToColor(int quad, int r, int g, int b){
  int _time = 50;
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
    pixels.show();
  }
}

/* Change led color in a quad of the loop, with NO animation. */ 
void changeColor(int quad, int r, int g, int b){
  changeColor(quad,r,g,b,false);
}

/* Change led color in a quad of the loop, with animation. */ 
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

/* Func Replaces getColorIncrement */
int getColorChange(int a, int b){
  if(a>b){
    if(a>10)
       a = a * 0.9;
     else
       a-= 3;
  } else {
    if(a>110)
       a += 3;
     else
       a = a * 1.1;
  }
  a = confine(a, 0,128);
  return a;
}

/* Func returns a random 32-bit color for a pixel */
long getRandomColor(int r, int g, int b){
   randomSeed(micros());
   r = (int)(random(r));
   g = (int)(random(g));
   b = (int)(random(b));
   return get32Color(r,g,b);
}

/* Func determines whether it should be increasing or decreasing color values */
int getColorIncrement(int a, int b){
  if(a>b){
    a--;
    return a;
  } else {
    a++;
    return a;
  }
}

/* Update all Led pixels at once */
void updateAllPixels(){
  for(int i=0;i<NUMPIXELS;i++)
      {
          pixels.setPixelColor(i, pixels.Color((ledIndex[i] >> 16) & 0xff,(ledIndex[i] >> 8) & 0xff, ledIndex[i] & 0xff)); 
      }
  pixels.show(); 
}

/* convert r,g,b to 32 bit long */
long get32Color(unsigned int r, unsigned int g, unsigned int b)
{
  long red = r;
  return (red << 16) | (g << 8) | b;

}


