/** @file task_fingers.cpp
 *  This file contains code to run the servo motors.
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Nov-25
 */

// Include the relevant libraries.
#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Servo.h>
#include "task_flx.h"
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include "task_fingers.h"

// Define the pins used to run the finger servo motors. 
#define THUMB_PIN 16 
#define POINTER_PIN 17
#define MIDDLE_PIN 5
#define RING_PIN 18
#define PINKY_PIN 19

// Define Servo objects for each finger on the hand.
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
    // Hand Servo setup, attach the servo objects to its corresponding pin.
    ThumbServo.attach(THUMB_PIN);
    PointerServo.attach(POINTER_PIN);
    MiddleServo.attach(MIDDLE_PIN);
    RingServo.attach(RING_PIN);
    PinkyServo.attach(PINKY_PIN);

    // A on and off state were created for each finger.
    while (true)
    {
        if (thumb_pwm.get() >= 50)
        {  
            ThumbServo.write(0);
        }
        else
        {
            ThumbServo.write(180);
        }

        if (pointer_pwm.get() >= 50)
        {  
            PointerServo.write(0);
        }
        else
        {
            PointerServo.write(180);
        }

        if (middle_pwm.get() >= 50)
        {  
            MiddleServo.write(0);
        }
        else
        {
            MiddleServo.write(180);
        }

        if (ring_pwm.get() >= 50)
        {  
            RingServo.write(0);
        }
        else
        {
            RingServo.write(180);
        }

        if (pinky_pwm.get() >= 50)
        {  
            PinkyServo.write(0);
        }
        else
        {
            PinkyServo.write(180);
        }
        vTaskDelay(10);            
    } 
}