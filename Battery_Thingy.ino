#include<CoDrone.h>
int Battery;
int Mode;
unsigned long StartTime;
int FLAG;

//Did you know that cashews come from a fruit?
//mhgcmjgk
void setup()
{
  CoDrone.begin(115200);
  CoDrone.AutoConnect(NearbyDrone);
  CoDrone.LowBatteryCheck(10);
  CoDrone.DroneModeChange(Flight);
  Battery = CoDrone.LowBatteryCheck(0);
}

void loop()
{
  byte bt1 = digitalRead(11);
  byte bt4 = digitalRead(14);
  byte bt8 = digitalRead(18);

  if (bt1)
  {
    CoDrone.FlightEvent(Stop);
    FLAG = 0;
  }

  /*
    for (int i = 100; i >= 0; i -= 5)
    {
      if (Battery < i && Battery > i - 10)
      {
        THROTTLE = 100 + (100 - i);
      }
    }
  */


  if (!bt1 && bt4 && !bt8)
  {
    Mode = Mode + 1;
    if (Mode > 2)
    {
      Mode = 0;
    }
    //CoDrone.Buzz(2000 + (Mode * 3000), 7);
    CoDrone.Buzz(2000, 1);
    delay(200);
  }

  if (!bt1 && bt4 && !bt8)
  {
    FLAG = 1;
    StartTime = millis();
  }

  if (!bt1 && !bt4 && bt8)
  {
    FLAG = 1;
    StartTime = millis();
  }

  if (Mode == 0)
  {
    if (PAIRING == true && FLAG == 0)
    {
      YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));
      THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
      ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
      PITCH = CoDrone.AnalogScaleChange(analogRead(A6));

      CoDrone.Control(50);
    }
  }
  else if (Mode == 1)
  {
    if (FLAG == 1)
    {
      int CurrentTime = millis() - StartTime;

      if (CurrentTime < 1000)
      {
        THROTTLE = 70;
        for (int i = 70; i >= 0; i -= 5)
        {
          if (Battery < i && Battery > i - 10)
          {
            THROTTLE = 70 + (70 - i);
          }
        }
        if(THROTTLE < 50)
        {
          THROTTLE = 50;
        }
        CoDrone.Control(50);
      }
      else if (CurrentTime < 2500)
      {
        PITCH = 50;
        for (int i = 50; i >= 0; i -= 5)
        {
          if (Battery < i && Battery > i - 10)
          {
            PITCH = 50 + (50 - i);
          }
        }
        CoDrone.Control(50);
      }
      else if (CurrentTime < 3000)
      {
        CoDrone.FlightEvent(Stop);
      }
      else
      {
        FLAG = 0;
      }
    }
  }
  else
  {
    if (FLAG == 1)
    {
      int CurrentTime = millis() - StartTime;

      if (CurrentTime < 1000)
      {
        THROTTLE = 70;
        CoDrone.Control(50);
      }
      else if (CurrentTime < 2500)
      {
        CoDrone.Control(50);
      }
      else if (CurrentTime < 3000)
      {
        CoDrone.FlightEvent(Stop);
      }
      else
      {
        FLAG = 0;
      }
    }
  }
}
