#include <Adafruit_MLX90614.h>

// Instanciamos el sensor de temperatura
Adafruit_MLX90614 sensorTemp = Adafruit_MLX90614();

unsigned long inicioMillis;
unsigned long actualMillis;
//const unsigned long periodo = 0.25 * 60 * 1000; //15 segundos
const unsigned long periodo = 5 * 1000;

//const int pingPin = 7; // Sensor de Ultrasonido
const int Trigger = 9;   //Pin digital 9 para el Trigger del sensor
const int Echo = 8;   //Pin digital 8 para el echo del sensor

void setup() {
  inicioMillis = millis()

                 // Inicializamos Variables
                 // ...

                 // Inicializar el Puerto Serial
                 ; Serial.begin(115200);

  // Inicializamos Sensores / Puertos
  sensorTemp.begin();
  // Configurar modo fila

  Serial.println("** JANPITA **");

  pinMode(12, OUTPUT)//declaracion del pin 12 como salida
  }



void loop() {
 

  long duracion, distancia; // Para el sensor de ultrasonido


  // ;digitalWrite(8, HIGH);//encendemos led
  //;delay (200)
  //;digitalWrite(8, LOW )//apagamos el led
  //;delay (200);


  actualMillis = millis();



//distancia = duracionEnCentimetros(duracion);


  if ( actualMillis - inicioMillis >= periodo ) {
    double temperaturaCorporal = sensorTemp.readObjectTempC();
    Serial.println("TEMPERATURA CORPORAL :");
    Serial.println(String(temperaturaCorporal, 2));

    if (temperaturaCorporal > 37.0) { // Hay fiebre
      // mandar una alerta por Buzzer/Vibracion
      for (int i = 0;i<5;i = i + 1){
       digitalWrite(12, HIGH);       //encendemos led
       delay (200);
       digitalWrite(12, LOW );       //apagamos el led
       delay (200);
      }
    }

    inicioMillis = actualMillis;
  }

  // Loop principal
  // Leer el sensor corporal de temperatura cada 5 min
  double temperaturaAmbiente = sensorTemp.readAmbientTempC();

  // Serial.println("TEMPERATURA AMBIENTE :");
  // Serial.println(String(temperaturaAmbiente, 2));

 long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros



  // MQ 134 - MQ 135 (dioxido de carbono y el monoxido de carbono)

  // Sensor de Pulso cardiaco y oximetro MAX30102

  // Retraso en ms
  delay(300);
}

long duracionEnCentimetros(long duracion) {
  // The speed of sound is 340 m/s or 29 microseconds per c entimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return duracion / 29 / 2;
}
