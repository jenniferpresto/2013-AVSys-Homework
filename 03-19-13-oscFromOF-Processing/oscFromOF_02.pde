/* Jennifer Presto
 AVSys Homework
 March 19, 2013
 OSC language adapted from tutorial located here:
 http://learning.codasign.com/index.php?title=Sending_and_Receiving_OSC_Data_Using_Processing
 */

import ddf.minim.spi.*;
import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.ugens.*;
import ddf.minim.effects.*;

import oscP5.*;
import netP5.*;

Minim minim;
AudioPlayer one;
AudioPlayer two;
AudioPlayer three;
AudioPlayer four;

OscP5 oscP5;
NetAddress myRemoteLocation;

color colorFlash;

void setup() {
  size(100, 500);

  // start oscP5, telling computer to listen for new messages at 5001
  oscP5 = new OscP5(this, 5001);
  minim = new Minim(this);
  one = minim.loadFile("one.mp3");
  two = minim.loadFile("two.mp3");
  three = minim.loadFile("three.mp3");
  four = minim.loadFile("four.mp3");

  // set remote location to localhost on port 5001
  myRemoteLocation = new NetAddress ("127.0.0.1", 5001);
}

void draw() {
  background(colorFlash);
}


void oscEvent(OscMessage theOscMessage) {
  int valueReceived = theOscMessage.get(0).intValue();
  
  if (valueReceived == 1){
    one.play();
    one.rewind();
    colorFlash = color(165, 96, 96);
  }
  if (valueReceived == 2){
    two.play();
    two.rewind();
    colorFlash = color(97, 128, 163);
  }
  if (valueReceived == 3){
    three.play();
    three.rewind();
    colorFlash = color(160, 153, 71);
  }
  if (valueReceived == 4){
    four.play();
    four.rewind();
    colorFlash = color(63, 104, 37);
  }
  

  // print it out
}

void stop(){
  one.close();
  two.close();
  three.close();
  four.close();
  minim.stop();
  super.stop();
}

