// Helper functions for the Think Physics Chain Reaction workshop
// Jonathan Sanderson, Northumbria University
// Intitial version: 0.1 2015-11-19

// Blink an LED on ledPin1 (default is pin 13, so also blinks onboard LED)
void blink(int time) {
	digitalWrite(ledPin1, HIGH);
	delay(time);
	digitalWrite(ledPin1, LOW);
	delay(time);
}

int updateSensors() {
	int sensorReading; // Declare the variable we're about to use
	
	// Cascade through possible inputs, pulling data off the relevant sensor pin
	if ( input == "LDR" ) {
		sensorReading = analogRead(ldrAnalogPin);
		sensorReading = map(sensorReading, 100, 800, 0, 180);
	} else if ( input == "FSR" ) {
		sensorReading = analogRead(fsrAnalogPin);
		sensorReading = map(sensorReading, 0, 1023, 0, 180);
	} else {
		sensorReading = 88; // If all you see in the serial window is this, it's gone wrong
	}
	
	// Make extra certain we're not returning anything except an int between 0 and 180
	sensorReading = constrain(sensorReading, 0, 180);
	
	return sensorReading;
}