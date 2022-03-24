/* ------------------- General config ------------------- */
// WiFi - VLC
const char* ssid          = "MiFibra-93C7";     // Your WiFi SSID
const char* password      = "gKxFRET6";         // Your WiFi password
// WiFi - Puebla
//const char* ssid          = "MiFibra-40FA";     // Your WiFi SSID
//const char* password      = "QG6wJJai";         // Your WiFi password

// MQTT
// char* mqtt_broker   = "test.mosquitto.org";        // IP address of your MQTT broker
const char* mqtt_broker   = "192.168.1.37";     // IP address of your MQTT broker
int port                  = 1883;               // Port connection
const char* mqtt_username = "mqtt_username";    // Your MQTT username
const char* mqtt_password = "mqtt_password";    // Your MQTT password
#define REPORT_MQTT_SEPARATE true              // Report each valoue to its own topic
#define REPORT_MQTT_JSON true                   // Report all values in a JSON message
const char* status_topic = "events";            // MQTT topic to report startup

// Serial
#define SERIAL_BAUD_RATE 115200                 // Speed for USB serial console
