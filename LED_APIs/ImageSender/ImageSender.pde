import gifAnimation.*;
import processing.serial.*;
Serial myPort; 
String val;
boolean firstContact = false;
PImage[] animation;
Gif loopingGif;
String colors= "";
int ct = 0;
void setup() 
{
  size(300, 300); 
  frameRate(60);
  println("gifAnimation " + Gif.version());
  loopingGif = new Gif(this, "ellipse.gif");
 // loopingGif.loop();
  //loopingGif.play();
  animation= Gif.getPImages(this, "ellipse.gif");

  println(Serial.list());
  String portName = Serial.list()[2]; 
  myPort = new Serial(this, portName, 115200);
  //myPort.bufferUntil('\n'); 
}

void draw() {
  
   if (mousePressed == true) 
  {                           //if we clicked in the window
   myPort.write('1');         //send a 1
   println("1");   
  } else 
  {                           //otherwise
  myPort.write('0');          //send a 0
  }  
  image(animation[ct], 0, 0);
  loadPixels();
  //get all pixels
  int j = 0; //height

  color c;
  for (int i = 0 ; i < (30*30); i ++) {
    c = pixels[i];
    colors = colors + "," + red(c);
  }
  colors = colors.substring(0, colors.length() - 1);
  
  ct++;
  if(ct > (animation.length-1))
    ct = 0;
}




