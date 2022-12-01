/** @file webserver.h
 *  This is the header for a webserver module which writes data to a webpage.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   2022-Nov-30
 */

#include <Arduino.h>
#include "PrintStream.h"
#include <WiFi.h>
#include <WebServer.h>

/** @brief   Class which maintains a MQTT client
 * 
 */
class Webdriver
{
// private:
//     const char* ssid;
//     const char* password;
//     IPAddress local_ip; // Address of ESP32 on its own network
//     IPAddress gateway;  // The ESP32 acts as its own gateway
//     IPAddress subnet;   // Network mask; just leave this as is
//     WebServer server;

public:
    const char* ssid;
    const char* password;
    IPAddress local_ip; // Address of ESP32 on its own network
    IPAddress gateway;  // The ESP32 acts as its own gateway
    IPAddress subnet;   // Network mask; just leave this as is
    WebServer server;
    Webdriver (void* params);
    void setup_wifi (void);
    void HTML_header (String& a_string, const char* page_title);
    void handle_DocumentRoot ();
    void handle_NotFound (void);
    void handle_Toggle_LED (void);
    void handle_CSV (void);
};