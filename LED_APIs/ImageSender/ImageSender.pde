import processing.serial.*;
Serial xImageSender; 
String val;
boolean firstContact = false;
PImage img;

void setup() 
{
  size(200,200); 
  println(Serial.list());
  String portName = Serial.list()[2]; 
  xImageSender = new Serial(this, portName, 9600);
  xImageSender.bufferUntil('\n');
}

void draw() {
  
}

void serialEvent( Serial xImageSender) {
//put the incoming data into a String - 
//the '\n' is our end delimiter indicating the end of a complete packet
val = xImageSender.readStringUntil('\n');
//make sure our data isn't empty before continuing
if (val != null) {
  //trim whitespace and formatting characters (like carriage return)
  val = trim(val);
  println(val);

  //look for our 'A' string to start the handshake
  //if it's there, clear the buffer, and send a request for data
  if (firstContact == false) {
    if (val.equals("A")) {
      xImageSender.clear();
      firstContact = true;
      xImageSender.write("A");
      println("contact");
    }
  }
  else { //if we've already established contact, keep getting and parsing data
    println(val);

    if (mousePressed == true) 
    {                           
      xImageSender.write("ASD");      
    }

    // when you've parsed the data you have, ask for more:
    xImageSender.write("A");
    }
  }
}

