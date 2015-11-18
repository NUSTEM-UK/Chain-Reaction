// Include Servo library, in case we use it
#include <Servo.h>

int ledPin1 = 13; // pin 13 is mirrored to the onboard LED

Servo myServo1;
int servoPin1 = 9;

// Configure servo angles
const int angleRest = 0;
const int angleTwitch = 180;



void setup() {
  pinMode(ledPin1, OUTPUT);     // set up the LED
  myServo1.attach(servoPin1);   // set up the servo
  myServo1.write(angleRest);
  delay(200);                   // wait for servo to move into position
}

void loop() {

  

  // Heartbeat LED to demonstrate that we're powered up
  // On an Uno, will flash the onboard LED beside pin 13 (assuming that's ledPin1)
  digitalWrite(ledPin1, HIGH);
  delay(250);
  digitalWrite(ledPin1, LOW);
  delay(250);
}
