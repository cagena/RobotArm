/** @file task_fingers.cpp
 *  This file contains code to run the servo motors.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */

#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Servo.h>
#include "task_flx.h"
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include "task_fingers.h"

//Defining Finger Servos 
#define THUMB_PIN 16 
#define POINTER_PIN 17
#define MIDDLE_PIN 5
#define RING_PIN 18
#define PINKY_PIN 19

// Hand Servos
Servo ThumbServo;
Servo PointerServo;
Servo MiddleServo;
Servo RingServo;
Servo PinkyServo;

/** @brief   Task which implements the servo motors.
 *  @details This task sets the servo motors to the pwm recieved from the flex
 *           sensor task.
 */
void task_fingers (void* p_params)
{
    // Hand Servo Setup and sequence
    ThumbServo.attach(THUMB_PIN);
    PointerServo.attach(POINTER_PIN);
    MiddleServo.attach(MIDDLE_PIN);
    RingServo.attach(RING_PIN);
    PinkyServo.attach(PINKY_PIN);

    while (true)
    {
        if (thumb_pwm.get() >= 50)
        {  
            ThumbServo.write(180);
        }
        else
        {
            ThumbServo.write(0);
        }

        if (pointer_pwm.get() >= 50)
        {  
            PointerServo.write(180);
        }
        else
        {
            PointerServo.write(0);
        }

        if (middle_pwm.get() >= 50)
        {  
            MiddleServo.write(180);
        }
        else
        {
            MiddleServo.write(0);
        }

        if (ring_pwm.get() >= 50)
        {  
            RingServo.write(180);
        }
        else
        {
            RingServo.write(0);
        }

        if (pinky_pwm.get() >= 50)
        {  
            PinkyServo.write(180);
        }
        else
        {
            PinkyServo.write(0);
        }
        vTaskDelay(10);            
    } 
}