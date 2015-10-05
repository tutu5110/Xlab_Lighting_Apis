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
   if(t.length() != 123){
     return;
   }
   Serial.println(t.length());
   char str[t.length()];
   t.toCharArray(str, t.length());
   const char s[2] = ",";
   boolean inputData = false;
   char *token;
   int lct = 0;
   int ledIndexCt = 0;
   int multi = 0;
   //get header
   //Serial.println(t);
   token = strtok(str, s);
   long result = atol(token);
      //package number
   if(currentPackage == result){
      //  Serial.println("P1!");
       while( token != NULL ) 
       {
          printf( " %s\n", token );
          token = strtok(NULL, s);
          result = atol(token);
          if(inputData == false){
            inputData = true;
           // Serial.println(result);
            sections[result] = true;
            multi = result;
            } else{
             ledIndexCt = (lct + (multi * 15));
             if(ledIndexCt < NUMPIXELS){
                ledIndex[ledIndexCt] = result;   
                lct++;
             }
          }
       }
      
   }
   multi = 0;
   lct = 0;
   free(token);
   
   //check update
   for(int i = 0 ; i < NOPACKAGES; i ++){
     if(sections[i])
        gReadyToUpdate = true;
     else{
       gReadyToUpdate = false;
       String str = "H:";
      // str = str + "Current State: " + i + " is false? :" + sections[i];
      // Serial.println(str);
     }
    // delay(5);
   }
   
   if(gReadyToUpdate){
//     Serial.println("yes!!!");
     updateAllPixels();
//     var_dump(ledIndex);
    //reset
      for(int i = 0 ; i < NOPACKAGES; i ++){
        sections[i] = false;
      }
      gReadyToUpdate =  false;
   //  pause = true;
  
   }
  // var_dump(ledIndex);
 }
 
void var_dump(unsigned long l[]){
  int s = sizeof(l);
  String str = "";
  for(int i = 0 ; i <15; i ++){
    str = str + " i: " + i + " value: " + l[i] +"; ";
  }
  Serial.println(str);
}
  
