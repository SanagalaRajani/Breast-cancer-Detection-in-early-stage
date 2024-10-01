#include <OneWire.h>
#include <DallasTemperature.h>

// Pin assignments
#define ONE_WIRE_BUS 15  // DS18B20 pin
#define TOUCH_PIN 5      // Touch sensor pin
#define FORCE_PIN 34     // Analog pin for force sensor

// Setup OneWire instance and DallasTemperature library
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Status label variable
String statusLabel;

void setup() {
  Serial.begin(9600);

  // Start the DS18B20 sensor
  sensors.begin();

  // Set up the touch sensor pin
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  // Request temperature from DS18B20
  sensors.requestTemperatures(); 
  float temperature = sensors.getTempCByIndex(0); // Get temperature in Celsius

  // Read force sensor value
  int forceValue = analogRead(FORCE_PIN);

  // Read touch sensor value (1 if touched, 0 otherwise)
  int touchValue = digitalRead(TOUCH_PIN);

  // Define thresholds for a single status label
  if (temperature > 32 && forceValue > 600 && touchValue == 1) {
    statusLabel = "Critical";  // High temperature, high force, and touch detected
  } 
  else if (temperature > 32 && forceValue <= 600 && touchValue == 0) {
    statusLabel = "Warning";   // High temperature, low force, and no touch
  } 
  else if (temperature <= 32 && forceValue > 600 && touchValue == 0) {
    statusLabel = "Pressure High";   // Normal temperature but high force
  } 
  else if (temperature <= 32 && touchValue == 1) {
    statusLabel = "Touched";   // Normal temperature but touch detected
  } 
  else {
    statusLabel = "Normal";    // Normal readings for all sensors
  }

  // Print data in CSV format with status label to the Serial Monitor
  Serial.print("#");              // Start of Frame (SOF)
  Serial.print(",");
  Serial.print(temperature);      // Temperature value
  Serial.print(",");
  Serial.print(forceValue);       // Force sensor value
  Serial.print(",");
  Serial.print(touchValue ? 1 : 0); // Touch state (1 for touched, 0 for not touched)
  Serial.print(",");
  Serial.print(statusLabel);      // Single status label
  Serial.print(",");
  Serial.println("~");            // End of Frame (EOF)

  delay(1000);  // Adjust delay for your needs
}
