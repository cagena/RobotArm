
//Copyright!!!!
// Basic demo for accelerometer readings from Adafruit MPU6050
// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/
// Motor Driver Guide: https://github.com/natnqweb/Motor_PID

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h> 
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include <Motor_PID.h>

// Defining Motor and Encoder 
#define A_ENCA 33
#define A_ENCB 32 
#define A_IN1 8
#define A_IN2 7
#define PWM_A 6

// PID Variables
long prevT;
int target = 900;

float kp = 1;
float kd = 0.1;
float ki = .02;
//int pwm_lower_limit=20;//to balance voltage if you are using too powerful power source  // limited
//int pwm_upper_limit=100;//to balance voltage if you are using too powerful power source  // limited
int pwm_lower_limit=0;//full range
int pwm_upper_limit=255;//full range
//int target = 50*sin(prevT/1e6);
motor motor1(A_ENCA, A_ENCB, A_IN2, A_IN1, PWM_A, pwm_lower_limit, pwm_upper_limit);


// Test Defines
#define SERVO_PIN 32
#define SERVO_PIN2 15

// Defining Fingers
// #define THUMB_PIN 33 
// #define POINTER_PIN 25
// #define MIDDLE_PIN 26
// #define RING_PIN 27
// #define PINKY_PIN 14

// Test Servos
Servo servoMotor;
Servo servoMotor2;

// Finger Resistor

// Hand Servos
// Servo ThumbServo;
// Servo PointerServo;
// Servo MiddleServo;
// Servo RingServo;
// Servo PinkyServo;

Adafruit_MPU6050 mpu;
int ax, ay, az ;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Test Servo Attachment 
  servoMotor.attach(SERVO_PIN);
  servoMotor2.attach(SERVO_PIN2);
  servoMotor.write(180);
  servoMotor2.write(180);
  delay(30);
  servoMotor.write(0);
  servoMotor.write(0);
  
  // Hand Servo Setup and sequence
  // ThumbServo.attach(THUMB_PIN);
  // PointerServo.attach(POINTER_PIN);
  // MiddleServo.attach(MIDDLE_PIN);
  // RingServo.attach(RING_PIN);
  // PinkyServo.attach(PINKY_PIN);

  // ThumbServo.write(180);
  // PointerServo.write(180);
  // MiddleServo.write(180);
  // RingServo.write(180);
  // PinkyServo.write(180); 
  // delay(30);
  // ThumbServo.write(0);
  // PointerServo.write(0);
  // MiddleServo.write(0);
  // RingServo.write(0);
  // PinkyServo.write(0); 

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
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

  Serial.println("");
  delay(100);

  motor1.init(kp, kd, ki);
  motor1.set_target(target);
}

void loop() {
  /* IMU servo movement */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax = map (a.acceleration.x, -10, 10, 0, 180);
  servoMotor.write(ax);
  delay(10);
  //Serial.println(ax);
  delay(10);

  //Finger Setup 

  // Thumb_R = analogRead(36);
  // Pointer_R = analogRead(39);
  // Middle_R = analogRead(34);
  // Ring_R = analogRead(35);
  // Pinky_R = analogRead(32);
 
  // Finger Test
  int Motor2value = analogRead(36);
  int value2 = map(Motor2value, 0, 4095, 0, 180);
  
  Serial.print( "Angle of Servo is:");
  Serial.println(value2);
  
  servoMotor2.write(value2);
  delay(100);

  motor1.start();

  if(motor1.get_position()==target) 
  {
  motor1.turn_off();
  }


}