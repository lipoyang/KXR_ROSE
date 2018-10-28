// KONDO ICS Serial Servo Controller
// Based on ICS3.5

#include <Arduino.h>
#include "IcsController.h"
#include "IcsServo.h"

// ICS servo needs 400usec wait after communication
#define SERVO_WAIT 400

/****************************************
 API
 ****************************************/

// constructor
// serial : serial port for ICS communication
IcsController::IcsController(HardwareSerial& serial)
{
    this->serial = &serial;
    
    onError = NULL;
    servoFirst = NULL;
    servoLast  = NULL;
    servoNow   = NULL;
    
    toWait = false;
    busyPrev = false;
}

// start ICS controller
void IcsController::begin(int baud)
{
    // data 8bit, parity even, stop 1bit
    serial->begin(baud, SERIAL_8E1);
#ifdef GRROSE
    serial->direction(HALFDUPLEX);
#endif
}

#if 0
extern IcsController ics1;
extern IcsController ics2;
#endif

// call this in main loop (for Asynchronous API)
void IcsController::loop()
{
#if 0
    // ICS servo needs 400usec wait after communication
    if(toWait){
        uint32_t now = micros();
        uint32_t elapsed = now - T1_wait;
        if(elapsed > SERVO_WAIT){
            toWait = false;
            if(this == &ics1){
    			Serial.print("f");
            }else{
    			Serial.print("F");
            }
        }
    }
    if(toWait) return;
#endif
    
    // if no servo, do nothing
    if(servoNow == NULL) return;
    
    // receive response
    if(servoNow->isReceiving)
    {
        servoNow->receiveAsync();
    
#if 0  
        // ICS servo needs 400usec wait after communication
        if(!servoNow->isReceiving){
            if(this == &ics1){
                Serial.print("w");
            }else{
                Serial.print("W");
            }
	        toWait = true;
	        T1_wait = micros();
		}
#endif
    }
    // send command
    else
    {
        // any request?
        if(servoNow->request)
        {
            servoNow->sendAsync();
        }
        // select next servo
        else
        {
            servoNow = (servoNow != servoLast) ? servoNow->next : servoFirst;
        }
    }
}

// requested communication completed? (for Asynchronous API)
bool IcsController::isReady()
{
    // if no servo, ready
    if(servoFirst == NULL) return true;
    
    // all servo is ready?
    for(IcsServo* servo = servoFirst; servo != NULL; servo = servo->next)
    {
        if(!servo->isReady()) return false;
    }
    return true;
}

/****************************************
 Private Functions
 ****************************************/

// get received data size
// return : received data size [byte]
int IcsController::getRxSize()
{
    return serial->available();
}

// read received data (1 byte)
// return : received data (1 byte)
uint8_t IcsController::read()
{
    return (uint8_t)(serial->read());
}

// write data to send
// data : data to send
// len : size of data to send
// return : size of sent data
int IcsController::write(uint8_t *data, int len)
{
    // discard trash data
    while(serial->available() > 0)
    {
        serial->read();
    }
    
    return serial->write(data, len);
}

// set timeout [msec]
// ms : time limit [msec]
void IcsController::setTimeout(int msec)
{
    uint32_t cnt = (uint32_t)(msec * 1000);
    T1 = micros();
    T2 = T1 + cnt;
}

// is timeout?
bool IcsController::isTimeout()
{
    uint32_t t = micros();

    bool timeup = (
        ((T1 < T2) && (T2 <= t)) ||
        ((t  < T1) && (T1 < T2)) ||
        ((T2 <= t) && (t  < T1))
    );
    
    return timeup;
}

