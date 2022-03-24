// https://forum.arduino.cc/t/sensor-max30100-y-pantalla-tft-ili9486/693174

#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;

float HR = 0.0;
int spo2 = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(115200);
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
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        HR = pox.getHeartRate();
        Serial.print(HR);
        Serial.print("bpm / SpO2:");
        spo2 = pox.getSpO2();
        Serial.print(spo2);
        Serial.println("%");

 
        tsLastReport = millis();
    }
}
