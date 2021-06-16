/*
 * PROYECTO SISTEMAS EMBEBIDOS- PROYECTO 2B
 * OBJETIVO: Demostrar el teorema de Bayes con datos filtrados del sensor.
 * INTEGRANTES: Flores Erik - Martinez Juan
 */
#include <ListLib.h>                                              //Llamado de libreeria para listar los datos                                             
#include "datos.h"                                                 //Llamamos a la ventana datos
#include "prueba.h"                                               //Llamamos a la ventan prueba
int resultado;                                                    //Se crea la variable para el resultado de etiqueta
int porcent;
List <int> list;                                                  //listar, tipo de dato, el nombre de lista
int cont;                                                         //Se crea la variable para el recorrido de la matriz1
void setup() {
  Serial.begin(9600);                                             //Se inicializa la comunicacion serial
  for(cont=0;cont<42;cont++){                                     //Recorrido para la matriz en cada posicion
  bayes();                                                        // llamada al metodo 
  }
  Serial.println("El porcentaje es ");                            //Impresion de mensaje
  Serial.println(porcent/42);                                     //Se imprimeel mensaje de porcentaje de datos procesados 
}

void loop() {  
}
void bayes(){                                                                  //Creación de metodo del teorema de Bayes
 list=0;                                                                       //Se encera la lista
 float datos_prueba [3]={matriz1[cont][0],matriz1[cont][1],matriz1[cont][2]}; // creacion de datos de prueba de ,os valores de la matriz
 int etiquetas=2;                                                             //Se crea el numero de etiquetas
 int columnas=3;                                                              //Se crea en numero de columnas
 int filas=182;                                                               //Se crea el numero de filas.
 float r=0.2;                                                                 //Se crea el valor de radio
 int i=0;                                                                     // variable de recorrido en matriz
 int j=0;                                                                     // variable de recorrido en matriz
 int k=0;                                                                     // variable de recorrido en matriz
 int t=0;                                                                     // variable de recorrido en matriz
 float p_x=0.0;                                                               // probabilidad marginal
 float distancia=0.0;                                                         //Inicializacion de variable entre puntos
 float sumatoria=0.0;                                                         //Variable para las sumatorias
 float normalizador=0.0;                                                      //Variable normalizar todos los datos
 float dist_mayor=0.0001;                                                     //Variable de distancia mayor
 int resultado;                                                               //Resultado de etiqueta
 float aux=0;                                                                 //Auxiliar de cambio de variable

   float prob [4][etiquetas];                                                 //Se crea matriz para probabilidad
   //Encerar matriz y asignar etiquetas a la fila 0
    for(i=0;i<4;i++){                                                         //Se crea el recorrido 4 sin la etiqueta
       for(j=0;j<etiquetas;j++){   // |    1   |   2    |    3   |            //Se asigna etiqutas a la fila0
          prob[i][j]=0;            // |    0   |   0    |    0   |            //Se encera la matriz
          if(i==0)                 // |    0   |   0    |    0   |            //Si la primera fila es =0
          prob[i][j]=j+1;          // |    0   |   0    |    0   |            //Se llena la primera fila con respecto a los valores en cada columna hasta llegar al numero de la etiqueta.
        }
      }
    //Sumar el valor del total por etiqueta en la matriz
    for(i=0;i<etiquetas;i++){               // |    1   |   2    |    3   |   //Recorrido de columnas con respecto al numero de etiquetas total.    
        for(j=0;j<filas;j++){               // |   40   |   40   |   40   |   //Recorrido en las filas
          if(matriz[j][columnas-1]==i+1)    // |    0   |   0    |    0   |   //Condicion para el llenado de los valores para la sumatoria 
            prob[1][i]++;                   // |    0   |   0    |    0   |   //Llenado de la fila 1 y aumnto de columnas
          }
      }

    //Encontrar la distancia mayor 
    for(i=0;i<filas;i++){                                                     //Recorrido de filas
       for(j=0;j<columnas-1;j++){                                             //Recorrido de columnas -1 porque inicia desde 0.
         sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2);             //Realizar la sumatoria de potencia, aplicando formula
        }
        distancia=sqrt(sumatoria);                                            //Raiz cuadrada para distancia entre dos puntos
        sumatoria=0;                                                          //Se inicializa la sumatoria en 0
        if(distancia>dist_mayor)                                              //condición de comparación dentro del circulo de radio
          dist_mayor=distancia;                                               //Encuentro distancia mayor
      }
      distancia=0;                                                            //Vuelve a iniciar a 0 para la comparación
    //Normalizar la distancia en toda la matriz 
    for(i=0;i<filas;i++){                                                     //Recorrido el numero de filas.
       for(j=0;j<columnas-1;j++){                                             //Recorrido en numero de columnas 
         sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2);             //Realizar la sumatoria de potencia
       }
        distancia=sqrt(sumatoria);                                            //Raiz cuadrada para distancia entre dos puntos
        sumatoria=0;                                                          //Sumatoria=0;
        normalizador=distancia/dist_mayor;                                    //Distancias entre 0 y 1 dos valores
        if(normalizador<r)                                                    //Si el valor esto dentro del rango
            list.Add(i);                                                      //Almancenar la fila de los datos que son parte de la circunferencia
    }
    //Sumar por etiqueta a todos los datos que se encuentran en la circuferencia
    for(i=0;i<list.Count();i++){                          // |    1   |   2    |    3   | //Recorrido de lista
      for(j=0;j<etiquetas;j++){                           // |   40   |   40   |   40   | //Recorrido de la etiqueta
          if(matriz[list[i]][columnas-1]==prob[0][j])     // |    4   |   1    |    0   | //Condicion para definir el numero de etiquetas con respecto a los valores
            prob[2][j]++;                                 // |    0   |   0    |    0   | //Conteo de valores para la fila dos con respecto a las columnas.
        }
      }
      //Probabilidades por cada etiqueta
      p_x=float(list.Count())/float(filas);                                               //Se relllena la probababilidad por cada etiqueta 
   for(k=0;k<etiquetas;k++){                                                              //Encontrar la probabilidad por etiqueta
      prob[3][k]=((prob[1][k]/filas)*(prob[2][k]/prob[1][k]))/p_x;                        //Se aplica la formula para rellenar la trecer fila con respecto a las 3 etiquetas
    }

      //Busqueda de probabilidad por etiqueta
      for(k=0;k<etiquetas;k++){                                                           //Recorrido de las etiquetas o columnas
         if(prob[3][k]>aux){                                                              //Condicion en la tercer fila y en cada colummna .
           resultado=int(prob[0][k]);                                                     //Se actualiza el valor de resultado
           aux=prob[3][k];                                                                //Se guarda el valor mayor
          }   
        }
    //Retorna el resultado de etiqueta
  Serial.println(resultado);                                                              //Se imprime el resultado si es puro o  no
  switch(resultado){                                                                      //Caso 1 o 2
    case 1:                                                                               //Caso1
      Serial.println("Aire Puro");                                                        //Impresion de Aire Puro
    break;
    case 2:                                                                               //Case 2
    Serial.println("Aire Contaminado");                                                   //Aire contaminado
    break;
    }
    if(resultado==matriz1[cont][2]){                                                      //Condicion para el porcentage de recorrido
      porcent++;                                                                          //Contador de aumento
    }
   r=0.2;
   i=0;                                                                                   // Variable de recorrido en matriz
   j=0;                                                                                   // Variable de recorrido en matriz
   k=0;                                                                                   // Variable de recorrido en matriz
   t=0;                                                                                   // Variable de recorrido en matriz
   p_x=0.0;                                                                               // Probabilidad marginal
   distancia=0.0; 
   sumatoria=0.0;
   normalizador=0.0;
   dist_mayor=0.0001;
   resultado;                                                                             // Resultado de etiqueta
   aux=0;                                                                                 // Auxiliar de cambio de variable
    return resultado;
 }
