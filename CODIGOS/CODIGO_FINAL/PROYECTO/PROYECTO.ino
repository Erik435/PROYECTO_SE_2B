/*
 * PROYECTO FINAL SISTEMAS EMBEBIDOS SEGUNDO BIMESTRE
 * OBJETIVO: Concatenar los códigos de ejecucuón del proyecto y formar uno solo
 * INTEGRANTES: Flores Erik, Martinez Juan
 */
#include<LiquidCrystal.h>   //Se llama a la libreria de la LCD
#include "datos.h"          //Se llama a venatana de nombre datos
#include<avr/power.h>       //Se llama a la librería de reduccion de energia
#include<avr/sleep.h>       //Se llama a la librería de adminitracion de energia y suspencion
#include<avr/wdt.h>         //Se llama a la libreria de perro guardián
#include<EEPROM.h>          //Se llama a la librería de la memoria EEPROM


LiquidCrystal lcd(13,12,11,10,9,8);    //Se crea la variable de la lcd con sus pines de conexion
int dato;                              //Creación de la variable para la memoria EEPROM
int k;                                 //Creacion de variable para el conteo de tiempos
int i=0;                               //Creación de variables para ciclos
int led1 = 4;                          //Creacion de la variable para el led 
int led2 = 5;                          //Creacion de la variable para el led2
float a;                               //Creacion de variable float para lectura de variables de un sensor.
float b;                               //Creación de variable float para lectura de variable del otro sensor.
double senialE [15];                   //Creación de vector de tamaño 15.
double senialE2 [15];                  //Creeacion de vector para señal dos de tamaño15.
int enviar;                 
double senial_Sua[15];                 //Se crea un vector con un tamaño de salida para visualizar en LCD 
double senial_Sua2[15];                //Se crea un vector con un tamaño de salida para visualizar en LCD
int respuesta;                         //Se crea variable para definir si es puro o no.

void (* resetFunc)(void)=0;            //Se crea método de reinicio de arduino
int knn (int k, int etiquetas, int tam_col, int col_fil);                             // Se crea la variable con los parámetros para método de aprendizaje
void media (double *senial_E, double *senial_Sua, int tam_SE, int filter);            // Se crea el método de suavizado con los parámetros
void media2 (double *senial_E, double *senial_Sua, int tam_SE, int filter);           // Se crea el método de suavizado con los parámetros. 


void setup() {  
  dato=EEPROM.read(0);                                                                //Lectura del dato 0, para activacion del sistema completo
  Serial.begin(9600);                                                                 //Inicializamos la comunicación serial
  if(dato==0){                                                                        //Condicion de activacion de metodo de inicio
    EEPROM.update(0,1);                                                               //Escritura en la eeprom si se tiene un valor es diferente al guardado, direccion,valor
    sistema();                                                                        //Activacion de metodo sistema
    Serial.begin(9600);                                                               //Inicializacion de la comunicacion serial
    lcd.begin(16,2);                                                                  //Inicialización de la LCD
    pinMode(led1,OUTPUT);                                                             //Inicializacion modo de led                       
    pinMode(led2,OUTPUT);                                                             //Inicializacion modo de led2
    digitalWrite(led1,LOW);                                                           //Se escribe el estado incial del led
    digitalWrite(led2,LOW);                                                           // se escribe el estado inicial del led2.
    for(i=0;i<15;i++)                                                                 //Inicializacion del ciclo for para la toma de datos de los sensores                             
      {
        senialE[i]=analogRead(0);                                                     //Lectura análoga del sensor del pin 0
        senialE2[i]=analogRead(1);                                                    //Lectura análoga del sensor del pin1
      }
      media ((double *)&senialE[0], (double *)&senial_Sua[0], (int) 15,9);         //Se inicializa el método de suavizado con relleno de 0 los vectores.                     
      media2 ((double *)&senialE2[0], (double *)&senial_Sua2[0], (int) 15,9);      //Se inicializa el método de suavizado2 con relleno de 0 los vectores.
      a=senial_Sua[8];                                                                //Se inicializa el tamaño del vector para mostrar en la LCD
      b=senial_Sua2[8];                                                               //Se inicializa el tamaño del vector2 para mostrar en la LCD
      respuesta=knn(3,2,3,182);                                                       // Se define los valores para la definicion de aire,numero de k, numero de etiquetas, tamano de la matriz  
      delay(250);                                                                     //Tiempo para la visualizacion
      Serial.write(respuesta);                                                        //Se escriba en el serial los valores de tipo de aire
    EEPROM.write(1,0);                                                                //Actualizacion dato para manatener la placa en ahorro de energia.
    k=EEPROM.read(1);                                                                 //Lectura de dato auxiliar.
  }else{
    k=EEPROM.read(1);                                                                 //LEctura de dato auxiliar
    k=k+1;                                                                            //Aumento de dato auxiliar para el ciclo
    EEPROM.update(1,k);                                                               //Actualizacion dato auxiliar para el ciclo de dormido
  }
  if(k<(1+299)){           //Condicion de activacion del modo sleep (1) * 4 + (x) * 4 = 4 segundos activado y  2x secundos desactivado ,segundo 1 es de ciclos, primero para que funcione, //74
  delay(100);            //Tiempo de rebote
  modo();                //Se llama al método de activacion de modo sleep.
  }else{
    EEPROM.update(0,0);       //Actualizacion dato principal para el sistema si ya llega al tiempo límite de dormido
    wdt_enable(WDTO_15MS);    //Condicion reinicio del sistema, 15ms de comprobacion de la condicion para verificar si ha acabado el tiempo de apagado.
  }
}

void loop() { 
 }

//FILTRADO Señal 1
void media (double *senial_E, double *senial_Sua, int tam_SE, int filter){    //Creación de metodo media con los valores de salida
  int i,j;                                                                    //Creación de vaariables para los ciclos for
  for(i=floor(filter/2);i<tam_SE-floor(filter/2)-1;i++){                      //Se crea el ciclo de recorrdio para cada posición del vector a salir
    senial_Sua[i]=0;                                                          //Se iguala a 0 el vector
    for(j=-floor(filter/2);j<floor(filter/2);j++){                            //Se crea el ciclo para recorrido con la variable j
        senial_Sua[i]=senial_Sua[i]+senial_E[i+j];                            //Se realiza las operaciones con los valores guardados
      }                             
      senial_Sua[i]=senial_Sua[i]/filter;                                     //Senial resultante suavizada.
    }
  }


//FILTRADO Señal 2
void media2 (double *senial_E, double *senial_Sua2, int tam_SE, int filter){   //Creación de metodo media2 con los valores de salida
  int i,j;                                                                      //Creación de vaariables2 para los ciclos for
  for(i=floor(filter/2);i<tam_SE-floor(filter/2)-1;i++){                       //Se crea el ciclo de recorrdio para cada posición del vector a salir
    senial_Sua2[i]=0;                                                           //Se iguala a 0 el vector2
    for(j=-floor(filter/2);j<floor(filter/2);j++){                              //Se crea el ciclo para recorrido con la variable j
        senial_Sua2[i]=senial_Sua2[i]+senial_E[i+j];                            //Se realiza las operaciones con los valores guardados                         
      }
      senial_Sua2[i]=senial_Sua2[i]/filter;                                      //Senial resultante suavizada.
    }
  }
  
//Aprendizaje de maquina con datos guardados
int knn (int k, int etiquetas, int tam_col, int tam_fil){                       //Definición de parámetros para el método KNN
float datos_prueba [3]={a,b,0.0};                                               //Creación del vector el cual se va a compara
int col;                                                                        //Número de columnas de la matriz de los datos
int fil=0;                                                                      //Número de filas de la matriz de los datos                                                  
int i=0;                                                                        //Variable de recorridos de los ciclos
int j;                                                                          //Variable de recorridos de los ciclos
float aux;                                                                      //variable de disntancia 
float aux_etiqueta;                                                             //variable de auxiliar para etiquetas                              
float potencia;                                                                 //Potencia para aplicación de fórmula
float raiz;                                                                     //Raiz para aplicación de fórmula
int label;                                                                      //Variable de información aire limpio o contaminado 
String salida="";                                                               //variable para mensaje de salida


 float matriz_k [3][k];                                                         //Matriz de k-vecinos
 for(;i<k;i++){                                                                 //Ciclo for para el recorrido                                                                  
  matriz_k[0][i]=i+1.00;  //  |   1 |   2   |   3   |                           //Número de vecinos cecanos                      
  matriz_k[1][i]=0; //     |  0  |   0   |   0   |                              //Etiquetas 
  matriz_k[2][i]=2500.0+i;// |2500 | 25001 | 25002 |                            //Almacena la menor distancia
  }
  i=0;

  float matriz_eti[2][etiquetas];                                               //Se crea una matriz para las dos etiquetas limpio-contaminado 
  for(;i<etiquetas;i++){                                                        //Cliclo for para el recorrido de columnas
      matriz_eti[0][i]=i+1.0; // |  1 |  2 |  3  |                              //Se llena las etiquetas para las columnas
      matriz_eti[1][i]=0.0;   // |  0 |  0 |  0  |                              //Fila 1, se le asigna ceros
    }

   for(;fil<tam_fil;fil++){                                                      //Ciclo for para el recorrido de las filas
      for(col=0;col<tam_col-1;col++){                                            //Ciclo para el recorrido de las columnas menos la ultima columna que corresponde a la etiqueta   
          potencia=potencia+pow(matriz[fil][col]-datos_prueba[col],2);           //Cálculo de la potencia entre clumnas
        }
        raiz=sqrt(potencia);                                                     //Cálculo de distancia entre los dos puntos
        potencia=0;                                                              //Reinicio de la variable potencia finalizado el ciclo
        
        if(raiz<matriz_k[2][k-1]){                                               //Condición para comparar la menor distancia entre los datos 
          matriz_k[2][k-1]=raiz;                                                 //Almacenamiento del nuevo valor de la distancia menor                     
          matriz_k[1][k-1]=matriz[fil][tam_col-1];                               //Signo de predicción de etiquetas
                                                                                 //Ordenamiento de la matriz por el método de la burbuja
          for(i=0;i<k;i++){                                                      //Recorrido de filas       
             for(j=i+1;j<k;j++){                                                 //Recorrido de columnas
               if(matriz_k[2][i]>matriz_k[2][j]){                                //Condicional que compara si el número actual es mayor ue el número siguiente de la matriz
                 // DISTANCIA
                  aux=matriz_k[2][i];                                            //Intercambiambio de valores 
                  matriz_k[2][i]=matriz_k[2][j];                                 //Número actual, se agrega el valor del número siguiente                           
                  matriz_k[2][j]=aux;                                            //El numero siguiente será el número actual
                  // ETIQUETA
                  aux_etiqueta=matriz_k[1][i];                                   //Intercambio del valor de la etiqueta pra ordenamiento
                  matriz_k[1][i]=matriz_k[1][j];                                 //Etiqueta actual, se agrega el valor del número siguiente 
                  matriz_k[1][j]=aux_etiqueta;                                   //Etiqueta siguiente será el número actual
                }
              } 
            } 
        } 
    } 
    //buscar etiqueta con mayor repitencia
    for(i=0;i<etiquetas;i++){                                                    //Recorrido de etiquetas 
      for(j=0;j<k;j++){                                                          //recorrido de los valores de k 
          if(matriz_eti[0][i]==matriz_k[1][j]){                                  //Condicional de igualdad de de los valores
            matriz_eti[1][i]++;                                                  //Aumento de recorrido
          }
        }
      }

    for(i=0;i<etiquetas-1;i++){
       if(matriz_eti[1][i]<matriz_eti[1][i+1])      // buscar el valor menor entre conteo de etiquetas
        label=(int)matriz_eti[0][i+1];              //asgina a label la etiqueta de mayor valor
        else 
        label=(int)matriz_eti[0][i];              //asgina a label la etiqueta de mayor valor
      }  
 switch(label){                                   //Se crea en menu para las etiquitas
  case 1:                                         //Etiqueta 1.
    lcd.clear();                                  //Se limpia la
    lcd.setCursor(0,0);                           //Ubicarse en la lcd en columnas y filas
    lcd.print("Aire Limpio");                     //Envío de mensaje limpio
    lcd.setCursor(0,1);                           //Posición en la LCD
    lcd.print(String("MQ7 ")+String (a));         //Se imprime en la lcd del sensor MQ7 y los valores del sensor
    delay(1000);                                  //Tiempo para una visualización
    lcd.clear();                                  //Se limpia la LCD
    lcd.setCursor(0,0);                           //Ubicarse la posición en la LCD
    lcd.print("Aire Limpio");                     //Envía mensaje del segundo sensor
    lcd.setCursor(0,1);                           //Ubicacion de la LCD
    lcd.print(String("MQ135 ")+String (b));       //Impresion en la lcd del sensor MQ135
    digitalWrite(led1,HIGH);                      //Prendido de led
  
  break;
  case 2:
    lcd.clear();                                  //Se limpia la lcd
    lcd.setCursor(0,0);                           //Ubicarse en la lcd en columnas y filas
    lcd.print("Aire Contaminado");                //Envía mensaje aire contaminado
    lcd.setCursor(0,1);                           //Posición en la LCD
    lcd.print(String("MQ7 ")+String (a));         //Se imprime en la lcd del sensor MQ7 y los valores del sensor
    delay(1000);                                  //Tiempo de visualización.
    lcd.clear();                                  //Se limpia en la lcd
    lcd.setCursor(0,0);                           //Ubicarse en la lcd
    lcd.print("Aire Contaminado");                //Envía mensaje
    lcd.setCursor(0,1);                           //Posición en la LCD   
    lcd.print(String("MQ135 ")+String (b));       //Impresion en la lcd del sensor MQ135
    digitalWrite(led2,HIGH);                      //Se activa el led cuando es aire contaminado
  break;
  }
  return label;
};
//PERRO GUARDIAN
void modo(){                              //Se crea el método modo
    wdt_enable(WDTO_4S);                  //Se activa el perro guardian 4s.
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);  //Seleccion modo sleep
    sleep_enable();                       //Activacion modo sleep
    sleep_mode();                         //Funcionamiento modo sleep 
    sleep_disable();                      //Desactivar modo sleep 
    wdt_disable();                        //Desactivar perro guiardian
}
void sistema(){                           //Método de reinicio
  delay(100);
  EEPROM.update(0,1);                     //Actualizacion dato principal del sistema
}
void encender(){
  resetFunc();                           //Funcion reiniciar arduino
}
