/*
 * PROYECTO SISTEMAS EMBEBIDOS- PROYECTO 2B
 * OBJETIVO: Adquirir datos mediante la placa arduino física y sensores de aire.
 * INTEGRANTES: Flores Erik - Martinez Juan
 */
 #include <LiquidCrystal.h>
 //DENICINION DE VARIABLES A UTILIZAR
 int sensorMQ=0;                      //Definición del sensor MQ135 en el pin de entrada 0
 int sensorM=1;                       //Difinición del sensor MQ7 en el pin 1 de entrada.
 int led=4;                           //Se define la variable para el led de identificación de etiqueta.
 int led1=5;                           //Se define la variable para el led de identificación de etiqueta.
LiquidCrystal lcd(13,12,11,10,9,8);    //Se crea la variable de la lcd con sus pines de conexion
 
 
void setup() {
  Serial.begin(9600);                 //Se inicializa la configuración serial.
  lcd.begin(16,2);
  pinMode(led,OUTPUT);               //Inicialización del pin led5 como salida.
  pinMode(led1,OUTPUT);               //Inicialización del pin led6 como salida.
  digitalWrite(led,LOW);             //Se define el pin led5 como salida.
  digitalWrite(led1,LOW);             //Se define el pin led6 como salida.
}
void loop() {
  Serial.println("Sensor MQ 135");    //Se envia mensaje para los datos del sensor MQ 135.
  for(int i=0;i<=120;i++)                 //Se crea el ciclo del tamaño de muestras del sensor.
  {
    sensorMQ=analogRead(0);           //Lectura anlógica del sensor en el pin A0.
    Serial.println(sensorMQ,DEC);     //Impresion de datos analógicos
    lcd.println(sensorMQ,DEC);     //Impresion de datos analógicos
    digitalWrite(led,HIGH);
    delay(500);                       //Tiempo de espera para visualización.
  }
  Serial.println("Sensor MQ 7");      //Impresion de mensaje para los datos del sensor MQ 7.
  for(int i=0; i<120;i++)                 //Se crea el ciclo del tamaño de muestras del sensor.
  {
    sensorM=analogRead(1);            //Lectura analógica del sensor en el Pin1.
    Serial.println(sensorM,DEC);      //Se imprime detos analógicos, DEC--> Decimales
    lcd.println(sensorM,DEC);
    digitalWrite(led1,HIGH);
    delay(500);
  }
}
