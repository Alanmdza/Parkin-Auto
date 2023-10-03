#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <string>
#include <LugarEstacionamiento.hpp>
#include <ArduinoJson.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

WebServer server(80);
std::vector<LugarEstacionamiento> listaDeLugares(20);


void setup(void)
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  int i = 1;
  char c = 'A';
  for (int j = 0; j < 20; j++)
  {
    listaDeLugares[j].setLugar(std::string(1, c) + std::to_string(i));
    i++;
    if (i > 5)
    {
      i = 1;
      c++;
    }
  }

  server.on("/", HTTP_GET, sendJson); // Manejar una solicitud GET en la ruta "/getJson"
  server.begin();
  Serial.println("HTTP server started (http://localhost:8180)");
  sendJson();
}

void loop(void)
{
  server.handleClient();
  delay(800);
}


void sendJson()
{
  // Crear un objeto JSON
  DynamicJsonDocument doc(2048);

  // Crear un objeto JSON para almacenar los lugares
  JsonObject lugares = doc.createNestedObject("lugares");

  // Iterar sobre la lista de lugares y agregar cada lugar al objeto JSON
  for (int j = 0; j < 20; j++)
  {
    JsonObject lugarJson = lugares.createNestedObject(listaDeLugares[j].getlugar());

    lugarJson["Patente"] = listaDeLugares[j].getPatente();
    lugarJson["Ocupado"] = listaDeLugares[j].estaOcupado();
  }

  // Convertir el objeto JSON en una cadena
  String jsonResponse;
  serializeJson(doc, jsonResponse);
  server.send(200, "application/json", jsonResponse);
}