#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];

const int trigPin = 3;//Trig - grey Jumper
const int echoPin = 9;//Echo - white Jumper
int leftmotor = 5; // left motor in pin 5
int rightmotor = 10; // right motor in pin 10
int distance;

long duration, cm, inches;// reads in increments of cm and inches


void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
//  Serial.begin(9600);  // start serial for output
  t = 0;

  pinMode(trigPin, OUTPUT);//defines the different pins as input vs. output
  pinMode(echoPin, INPUT); // white jumper = output
  pinMode(leftmotor, OUTPUT);
  pinMode(rightmotor, OUTPUT);
}

void loop() {

  tag();
  ultra();

}

void tag() {

  Wire.requestFrom(9, 16);
  while (Wire.available())
  {
    data[t] = Wire.read();
    if (t < 15)
      t++;
    else
      t = 0;
  }

}

void ultra() { // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration / 2) / 29.1;
  // Prints the distance on the Serial Monitor
//  Serial.println(distance);
//    Serial.print(" cm");



    if (data[14] < 35 && data[0] > 35) { //when right sensor senses line
      analogWrite(5, 20*speedmult);
      analogWrite(6, 0);
      analogWrite(10, 120*speedmult);
      analogWrite(11, 0);
    }

    else if (data[12] < 35 && data[0] > 35) { //when right sensor senses line
      analogWrite(5, 20*speedmult);
      analogWrite(6, 0);
      analogWrite(10, 120*speedmult);
      analogWrite(11, 0);
    }


    else if (data[14] > 35 && data[0] < 35) { //when left sensor senses line

      analogWrite(5, 120*speedmult);
      analogWrite(6, 0);
      analogWrite(10, 20*speedmult);
      analogWrite(11, 0);
    }

    else if (data[14] < 35 && data[0] < 35) {
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(10, 0);
      analogWrite(11, 0);

    }

    else {
      analogWrite(5, 120*speedmult); //left
      analogWrite(6, 0);
      analogWrite(10, 20*speedmult); //right
      analogWrite(11, 0);
    }
    


}
  long microsecondsToInches(long microseconds) {
    return microseconds / 74 / 2;
  }

  long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
  }

