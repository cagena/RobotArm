/** @file task_flx.cpp
 *  This file contains code to read the flex sensors.
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Nov-25
 */

// Include the relevent libraries.
#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include "task_flx.h"

// Defining pins for the flex sensor.
#define THUMB_R 12
#define POINTER_R 14
#define MIDDLE_R 27
#define RING_R 26
#define PINKY_R 25

// Define integer variables for the flex sensor analog values.
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
        // Read the thumb sensor and map it to a pwm value.
        thumb_flx = analogRead(THUMB_R);
        thumb_pwm.put(map(thumb_flx, 0, 4095, 180, 0));

        // Read the pointer finger sensor and map it to a pwm value.
        pointer_flx = analogRead(POINTER_R);
        pointer_pwm.put(map(pointer_flx, 0, 4095, 180, 0));

        // Read the middle finger sensor and map it to a pwm value.
        middle_flx = analogRead(MIDDLE_R);
        middle_pwm.put(map(middle_flx, 0, 4095, 180, 0));

        // Read the ring finger sensor and map it to a pwm value.
        ring_flx = analogRead(RING_R);
        ring_pwm.put(map(ring_flx, 0, 4095, 180, 0));

        // Read the pinky finger sensor and map it to a pwm value.
        pinky_flx = analogRead(RING_R);
        pinky_pwm.put(map(pinky_flx, 0, 4095, 180, 0));
        vTaskDelay(10);
    } 
}