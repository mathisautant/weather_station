#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <DHT.h>
#include <TimeLib.h>

#define DHTPIN 2  // Pin de données du capteur DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

IPAddress server_addr(127,0,0,1);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "weaselweatherstation";        // MySQL user login password

MySQL_Connection conn((Client *)&Serial);



void setup() {
  Serial.begin(9600);
  dht.begin();

  setTime(0, 0, 0, 1, 1, 1970); // Initialiser l'horloge (peut être ajusté selon vos besoins)

  while (!Serial);
  Serial.println("Connecting to MySQL Server...");
  if (conn.connect(server_addr, 3306, user, password)) {
    Serial.println("Connected to MySQL server!");
  } else {
    Serial.println("Connection failed.");
  }
}

void loop() {
  // Lire les données du capteur
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // Envoyer les valeurs au port série
  Serial.println(temperature);
  Serial.println(humidity);
  // Obtenir le timestamp actuel
  char timestamp[20];
  sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());

  // Insérer les données dans MySQL
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  cur_mem->execute("INSERT INTO weather_data (timestamp, temperature, humidity) VALUES ('" + String(timestamp) + "', " + String(temperature) + ", " + String(humidity) + ")");
  delete cur_mem;

  delay(1000);  // Attendre 10 secondes avant la prochaine insertion
}
