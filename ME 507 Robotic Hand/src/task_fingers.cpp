/** @file task_fingers.cpp
 *  This file contains code to run the servo motors.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */

#include <Arduino.h>
#include <ESP32Servo.h>
#include "task_flx.h"

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

// Hand Servo Setup and sequence
ThumbServo.attach(THUMB_PIN);
PointerServo.attach(POINTER_PIN);
MiddleServo.attach(MIDDLE_PIN);
RingServo.attach(RING_PIN);
PinkyServo.attach(PINKY_PIN);

/** @brief   Task which implements the servo motors.
 *  @details This task sets the servo motors to the pwm recieved from the flex
 *           sensor task.
 */
void task_fingers (void* p_params)
{
    while (true)
    {
        ThumbServo.write(thumb_pwm);
        PointerServo.write(pointer_pwm);
        MiddleServo.write(middle_pwm);
        RingServo.write(ring_pwm);
        PinkyServo.write(pinky_pwm);
        vTaskDelay(50);            
    } 
}