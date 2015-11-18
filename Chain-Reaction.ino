// Include Servo library, in case we use it
#include <Servo.h>

// Configure operation mode
String input = "FSR";          // LDR or FSR
String output = "SERVO";       // set to MOTOR or SERVO. Not currently used.
String mode = "THRESHOLD";     // set to THRESHOLD or CONTINUOUS
String behaviour = "RESET"; // set to LATCHING or RESET

// Configure value for threshold mode
const int threshold = 10;

// Configure input
int ldrAnalogPin = 0; // analog pin to which the light-dependent resistor is connected
int fsrAnalogPin = 1; // pin to which force-sensitive resistor is connected
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
  int lightLevel = analogRead(ldrAnalogPin);

  // ...and map the result to a range the servo can handle
  // you may need to tinker with these values. Here, we're 
  // mapping bright office light to servo angles (0..180 degrees)
  lightLevel = map(lightLevel, 100, 800, 0, 180);
  lightLevel = constrain(lightLevel, 0, 180);     // Make really sure it's within that range

  // Read the value from the FSR...
  int forceLevel = analogRead(fsrAnalogPin);
  forceLevel = map(forceLevel, 0, 1023, 0, 180);
  forceLevel = constrain(forceLevel, 0, 180);


  if ( mode == "THRESHOLD" ) {
    if ( input == "LDR" ) {
      if ( lightLevel > threshold ) {
        // threshold reached, trigger the servo action
        myServo1.write(angleTriggered);
      } else {
        // threshold not reached, return servo to rest
        if ( behaviour == "RESET") {myServo1.write(angleRest); };
      }
    } else if (input == "FSR") {
      if ( forceLevel > threshold ) {
        myServo1.write(angleTriggered);
        } else {
          if ( behaviour == "RESET") { myServo1.write(angleRest); };
        }
      }
  } else {
    // We're working continuously, so update the output directly
    if ( input == "LDR") { myServo1.write(lightLevel); };
    if ( input == "FSR") { myServo1.write(forceLevel); };
  }

  // Output lightLevel to serial for debug purposes
  if ( input == "LDR" ) {
    Serial.print("lightLevel = ");
    Serial.println(lightLevel);
  }
  if ( input == "FSR" ) {
    Serial.print("forceLevel= ");
    Serial.println(forceLevel);
  }

  

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

