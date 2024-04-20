#include "../include/Xbee.h"
#include <Arduino.h>
#include <algorithm>

Xbee::Xbee()
{
    //Serial2.begin(9600, SERIAL_8N1);
    //Serial2.addMemoryForRead(bigserialbuffer, sizeof(bigserialbuffer));
    Serial.println("Xbee Initialized");
    for(int i = 0; i<6; i++)
    {
        // buttons default to false
        for(int j = 0; j<SAVE_SIZE; j++)
        {
            buttonvalues[i][j] = false;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < SAVE_SIZE; j++)
        {
            // axis values default to 0
            axisvalues[i][j] = 0.0;

            // triggers default to -1
            axisvalues[i+2][j] = -1.0;
        }
    }
    numNoSignal = 0;
    lastSignalCount = 0;
}

void Xbee::UpdateValues()
{
    //get the values from the xbee
    if(Serial2.available() >= 3 && isDisabled == false)
    {
        firstConnected = true;
        if(Serial2.read() != START_COMMAND)
        {
            return;
        }
        numNoSignal = 0;
        //get the value of the axes
        for(int i = 0; i < 2; i++)
        {
            int input = Serial2.read();
            if(input > 200 || input < 0)
            {
                error_count++;
            }
            else
            {
                good_count++;
                float value = (input - 100.0)/100.0;
                this->axisvalues[i][currentHead] = value;
            }
            // Serial.print("axis ");
            // Serial.print(i);
            // Serial.print(": ");
            // Serial.println(value);
        }

        //get the value of the buttons
        //for (int i = 0; i < 6; i++)
        //{
            //int button = Serial2.read();
            //if(translate.find(button) != translate.end())
            //{
            //    buttonvalues[i][currentHead] = translate[button];
            //}
        //}
        currentHead++;
        if(currentHead >= SAVE_SIZE)
        {
            currentHead=0;
        }
    }
    else if(firstConnected)
    {
        numNoSignal++;
        if(numNoSignal > 100)
        {
            for(int i = 0; i<6; i++)
            {
                for(int j = 0; j<SAVE_SIZE; j++)
                {
                    buttonvalues[i][j] = false;
                }
            }
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < SAVE_SIZE; j++)
                {
                    axisvalues[i][j] = 0.0;
                    axisvalues[i+2][j] = -1.0;
                }
            }
            isDisabled = true;
        }
    
    }
}

float Xbee::getCurrentValue(CONTROLLER controller)
{
    switch (controller)
    {
    case LEFT_Y_AXIS:
        return findAxisMedian(0);
        break;
    case RIGHT_Y_AXIS:
        return findAxisMedian(1);
        break;
    case LEFT_TRIGGER:
        return findAxisMedian(2);
        break;
    case RIGHT_TRIGGER:
        return findAxisMedian(3);
        break;
    case A_BUTTON:
        return findButtonMedian(0);
        break;
    case B_BUTTON:
        return findButtonMedian(1);
        break;
    case X_BUTTON:
        return findButtonMedian(2);
        break;
    case Y_BUTTON:
        return findButtonMedian(3);
        break;
    case LB_BUTTON:
        return findButtonMedian(4);
        break;
    case RB_BUTTON:
        return findButtonMedian(5);
        break;
    default:
        return 0;
        break;
    }
    return this->axisvalues[0][0];
}

//[0,1,2,5,3,3,3]
float Xbee::findAxisMedian(int index)
{
    int num_higher = 0;
    int num_lower = 0;
    int num_same = 0;
    //Serial.println("axis median");
    for(int i = 0; i<SAVE_SIZE; i++)
    {
        // Serial.print("axis ");
        // Serial.print(index);
        // Serial.print(": ");
        // Serial.println(this->axisvalues[index][i]);
    }
    //int n = sizeof(this->axisvalues[index])/sizeof(this->axisvalues[index][0]);
    for(int i = 0; i<SAVE_SIZE; i++)
    {
        num_lower=0;
        num_higher=0;
        num_same=0;
        for(int j = 0; j<SAVE_SIZE; j++)
        {
            if(this->axisvalues[index][i] < this->axisvalues[index][j])
            {
                num_higher++;
            }
            else if(this->axisvalues[index][i] > this->axisvalues[index][j])
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
    return 0;
}

bool Xbee::findButtonMedian(int index)
{
    int num_true = 0;
    int num_false = 0;
    for(int i = 0; i<SAVE_SIZE; i++)
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
