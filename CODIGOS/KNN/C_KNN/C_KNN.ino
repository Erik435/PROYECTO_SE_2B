/*
 * SISTEMAS EMBEBIDOS PROYECTO 2B
 * OBJETIVO: Ralizar el algoritmo de clasificación Knn a los datos de los sensores filtrados.
 * INTEGRANTES: Flores Erik, Martinez Juan
 */
#include "datos.h"                                                                          //Llamado a la ventana datos.                                                               
#include "prueba.h"                                                                         //Llamado a la ventana prueba. 

int respuesta;                                                                              //Creaci+oon de variable de relleno para cada operación realzada 
int cont=0;                                                                                 //Variable el número de filas de la matriz llamada
int porcent=0;                                                                              //Variable para relleno de valores de porcentaje      
int knn (int k, int etiquetas, int tam_col, int col_fil);                                   //Creación de la variable para los datos de clasificación  
void setup() {
Serial.begin(9600);                                                                         //Inicio de la comunicación Serial
  for(cont;cont<42;cont++){                                                     
    respuesta=knn(3,2,3,182);                                                               //Se rellena todos los valores para la clasificación de los datos numero de k(vecinos cercanos), numero de etiquetas, tamano de la matriz     
  }
  Serial.println(String("PORCENTAJE ")+String(porcent/42));                                 //Impresión de porcentaje del total de recorrido
}

void loop() {
}

int knn (int k, int etiquetas, int tam_col, int tam_fil){                                   //Definición de parámetros para el método KNN
float datos_prueba [3]={matriz1[cont][0],matriz1[cont][1],matriz1[cont][2]};                //Creación del vector el cual se va a compara 
int col;                                                                                    //Número de columnas de la matriz de los datos
int fil=0;                                                                                  //Número de filas de la matriz de los datos
int i=0;                                                                                    //Variable de recorridos de los ciclos
int j;                                                                                      //Variable de recorridos de los ciclos  
float aux;                                                                                  //variable de disntancia                                                                               
float aux_etiqueta;                                                                         //variable de auxiliar para etiquetas
float potencia;                                                                             //Potencia para aplicación de fórmula
float raiz;                                                                                 //Raiz para aplicación de fórmula  
int label;                                                                                  //Variable de información aire limpio o contaminado  
String salida="";                                                                           //variable para mensaje de salida
/*  
 *   matriz de k-vecinos
 *   |1   |2   |3  | -> # vecinos mas cercanos
 *   | 1  |   1| 2 | -> etiqueta correspondiente
 *   |0.12|0.18|025|-> valor de las k distancias menores
 */
 float matriz_k [3][k];                                                                     //Matriz de k-vecinos
 for(;i<k;i++){                                                                             //Ciclo for para el recorrido      
  matriz_k[0][i]=i+1.00;  //  |   1 |   2   |   3   |                                       //Número de vecinos cecanos    
  matriz_k[1][i]=0; //     |  0  |   0   |   0   |                                          //Etiquetas   
  matriz_k[2][i]=2500.0+i;// |2500 | 25001 | 25002 |                                        //Almacena la menor distancia 
  }
  i=0;
 /*
  *  matriz de etiquetas
  *  |1  |2  |3  | -> # de etiquetas
  *  |2  |1  |0  | -> el conteo de cada una de ellas con respecto a matriz k_vecinos   
  */
  float matriz_eti[2][etiquetas];                                                                     //Se crea una matriz para las dos etiquetas limpio-contaminado                                                       
  for(;i<etiquetas;i++){                                                                              //Cliclo for para el recorrido de columnas
      matriz_eti[0][i]=i+1.0; // |  1 |  2 |  3  |                                                    //Se llena las etiquetas para las columnas
      matriz_eti[1][i]=0.0;   // |  0 |  0 |  0  |                                                    //Fila 1, se le asigna ceros
    }

   for(;fil<tam_fil;fil++){                                                                           //Ciclo for para el recorrido de las filas
      for(col=0;col<tam_col-1;col++){                                                                 //Ciclo para el recorrido de las columnas menos la ultima columna que corresponde a la etiqueta        
          potencia=potencia+pow(matriz[fil][col]-datos_prueba[col],2);                                //Cálculo de la potencia entre clumnas  
        }
        raiz=sqrt(potencia);                                                                          //Cálculo de distancia entre los dos puntos
        potencia=0;                                                                                   //Reinicio de la variable potencia finalizado el ciclo
                                                                                                      
        if(raiz<matriz_k[2][k-1]){                                                                    //Condición para comparar la menor distancia entre los datos       
          matriz_k[2][k-1]=raiz;                                                                      //Almacenamiento del nuevo valor de la distancia menor 
          matriz_k[1][k-1]=matriz[fil][tam_col-1];                                                    //Signo de predicción de etiquetas
                                                                                                      //Ordenamiento de la matriz por el método de la burbuja
          for(i=0;i<k;i++){                                                                           //Recorrido de filas                                                                         
             for(j=i+1;j<k;j++){                                                                      //Recorrido de columnas
               if(matriz_k[2][i]>matriz_k[2][j]){                                                     //Condicional que compara si el número actual es mayor ue el número siguiente de la matriz
                  // DISTANCIA
                  aux=matriz_k[2][i];                                                                 //Intercambiambio de valores 
                  matriz_k[2][i]=matriz_k[2][j];                                                      //Número actual, se agrega el valor del número siguiente
                  matriz_k[2][j]=aux;                                                                 //El numero siguiente será el número actual   
                  //ETIQUETA                                                                          
                  aux_etiqueta=matriz_k[1][i];                                                        //Intercambio del valor de la etiqueta pra ordenamiento
                  matriz_k[1][i]=matriz_k[1][j];                                                      //Etiqueta actual, se agrega el valor del número siguiente                                                  
                  matriz_k[1][j]=aux_etiqueta;                                                        //Etiqueta siguiente será el número actual
                }
              } 
            } 
        }
    }
    
    //buscar etiqueta con mayor repitencia
    for(i=0;i<etiquetas;i++){                                                                        //Recorrido de etiquetas 
      for(j=0;j<k;j++){                                                                              //recorrido de los valores de k  
          if(matriz_eti[0][i]==matriz_k[1][j]){                                                      //Condicional de igualdad de de los valores  
            matriz_eti[1][i]++;                                                                      //Aumento de recorrido
          }
        }
      }

    for(i=0;i<etiquetas-1;i++){                                                                      //Recorrido para el núermo de las etiqueas 
       if(matriz_eti[1][i]<matriz_eti[1][i+1])                                                       //Buscar el valor menor entre conteo de etiquetas
        label=(int)matriz_eti[0][i+1];                                                               //Ssgina a label la etiqueta de mayor valor
        else 
        label=(int)matriz_eti[0][i];                                                                 //Asgina a label la etiqueta de mayor valor
      }

 //Condicional para detminar que tipo de etique es Puro o Contaminado
 switch(label){
  case 1:                                                                                            //Caso 1 - etiqueta "AIRE PURO"
    Serial.println("Puro");                                                                          //Envio de información "AIRE PURO" 
  break;
  
  case 2:                                                                                            //Caso 1 - etiqueta "AIRE CONTAMINADO"                                                        
    Serial.println("Contaminado");                                                                   //Envio de información "AIRE CONTAMINADO"
  break;
  }
  if(matriz1[cont][2]==label){
    porcent++;                                                                                       //Aumento de porcentaje de conteo de datos
  }
  return label;                                                                                      
};
