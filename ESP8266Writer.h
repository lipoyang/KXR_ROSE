#ifndef __ESP8266_WRITER__
#define __ESP8266_WRITER__

// ESP 8266 Flash writer
class ESP8266Writer
{
public:
	// begin writer if pin_sw is LOW
	void begin(int pin_sw);
};

#endif
