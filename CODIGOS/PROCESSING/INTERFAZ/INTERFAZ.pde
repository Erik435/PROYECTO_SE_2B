/*
*PROYECTO 2B SISTEMAS OPERATIVOS
*OBJETIVO: Realizar una interfaz para visualización de aire puro o contaminado desde arduino
*INTEGRANTES: Flores Erik, Martinez Juan
*/
import processing.serial.*;            //Se importa la libreria para la comunicacion serial
import ddf.minim.*;                    //Se importa la libreria

PImage img,img1,img2;                  //Se inicializa el tipo de dato para las imágenes
int alt = 0;                           //Se inicializa el valor de alt

Serial port;                           //Se creal el metodo de comunicacion serial
void setup(){
port=new Serial(this,"COM4",9600);     //Se define los parámetros para el puerto
 size (700,700);                       //Se define el tamaño de la pantalla
 background(#CCD3FA);                  //Se define el color de la pantalla
 img=loadImage("utn.png");             //Se carga la imagen
 img1=loadImage("airp.png");           //Se carga la imagen
 img2=loadImage("airc.png");           //Se carga la imagen
 fill(1);                              //Se define el color del texto
 textSize(25);                         //Tamaño del texto
 text("UNIVERSIDAD TÉCNICA DEL NORTE",135,50);  //Se envia el mensaje de encabezado con su posicion x,y
 text("SISTEMAS EMBEBIDOS 2B",215,90);          //Se envia el mensaje de encabezado con su posicion x,y
 text("DETECTOR DE GASES",230,130);             //Se envia el mensaje de encabezado con su posicion x,y
 text("Autores:",100,600);                      //Se envia el mensaje de nombre con su posicion x,y
 text("Flores Erik, Martinez Juan Diego",100,650);           //Se envia el mensaje de nombre con su posicion x,y
 regresion();                                   //Se llama al metodo
}
void draw(){
  fill(#D9D9DB);                                    //Se define Color del rectangulo
  rect(100,200,500,350);                        //Se dibuja un rectangulo en la pantalla con la posicion x,y anchura,altura
  image(img,50,30,80,80);                       //Se presenta la imagen en la ventana de visualizacion
  regresion();                                  //Se llama al metodo
}
void regresion(){                               //Se crea el método de regresion
  
    switch(alt){                                //Se crea el menu para la recepecion de informacion
      case 0:                                   //Caso 0 
      fill(1);                                  //Se define el color del texto
      textSize(25);                             //Se define el tamaño del texto
      text("ANALIZANDO ÁREA",223,300);           //Se envia el mensaje con su ubicación.
      break;                                    //Finaliza el caso
      
      case 1:                                   //Caso 1
      fill(1);                                  //Se define el color del texto
      textSize(25);                             //Se define el tamaño del texto
      text(" EL AIRE ESTÁ LIMPIO",215,300);              //Se envia el mensaje con su ubicación.        
      image(img1,270,310,120,120);              //Se envia una imágen demostrando el aire limpio
      break;                                    //Se finaliza el caso
      
      case 2:                                   //Caso 2
      fill(1);                                  //Se define el color del texto
      textSize(25);                             //Se define el tamaño del texto
      text("EL AIRE ESTÁ CONTAMINADO",208,300);         //Se envia el mensaje con su ubicación. 
      image(img2,300,310,120,120);              //Se envia una imágen demostrando el aire limpio
      break;                                    //Se finaliza el caso
    }
}
void serialEvent(Serial port){                  //Se crea método para la comunicación
  alt = port.read();                            //Lee el dato mediante la comunicacion serial.
  println(alt);                                 //Se imprime el dato leído
}
