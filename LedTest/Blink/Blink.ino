//#define DEBUG
#ifdef DEBUG
int fade;
#endif

#define PIN_OUT_1 9
#define PIN_OUT_2 10
#define PIN_OUT_3 11
#define PIN_IN_1 A0
#define PIN_IN_2 A1
#define PIN_IN_3 A2

int activePinId;
bool readMode;
int delayTime;

void setup() 
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  activePinId = PIN_IN_1;
  readMode = false;
  delayTime = 1000;
  Serial.begin(9600);
  
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
  ResolveMessage();
  return;
}

void ResolveMessage()
{
  char mode = Serial.read();
  switch(mode)
  {
    // Sets active pin.
    case 'i': GetPinsInfo(); break;
    case 's': SetActivePin(); break;
    case 'd': SetDelay(); break;
    case 'w': WritePin(); break;
    case 'r': ReadPin();
    default: Serial.print("Cant resolve mode"); return;
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

void SetActivePin()
{
  activePinId = Serial.parseInt();
}

void SetDelay()
{
  delayTime = Serial.parseInt();
}

void WritePin()
{
  int writeValue = Serial.parseInt();
  
#ifdef DEBUG
  Serial.print("WritePin ");
  Serial.print(activePinId);
  Serial.print(' ');
  Serial.println(writeValue);
#endif
  analogWrite(activePinId, writeValue);
}

void ReadPin()
{
  readMode = true;
  int readValue = analogRead(A0);
#ifdef DEBUG
  Serial.print("ReadPin ");
  Serial.print(activePinId);
  Serial.print(' ');
  Serial.println(readValue);
#endif
  StartSerial('r');
  PrintSerial(readValue);
  EndSerial();
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
  delay(delayTime);
}


