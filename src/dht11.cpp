#include <DHT.h>

// Define the type of sensor (DHT11 or DHT22)
#define DHT_TYPE DHT11
// Define the pin to which the sensor is connected
#define DHT_PIN 2

// Initialize the DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // Start serial communication
  Serial.begin(9600);
  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Delay for a few seconds between readings
  delay(500);

  // Read temperature and humidity from the sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the temperature and humidity to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
