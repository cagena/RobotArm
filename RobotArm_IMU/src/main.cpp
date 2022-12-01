#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "task_wrist.h"
//#include "task_imu.h"

Adafruit_MPU6050 mpu;
int ax, ay;

Share<uint8_t> ax_pwm (0);
Share<uint8_t> ay_pwm (0);


// void task_print(void* p_params)
// {
//   for(;;)
//   {
//     Serial.print(ax_pwm.get());
//     Serial.print(',');
//     Serial.println(ay_pwm.get());
//     vTaskDelay (1000);
//   }
// }

/** @brief   Task which implements the Adafruit_MPU6050.h library.
 *  @details This task reads the IMU for acceleration in the x and y direction.
 */
void task_imu (void* p_params)
{  
    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
        Serial.println("+-2G");
        break;
    case MPU6050_RANGE_4_G:
        Serial.println("+-4G");
        break;
    case MPU6050_RANGE_8_G:
        Serial.println("+-8G");
        break;
    case MPU6050_RANGE_16_G:
        Serial.println("+-16G");
        break;
    }
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
        Serial.println("+- 250 deg/s");
        break;
    case MPU6050_RANGE_500_DEG:
        Serial.println("+- 500 deg/s");
        break;
    case MPU6050_RANGE_1000_DEG:
        Serial.println("+- 1000 deg/s");
        break;
    case MPU6050_RANGE_2000_DEG:
        Serial.println("+- 2000 deg/s");
        break;
    }
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        break;
    case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        break;
    case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        break;
    case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        break;
    case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        break;
    case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        break;
    case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        break;
    }
    sensors_event_t a, g, temp;
    while (true)
    {
        mpu.getEvent(&a, &g, &temp);
        ax = map(a.acceleration.x, -10, 10, 0, 180);
        ay = map(a.acceleration.y, -10, 10, 0, 180);
        ax_pwm.put(ax);
        ay_pwm.put(ay);
        vTaskDelay (10);
    }
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

    mpu.begin(104);
   
    // Serial.println("MPU6050 Found!");

    // mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    // Serial.print("Accelerometer range set to: ");
    // switch (mpu.getAccelerometerRange()) {
    // case MPU6050_RANGE_2_G:
    //     Serial.println("+-2G");
    //     break;
    // case MPU6050_RANGE_4_G:
    //     Serial.println("+-4G");
    //     break;
    // case MPU6050_RANGE_8_G:
    //     Serial.println("+-8G");
    //     break;
    // case MPU6050_RANGE_16_G:
    //     Serial.println("+-16G");
    //     break;
    // }
    // mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    // Serial.print("Gyro range set to: ");
    // switch (mpu.getGyroRange()) {
    // case MPU6050_RANGE_250_DEG:
    //     Serial.println("+- 250 deg/s");
    //     break;
    // case MPU6050_RANGE_500_DEG:
    //     Serial.println("+- 500 deg/s");
    //     break;
    // case MPU6050_RANGE_1000_DEG:
    //     Serial.println("+- 1000 deg/s");
    //     break;
    // case MPU6050_RANGE_2000_DEG:
    //     Serial.println("+- 2000 deg/s");
    //     break;
    // }
    // mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    // Serial.print("Filter bandwidth set to: ");
    // switch (mpu.getFilterBandwidth()) {
    // case MPU6050_BAND_260_HZ:
    //     Serial.println("260 Hz");
    //     break;
    // case MPU6050_BAND_184_HZ:
    //     Serial.println("184 Hz");
    //     break;
    // case MPU6050_BAND_94_HZ:
    //     Serial.println("94 Hz");
    //     break;
    // case MPU6050_BAND_44_HZ:
    //     Serial.println("44 Hz");
    //     break;
    // case MPU6050_BAND_21_HZ:
    //     Serial.println("21 Hz");
    //     break;
    // case MPU6050_BAND_10_HZ:
    //     Serial.println("10 Hz");
    //     break;
    // case MPU6050_BAND_5_HZ:
    //     Serial.println("5 Hz");
    //     break;
    // }
  delay(100);

  xTaskCreate (task_imu, "IMU", 4000, NULL, 4, NULL);
  xTaskCreate (task_wrist, "Wrist", 2048, NULL, 5, NULL);
  ///xTaskCreate (task_print, "Print PWM", 2048, NULL, 1, NULL);
}



void loop (void) {}
