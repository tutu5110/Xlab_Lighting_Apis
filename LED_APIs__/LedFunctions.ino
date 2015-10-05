

/********* Single Panel Functions *************/

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
    if(i % 30 == 0){
      lightCount ++;
    }
    delay(_time);
    pixels.show();
  }
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


long get32Color(unsigned int r, unsigned int g, unsigned int b)
{
  long red = r;
  return (red << 16) | (g << 8) | b;

}


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


void AssignRandomColor(){
  int s = DISPWIDTH * DISPHEIGHT;
  unsigned int r = (int)(random(58));
  unsigned int g = (int)(random(24));
  unsigned int b = (int)(random(24));
  for(int i = 0 ; i < s; i ++){
    randomSeed(micros());
    r = (int)(random(58));
    g = (int)(random(24));
    b = (int)(random(24));
//    pxArr[i] = get32Color(r,g,b);
    //   pxArr[i] = get32Color(0,0,0);
  }
}



//void initializeLedIndex(){
//  ledIndex[0] = pxArr[6];
//  ledIndex[1] = pxArr[7];
//  ledIndex[23] = pxArr[5];
//  ledIndex[22] = pxArr[4+DISPWIDTH];
//  ledIndex[2] = pxArr[8+DISPWIDTH];
//  ledIndex[21] = pxArr[3+DISPWIDTH*2];
//  ledIndex[20] = pxArr[2+DISPWIDTH*2];
//  ledIndex[3] = pxArr[9+DISPWIDTH*2];
//  ledIndex[4] = pxArr[10+DISPWIDTH*2];
//  ledIndex[19] = pxArr[1+DISPWIDTH*4];
//  ledIndex[5] = pxArr[11+DISPWIDTH*4];
//  ledIndex[18] = pxArr[1+DISPWIDTH*6];
//  ledIndex[6] = pxArr[11+DISPWIDTH*6];
//  ledIndex[17] = pxArr[1+DISPWIDTH*7];
//  ledIndex[7] = pxArr[11+DISPWIDTH*7];
//  ledIndex[16] = pxArr[1+DISPWIDTH*9];
//  ledIndex[8] = pxArr[11+DISPWIDTH*9];
//  ledIndex[15] = pxArr[2+DISPWIDTH*10];
//  ledIndex[9] = pxArr[10+DISPWIDTH*10];
//  ledIndex[14] = pxArr[3+DISPWIDTH*11];
//  ledIndex[10] = pxArr[9+DISPWIDTH*11];
//  ledIndex[13] = pxArr[5+DISPWIDTH*12];
//  ledIndex[12] = pxArr[6+DISPWIDTH*12];
//  ledIndex[11] = pxArr[7+DISPWIDTH*12];
//}

int getColorIncrement(int a, int b){
  if(a>b){
    a = a - 1;
    return a;
  }
  else{
    a = a +1;
    return a;
  }
}

void updateAllPixels(){

    
     for(int i=0;i<NUMPIXELS;i++)
      {
          pixels.setPixelColor(i, pixels.Color((ledIndex[i] >> 16) & 0xff,(ledIndex[i] >> 8) & 0xff, ledIndex[i] & 0xff)); // Moderately bright green color.
         
         // delay(delayval); // Delay for a period of time (in milliseconds).
      }
       pixels.show(); // This sends the updated pixel color to the hardware.
    
}


