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
void LedSplit(String t)
{
   char str[t.length()];
   t.toCharArray(str, t.length());
   const char s[2] = ",";
   char *token;
   token = strtok(str, s);
   int lct = 0;
   ledIndex[lct] = atol(token);
   while( token != NULL ) 
   {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
      ledIndex[lct] = atol(token);
      lct++;
   }
   lct = 0;
   free(token);

//    char *p = new char[t.length()+1];
//    strcpy(p, t.c_str());
//   char *str;
//    int ct = 0;
//    while ((str = strtok_r(p, ",", &p)) != NULL)
//    {
//     str = strtok_r(p, ",", &p);
//    ledIndex[0] = atoi(str);
//       ct++;
//    }
//    free(p);
//    free(str);
//    ct = 0;
}
