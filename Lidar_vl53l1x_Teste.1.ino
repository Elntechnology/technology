#include <Wire.h>
#include "VL53L1X.h"

#define NUM_SENSORS 4

VL53L1X sensors[NUM_SENSORS];
uint16_t distances[NUM_SENSORS];

void setup() {
  Wire.begin();
  Serial.begin(9600);

  for (int i = 0; i < NUM_SENSORS; i++) {
    if (!sensors[i].init()) {
      Serial.println("Falha ao iniciar o sensor " + String(i));
      while (1); // Aguarda indefinidamente caso haja falha em algum sensor
    }

    sensors[i].setDistanceMode(VL53L1X::Long);
    sensors[i].startContinuous(50);
  }
}

void loop() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    distances[i] = sensors[i].read();
    delay(10);
  }

  // Processar os dados dos sensores para criar uma representação 3D

  // Exibir os resultados
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("Distancia " + String(i) + ": ");
    Serial.print(distances[i]);
    Serial.println(" mm");
  }

  delay(1000); // Espera um intervalo entre as medições
}
