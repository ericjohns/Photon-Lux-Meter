#include "Particle.h"

// Test Program #1 for Firebase Integration
// Just generates some simple random data once a minute

#include <math.h> // This is just for cos and M_PI, used in generating random sample data

// Forward declarations
void publishData();

const unsigned long PUBLISH_PERIOD_MS = 10000;
const unsigned long UPDATE_PERIOD_MS = 10000;
const unsigned long FIRST_PUBLISH_MS = 5000; //5000
const char *PUBLISH_EVENT_NAME = "test1data";

unsigned long lastPublish = FIRST_PUBLISH_MS - PUBLISH_PERIOD_MS;
int nextValue = 1;

int photoresistor = A0;
int power = A5;
int analogvalue;

void setup() {
	Serial.begin(9600);

	pinMode(photoresistor,INPUT);
    pinMode(power,OUTPUT);
    digitalWrite(power,HIGH);
    Particle.variable("analogvalue", &analogvalue, INT);

}

void loop() {
    analogvalue = analogRead(photoresistor);
	if (millis() - lastPublish >= PUBLISH_PERIOD_MS) {
		lastPublish = millis();
		publishData();
	}
	if (millis() - lastPublish >= UPDATE_PERIOD_MS) {
	    lastPublish = millis();
	    updateData();
	}
}

void publishData() {
	// This just publishes some somewhat random data for testing

	// a is a monotonically increasing integer
	//int entrynumber = nextValue++;

	int lux = analogvalue; //rand();

	char buf[256];
	snprintf(buf, sizeof(buf), "{\"lux\":%d}", lux);
	Serial.printlnf("publishing %s", buf);
	Particle.publish(PUBLISH_EVENT_NAME, buf, PRIVATE);
}

void updateData() {
	// This just publishes some somewhat random data for testing

	// a is a monotonically increasing integer
	//int entrynumber = nextValue++;

	int luxcurrent = analogvalue; //rand();

	char buf[256];
	snprintf(buf, sizeof(buf), "{\"lux\":%d}", luxcurrent);
	Serial.printlnf("publishing %s", buf);
	Particle.publish(PUBLISH_EVENT_NAME, buf, PRIVATE);
}
