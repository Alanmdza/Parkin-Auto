#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
// Defining the WiFi channel speeds up the connection:
#define WIFI_CHANNEL 6

WebServer server(80);

//-----------------------Variables de prueba
int LUGAR1 = 26;
String Patente1 = "aaa0023";
bool Ocupado1 = false;
//-----------------------

void sendJson()
{
  // Para cada lugar vamos a agregarle un pedacito más de información al JSON. El objetivo es mandar un solo JSON grande con todos los lugares.
  String response = R"(
    {
      "lugar": "LUGAR1",
      "Patente": "PATENTE1",
      "Ocupado": "Ocupado1"
    }
  )";
  response.replace("LUGAR1", String(LUGAR1));
  response.replace("PATENTE1", Patente1);
  response.replace("Ocupado1", Ocupado1 ? "True" : "False");

  server.send(200, "application/json", response);
}

void setup(void)
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", sendJson);
  server.begin();
  Serial.println("HTTP server started (http://localhost:8180)");
  sendJson();
}

void loop(void)
{
  server.handleClient();
  delay(800);
}
