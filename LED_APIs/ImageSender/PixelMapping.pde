void updateIndex(int p){
  int line = p /2;
  int f = (p % 2);
  int lineShift = line * (DISPWIDTH * 12);
  
  int s = (12* f) + lineShift;
 
  int indexSft = p * 24;
  ledIndex[0+indexSft] = pxArr[6 + s];
  ledIndex[1+indexSft] = pxArr[7 + s];
  ledIndex[23+indexSft] = pxArr[5 + s];
  ledIndex[22+indexSft] = pxArr[4+DISPWIDTH +s];
  ledIndex[2+indexSft] = pxArr[8+DISPWIDTH +s];
  ledIndex[21+indexSft] = pxArr[3+DISPWIDTH*2 + s];
  ledIndex[20+indexSft] = pxArr[2+DISPWIDTH*2+ s];
  ledIndex[3+indexSft] = pxArr[9+DISPWIDTH*2+ s];
  ledIndex[4+indexSft] = pxArr[10+DISPWIDTH*2+ s];
  ledIndex[19+indexSft] = pxArr[1+DISPWIDTH*4+ s];
  ledIndex[5+indexSft] = pxArr[11+DISPWIDTH*4+ s];
  ledIndex[18+indexSft] = pxArr[1+DISPWIDTH*6+ s];
  ledIndex[6+indexSft] = pxArr[11+DISPWIDTH*6+ s];
  ledIndex[17+indexSft] = pxArr[1+DISPWIDTH*7+ s];
  ledIndex[7+indexSft] = pxArr[11+DISPWIDTH*7+ s];
  ledIndex[16+indexSft] = pxArr[1+DISPWIDTH*9+ s];
  ledIndex[8+indexSft] = pxArr[11+DISPWIDTH*9+ s];
  ledIndex[15+indexSft] = pxArr[2+DISPWIDTH*10+ s];
  ledIndex[9+indexSft] = pxArr[10+DISPWIDTH*10+ s];
  ledIndex[14+indexSft] = pxArr[3+DISPWIDTH*11+ s];
  ledIndex[10+indexSft] = pxArr[9+DISPWIDTH*11+ s];
  ledIndex[13+indexSft] = pxArr[5+DISPWIDTH*12+ s];
  ledIndex[12+indexSft] = pxArr[6+DISPWIDTH*12+ s];
  ledIndex[11+indexSft] = pxArr[7+DISPWIDTH*12+ s];
}
