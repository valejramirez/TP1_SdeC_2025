#include <Arduino.h>
// Added some emojis, more fun
void ejecutarTest(int frecuenciaMHz) {
  Serial.println();
  Serial.println("==========================================");
  Serial.print("⚙️  Iniciando benchmark en ");
  Serial.print(frecuenciaMHz);
  Serial.println(" MHz");
  Serial.println("==========================================");

  setCpuFrequencyMhz(frecuenciaMHz);
  delay(500);  // Wait till system is stable

  // --------- INT LOOP ---------
  Serial.println("🔢 [Test 1] Suma de enteros en ejecución...");

  unsigned long tInicio = millis();
  volatile long sumaEnteros = 0;
  long repeticionesEnteros = 100000000;

  for (long i = 0; i < repeticionesEnteros; i++) {
    sumaEnteros += i;
  }

  unsigned long tFin = millis();
  Serial.print("⏱️  Duración: ");
  Serial.print(tFin - tInicio);
  Serial.println(" ms");

  // --------- FLOAT LOOP ---------
  Serial.println("🌊 [Test 2] Now with the floats...");

  tInicio = millis();
  volatile float sumaFloats = 0.0;
  long repeticionesFloats = 10000000;

  for (long i = 0; i < repeticionesFloats; i++) {
    sumaFloats += 0.1;
  }

  tFin = millis();
  Serial.print("⏱️  Duración: ");
  Serial.print(tFin - tInicio);
  Serial.println(" ms");

  Serial.println("✅ Benchmark completado para esta frecuencia.");
  Serial.println("------------------------------------------\n");

  delay(2000);  // DELAY BTWN TESTS
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  delay(1000);
  Serial.println("\n💻 Benchmark de rendimiento ESP32 💻");
  Serial.println("🧪 Grupo: ForkAround&FindOut");
  Serial.println("📊 Evaluación comparativa de frecuencias\n");

  int frecuencias[] = {80, 160};

  for (int i = 0; i < 2; i++) {
    ejecutarTest(frecuencias[i]);
  }

  Serial.println("🏁 Todos los tests han finalizado correctamente.");
}

void loop() {
  // NOOP
}
