import gifAnimation.*;
import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
boolean serialReady = false;

boolean firstContact = false;
PImage[] animation;
Gif loopingGif;
String[] colorsOutput;
String colorOutputStr = "";
int ct = 0;
int color32 = 0;
int test = 0;
int rgbReturn = 0 ;
String rgbStrBuilder = "";
void setup() 
{
  size(300,300); 
  frameRate(60);
  println("gifAnimation " + Gif.version());
  loopingGif = new Gif(this, "ellipse.gif");
 // loopingGif.loop();
  //loopingGif.play();
  animation= Gif.getPImages(this, "ellipse.gif");

  println(Serial.list());
  String portName = Serial.list()[2]; 
  colorsOutput = new String[0];
  myPort = new Serial(this, portName, 115200);
    myPort.bufferUntil('\n'); 
    serialReady = true;
  //myPort.bufferUntil('\n'); 
}

void draw() {
  image(animation[ct], 0, 0);
  
  loadPixels();
  //get all pixels
  int j = 0; //height
  int r = 0;
  int g = 0 ; 
  int b = 0;
  
  color c;
  String colors = "";
  for (int i = 0 ; i <2 ; i ++) {
    c = pixels[i];
   // colors = colors  +"(" +(int)(red(c)/2)+","+(int)(green(c)/2)+","+(int)(blue(c)/2)+");";
   r = (int)(red(c)/2);
   g = (int)(green(c)/2);
   b = (int)(blue(c)/2);
   
   color32 = rgb232(r,g,b); 
   colors = colors + color32 + ",";
  }
//  colors = colors.substring(0, colors.length()-1)+'#';
//  colorsOutput = (String[])append(colorsOutput, colors);
   colorOutputStr = colors;
//  ct++;
//  if(ct > 1){
//    saveStrings("anim1.txt", colorsOutput);
//    exit();
//  }

ct++;
  if(ct > (animation.length-1))
    ct = 0;
}


void serialEvent( Serial myPort) {
//  val = myPort.readStringUntil('\n');
//  if (val != null) {
//    val = trim(val);
//    if (firstContact == false) {
//      if (val.equals("A")) {
//        myPort.clear();
//        firstContact = true;
//        myPort.write("A");
//        println("contact");
//      }
//    } else { //if we've already established contact, keep getting and parsing data
//      println(val);
//     // myPort.write("7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210\n");
//     String a = "";
//     for(int i = 0 ; i < 10; i ++){
//      a = a + rgb232(int(random(38)),int(random(38)),int(random(10))) +",";
//     }
//     a = a.substring(0,a.length()-1) + "\n";
//     
//      //myPort.write("7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210\n");
//      myPort.write(a);
//      colorOutputStr = "";     
//    }
//  }
    String a = "";
    
//    val = myPort.readStringUntil('\n');
//    if (val != null) {
//      val = trim(val);
//      println(val);
//      
//      
//     
//    }
   
   for(int i = 0 ; i < 5; i ++){
      rgbReturn = rgb232(int(random(38)),int(random(38)),int(random(10)));
      rgbStrBuilder =  rgbReturn + "";
      while(rgbStrBuilder.length() < 7){
          rgbStrBuilder = "0"+rgbStrBuilder;
      }
      
      a = a + rgbStrBuilder+",";
     }
     a = "P1,A0," + a.substring(0,a.length()-1)+'\0';
     //println("P:" + a);
    // println("a size:" + a.length());
     myPort.write(a);
     a = "";
     
//     
//     for(int i = 25; i < 40; i ++){
//      a = a + rgb232(int(random(38)),int(random(38)),int(random(10))) +",";
//     }
     //a = a.substring(0,a.length()-1) + ",AN\n";
    // myPort.write(a);
     
     
      //myPort.write("7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210,7870210\n");
      
      colorOutputStr = "";  
}

void mouseReleased(){
 //if we clicked in the window
        if (mouseButton ==LEFT) {
          println("a pressed");
          myPort.write("test\n");        //send a 1
        } else {
          println("2 clicked");
          myPort.write('2');
        } 
}

int rgb232(int r, int g, int b){
  return (r << 16) | (g <<8 ) | b;
}

