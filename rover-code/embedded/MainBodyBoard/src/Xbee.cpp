#include "../include/Xbee.h"
#include <Arduino.h>
#include <algorithm>

Xbee::Xbee()
{   
    //Serial2.begin(9600, SERIAL_8N1);  
    //Serial.println("Xbee Initialized");
    for(int i = 0; i<6; i++)
    {
        // buttons default to false
        for(int j = 0; j<5; j++)
        {
            buttonvalues[i][j] = false;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        // axis values default to 0
        for (int j = 0; j < 5; j++)
        {
            axisvalues[i][j] = 0.0;
        }
        // triggers default to -1
        //for (int j = 0; i < 5; j++)
        //{
        //    axisvalues[i+2][j] = -1.0;
        //}
        
    }
    
}

void Xbee::UpdateValues()
{    
    //get the values from the xbee
    while(Serial2.available() >= 10)
    {        
        //get the value of the axes
        for(int i = 0; i < 4; i++)
        {
            float value = ((float)Serial2.read() - 100.0)/100.0;
            Serial.println(value);
            axisvalues[i][currentHead] = value;
        }

        //get the value of the buttons
        for (int i = 0; i < 6; i++)
        {
            int button = Serial2.read();
            //if(translate.find(button) != translate.end())
            //{
            //    buttonvalues[i][currentHead] = translate[button];
            //}
        }
        
    }
}

float Xbee::getCurrentValue(CONTROLLER controller)
{
    //switch (controller)
    //{
    //case LEFT_Y_AXIS:
    //    return findAxisMedian(axisvalues[0]);
    //    break;
    //case RIGHT_Y_AXIS:
    //    return findAxisMedian(axisvalues[1]);
    //    break;
    //case LEFT_TRIGGER:
    //    return findAxisMedian(axisvalues[2]);
    //    break;
    //case RIGHT_TRIGGER:
    //    return findAxisMedian(axisvalues[3]);
    //    break;
    //case A_BUTTON:
    //    return findButtonMedian(buttonvalues[0]);
    //    break;
    //case B_BUTTON:
    //    return findButtonMedian(buttonvalues[1]);
    //    break;
    //case X_BUTTON:
    //    return findButtonMedian(buttonvalues[2]);
    //    break;
    //case Y_BUTTON:
    //    return findButtonMedian(buttonvalues[3]);
    //    break;
    //case LB_BUTTON:
    //    return findButtonMedian(buttonvalues[4]);
    //    break;
    //case RB_BUTTON:
    //    return findButtonMedian(buttonvalues[5]);
    //    break;
    //default:
    //    return 0;
    //    break;
    //}
    for(int i = 0; i < 5; i++)
    {
        Serial.println(findAxisMedian(0));
        Serial.println(axisvalues[0][i]);
    }
    return this->axisvalues[0][0];
}

//[0,1,2,5,3,3,3]
float Xbee::findAxisMedian(int index)
{
    int num_higher = 0;
    int num_lower = 0;
    int num_same = 0;
    int n = sizeof(this->axisvalues[index])/sizeof(this->axisvalues[index][0]);
    for(int i = 0; i<n; i++)
    {
        num_lower=0;
        num_higher=0;
        num_same=0;
        for(int j = 0; j<n; j++)
        {
            if(this->axisvalues[index][i] < this->axisvalues[index][j])
            {
                num_higher++;
            }
            else if(this->axisvalues[index][i] < this->axisvalues[index][j])
            {
                num_lower++;
            }
            else
            {
                num_same++;
            }
        }
        if(abs(num_higher-num_lower) < num_same)
        {
            return this->axisvalues[index][i];
        }
    }
}

bool Xbee::findButtonMedian(int index)
{   
    int num_true = 0;
    int num_false = 0;
    for(int i = 0; i<sizeof(this->buttonvalues[index])/sizeof(this->buttonvalues[index][0]); i++)
    {
        if(this->buttonvalues[index][i])
        {
            num_true++;
        }
        else
        {
            num_false++;
        }
    }
    return num_true>num_false;
}