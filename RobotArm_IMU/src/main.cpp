#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"

#include <Adafruit_MPU6050.h>
#include "task_imu.h"


void task_print(void* p_params)
{
  for(;;)
  {
    Serial.print(ax_pwm.get());
    Serial.print(',');
    Serial.println(ay_pwm.get());
    vTaskDelay (1000);
  }
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  Serial.println("");
  delay(100);

  xTaskCreate (task_imu, "IMU", 2048, NULL, 4, NULL);
// xTaskCreate (task_wrist, "Wrist", 2048, NULL, 5, NULL);
  xTaskCreate (task_print, "Print PWM", 2048, NULL, 1, NULL);
}

void loop (void) {}