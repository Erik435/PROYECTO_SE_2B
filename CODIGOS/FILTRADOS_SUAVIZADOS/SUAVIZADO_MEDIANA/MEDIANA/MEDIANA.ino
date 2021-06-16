/*
 * CÓDIGO: PROYECTO 1B SISTEMAS EMBEBIDOS
 * OBJETIVO: Generar un filtro Suavizador-Mediana de la señal Cardica.
 * INTEGRANTES: Flores Erik, Martinez Juan Diego.
 */
#define tamSE 120

extern double senialE[tamSE];             //Se llama los valores de la otra pestaña.
void median_F();                          //Se define el metodo para la suavilizacion
void grafica(void);                       //Se define el método de la gráfica
double senial_Sua[tamSE];
double nrs[tamSE];                        //Vector para la señal de ruido
void setup() {
  Serial.begin(9600);
}


void loop() {
  median_F();           //Se inicializa el método para Suavizar.
  grafica();            //Se inicializa el método de la gráfica
  ruido();              //Se inicializa el metodo del ruido
  delay(100);           //Tiempe establecido.
}

//Metodo Suavizado de la señal

void median_F (){
  float varVolt = 1.1218;           //Deinimios el valor de la variable para aplicar en la formula
  float varProcess = 1e-2;          //Se define el valor de variable del proceso de suavizador
  float Pc =0.0;                    //Se define variable a llenar.
  float G =0.0;                     //Se define variable a llenar.
  float P = 1.0;                    //Se define la variable P=1  en float   
  float Xp = 0.0;                   //Se define variable a llenar.
  float Zp =0.0;                    //Se define variable a llenar.
  float Xe =0.0;                    //Se define variable a llenar.
  int i;                            //Variable de recorrido
  for(i=0;i<tamSE;i++){           //Ciclo para tomar todas las posiciones de la señal
    Pc = P+varProcess;              //Se llena la variable Pc para cada posicion del vectr
    G =Pc/(Pc+varVolt);             //Se obtiene el valor de G.
    P=(1-G)*Pc;                     //Se actualiza el valor de P.
    Xp=Xe;                          //Igualacion de variables para poder sumar en la señal de salida.
    Zp=Xp;                          //Igualacion de variables para poder sumar en la señal de salida.
    senial_Sua[i]=(G*(senialE[i]-Zp)+Xp)*4;//Se obtiene la señal suavizada.
  }
}

void ruido(){                                      //Se crea el metodo de la señal de ruido
  double ruido1 [tamSE];                           //Se crea una señal con el tamaño de la señal
  double ruido2 [tamSE];                           //Se crea una señal con el tamaño de la señal
  for(int i=0;i<tamSE;i++){                        //Bucle for para el recorrido en todas las posiciones de la señal
    ruido1[i]=pow(senialE[i],2);                   //funcion pow para calacular el valor de una potencia.
    ruido2[i]=pow((senialE[i]-senial_Sua[i]),2);   //Se aplica la funcionj pow a la segunda señal
    nrs[i]=10*log(ruido1[i]/ruido2[i]);            //Se aplica formula para el SNR
    }
  }

void grafica(void){ //puede ir sin void pero se pone para una manera mejor estrutura 
  int i;
  for(i=0;i<tamSE;i++){
    Serial.print(senialE[i]+1000);        //Señal sin filtrar impresion
    Serial.print(",");
    Serial.print(senial_Sua[i]+500);      //Se imprime la señal suavizada
    Serial.print(",");
    Serial.println(nrs[i]+200);           //Se imprime la SNR
    delay(5);
  }
}
