/* XLab Lighting Panel Basic Functions
***************************
** written by Jing Qian ***
*/

int confine(int a, int lower, int upper)
{
    if(a<= lower)
    return lower;
    if(a>= upper)
    return upper;
    return a;
}

int confine(int num, int upperlimit)
{
    if(num > upperlimit)
    return upperlimit;
    return num;
}

void establishContact()
{
    while (Serial.available() <= 0)
    {
        Serial.println("ready");  // send a capital A
        delay(300);
    }
}

int getBeginIndex(int quad)
{
    return (quad-1) * PXQUADS+1;
}

void var_dump(unsigned long l[]){
  int s = sizeof(l);
  String str = "";
  for(int i = 0 ; i <NUMPIXELS; i ++){
    str = str + " i: " + i + " value: " + l[i] +"; ";
  }
  Serial.println(str);
}

void _print(String w, int a){
  String str = "";
  str = w;
  str = str + a;
  Serial.println(str);
}

void _print(String w, long a){
  String str = "";
  str = w;
  str = str + a;
  Serial.println(str);
}
  
