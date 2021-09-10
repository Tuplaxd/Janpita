#include <Adafruit_MLX90614.h>

// Instanciamos el sensor de temperatura
Adafruit_MLX90614 sensorTemp = Adafruit_MLX90614();

unsigned long inicioMillis;
unsigned long actualMillis;
const unsigned long periodo = 0.25 * 60 * 1000; // 2 minutos

const int pingPin = 7; // Sensor de Ultrasonido

void setup() {

  inicioMillis = millis();

  // Inicializamos Variables
  // ...

  // Inicializar el Puerto Serial
  Serial.begin(115200);

  // Inicializamos Sensores / Puertos
  sensorTemp.begin();
  // Configurar modo fila

  Serial.println("** JANPITA **");
}

void loop() {

  long duracion, distancia; // Para el sensor de ultrasonido

  actualMillis = millis();

  // Realizamos la inicializacion del sensor de distancia
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // Realizamos la lectura de la distancia
  pinMode(pingPin, INPUT);
  duracion = pulseIn(pingPin, HIGH);

  distancia = duracionEnCentimetros(duracion);

  Serial.print("DISTANCIA CM :");
  Serial.println(distancia);

  if ( distancia > 170 ) {
    // mandar una alerta por Buzzer/Vibracion
  }

  if ( actualMillis - inicioMillis >= periodo ) {
    double temperaturaCorporal = sensorTemp.readObjectTempC();
    Serial.println("TEMPERATURA CORPORAL :");
    Serial.println(String(temperaturaCorporal, 2));
    
    if (temperaturaCorporal > 37.0) { // Hay fiebre
      // mandar una alerta por Buzzer/Vibracion
    }
    
    inicioMillis = actualMillis;
  }

  // Loop principal
  // Leer el sensor corporal de temperatura cada 5 min
  double temperaturaAmbiente = sensorTemp.readAmbientTempC();
  
  // Serial.println("TEMPERATURA AMBIENTE :");
  // Serial.println(String(temperaturaAmbiente, 2));

  // Sensor de ultrasonido
  // if (modoFila) {
    // distancia = sensorUltra.distance();
    // if (distancia < 150) {
      // mandar una alerta por Buzzer/Vibracion
    // }
  // }

  // MQ 134 - MQ 135 (dioxido de carbono y el monoxido de carbono)
  
  // Sensor de Pulso cardiaco y oximetro MAX30102

  // Retraso en ms
  delay(300);
}

long duracionEnCentimetros(long duracion) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return duracion / 29 / 2;
}
