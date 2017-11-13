#ifndef IARDUINOSERIALDATAMANAGER_H
#define IARDUINOSERIALDATAMANAGER_H

#include "../../interfaces.h"

//! defgroup ArduinoSerialDataManager
//!     ingroup MainMenuPlugin_rel_m
//! defgroup ArduinoSerialDataManager_int Interface
//!     ingroup ArduinoSerialDataManager
//! defgroup ArduinoSerialDataManager_imp Implementation
//!     ingroup ArduinoSerialDataManager

//! addtogroup ArduinoSerialDataManager_int
//! {
class IArduinoSerialDataManager :
    public IDataManagerPlugin
{
public:
    enum PinMode
    {
        INPUT,
        OUTPUT
    };
    enum DigitalValue
    {
        LOW,
        HIGH
    };
    enum OscilloscopeRepeatMode
    {
        OFF,
        ON
    };

    virtual QMap<QString, QList<PinMode>> GetAvailablePins() = 0;

    virtual void SetPinMode(int pin, PinMode pinMode) = 0;
    virtual void DigitalWrite(int pin, DigitalValue value) = 0;
    virtual void AnalogWrite(int pin, int value) = 0;
    virtual void SetDelay(int delayIntMills) = 0;
    virtual void OscilloscopeOn(int pin, int resolution, int trigger) = 0;
    virtual void OscilloscopeGo(OscilloscopeRepeatMode mode) = 0;
    virtual void OscilloscopeOff() = 0;

    // These methods send request to device. Request values are recieving via signals below.
    virtual void DigitalRead(int pin) = 0;
    virtual void AnalogRead(int pin) = 0;
    virtual void TimeSinceDeviceStart() = 0;

signals:
    void ReadOscilloscopeValue(int value);
    void ReadDigitalValue(DigitalValue value);
    void ReadAnalogValue(int value);
    void ReadTimeSinceDeviceStartValue(int value);
};
//! }
Q_DECLARE_INTERFACE(IArduinoSerialDataManager, "IArduinoSerialDataManager")
#endif // IARDUINOSERIALDATAMANAGER_H

/*
    Based on arduino sketch which you can find at:
    http://www.robertovalgolio.com/sistemi-programmi/arduino-serial-protocol

    Arduino Serial Protocol 1.7
    command format: id,function[,arg1][,arg2][,arg3] (id: sender id string)
    functions are:
      pinMode,pin,mode (mode: 0 for INPUT, 2 for INPUT_PULLUP, 1 for OUTPUT)
      digitalRead,pin
      digitalWrite,pin,value (value: 0 for LOW, 1 for HIGH)
      analogRead,pin
      analogWrite,pin,dutycycle (dutycycle: between 0 always off and 255 always on)
      pulseIn,pin,mode,timeout (mode: 0 for LOW, 1 for HIGH) (timeout unit: microseconds)
      tone,pin,frequency (frequency: between 31 to 65535)
      noTone,pin
      millis
      delay,milliseconds
      myFunction
      oscilloscopeOn,pin,resolution,trigger (resolution: between 1 and 4294966)
        (resolution unit: milliseconds) (trigger:  between 0 no trigger to 1023)
      oscilloscopeGo,repeat (repeat: 0 for OFF 1 for ON
      oscilloscopeOff
      csvOn,frequency (frequency unit: seconds)
      csvOff
      function use: see http://arduino.cc/en/Reference/HomePage
*/
