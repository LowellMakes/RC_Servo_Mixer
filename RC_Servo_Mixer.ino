//********************************************************
//  RC_Signal_Mixer
//  Author: Brian Bailey
//  License: Beerware
// 
// This code takes in signals from a standard remote control receiver 
// and puts out modified signals.  It's useful for chaning the behavior
// of your RC transmitter.  For example: Maybe you have a tank drive robot.
// You want one channel to act as a mixer for two other channels.  
// So you have two motors driven by two ESCs controlled by two separate 
// channels, then a third channel controls the proportion of the drive
// channels.
// 
// Many transmitters will allow you to use a channel as a mixer, but this
// code can allow more complex interactions.  Perhaps use one channel as
// a throttle limit, etc.

// Includes
#include <Servo.h>

// These value will need calibrating for different receivers
#define MIN_PULSE_WIDTH (1000) // Standard servos have a min pulse width of 1000ms
#define MAX_PULSE_WIDTH (2000) // Standard servos have a max pulse width of 2000ms
#define PULSE_TIMEOUT (10000)  // Max time to wait for a pulse to end 20ms

// These pins can go out to servos
#define SERVO_1_PIN (3)
#define SERVO_2_PIN (4)
#define SERVO_3_PIN (5)
#define SERVO_4_PIN (6)
#define SERVO_5_PIN (7)
#define SERVO_6_PIN (8)

// These pins come in from the RC receiver
#define CHAN_IN_1_PIN (9)
#define CHAN_IN_2_PIN (10)
#define CHAN_IN_3_PIN (11)
#define CHAN_IN_4_PIN (12)
#define CHAN_IN_5_PIN (13)
#define CHAN_IN_6_PIN (14)

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

void setup()
{
	Serial.begin(115200);
	Serial.println("RC Servo Mixer 0.0.0");
	
	servo1.attach(SERVO_1_PIN);
	servo2.attach(SERVO_2_PIN);
	servo3.attach(SERVO_3_PIN);
	servo4.attach(SERVO_4_PIN);
	servo5.attach(SERVO_5_PIN);
	servo6.attach(SERVO_6_PIN);
}

void loop()
{

	int chan1;
	int chan2;
	int chan3;
	int chan4;
	int chan5;
	int chan6;
	char output[256];

	// Read all servos
	chan1 = pulseIn(CHAN_IN_1_PIN, HIGH, PULSE_TIMEOUT);
	chan2 = pulseIn(CHAN_IN_2_PIN, HIGH, PULSE_TIMEOUT);
	chan3 = pulseIn(CHAN_IN_3_PIN, HIGH, PULSE_TIMEOUT);
	chan4 = pulseIn(CHAN_IN_4_PIN, HIGH, PULSE_TIMEOUT);
	chan5 = pulseIn(CHAN_IN_5_PIN, HIGH, PULSE_TIMEOUT);
	chan6 = pulseIn(CHAN_IN_6_PIN, HIGH, PULSE_TIMEOUT);

	// Map each channel input to a standard servo angle value
	chan1 = map(chan1, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
	chan2 = map(chan2, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
	chan3 = map(chan3, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
	chan4 = map(chan4, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
	chan5 = map(chan5, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
	chan6 = map(chan6, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);

	// Debug, write the values to the console
	sprintf(output, "%i, %i, %i, %i, %i, %i", chan1, chan2, chan3, chan4, chan5, chan6);
	Serial.println(output);

	// Default behavior, write them all out unchanged
	servo1.write(chan1);
	servo2.write(chan2);
	servo3.write(chan3);
	servo4.write(chan4);
	servo5.write(chan5);
	servo6.write(chan6);
	

}
