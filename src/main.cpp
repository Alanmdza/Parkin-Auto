#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <string>
#include <LugarEstacionamiento.hpp>
#include <ArduinoJson.h>
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
// Defining the WiFi channel speeds up the connection:
#define WIFI_CHANNEL 6

WebServer server(80);
std::vector<LugarEstacionamiento> listaDeLugares(20);

void sendJson()
{
  // Crear un objeto JSON
  DynamicJsonDocument doc(1024); // Tamaño del documento JSON, ajusta según tus necesidades

  // Crear un array JSON para almacenar los lugares
  JsonArray lugares = doc.createNestedArray("lugares");

  // Iterar sobre la lista de lugares y agregar cada lugar al array JSON
  for (int j = 0; j < 20; j++) // Cambia el límite de iteración a 20
  {
    JsonObject lugarJson = lugares.createNestedObject();
    Serial.println(listaDeLugares[j].getlugar().c_str());
    lugarJson["lugar"] = listaDeLugares[j].getlugar();
    lugarJson["Patente"] = listaDeLugares[j].getPatente();
    lugarJson["Ocupado"] = listaDeLugares[j].estaOcupado();
  }

  // Convertir el objeto JSON en una cadena
  String jsonResponse;
  serializeJson(doc, jsonResponse);
  Serial.println(jsonResponse.c_str());
  server.send(200, "application/json", jsonResponse);
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
  int i = 1;
  char c = 'A';
  for (int j = 0; j < 20; j++) // Cambia el límite de iteración a 20
  {
    listaDeLugares[j].setLugar(std::string(1, c) + std::to_string(i));
    listaDeLugares[j].setPatente(0);
    listaDeLugares[j].setOcupado(false);
    i++;
    if (i > 5)
    {
      i = 1;
      c++;
    }
  }

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
