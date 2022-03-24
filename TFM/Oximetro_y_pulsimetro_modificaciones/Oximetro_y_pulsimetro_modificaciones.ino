#include <CircularBuffer.h>
#include <MAX30100.h>
#include <MAX30100_BeatDetector.h>
#include <MAX30100_Filters.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100_Registers.h>
#include <MAX30100_SpO2Calculator.h>

// https://forum.arduino.cc/t/sensor-max30100-y-pantalla-tft-ili9486/693174

/*------------------- Configuration -------------------------*/
// Configuration should be done in the included file:
#include "configuration.h";

/*------------------- Libraries -----------------------------*/
#include <WiFiNINA.h>
#include <PubSubClient.h>
//#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000 // 1 segundo



/*------------------ Global Variables -----------------------*/
// g_: for global

// SENSORS

int g_data_buffer[100];                       // Vector de datos

bool g_GSR_readings_taken     = false;      // true/fasle: whether any readings have been taken
float g_GSR_value             = 0.0;          // Value for sensor GSR
int g_pin_GSR                 = A0;         // Analog pin on NN33IoT
float g_GSR_time_sep          = 0.0;        // Tiempo entre muestra y muestra

float g_HR_value              = 0.0;        // Value for sensor MAX30100 Heart Rate
float g_SpO2_value            = 0.0;        // Value for sensor MAX30100 SpO2 

// MQTT
# define g_topicSize 100                          // Tamaño del string de los topics. Peso en bytes del paquete. 
char g_mqtt_message_buffer[g_topicSize*5];        // General purpose buffer for MQTT messages
char g_command_topic[g_topicSize];                // MQTT topic for receiving commands

#if REPORT_MQTT_SEPARATE
char g_GSR_mqtt_topic[g_topicSize];               // MQTT topic for reporting GSR values
char g_npaquete_mqtt_topic[g_topicSize];          // MQTT topic for reporting GRS time value
#endif

#if REPORT_MQTT_JSON
char g_mqtt_json_topic[g_topicSize];              // MQTT topic for reporting all values using JSON
#endif

unsigned long g_npaquete       = 0;               // Value for number of pacakge sent

// WiFi
#define WIFI_CONNECT_INTERVAL       500     // Wait 500ms intervals for wifi connection
#define WIFI_CONNECT_MAX_ATTEMPTS   10      // Number of attempts/intervals to wait

// Time
unsigned long g_segundo          = 0;        // Variable tiempo
unsigned long g_tiempo_inicio    = 0;
unsigned long g_tiempo_actual    = 0;


//General
char* g_cliente_ID;                        // Simulate chipID. *: NO CAMBIA 

unsigned long g_tStart_loop  = 0;          // Initial time for measuring time spent
unsigned long g_tEnd_loop    = 0;          // End time for measuring time spent

// Contador
unsigned int g_contador = 0;               // Contar el numero de paquetes enviados (en la variable time) -----CAMBIAR NOMBRE ¡¡¡¡¡


// Nuevas var 11.08.2021
uint32_t g_tsLastReport       = 0;                  // ts: timeStamp?
#define MUESTRAS_SEGUNDO 360.0             
float g_reporting_period      = 1000000 / MUESTRAS_SEGUNDO; // 10^6 por ser micros. Cada cuanto queremos que muestree
int g_cantidad_datos_leidos   = 0;


// Var de este fichero de antes
uint32_t tsLastReport = 0;

float HR = 0.0;
int spo2 = 0;

//PulseOximeter::update()
//MAX30100.update()

/*------------------- Instantiate Global Objects ----------------*/
// MQTT
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
PulseOximeter pox;
/*-------------------- Function Signatures -----------------------*/
void mqttCallback(char* topic, byte* payload, unsigned int len);    // 
bool initWiFi();                                                    // 
void reconnectMqtt();                                               // 
void updateReadings();                                              // 
void reportToMqtt();                                                // 
void reportToSerial();                                              // 
String NewClientID();                                               // 
void oneBeatDetected();                                             // Done

void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);

    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println();
    Serial.print("Initializing pulse oximeter..");

    // Initialize the PulseOximeter instance and register a beat-detected callback
    // The parameter passed to the begin() method changes the samples flow that
    // the library spews to the serial.
    // Options: (R: lecturas)
    //  * PULSEOXIMETER_DEBUGGINGMODE_PULSEDETECT : filtered samples and beat detection threshold 
    //  * PULSEOXIMETER_DEBUGGINGMODE_RAW_VALUES : sampled values coming from the sensor, with no processing
    //  * PULSEOXIMETER_DEBUGGINGMODE_AC_VALUES : sampled values after the DC removal filter
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    //pox.setOnBeatDetectedCallback(onBeatDetected);

    // We need a unique device ID for our MQTT client connection.
    // Normalmente utilizariamos el ID del dispositivo (los de arduino no los tienen)
    g_cliente_ID = "IDSPV001";       // Get ID. Revisar TODO.

    /*------------------TOPICS-----------------------------------------------------------------------------------------*/
    // Set up the topics for publishing sensor readings. By inserting the unique ID,
    // the result is of the form: "arduino_1/GSR/valor" etc
    
    // Mostrar los topics utilizados
    sprintf(g_command_topic, "cmnd/%s/COMMAND", g_cliente_ID);                          // For receiving commands
  
    #if REPORT_MQTT_SEPARATE
      sprintf(g_GSR_mqtt_topic, "arduino_1/%s/GSR/valor", g_cliente_ID);                // Data form AN33IoT
      sprintf(g_npaquete_mqtt_topic, "arduino_1/%s/numPaquete", g_cliente_ID);      // Data form AN33IoT
    #endif
  
    #if REPORT_MQTT_JSON
      sprintf(g_mqtt_json_topic, "arduino_1/%s/SENSOR", g_cliente_ID);                  // Data from AN33IoT
    #endif
  
    // Report the MQTT topics to the serial console
    Serial.println(g_command_topic);                   // For receiving messages
    
    #if REPORT_MQTT_SEPARATE
      Serial.println("MQTT separate topics: ");
      Serial.println(g_GSR_mqtt_topic);                // From AN33IoT
      Serial.println(g_npaquete_mqtt_topic);           // From AN33IoT
    #endif
  
    #if REPORT_MQTT_JSON
      Serial.println("MQTT topics en JSON: ");
      Serial.println(g_mqtt_json_topic);               // From AN33IoT
    #endif

    /*---------------*/
    // Connect to WiFi
      if (initWiFi()){
        Serial.println("Funcion WIFI");
      }
      


}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

      updateReadings();
 
      tsLastReport = millis();
    }
}

void updateReadings(){
    Serial.print("Heart rate:");
    HR = pox.getHeartRate();
    Serial.print(HR);
    Serial.print("bpm / SpO2:");
    spo2 = pox.getSpO2();
    Serial.print(spo2);
    Serial.println("%");
}


/*-------------------------------------------------------------*/

// FUNCTION - Connect to WiFi ---------------------------------------------------------------
bool initWiFi()
{
   Serial.println();
   Serial.print("Connecting to wifi ");
   Serial.println(ssid);

   // Conenecto to WiFi
   WiFi.begin(ssid, password);
   

   // Wait for connection ser amount of intervals
   int num_attempts = 0;
   while (WiFi.status() != WL_CONNECTED && num_attempts <= WIFI_CONNECT_MAX_ATTEMPTS)
   {
    delay(WIFI_CONNECT_INTERVAL);
    Serial.print(".");
    num_attempts++;
   }

   if (WiFi.status() != WL_CONNECTED)
   {
     Serial.print("Falied connexion to Wifi. Attempts: ");
     Serial.println(num_attempts);
     return false;
   } 
   else
   {
     return true;
   }   
}
