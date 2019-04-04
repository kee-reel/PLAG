/*
  Modbus-Arduino Example - TempSensor (Modbus Serial)
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/

#include <Modbus.h>
#include <ModbusSerial.h>

static int i;

// Coils (bool read/write)
const int COIL_COUNT = 3;
const int coilPins[COIL_COUNT] = {3, 5, 6};

// Holding Registers (int read/write)
const int HREG_COUNT = 3;
const int hregPins[HREG_COUNT] = {9, 10, 11};
const int SERVICE_HREG_BEGIN = 50;
const int SERVICE_HREG_COUNT = 1;

// Input Status (bool read)
const int ISTS_COUNT = 2;
const int istsPins[ISTS_COUNT] = {4, 7};

// Input Registers (int read)
const int IREG_COUNT = 6;
const int iregPins[IREG_COUNT] = {A0, A1, A2, A3, A4, A5};
const int SERVICE_IREG_BEGIN = 50;
const int SERVICE_IREG_COUNT = 4;

// ModbusSerial object
ModbusSerial mb;

long ts;

void setup() {
  // Config Modbus Serial (port, speed, byte format)
  mb.config(&Serial, 19200, SERIAL_8N1);
  // Set the Slave ID (1-247)
  mb.setSlaveId(1);

  // Register Coils
  for (i = 0; i < COIL_COUNT; ++i)
  {
    pinMode(coilPins[i], OUTPUT);
    mb.addCoil(i);
  }

  // Register Holding Registers
  for (i = 0; i < HREG_COUNT; ++i)
  {
    pinMode(hregPins[i], OUTPUT);
    mb.addHreg(i);
  }

  // Register Input Status
  for (i = 0; i < ISTS_COUNT; ++i)
  {
    pinMode(istsPins[i], INPUT);
    mb.addIsts(i);
  }

  // Register Input Registers
  for (i = 0; i < IREG_COUNT; ++i)
  {
    pinMode(iregPins[i], INPUT);
    mb.addIreg(i);
  }

  //==== Service Info ====
  // Delay
  mb.addHreg(SERVICE_HREG_BEGIN, 2000);
  // Sizes of registered data
  mb.addIreg(SERVICE_IREG_BEGIN + 0, ISTS_COUNT);
  mb.addIreg(SERVICE_IREG_BEGIN + 1, COIL_COUNT);
  mb.addIreg(SERVICE_IREG_BEGIN + 2, IREG_COUNT);
  mb.addIreg(SERVICE_IREG_BEGIN + 3, HREG_COUNT);
    
  ts = millis();
}

void loop() {
  //Call once inside loop() - all magic here
  mb.task();

  //Read each two seconds
  if (millis() > ts + mb.Hreg(HREG_COUNT)) {
    ts = millis();

    // Update Coils
    for (i = 0; i < COIL_COUNT; ++i)
    {
      digitalWrite(coilPins[i], mb.Coil(i));
    }

    // Update Holding Registers
    for (i = 0; i < HREG_COUNT; ++i)
    {
      analogWrite(hregPins[i], mb.Hreg(i));
    }
  
    // Update Input Status
    for (i = 0; i < ISTS_COUNT; ++i)
    {
      mb.Ists(i, digitalRead(istsPins[i]));
    }
  
    // Update Input Registers
    for (i = 0; i < IREG_COUNT; ++i)
    {
      mb.Ireg(i, analogRead(iregPins[i]));
    }
  }
}
