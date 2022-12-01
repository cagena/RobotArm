#include <Arduino.h>
#include <ESP32Encoder.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include "task_imu.h"
#include "cmath"
// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>


// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 0
#define AIN2 2
#define PWMA 15
#define STBY 4

#define CLK 33
#define DT 32

//Linear Actuator Motor 
#define BIN1 16
#define BIN2 17
#define PWMB 5

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

//Linear Actuator
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

ESP32Encoder encoder;




void task_wrist (void* p_params)
{
  encoder.attachHalfQuad(CLK, DT);
  //encoder.setCount(0);
  //int target= ax_pwm.get();
  while(true)
  {
    float imu_current = -ax_pwm.get() +90;
    float encoder_current = encoder.getCount();
    float encoder_max = 450;
    float imu_max = 90;
    float gain_max = 255;
    float gain_motor = gain_max*((imu_current/imu_max)-(encoder_current/encoder_max));
    //Serial.println(gain_motor);
    motor1.drive(-1*gain_motor);



    Serial.println(ay_pwm.get());
    if(ay_pwm.get()<= 90)
    {
      motor2.drive(-155);
    }
    else if(ay_pwm.get()>= 145)
    {
      motor2.drive(155);
    }
 
    vTaskDelay(10);
    //long newPosition = encoder.getCount()/2;
    //Serial.println(newPosition);
    //if(newPosition < target)
    //{
    //motor1.drive(-255);
    //}
    //else if (newPosition > target)
    //{
    //  motor1.drive(255);
    //}
    //else motor1.brake();
    //vTaskDelay(10);
  }

}

