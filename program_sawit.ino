#include <SPI.h>  
#include <Pixy2.h>

Pixy2 pixy;

int signature = 0;
int x = 0;                               //positon x axis
int y = 0;                             //position y axis
unsigned int width = 0;         //object's width
unsigned int height = 0; 
static int i = 0;

int state = 0;
int state1 = 0;

//driver motor
const int M1_DIR = 7;
const int M1_PWM = 6;
const int M2_DIR = 4;
const int M2_PWM = 5;

int onoff = 8;
int valuebutton = 0;

int relay1 = 18;
int relay2 = 19;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixy.init();

  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR, OUTPUT); 
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);

  pinMode (onoff, INPUT_PULLUP);
  pinMode (relay1, OUTPUT);
  pinMode (relay2, OUTPUT);

  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, HIGH);
}

void loop() {

  valuebutton = digitalRead (onoff);

  if (valuebutton == LOW){

  uint16_t blocks;
  pixy.setLamp(1,1);
  pixy.ccc.numBlocks;
  blocks = pixy.ccc.getBlocks();                            //receive data [block] from pixy 
  signature = pixy.ccc.blocks[i].m_signature;    //get object's signature
  x = pixy.ccc.blocks[i].m_x;                             //get x position
  y = pixy.ccc.blocks[i].m_y;                            //get y position
  width = pixy.ccc.blocks[i].m_width;                //get width
  height = pixy.ccc.blocks[i].m_height;

  Serial.print ("x= ");
  Serial.print (x);
  Serial.print (" y= ");
  Serial.print (y);
  Serial.print (" width= ");
  Serial.print (width);
  Serial.print (" height= ");
  Serial.print (height);
  Serial.print (" s= ");
  Serial.println (signature);
  delay (1000);

  if (x <= 5 && y <= 5){
    depan ();
    digitalWrite (relay1, LOW);
    digitalWrite (relay2, HIGH);
    }

  else if (x >= 5 && y >= 5){
    state = 1;
    }

  if (signature == 5){
    kanan();
    delay (2000);
    Stop();
    }

  if (state == 1) {
    digitalWrite (relay1, LOW);
    digitalWrite (relay2, HIGH);

    if (x <=60){
      kanan ();
      }

    if (x >= 250){
      kiri ();    
      }

    if (x >= 100 && x <= 200){
      depan ();
      }
      
    }
    
    
    }

  else {
    digitalWrite (relay1, HIGH);
    digitalWrite (relay2, HIGH);
    }
    
    }

    

void depan () {
  digitalWrite (M1_DIR, LOW);
  digitalWrite (M2_DIR, LOW);
  analogWrite (M1_PWM, 200);
  analogWrite (M2_PWM, 200);
  }


void kanan () {
  digitalWrite (M1_DIR, HIGH);
  digitalWrite (M2_DIR, LOW);
  analogWrite (M1_PWM, 200);
  analogWrite (M2_PWM, 200);
  }

void kiri () {
  digitalWrite (M1_DIR, LOW);
  digitalWrite (M2_DIR, HIGH);
  analogWrite (M1_PWM, 200);
  analogWrite (M2_PWM, 200);
  }

void Stop () {
  digitalWrite (M1_DIR, LOW);
  digitalWrite (M2_DIR, LOW);
  digitalWrite (M1_PWM, LOW);
  digitalWrite (M2_PWM, LOW);
  }
