int confine(int a, int lower, int upper)
{
    if(a<= lower)
    return lower;
    if(a>= upper)
    return upper;
    return a;
}
void establishContact()
{
    while (Serial.available() <= 0)
    {
        Serial.println("A");  // send a capital A
        delay(300);
    }
}
int getBeginIndex(int quad)
{
    return (quad-1) * PXQUADS+1;
}
int confine(int num, int upperlimit)
{
    if(num > upperlimit)
    return upperlimit;
    return num;
}
void AssembleData(String t)
{
   char str[t.length()];
   t.toCharArray(str, t.length());
   const char s[2] = ",";
   char *token;
   token = strtok(str, s);
   int lct = 0;
   Serial.println(t);
   long result = atol(token);
   ledIndex[lct] = result;
   ha[ACounter] = result;
   lct++;
   ACounter++;
   while( token != NULL ) 
   {
      printf( " %s\n", token );
      token = strtok(NULL, s);
      result = atol(token);
      ledIndex[lct] = result;
      ha[ACounter] = result;      
      lct++;
      ACounter++;
   }
   lct = 0;
   ACounter = 0 ;
   free(token);
//   if(Acounter != 7){
////       Serial.println("
//   }
//   Serial.println("haha");
  }
