#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <string>

#include <ArduinoJson.h>
#include <LugarEstacionamiento.hpp>
#include <config.hpp>
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
}

void loop(void)
{
  server.handleClient();
  delay(800);
}

void sendJson()
{
  update();
  // Crear un objeto JSON
  DynamicJsonDocument doc(2048);

  // Crear un objeto JSON para almacenar los lugares
  JsonObject lugares = doc.createNestedObject("lugares");

  // Iterar sobre la lista de lugares y agregar cada lugar al objeto JSON
  for (int j = 0; j < 20; j++)
  {
    JsonObject lugarJson = lugares.createNestedObject(listaDeLugares[j].getlugar());

    lugarJson["patente"] = listaDeLugares[j].getPatente();
    lugarJson["ocupado"] = listaDeLugares[j].estaOcupado();
  }

  // Convertir el objeto JSON en una cadena
  String jsonResponse;
  serializeJson(doc, jsonResponse);
  server.send(200, "application/json", jsonResponse);
}

bool detectarCuerpo(int triggerPin, int echoPin)
{
  // Iniciamos el pin del emisor de reuido en salida
  pinMode(triggerPin, OUTPUT);
  // Apagamos el emisor de sonido
  digitalWrite(triggerPin, LOW);
  // Retrasamos la emision de sonido por 2 milesismas de segundo
  delayMicroseconds(2);
  // Comenzamos a emitir sonido
  digitalWrite(triggerPin, HIGH);
  // Retrasamos la emision de sonido por 2 milesismas de segundo
  delayMicroseconds(10);
  // Apagamos el emisor de sonido
  digitalWrite(triggerPin, LOW);
  // Comenzamos a escuchar el sonido
  pinMode(echoPin, INPUT);
  // Calculamos el tiempo que tardo en regresar el sonido
  return (0.01723 * pulseIn(echoPin, HIGH)) < 100;
}

std::string generarPatenteArgentinaAleatoria()
{
  // Letras válidas para las patentes (A-Z)
  const std::string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // Genera tres letras aleatorias
  std::string patente;
  for (int i = 0; i < 3; i++)
  {
    patente += letras[rand() % letras.size()];
  }

  // Genera tres números aleatorios
  for (int i = 0; i < 3; i++)
  {
    patente += std::to_string(rand() % 10);
  }

  return patente;
}

void update()
{
  for (int i = 0; i <= 16; i++)
  {
    bool ocupacion = detectarCuerpo(obtenerTrigger(i), obtenerEco(i));
    if (listaDeLugares[i].estaOcupado() != ocupacion)
    {
      if (!ocupacion)
      {
        listaDeLugares[i].setPatente("NULL");
      }
      else
      {
        listaDeLugares[i].setPatente(generarPatenteArgentinaAleatoria());
      }
      listaDeLugares[i].setOcupado(ocupacion);
    }
  }
}
