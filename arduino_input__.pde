import processing.serial.*;
int i;
Serial myPort;
float data;

static final int kNbrDots = 512;
float rStart;

public static int ON =1;
public static int OFF = 0;

void setup() {
  size (500,500);
  delay(300);
  rStart = 30 + random(60);
  background(0);
  
  bad = loadImage("bad.png");
  
  String portName = Serial.list()[1];
  
  println(Serial.list());
  myPort = new Serial(this, "/dev/tty.usbserial-14120", 9600);
}

void setDayglowColor(float myHue)
{
  float ph = sin(millis()*.0001);
 
  int rr = (int) (sin(myHue) * 127 + 128);
  int gg = (int) (sin(myHue + (2*ph) * PI/3) * 127 + 128);
  int bb = (int) (sin(myHue + (4*ph) * PI/3) * 127 + 128);
  stroke(rr,gg,bb);
}


void draw() {
  
  filter(BLUR);
  filter(ERODE);
   
  float n = millis()*.0001 + rStart;
  float rad = width*.97/2;
  float cx = width/2;
  float cy = height/2;
  for (int i = 0; i <= kNbrDots; ++i)
  {
    float theta = i*PI*2 / kNbrDots;
    setDayglowColor(n+theta/6);
    float r = rad * sin(n*theta);
    float px = cx + cos(theta)*r;
    float py = cy + sin(theta)*r;
    ellipse(px,py,4,4);
    
    image(bad,110,75,data,data);
   // fill(0,0,0);
  }

}

  void serialEvent(Serial p){
  String message = myPort.readStringUntil(10);
  if (message != null)
  {
    print("Received: ");
    println(message);
    data = float(message);
  }
 
}

  
