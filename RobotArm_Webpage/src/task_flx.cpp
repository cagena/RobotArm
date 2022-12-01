/** @file task_flx.cpp
 *  This file contains code to read the flex sensors.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */

#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include "task_flx.h"

//Defining Fingers Resistance Measurement
#define THUMB_R 12
#define POINTER_R 14
#define MIDDLE_R 27
#define RING_R 26
#define PINKY_R 25

int thumb_flx, pointer_flx, middle_flx, ring_flx, pinky_flx ;

// Shares which hold the pwm values for the servo motor.
Share<uint8_t> thumb_pwm (0);
Share<uint8_t> pointer_pwm (0);
Share<uint8_t> middle_pwm (0);
Share<uint8_t> ring_pwm (0);
Share<uint8_t> pinky_pwm (0);

/** @brief   Task which implements the flex sensors.
 *  @details This task reads the voltage from the flex sensors and writes a
 *           pwm value to the respective variable for the corresponding finger.
 */
void task_flx (void* p_params)
{
    while (true)
    {
        thumb_flx = analogRead(THUMB_R);
        thumb_pwm.put(map(thumb_flx, 0, 4095, 180, 0));

        pointer_flx = analogRead(POINTER_R);
        pointer_pwm.put(map(pointer_flx, 0, 4095, 180, 0));

        middle_flx = analogRead(MIDDLE_R);
        middle_pwm.put(map(middle_flx, 0, 4095, 180, 0));

        ring_flx = analogRead(RING_R);
        ring_pwm.put(map(ring_flx, 0, 4095, 180, 0));

        //Comment this section out if using pinky control through webpage
        // pinky_flx = analogRead(RING_R);
        // pinky_pwm.put(map(pinky_flx, 0, 4095, 180, 0));

        vTaskDelay(10);
    } 
}