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
        Serial.println("ready");  // send a capital A
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
   if(t.length() != 196){
     return;
   }
  // Serial.println(t.length());
   char str[t.length()];
   t.toCharArray(str, t.length());
   const char s[2] = ",";
   boolean inputData = false;
   int multi = 0;
   char *token;
   int lct = 0;
   int ledIndexCt = 0;
   String zz = "";
   //get header
  // Serial.println(t);
   token = strtok(str, s);
   long result = atol(token);
      //package number
//   if(currentPackage == result){
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
             ledIndexCt = (lct + (multi * 24));
             if(ledIndexCt < NUMPIXELS){
                ledIndex[ledIndexCt] = result;   
                lct++;
             }
          }
       }
  
   //  var_dump(ledIndex);
  // }
   //zz = "multi value: " + multi;
   // p("multi value is ", multi);
      
   multi = 0;
   lct = 0;
   free(token);
   
   //check update
   for(int i = 0 ; i < NOPACKAGES; i ++){
     if(sections[i])
        gReadyToUpdate = true;
     else{
       gReadyToUpdate = false;
       break;
      // String str = "H:";
      // str = str + "Current State: " + i + " is false? :" + sections[i];
      // Serial.println(str);
     }
    // delay(5);
   }
   
   if(gReadyToUpdate){
//     Serial.println("yes!!!");
     updateAllPixels();
 //    Serial.println(" LED UPDATED!");
///     var_dump(ledIndex);
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
  for(int i = 0 ; i <NUMPIXELS; i ++){
    str = str + " i: " + i + " value: " + l[i] +"; ";
  }
  Serial.println(str);
}

void p(String w, int a){
  String str = "";
  str = w;
  str = str + a;
  Serial.println(str);
}

void p(String w, long a){
  String str = "";
  str = w;
  str = str + a;
  Serial.println(str);
}
  
