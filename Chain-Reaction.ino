#include <Servo.h>

// Configure operation mode
String input = "FSR";		// LDR, FSR, FLEX, DISTANCE, POTENTIOMETER, TILT, HALL, LOAD
String output = "CONTSERVO";					// SERVO, CONTSERVO, RELAY
String mode = "THRESHOLD";				// set to THRESHOLD or CONTINUOUS (NB. use THRESHOLD for RELAY output)
String behaviour = "RESET";				// set to LATCHING or RESET

// Configure value for threshold mode
const int threshold = 90;

// Configure inputs
const int ldrAnalogPin = 0;						// pin to which the light-dependent resistor is connected
const int fsrAnalogPin = 1;						// pin to which force-sensitive resistor is connected
const int flexAnalogPin = 2;					// pin to which flex sensor is connected
const int distanceAnalogPin = 3; 			// pin to which distance sensor is connected
const int potentiometerAnalogPin = 4; // pin to which potentiometer is connected
const int tiltDigitalPin = 2;					// pin to which tilt sensor is connected
const int hallDigitalPin = 3;					// pin to which hall sensor is connected
const int loadAnalogPin = 5;					// pin to which load sensor is connected

const int ledPin1 = 13; 							// use for diagnostic flashing LED. Pin 13 is mirrored to the onboard LED

// Configure servo
int servoPin1 = 9;
const int angleRest = 0;
const int angleTriggered = 180;
const int contServoStop = 90;
const int contServoMove = 180;
Servo myServo1;

// Configure continuous servo
const int servoPinCont = 10;
Servo contServo1;

// Configure relay
const int relayPin1 = 4;								// pin to which relay is connected

// The loop is the code the Arduino executes over and over and over. 
void loop() {
	
	// Get updated data from sensor, which comes back mapped as an integer between 0 and 180
	int sensorValue = updateSensors();	
	
	if ( mode == "THRESHOLD" ) {
		
		// Test if sensor input has exceeded threshold
		if ( sensorValue > threshold ) {
			// It has, so move the servo
			if ( output == "SERVO" ) {
				myServo1.write(angleTriggered);
			} else if ( output == "CONTSERVO" ) {
				contServo1.write(contServoMove);
			} else if ( output == "RELAY" ) {
				digitalWrite(relayPin1, HIGH);
			}
		} else {
			// It hasn't, so return servo to rest if we're in RESET mode
			// (LATCHING mode will not return to rest once triggered, until Arduino is reset)
			if ( behaviour == "RESET" ) { 
				if ( output == "SERVO" ) {
					myServo1.write(angleRest);
				} else if ( output == "CONTSERVO" ) {
					contServo1.write(contServoStop);
				} else if ( output == "RELAY" ) {
					digitalWrite(relayPin1, LOW);
				}
			}
		}
		// end of THRESHOLD mode
	} else {
		// We're working CONTINUOUS, so update the servo directly
		// myServo1.write(sensorValue);

		if ( output == "SERVO" ) {
			myServo1.write(sensorValue);
		} else if ( output == "CONTSERVO" ) {
			contServo1.write(sensorValue);
		}
		
	}
	
	// Output sensorValue to serial for debug purposes
	Serial.print("sensorValue = ");
	Serial.println(sensorValue);
	
	// Flash the LED to prove things are working. Comment out to speed up the loop.
	// blink(100);
}


