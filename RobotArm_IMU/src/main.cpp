/** @file main.cpp
 *  This is the main file for the IMU portion of the RobotArm project.
 *  The program includes code to run a webpage and code to set up the
 *  MPU5060 chip. It also includes the arduino setup function that
 *  initializes the comunication ports and gets the tasks running.
 *  After set up, the the program also includes a loop.
 * 
 *  Webserver portion based on an example by A. Sinha at 
 *  @c https://github.com/hippyaki/WebServers-on-ESP32-Codes
 * 
 *  MPU6050 portion based on an example by B. Siepert at
 *  @c https://github.com/adafruit/Adafruit_MPU6050.git
 * 
 *  @author A. Sinha
 *  @author JR Ridgely
 *  @author B. Siepert
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Mar-28 Webpage portion by Sinha
 *  @date   2022-Nov-04 Webpage portion modified for ME507 use by Ridgely
 *  @date   2019 MPU6050 portion by Bryan Siepert for Adafruit Industries
 *  @date   2022-Nov-25 Edited for the Robot Arm Project by Agena, Ceja, and
 *          Tenney
 *  @copyright 2022 by the authors, released under the MIT License.
 */

// Include the relevant libraries.
#include <Arduino.h>
#include <PrintStream.h>
#include "taskshare.h"
#include "taskqueue.h"
#include "shares.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "task_wrist_arm.h"
#include <WiFi.h>
#include <WebServer.h>

// Create a Adafruit_MPU6050 object.
Adafruit_MPU6050 mpu;

// Create integer variable for acceleration in the x and y directions.
int ax, ay;

// Create share variables for the pwm values for the x and y motors.
Share<uint8_t> ax_pwm (0);
Share<uint8_t> ay_pwm (0);

// #define USE_LAN to have the ESP32 join an existing Local Area Network or 
// #undef USE_LAN to have the ESP32 act as an access point, forming its own LAN
#undef USE_LAN

// If joining an existing LAN, get certifications from a header file which you
// should NOT push to a public repository of any kind
#ifdef USE_LAN
#include "mycerts.h"       // For access to your WiFi network; see setup_wifi()

// If the ESP32 creates its own access point, put the credentials and network
// parameters here; do not use any personally identifying or sensitive data
#else
const char* ssid = "robot_arm";   // SSID, network name seen on LAN lists
const char* password = "password";   // ESP32 WiFi password (min. 8 characters)

/* Put IP Address details */
IPAddress local_ip (192, 168, 5, 1); // Address of ESP32 on its own network
IPAddress gateway (192, 168, 5, 1);  // The ESP32 acts as its own gateway
IPAddress subnet (255, 255, 255, 0); // Network mask; just leave this as is
#endif

/** @brief   The web server object for this project.
 *  @details This server is responsible for responding to HTTP requests from
 *           other computers, replying with useful information.
 *
 *           It's kind of clumsy to have this object as a global, but that's
 *           the way Arduino keeps things simple to program, without the user
 *           having to write custom classes or other intermediate-level 
 *           structures. 
*/
WebServer server (80);

/** @brief   Get the WiFi running so we can serve some web pages.
 */
void setup_wifi (void)
{
#ifdef USE_LAN                           // If connecting to an existing LAN
    Serial << "Connecting to " << ssid;

    // The SSID and password should be kept secret in @c mycerts.h.
    // This file should contain the two lines,
    //   const char* ssid = "YourWiFiNetworkName";
    //   const char* password = "YourWiFiPassword";
    WiFi.begin (ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        vTaskDelay (1000);
        Serial.print (".");
    }

    Serial << "connected at IP address " << WiFi.localIP () << endl;

#else                                   // If the ESP32 makes its own LAN
    Serial << "Setting up WiFi access point...";
    WiFi.mode (WIFI_AP);
    WiFi.softAPConfig (local_ip, gateway, subnet);
    WiFi.softAP (ssid, password);
    Serial << "done." << endl;
#endif
}


/** @brief   Put a web page header into an HTML string. 
 *  @details This header may be modified if the developer wants some actual
 *           @a style for her or his web page. It is intended to be a common
 *           header (and stylle) for each of the pages served by this server.
 *  @param   a_string A reference to a string to which the header is added; the
 *           string must have been created in each function that calls this one
 *  @param   page_title The title of the page
*/
void HTML_header (String& a_string, const char* page_title)
{
    a_string += "<!DOCTYPE html> <html>\n";
    a_string += "<head><meta name=\"viewport\" content=\"width=device-width,";
    a_string += " initial-scale=1.0, user-scalable=no\">\n<title> ";
    a_string += page_title;
    a_string += "</title>\n";
    a_string += "<style>html { font-family: Helvetica; display: inline-block;";
    a_string += " margin: 0px auto; text-align: center;}\n";
    a_string += "body{margin-top: 50px;} h1 {color: #4444AA;margin: 50px auto 30px;}\n";
    a_string += "p {font-size: 24px;color: #222222;margin-bottom: 10px;}\n";
    a_string += "</style>\n</head>\n";
}


/** @brief   Callback function that responds to HTTP requests without a subpage
 *           name.
 *  @details When another computer contacts this ESP32 through TCP/IP port 80
 *           (the insecure Web port) with a request for the main web page, this
 *           callback function is run. It sends the main web page's text to the
 *           requesting machine.
 */
void handle_DocumentRoot ()
{
    Serial << "HTTP request from client #" << server.client () << endl;

    String a_str;
    HTML_header (a_str, "ESP32 Web Server Test");
    a_str += "<body>\n<div id=\"webpage\">\n";
    a_str += "<h1>Test Main Page</h1>\n";
    a_str += "...or is it Main Test Page?\n";
    a_str += "<p><p> <a href=\"/csv\">IMU data</a>\n";
    a_str += "</div>\n</body>\n</html>\n";

    server.send (200, "text/html", a_str); 
}


/** @brief   Respond to a request for an HTTP page that doesn't exist.
 *  @details This function produces the Error 404, Page Not Found error. 
 */
void handle_NotFound (void)
{
    server.send (404, "text/plain", "Not found");
}


/** @brief   Show 100 pwm values provided to the motors.
 *  @details The data is taken every sent in a relatively efficient Comma
 *           Separated Variable (CSV) format which is easily read by Matlab(tm)
 *           and Python and spreadsheets.
 */
void handle_IMU (void)
{
    // The page will be composed in an Arduino String object, then sent.
    // The first line will be column headers so we know what the data is
    String IMU_str = "ax, ay\n";

    // Create some fake data and put it into a String object. We could just
    // as easily have taken values from a data array, if such an array existed
    for (uint8_t index = 0; index < 20; index++)
    {
        IMU_str += String (ax_pwm.get());
        IMU_str += ",";
        IMU_str += String (ay_pwm.get());
        IMU_str += "\n";
    }

    // Send the CSV file as plain text so it can be easily saved as a file
    server.send (404, "text/plain", IMU_str);
}


/** @brief   Task which sets up and runs a web server.
 *  @details After setup, function @c handleClient() must be run periodically
 *           to check for page requests from web clients. One could run this
 *           task as the lowest priority task with a short or no delay, as there
 *           generally isn't much rush in replying to web queries.
 *  @param   p_params Pointer to unused parameters
 */
void task_webserver (void* p_params)
{
    // The server has been created statically when the program was started and
    // is accessed as a global object because not only this function but also
    // the page handling functions referenced below need access to the server
    server.on ("/", handle_DocumentRoot);
    server.on ("/csv", handle_IMU);
    server.onNotFound (handle_NotFound);

    // Get the web server running
    server.begin ();
    Serial.println ("HTTP server started");

    for (;;)
    {
        // The web server must be periodically run to watch for page requests
        server.handleClient ();
        vTaskDelay (500);
    }
}

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

  // Begin the connection to the mpu
  mpu.begin(104);
   
  // Call function which gets the WiFi working
  setup_wifi ();
  delay(100);

  // Task which runs the web server. It runs at a low priority
  xTaskCreate (task_webserver, "Web Server", 8192, NULL, 2, NULL);

  // Task which reads from the IMU
  xTaskCreate (task_imu, "IMU", 4000, NULL, 4, NULL);

  // Task which moves the wrist
  xTaskCreate (task_wrist_arm, "Wrist and Arm", 2048, NULL, 5, NULL);
}



void loop (void) {}
