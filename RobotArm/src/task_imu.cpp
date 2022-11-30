/** @file task_imu.cpp
 *  This file contains code to read a IMU (MPU6050).
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

Adafruit_MPU6050 mpu;
int ax, ay, az ;

Share<uint8_t> ax_pwm (0);
Share<uint8_t> ay_pwm (0);

/** @brief   Task which implements the Adafruit_MPU6050.h library.
 *  @details This task reads the IMU for acceleration in the x and y direction.
 */
void task_imu (void* p_params)
{
    while (true)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        ax = map(a.acceleration.x, -10, 10, 0, 180);
        ay = map(a.acceleration.y, -10, 10, 0, 180);
        ax_pwm.put(ax);
        ay_pwm.put(ay);
        vTaskDelay (10);
    }
    
}