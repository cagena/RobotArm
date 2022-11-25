/** @file task_flx.cpp
 *  This file contains code to read the flex sensors.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */

#include <Arduino.h>

//Defining Fingers Resistance Measurement
#define THUMB_R 12
#define POINTER_R 14
#define MIDDLE_R 27
#define RING_R 26
#define PINKY_R 25

int thumb_flx, pointer_flx, middle_flx, ring_flx, pinky_flx ;
int thumb_pwm, pointer_pwm, middle_pwm, ring_pwm, pinky_pwm;

/** @brief   Task which implements the flex sensors.
 *  @details This task reads the voltage from the flex sensors and writes a
 *           pwm value to the respective variable for the corresponding finger.
 */
void task_flx (void* p_params)
{
    while (true)
    {
        thumb_flx = analogRead(THUMB_R);
        thumb_pwm = map(thumb_flx, 0, 4095, 0, 180);

        pointer_flx = analogRead(POINTER_R);
        pointer_pwm = map(pointer_flx, 0, 4095, 0, 180);

        middle_flx = analogRead(MIDDLE_R);
        middle_pwm = map(middle_flx, 0, 4095, 0, 180);

        ring_flx = analogRead(RING_R);
        ring_pwm = map(ring_flx, 0, 4095, 0, 180);

        pinky_flx = analogRead(RING_R);
        pinky_pwm = map(pinky_flx, 0, 4095, 0, 180);
        vTaskDelay(10);
    } 
}