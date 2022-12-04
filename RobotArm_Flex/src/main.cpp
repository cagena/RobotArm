/** @file main.cpp
 *  This is the main file for the flex sensor portion of the RobotArm project.
 *  The program includes a task for printing to the serial monitor for
 *  trouble shooting. It also includes the arduino setup function that
 *  initializes the comunication ports and gets the tasks running.
 *  After set up, the the program also includes a loop.
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Nov-25
 */

// Include the relevant libraries.
#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include <ESP32Servo.h>
#include "task_flx.h"
#include "task_fingers.h"

/** @brief   Task which prints pwm values to troubleshoot the sensors.
 *  @details The print statements can be changed to troubleshoot other
 *           components.
 *  @param   p_params Pointer to unused parameters
 */
void task_print(void* p_params)
{
  for(;;)
  {
    Serial.print(thumb_pwm.get());
    Serial.print(',');
    Serial.print(pointer_pwm.get());
    Serial.print(',');
    Serial.print(middle_pwm.get());
    Serial.print(',');
    Serial.print(ring_pwm.get());
    Serial.print(',');
    Serial.println(pinky_pwm.get());
    vTaskDelay (1000);
  }
}

/** @brief   Arduino setup method which initializes the communication ports and
 *           gets the tasks running.
 */
void setup(void) {
  Serial.begin(115200);
  while (!Serial)             // Wait for serial port to be working
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("");
  delay(100);

  // Task that reads the flex sensors.
  xTaskCreate (task_flx, "Flex Sensor", 2048, NULL, 4, NULL);

  // Task that runs the servo motors to control the fingers.
  xTaskCreate (task_fingers, "Finger Servos", 2048, NULL, 5, NULL);

  // Task that prints pwm values for troubleshooting purposes.
  xTaskCreate (task_print, "Print PWM", 2048, NULL, 1, NULL);

}

/** @brief   Arduino loop method which runs repeatedly, doing nothing much.
 */
void loop (void)
{
  vTaskDelay (1000);
}