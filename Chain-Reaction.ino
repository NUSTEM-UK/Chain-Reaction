// Include Servo library, in case we use it
#include <Servo.h>

int ldrPin = 0; // analog pin to which the LDR is connected


int ledPin1 = 13; // pin 13 is mirrored to the onboard LED

Servo myServo1;
int servoPin1 = 9;

// Configure servo angles
const int angleRest = 0;
const int angleTwitch = 180;

void setup() {
  Serial.begin(9600);           // establish a serial connection for debugging
  pinMode(ledPin1, OUTPUT);     // set up the LED
  myServo1.attach(servoPin1);   // set up the servo
  myServo1.write(angleRest);
  delay(200);                   // wait for servo to move into position
}

void loop() {

  // Read the light level from the LDR...
  int lightLevel = analogRead(ldrPin);
  
  // ...and map the result to a range the servo can handle
  lightLevel = map(lightLevel, 100, 800, 0, 180);
  lightLevel = constrain(lightLevel, 0, 180);     // Make really sure it's within that range

  // Now pass that value to the servo as an angle
  myServo1.write(lightLevel);
  Serial.print("lightLevel = ");
  Serial.println(lightLevel);


  // Heartbeat LED to demonstrate that we're powered up
  // On an Uno, will flash the onboard LED beside pin 13 (assuming that's ledPin1)
//  digitalWrite(ledPin1, 100);
//  delay(150);
//  digitalWrite(ledPin1, 100);
//  delay(150);
}
