import gifAnimation.*;
import processing.serial.*;
Serial myPort;
// Create object from Serial class
String val;
// Data received from the serial port
boolean serialReady = false;
boolean firstContact = false;
boolean firstResponse = false;
PImage[] animation;
Gif loopingGif;
String[] colorsOutput;
String colorOutputStr = "";
int ct = 0;
int color32 = 0;
int test = 0;
int tt = 0;
int rgbReturn = 0;
String rgbStrBuilder = "";
int testColor = 10;
int gct = 0;
int te = 0;
int di = 1;
int[] ledIndex;
int DISPWIDTH = 30;
int DISPHEIGHT = 30;
int[] pxArr;
void setup() {
    size(30, 30);
    frameRate(15);
    println("gifAnimation " + Gif.version());
    loopingGif = new Gif(this, "color1.gif");
    // loopingGif.loop();
    //loopingGif.play();
    animation = Gif.getPImages(this, "color1.gif");
    println(Serial.list());
    String portName = Serial.list()[2];
    colorsOutput = new String[0];
    myPort = new Serial(this, portName, 115200);
    myPort.bufferUntil('\n');
    serialReady = true;
    ledIndex = new int[96];
    pxArr = new int[DISPWIDTH * DISPHEIGHT];
   for(int i = 0 ; i < ledIndex.length; i ++){
     ledIndex[i] = 0;
   }
    
    
   
}
void draw() {
   image(animation[ct], 0, 0);
    loadPixels();
    int j = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    color c;
    String colors = "";
    for (int i = 0; i < 900; i++) {
        c = pixels[i];
        // colors = colors +"(" +(int)(red(c)/2)+","+(int)(green(c)/2)+","+(int)(blue(c)/2)+");
        r = (int)(red(c) / 2);
        g = (int)(green(c) / 2);
        b = (int)(blue(c) / 2);
        color32 = rgb232(r, g, b);
        pxArr[i] = color32;
        //colors = colors + color32 + ",";
    }
    updateIndex(0);
    updateIndex(1);
    updateIndex(2);
    updateIndex(3);
ct++;
if (ct > (animation.length - 1))
ct = 0;

}


void serialEvent(Serial myPort) {
    String a = "";
    int beginIndex = tt * 24;
    int endIndex = tt* 24 + 24;
    val = myPort.readStringUntil('\n');
    if (val != null) {
        val = trim(val);
        if (firstContact == false) {
            if (val.equals("ready")) {
                myPort.clear();
                firstContact = true;
                myPort.write("Processing Ready");
            }
        }
        else {
            println(val);
            if (val.equals("ready")) {
                for (int i = beginIndex;i < endIndex;i++) {
                   // rgbReturn = rgb232(testColor, testColor, testColor);
                    rgbReturn = ledIndex[i];
                    rgbStrBuilder = rgbReturn + "";
                    while (rgbStrBuilder.length() < 7) {
                        rgbStrBuilder = "0" + rgbStrBuilder;
                    }
                    a = a + rgbStrBuilder + ",";
                }
                a = "1," + tt + "," + a + '\0';
                myPort.write(a);
                a = "";
                tt++;
                if (tt > 3) {
                    tt = 0;
                    if (di == 1)
                    te += 4;
                    else
                    te -= 2;
                    if (te > 100) {
                        di = 0;
                    }
                    else if (te <= 3) {
                        di = 1;
                    }
                    testColor = te;
                }
            }
        }
    }
    colorOutputStr = "";
}


void mouseReleased() {
    //if we clicked in the window
    if (mouseButton == LEFT) {
        println("a pressed");
        myPort.write("testn");
        //send a 1
    }
    else {
        println("2 clicked");
        myPort.write('2');
    }
}
int rgb232(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}
