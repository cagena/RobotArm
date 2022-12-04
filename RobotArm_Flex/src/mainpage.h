/** @file mainpage.py
 *  File that holds the main page for the flex sensor portion of the RobotArm
 *  project.
 *  @mainpage
 *  @section intro Introduction
 *  The term project is to design a robot arm that can move at an elbow joint,
 *  wrist, and fingers. The arm will be operated by wearing a glove and moving
 *  it to desired positions.
 * 
 *  @section software Software Design
 *  Software is development in two parts one that interfaces with flex sensors
 *  and one that interfaces with an IMU. The code is distinctly split and ran
 *  with two different ESP32 microcontrollers. The code corresponding to the flex
 *  sensors control 5 finger servos. The code corresponding to the IMU control
 *  the wrist and arm motion, with a DC motor and linear actuator respectively.
 * 
 *  @subsection flex Flex Sensor Portion
 *  The flex sensor portion included 3 .cpp files and 3 .h files. The 
 *  RobotArm_Flex/src/main.cpp file initializes the communication ports and
 *  starts the task manager. The task_flx.cpp file reads the flex sensors and
 *  updates shared variables for the pwm. The task_fingers.cpp file uses the
 *  shared variables and runs the servo motors for each finger at the pwm
 *  determined from the flex sensors. The shares.h file includes declarations
 *  of shares used throughout the flex sensor portion. The task_fingers.h and
 *  task_flx.h are header files for their respective tasks.
 * 
 *  @subsection imu IMU Portion
 *  The flex sensor portion included 2 .cpp files and 2 .h files. The 
 *  RobotArm_IMU/src/main.cpp file initializes the communication ports and
 *  starts the task manager. The main file also includes the task_webpage and
 *  task_IMU. The webpage task creates a webpage that prints pwm values
 *  generated from the IMU readings and provided to the motors. The IMU task
 *  reads the IMU and updates shared variables for the pwm. The 
 *  The task_wrist_arm.cpp file uses the shared variables and runs the DC motor
 *  for the wrist and the linear actuator for the arm at the pwm values
 *  determined from the IMU. The shares.h file includes declarations
 *  of shares used throughout the flex sensor portion. The task_wrist_arm.h
 *  is a header file for its tasks 
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Dec-03
 */