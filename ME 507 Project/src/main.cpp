#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h> 
#include <ESP32Servo.h>

//Defining Fingers Resistance Measurement
#define THUMB_R 12
#define POINTER_R 14
#define MIDDLE_R 27
#define RING_R 26
#define PINKY_R 25

int thumb_flx, pointer_flx, middle_flx, ring_flx, pinky_flx ;
int thumb_pwm, pointer_pwm, middle_pwm, ring_pwm, pinky_pwm;


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

Adafruit_MPU6050 mpu;
int ax, ay, az ;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  
  // Hand Servo Setup and sequence
  ThumbServo.attach(THUMB_PIN);
  PointerServo.attach(POINTER_PIN);
  MiddleServo.attach(MIDDLE_PIN);
  RingServo.attach(RING_PIN);
  PinkyServo.attach(PINKY_PIN);

  ThumbServo.write(180);
  PointerServo.write(180);
  MiddleServo.write(180);
  RingServo.write(180);
  PinkyServo.write(180); 
  delay(30);
  ThumbServo.write(0);
  PointerServo.write(0);
  MiddleServo.write(0);
  RingServo.write(0);
  PinkyServo.write(0); 

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

  xTaskCreate (task_IMU,"IMU", 2048, NULL, 3, NULL);
  xTaskCreate (task_flx, "Flex Sensor", 2048, NULL, 4, NULL);
  xTaskCreate (task_fingers, "Finger Servos", 2048, NULL, 4, NULL);

}

// Flick of the Wrist
void task_IMU (void* p_params)
{
    while (true)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        ax = map (a.acceleration.x, -10, 10, 0, 180);
        ay = map (a.acceleration.y, -10, 10, 0, 180);
        vTaskDelay (10);
    }
    
}

void task_wrist (void* p_params)
{
    
}
// Fingers!!
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


void loop (void) {}