//The dial operation idea is from here https://www.instructables.com/id/Interface-a-rotary-phone-dial-to-an-Arduino/ 

#include <SimpleSDAudio.h>

//track1 pcen
//track2 pcgr
//track3 rec
//track4 recen
//track5 recgr
//track6 safe

int needToPrint = 0;
int count;
int in = 2;
int lastState = LOW;
int trueState = LOW;
long lastStateChangeTime = 0;
int cleared = 0;

// constants

const int dialHasFinishedRotatingAfterMs = 100;
const int debounceDelay = 10;

const String safe = "6971";
const String safen = "6970";
const String pcen = "1945";
const String pcgr = "1944";
const String rec = "1900";
const String recen = "1941";
const String recgr = "1940";

bool flagArray[4];
String tel = "";
int j = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(in, INPUT);
  SdPlay.setSDCSPin(10);


  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER))
  {
    while(1);
  }
  if(!SdPlay.setFile("safe.wav"))
  {
    Serial.println("File not found");
     while(1);
  }


  for(int i = 0; i<4; i++)
  {
    flagArray[i] = false;
//    Serial.print(flagArray[i]);
  }
  Serial.println("COMMENCING");
}

void resetDial()
{
  j = 0;
  for(int i = 0; i<4; i++)
  {
    flagArray[i] = false;
  }
  tel = "";
  Serial.println("==================");
}

void loop()
{
  int reading = digitalRead(in);

  if(flagArray[3] == true)
  {
    if(tel == safe)
    {
        Serial.println("Calling");
        SdPlay.setFile("safe.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else if(tel == safen)
    {
      Serial.println("Calling");
        SdPlay.setFile("safen.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else if(tel == pcen)
    {
      Serial.println("Calling");
        SdPlay.setFile("pcen.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else if(tel == pcgr)
    {
      Serial.println("Calling");
        SdPlay.setFile("pcgr.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else if(tel == rec)
    {
      Serial.println("Calling");
        SdPlay.setFile("rec.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else if(tel == recen)
    {
      Serial.println("Calling");
        SdPlay.setFile("recen.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else if(tel == recgr)
    {
      Serial.println("Calling");
        SdPlay.setFile("recgr.wav");
        SdPlay.play();
        while(!SdPlay.isStopped()) {
          ;
        }
        SdPlay.stop();
        resetDial();
    }
    else resetDial();

  }
  else
  {
        if ((millis() - lastStateChangeTime) > dialHasFinishedRotatingAfterMs) {
          // the dial isn't being dialed, or has just finished being dialed.
          if (needToPrint) {
            // if it's only just finished being dialed, we need to send the number down the serial
            // line and reset the count. We mod the count by 10 because '0' will send 10 pulses.

//            Serial.println(count % 10, DEC);
            flagArray[j] = true;
            tel = tel + count % 10;
            Serial.print(count % 10);
            j++;
            if(count % 10 == 8){
              resetDial();
            }
            needToPrint = 0;
            count = 0;
            cleared = 0;
          }
        }

        if (reading != lastState) {
          lastStateChangeTime = millis();
        }
       if ((millis() - lastStateChangeTime) > debounceDelay) {
          // debounce - this happens once it's stablized
          if (reading != trueState) {
            // this means that the switch has either just gone from closed->open or vice versa.
            trueState = reading;
            if (trueState == HIGH) {
              // increment the count of pulses if it's gone high.
              count++;
              needToPrint = 1; // we'll need to print this number (once the dial has finished rotating)
            }
          }
       }
        lastState = reading;
  }//else
}
