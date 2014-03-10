import edu.princeton.cs.chuck.*;

Jchuck jchuck;

void setup() {
  size(400,300);
  jchuck = Jchuck.start();
  noLoop();
}

void draw() {
  background(40);
  rect(100, 100, 200, 100);
  String[] files = { dataPath("sinetone.ck") };
  boolean sporked = jchuck.spork(files);
}

void mousePressed() {
  jchuck.sendTo("ChuckSimple", 1);
}
