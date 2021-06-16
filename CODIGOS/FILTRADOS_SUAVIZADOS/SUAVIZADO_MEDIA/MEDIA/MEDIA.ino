/*
 * CÓDIGO: PROYECTO 2B SISTEMAS EMBEBIDOS
 * OBJETIVO: Generar un filtro Suavizador-Media para la comparación de SNR.
 * INTEGRANTES: Flores Erik, Martinez Juan Diego.
 */
#define tamSE 120

extern double senialE[tamSE];                                               //Se llama los valores de la otra pestaña.
void grafica(void);                                                         //Se define el método de la gráfica
double senial_Sua[tamSE];
double nrs[tamSE];                                                          //Vector para la señal de ruido
void media(double *senial_E, double *senial_Sua, int tam_SE, int filter);   //Se dfine el metodo del suavizador media


void setup() {
  Serial.begin(9600);
}


void loop() {                                                               
  media ((double *)&senialE[0], (double *)&senial_Sua[0], (int) tamSE,9);   //Se inicializa el método del suavizador media y se rellena de 0 a los vectores
  grafica();                                                                //Se inicializa el método de la gráfica
  ruido();                                                                  //Se inicializa el metodo del ruido
  delay(100);                                                               //Tiempe establecido.
}

//Metodo Suavizado de la señal

void media (double *senial_E, double *senial_Sua, int tam_SE, int filter){   //Se crea el metodo con los valores de salida
  int i,j;
  for(i=(filter/2);i<tam_SE-(filter/2)-1;i++){                               //Se crea el ciclo de recorrido para cada posicion del vector a salir.
    senial_Sua[i]=0;                                                         //Se iguala a 0 el vector;
    for(j=-(filter/2);j<(filter/2);j++){                                     //Se crea el ciclo para el recorrido con la varibale j.
        senial_Sua[i]=senial_Sua[i]+senial_E[i+j];                           //Se realiza las operaciones con los valores guardados en cada posicion
      }
      senial_Sua[i]=senial_Sua[i]/filter;                                    //Señal resultante.
    }
  }
  //Metodo para el ruido
void ruido(){                                                                //Se crea el metodo de la señal de ruido
  double ruido1 [tamSE];                                                     //Se crea una señal con el tamaño de la señal
  double ruido2 [tamSE];                                                     //Se crea una señal con el tamaño de la señal
  for(int i=0;i<tamSE;i++){                                                  //Bucle for para el recorrido en todas las posiciones de la señal
    ruido1[i]=pow(senialE[i],2);                                             //funcion pow para calacular el valor de una potencia.
    ruido2[i]=pow((senialE[i]-senial_Sua[i]),2);                             //Se aplica la funcionj pow a la segunda señal
    nrs[i]=10*log(ruido1[i]/ruido2[i]);                                      //Se aplica formula para el SNR
    }
  }

void grafica(void){                                                         //puede ir sin void pero se pone para una manera mejor estrutura 
  int i;
  for(i=0;i<tamSE;i++){
    //Serial.println(senialE[i]);                                          //Señal sin filtrar impresion
    //Serial.println("FILTRADO");
    //Serial.println(senial_Sua[i]);                                        //Se imprime la señal suavizada
    //Serial.print(",");
    Serial.println(nrs[i]);                                            //Se imprime la SNR
    delay(50);
  }
}
