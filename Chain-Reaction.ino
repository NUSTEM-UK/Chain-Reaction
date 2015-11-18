// Include Servo library, in case we use it
#include <Servo.h>

// Configure operation mode
String input = "LDR";       // Not currently used
String output = "SERVO";    // set to MOTOR or SERVO. Not currently used.
String mode = "THRESHOLD"; // set to THRESHOLD or CONTINUOUS

// Configure value for threshold mode
const int threshold = 90;

// Configure input
int ldrPin = 0; // analog pin to which the LDR is connected
int ledPin1 = 13; // pin 13 is mirrored to the onboard LED

// Configure servo
int servoPin1 = 9;
const int angleRest = 0;
const int angleTriggered = 180;
Servo myServo1;

// setup connects all the bits and makes sure they're working. Ignore this and skip to loop() !
void setup() {
  Serial.begin(9600);           // establish a serial connection for debugging
  pinMode(ledPin1, OUTPUT);     // set up the LED
  myServo1.attach(servoPin1);   // set up the servo
  myServo1.write(angleRest);
  delay(200);                   // wait for servo to move into position
}

// The loop is the code the Arduino executes over and over and over. 
void loop() {

  // Read the light level from the LDR...
  int lightLevel = analogRead(ldrPin);
  
  // ...and map the result to a range the servo can handle
  // you may need to tinker with these values. Here, we're 
  // mapping bright office light to servo angles (0..180 degrees)
  lightLevel = map(lightLevel, 100, 800, 0, 180);
  lightLevel = constrain(lightLevel, 0, 180);     // Make really sure it's within that range

  if ( mode == "THRESHOLD" ) {
    // We're looking for a comparison to the threshold value
    if ( lightLevel > threshold ) {
      // threshold reached, trigger the servo action
      myServo1.write(angleTriggered);
    } else {
      // threshold not reached, return servo to rest
      myServo1.write(angleRest);
    }
  } else {
    // We're working continuously, so update the output directly
    myServo1.write(lightLevel);
  }

  // Output lightLevel to serial for debug purposes
  Serial.print("lightLevel = ");
  Serial.println(lightLevel);

  // Flash the LED to prove things are working. Comment out to speed up the loop.
  // blink(100);
}

// Simple function to blink an LED on ledPin1 (default is pin 13, so also blinks onboard LED)
void blink(int time) {
  digitalWrite(ledPin1, HIGH);
  delay(time);
  digitalWrite(ledPin1, LOW);
  delay(time);
}

