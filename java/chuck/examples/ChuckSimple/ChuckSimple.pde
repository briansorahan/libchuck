/*
 * Trigger random sine wave tones.
 * We do this by sending a 1 on the "ChuckSimple" channel.
 */
import edu.princeton.cs.chuck.*;

Jchuck jchuck;
int rectX=50, rectY=50, rectW=100, rectH=50;
int rectFill=40, rectStroke=180;

void setup() {
  size(200, 150);
  jchuck = Jchuck.start();
  String[] files = { dataPath("sinetone.ck") };
  boolean sporked = jchuck.spork(files);
}

void draw() {
  background(160);
  fill(rectFill);
  stroke(rectStroke);
  rect(rectX, rectY, rectW, rectH);
}

boolean inRect() {
  if (mouseX >= rectX && mouseX <= rectX + rectW && mouseY >= rectY && mouseY <= rectY + rectH) {
    return true;
  } else {
    return false;
  }
}

void mousePressed() {
  if (inRect()) {
    jchuck.sendTo("ChuckSimple", 1);
  }
}

void mouseMoved() {
  if (inRect()) {
    rectFill = 60;
  } else {
    rectFill = 40;
  }
}
