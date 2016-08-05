#include "RingBuffer.h"

// void setup();
// void loop();

RingBuffer buffer(10);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	while(!Serial);

	Serial.println("Ring Buffer Test!");
	Serial.println("Enter any message (terminate with \\n):");
	Serial.print(">");
}

void loop() {
  
	if(Serial.available())
	{
		int ch = Serial.read();

		if(ch == '\n')
		{
			while(!buffer.isEmpty())
			{
				Serial.print(buffer.pop());
			}
			Serial.println();
		}
		else
		{
			buffer.push(ch);
		}
	}
}
