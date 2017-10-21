//#define DEBUG
#ifdef DEBUG
int fade;
#endif

#define PIN_IN_1 9
#define PIN_IN_2 10
#define PIN_IN_3 11
#define PIN_OUT_1 A0
#define PIN_OUT_2 A1
#define PIN_OUT_3 A2

int activeInPinId;
int activeOutPinId;
bool readMode;
int delayTime;

void setup() 
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  activeInPinId = PIN_IN_1;
  activeOutPinId = PIN_OUT_1;
  readMode = false;
  delayTime = 1000;
  Serial.begin(9600);
  Serial.flush();
#ifdef DEBUG
  Serial.print("Init");
  fade = 0;
#endif
}

void loop() 
{
//#ifdef DEBUG
//  fade = fade < 255 ? fade+1 : 0;
//  analogWrite(9, fade);
//  delay(5);
//  return;
//#endif
  
  if(readMode)
  {
      ReadPin();
  }
  
  if(!Serial.available())
    return;
#ifdef DEBUG
  Serial.print(Serial.available());
#endif
  ResolveMessage();
  return;
}

void ResolveMessage()
{
  char mode = Serial.read();
  switch(mode)
  {
    // Sets active pin.
    case 'g': GetPinsInfo(); break;
    case 'i': SetActiveInPin(); break;
    case 'o': SetActiveOutPin(); break;
    case 'd': SetDelay(); break;
    case 'w': WritePin(); break;
    case 'r': ReadPin();
    default:  return;
  }
}

void GetPinsInfo()
{
  StartSerial('i');
  PrintSerial(PIN_IN_1);
  PrintSerial(PIN_IN_2);
  PrintSerial(PIN_IN_3);
  PrintSerial('o');
  PrintSerial(PIN_OUT_1);
  PrintSerial(PIN_OUT_2);
  PrintSerial(PIN_OUT_3);
  EndSerial();
}

void SetActiveInPin()
{
  activeInPinId = Serial.parseInt();
  return;
}

void SetActiveOutPin()
{
  int newActivePin = Serial.parseInt();
  if(activeOutPinId == newActivePin) 
    readMode = !readMode;
  else 
    readMode = true;
  activeOutPinId = newActivePin;
  return;
}

void SetDelay()
{
  delayTime = Serial.parseInt();
}

void WritePin()
{
  int writeValue = Serial.parseInt();
  analogWrite(activeInPinId, writeValue);
}

void ReadPin()
{
  int readValue = analogRead(activeOutPinId);
  StartSerial('r');
  PrintSerial(readValue);
  EndSerial();
  delay(delayTime);
}

void StartSerial(char letter)
{
  Serial.print('{');
  Serial.print(letter);
}

void PrintSerial(char letter)
{
  Serial.print(',');
  Serial.print(letter);
}

void PrintSerial(int value)
{
  Serial.print(',');
  Serial.print(value);
}

void EndSerial()
{
  Serial.print('}');
  Serial.flush();
}

void ErrorSerial(char str[])
{
  Serial.print("Error-");
  Serial.print(str);
  Serial.flush();
}


