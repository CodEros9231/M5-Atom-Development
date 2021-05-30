


#include "M5Atom.h"

extern const unsigned char image_num1W[77];
extern const unsigned char image_num2W[77];
extern const unsigned char image_num3W[77];
extern const unsigned char image_num4W[77];
extern const unsigned char image_num5W[77];
//Links all LED data for each number and symbol
extern const unsigned char image_num0B[122];
extern const unsigned char image_num1B[122];
extern const unsigned char image_num2B[122];
extern const unsigned char image_num3B[122];
extern const unsigned char image_num4B[122];
extern const unsigned char image_num5B[122];
extern const unsigned char image_num6B[122];
extern const unsigned char image_num7B[122];
extern const unsigned char image_num8B[122];
extern const unsigned char image_num9B[122];
extern const unsigned char image_degree[152];
extern const unsigned char image_negative[122];

bool IMU6886Flag = false;
bool atomState = false;
bool modeState = false;

int optionsCTR = 0;

double start, finished, elapsed;
double pitch, roll;

//sets value of temperature, to be changed once temperature is actually read
float temp = 0;
int Temp = 0;
int TempArray[8640];
int SumofTemp=0;

int ctr = 0;
int tempCounts=0;

//declare values for units in tens and ones place
int TempTens = 0;
int TempOnes = 0;

//double currentTime, lastUpdateTime, elapsed;
unsigned long currentTime=0;

void delayInterval(int num)
{ currentTime=millis();
 while (millis()<(currentTime+num))
 {
    //do nothing
 }
}

//reads the temperature at a given interval
float readTemp()
{
    M5.IMU.getTempData(&temp);
    Serial.print("The temperature is ");
    Serial.println(temp);    // print the temperature value
    return temp;
}

//records temperature at given interval
void recTemp()
{
  int Temp = readTemp();
  TempArray[tempCounts]=Temp;
  SumofTemp+=Temp;
  if (tempCounts>=8640)
  {
      SumofTemp=SumofTemp-TempArray[0];
      tempCounts=0;
  }
}

//check if temperature value is negative
void checkNegative(int tempValue)
{
    //check if number is negative
    if(tempValue < 0)
    {
    //display negative sign before value
    M5.dis.animation((uint8_t *)image_negative, 150, LED_DisPlay::kMoveLeft, 20);
    delayInterval(750);
    M5.update();
    }
}
//displays the unit in the tens place
void displayTens(int &TempTens, int Temp)
{
          //determine number in the tens place
            TempTens = (Temp / 10) % 10;

            //display number in the tens place
            switch(TempTens)
            {
              case 0:
              {
                  //if less than 10, display nothing
                  break;
              }

              case 1: //display 1
              {
                  M5.dis.animation((uint8_t *)image_num1B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 2: //display 2
              {
                  M5.dis.animation((uint8_t *)image_num2B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 3: //display 3
              {
                  M5.dis.animation((uint8_t *)image_num3B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 4: //display 4
              {
                  M5.dis.animation((uint8_t *)image_num4B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 5: //display 5
              {
                  M5.dis.animation((uint8_t *)image_num5B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 6: //display 6
              {
                  M5.dis.animation((uint8_t *)image_num6B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 7: //display 7
              {
                  M5.dis.animation((uint8_t *)image_num7B, 150, LED_DisPlay::kMoveLeft, 20);
                
                  break;
              }
              case 8: //display 8
              {
                  M5.dis.animation((uint8_t *)image_num8B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 9: //display 9
              {
                  M5.dis.animation((uint8_t *)image_num9B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
            }
            delayInterval(750);
            M5.update();
}

//displays the unit in the ones place
void displayOnes(int TempTens, int Temp, int &TempOnes)
{
  TempOnes = Temp - (TempTens * 10);
      
            //display number in the ones place
            switch(TempOnes)
            {
              case 0: //display 0
              {
                  M5.dis.animation((uint8_t *)image_num0B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
      
              case 1: //display 1
              {
                  M5.dis.animation((uint8_t *)image_num1B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 2: //display 2
              {
                  M5.dis.animation((uint8_t *)image_num2B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 3: //display 3
              {
                  M5.dis.animation((uint8_t *)image_num3B, 150, LED_DisPlay::kMoveLeft, 20);
               
                  break;
              }
              case 4: //display 4
              {
                  M5.dis.animation((uint8_t *)image_num4B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 5: //display 5
              {
                  M5.dis.animation((uint8_t *)image_num5B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 6: //display 6
              {
                  M5.dis.animation((uint8_t *)image_num6B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 7: //display 7
              {
                  M5.dis.animation((uint8_t *)image_num7B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 8: //display 8
              {
                  M5.dis.animation((uint8_t *)image_num8B, 150, LED_DisPlay::kMoveLeft, 20);
                
                  break;
              }
              case 9: //display 9
              {
                  M5.dis.animation((uint8_t *)image_num9B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
            }
            delayInterval(850);
            M5.update();
}


void setup() {
  // put your setup code here, to run once:
    M5.begin(true, true, true);
    M5.IMU.Init();
}

void loop() 
{
  //put temperature function here
  recTemp();
  //delayInterval(7000);// for 10 seconds use 7000
  
  //get current pitch and roll
  M5.IMU.getAttitude(&pitch, &roll);

  if(roll > -10 && roll < 0 && pitch > roll && pitch < 0) //face up
  {
    atomState = true;
  }

  if(M5.Btn.wasPressed()) //face up
  {
    atomState = true;
  }

  //print states of functions
  Serial.printf("%d,%i,%d\n", atomState, optionsCTR, modeState);
  delayInterval(500);

  while(atomState == true)
  {
//      recTemp();
      Serial.printf("%d,%i,%d,%.2f,%.2f\n", atomState, optionsCTR, modeState, pitch, roll);
      delayInterval(200);
      
      //get current pitch and roll
      M5.IMU.getAttitude(&pitch, &roll);

      if(modeState == false)
      {
          if(pitch < -10)
          {
            optionsCTR++;
            if (optionsCTR >= 5) //if counter exceeds number of states
            {
               optionsCTR = 0; //reset counter
            }
            delayInterval(500); //so that no other values are read
          }
        
          else if(pitch > 10)
          {
            optionsCTR--;
            if (optionsCTR <= -1) //if counter exceeds number of states
            {
               optionsCTR = 4; //reset counter
            }
            delayInterval(500); //so that no other values are read
          }
      }
     
      switch(optionsCTR)
      {
        case 0: //Show Active Temperature + Units
        {
          if(modeState == false)
          {
            M5.dis.displaybuff((uint8_t *)image_num1W, 0, 0);
            M5.update();
  
            if(M5.Btn.wasPressed())
            {
              modeState = true;
            } 
          }

          else if(modeState == true)
          {
            Temp = readTemp();
            //check if number is negative
            checkNegative(Temp);
            Temp=abs(Temp);

            //display the number in the tens place
            displayTens(TempTens, Temp);

            //display number in the ones place
            displayOnes(TempTens, Temp, TempOnes);
      
            //display the unit (celsius)
            M5.dis.animation((uint8_t *)image_degree, 150, LED_DisPlay::kMoveLeft, 20);
            delayInterval(1000);
            M5.update();
          }

          break;
          
        }
    
        case 1: //Show average of last 24 hours of temperature + Units
        {
          M5.dis.displaybuff((uint8_t *)image_num2W, 0, 0);
          M5.update();

          if(M5.Btn.wasPressed())
          {
            modeState = true;
          }

          if(modeState == true)
          {
            M5.dis.fillpix(0x0000FF);
            M5.update();
            delayInterval(500);

            M5.dis.clear();
            M5.update();
            delayInterval(500);
          }

          break;
           
        }

        case 2: //Show color scale of temperature range + current temperature as color
        {
          M5.dis.displaybuff((uint8_t *)image_num3W, 0, 0);
          M5.update();

          if(M5.Btn.wasPressed())
          {
            modeState = true;
          }

          if(modeState == true)
          {
            M5.dis.fillpix(0x008000);
            M5.update();
            delayInterval(500);

            M5.dis.clear();
            M5.update();
            delayInterval(500);
          }

          break;
           
        }

        case 3: //Show graph of temperature across a predefined range.
        {
          M5.dis.displaybuff((uint8_t *)image_num4W, 0, 0);
          M5.update();

          if(M5.Btn.wasPressed())
          {
            modeState = true;
          }

          if(modeState == true)
          {
            M5.dis.fillpix(0x008000);
            M5.update();
            delayInterval(500);

            M5.dis.clear();
            M5.update();
            delayInterval(500);
          }

          break;
           
        }

        case 4: //Change units
        {
          M5.dis.displaybuff((uint8_t *)image_num5W, 0, 0);
          M5.update();

          if(M5.Btn.wasPressed())
          {
            modeState = true;
          }

          if(modeState == true)
          {
            M5.dis.fillpix(0x008000);
            M5.update();
            delayInterval(500);

            M5.dis.clear();
            M5.update();
            delayInterval(500);
          }

          break;
           
        }
        
      }

    if(roll > 10 && roll > pitch) //face down
    {
      modeState = false;
      atomState = false;
    }
  }


    M5.dis.clear();
    M5.update();
    delayInterval(3300);
  

}