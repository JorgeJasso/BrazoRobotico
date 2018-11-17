//--------------------------------------------------------------------LIBRERIAS A UTILIZAR.

#include <Servo.h> // Incluimos la biblioteca Servo


//-------------------------------------------------------------------DECLARACIÓN DE VARIABLES.

//----------PINES PWM a utilizar
const int PIN_PINZA = 5; //Indica el pin que usará la pinza.
const int PIN_MUNECA = 6; //Indica el pin que usará la muñeca.
const int PIN_CODO = 9; //Indica el pin que usará el codo.
const int PIN_HOMBRO = 10; //Indica el pin que usará el hombro.


//----------Variables para los Servomotores
const char CARACTERES[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Se declara un arreglo de némeros que servira para convertir la información ASCII del Serial a números decimales.
const int TIEMPO = 50; // definimos el tiempo entre pasos del servo (velocidad).
const int PASOS = 2; //Se utiliza para definir cuando avanzará el servo en cada movimiento.
int posicionServoPinza = 60; //Se define el valor inicial de la pinza.
int posicionServoMuneca = 18; //Se define el valor inicial de la muñeca.
int posicionServoCodo = 90; //Se define el valor inicial para el codo.
int posicionServoHombro = 180; //Se define el valor inicial para el hombro.
int totalGrados = 0; //Serán los grados a donde se moverá el servo.

Servo servoPinza, servoMuneca, servoCodo, servoHombro; // Definimos los servos que vamos a utilizar

//----------Variables para ARREGLOS DINAMICOS
boolean realizarMovimiento = false; //Determina cuando se puede mover el brazo y cuando no.
volatile boolean realizarSecuencia = false; //Determina cuando realizar la secuencia completa.
String valor = ""; //Almacena los caracteres del Serial.
int posicion = 0; //Es la posicion de la lista que estará leyendo.
size_t cont; //Se especificara los elementos que tiene la lista.
size_t capacidad; //Variable para saber el tamaño de la lista.
String* lista; //Declara un arreglo que servira para almacenar todos los mensajes.


//--------------------------------------------------------------------------SETUP

void setup() {
  Serial.begin(9600); //Se inicia la comunicación serial en 9600.
  crearLista(100); //Crea la lista con un valor por defecto de 100.
  
  servoPinza.attach(PIN_PINZA);//Se indica el pin que utiliza servoPinza.
  servoMuneca.attach(PIN_MUNECA);//Se indica el pin que utiliza servoMuneca.
  servoCodo.attach(PIN_CODO);//Se indica el pin que utiliza servoCodo.
  servoHombro.attach(PIN_HOMBRO);//Se indica el pin que utiliza servoHombro.
  posicionesIniciales();//Posiciona el brazo en las posiciones iniciales por defecto.
}


//----------------------------------------------------------------------------LOOP

void loop() {
  while (Serial.available() > 0) { //Mientras haya caracteres que leer entrará al ciclo.
    delay(3);
    int dato = Serial.read(); //Lee el dato.
    if (dato == 44 || dato == 59) { //Compara si el valor ASCII del dato es 44 o 59, es decir una coma o punto y coma respectivamente.
      agregar(valor); //Agrega el valor a la lista.
      realizarMovimiento = true; //Indica que ya hay un movimiento por realizar.
      valor = "";
    } else {
      if (dato == 32) { //Si fue un espacio es decir 32 en codigo ASCII
        realizarSecuencia = true; //Indica que es momento de realizar toda la secuencia.
        valor = "";
      } else {
        valor = valor + ASCII_a_Numero(dato);//Concatenas los caracteres en valor.
      }
    }
  }
  if (realizarMovimiento) { //Realiza un movimiento individual en un servo.
    int val = lista[posicion].toInt(); //Se lee la primera posicion de la lista que almacena que servo se tiene que mover.
    posicion++;
    int tiempoMov = lista[posicion].toInt(); //Indica el tiempo que se tiene que mover el servo.
    posicion++;
    movimientoBrazo(val, tiempoMov); //Mueve el servo en la posicion y tiempo indicados.
    realizarMovimiento = false; //Indica que ya no hay movimientos por realizar.
  }
  if (realizarSecuencia) { //Si es verdadero quiere decir que se tiene que realizar toda la secuencia.
    int i = 0;
    int val = 0;
    int tiempoMov = 0;
    posicionesIniciales(); //Antes de realizar la secuencia se dirigen los servos a su posiciones inicial.
    while (realizarSecuencia) { //La repite indefinidamente hasta que se precione el boton de paro.
      val = lista[i].toInt();
      i++;
      tiempoMov = lista[i].toInt();
      movimientoBrazo(val, tiempoMov);
      i++;
      if (i == cont) {
        i = 0;
        posicionesIniciales(); //Cuando se haya leido la ultima posicion del servo se tendra que ir de nuevo a la posicion inicial de los servos.
      }
    }
  }
}


//--------------------------------------------------------------------CREACIÓN DE FUNCIONES


// Se define la función que servirá para subir el hombro.
void levantarHombro(int grados) {
  totalGrados = posicionServoHombro + grados;
  if  (totalGrados < 180) {
    for (; posicionServoHombro <= totalGrados; posicionServoHombro += PASOS) {
      servoHombro.write(posicionServoHombro);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoHombro <= 180; posicionServoHombro += PASOS) {
      servoHombro.write(posicionServoHombro);
      delay(TIEMPO);
    }
  }
}

// Se define la función que servirá para bajar el hombro.
void bajarHombro(int grados) {
  totalGrados = posicionServoHombro - grados;
  if (totalGrados > 90) {
    for (; posicionServoHombro  >= totalGrados; posicionServoHombro -= PASOS) {
      servoHombro.write(posicionServoHombro);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoHombro >= 90; posicionServoHombro -= PASOS) {
      servoHombro.write(posicionServoHombro);
      delay(TIEMPO);
    }
  }
}

// Se define la función que servirá para subir el codo.
void subirCodo(int grados) {
  totalGrados = posicionServoCodo - grados;
  if (totalGrados > 0) {
    for (; posicionServoCodo  >= totalGrados; posicionServoCodo -= PASOS) {
      servoCodo.write(posicionServoCodo);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoCodo >= 0; posicionServoCodo -= PASOS) {
      servoCodo.write(posicionServoCodo);
      delay(TIEMPO);
    }
  }
}

// Se define la función que servirá para bajar el codo.
void bajarCodo(int grados) {
  totalGrados = posicionServoCodo + grados;
  if  (totalGrados < 180) {
    for (; posicionServoCodo <= totalGrados; posicionServoCodo += PASOS) {
      servoCodo.write(posicionServoCodo);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoCodo <= 180; posicionServoCodo += PASOS) {
      servoCodo.write(posicionServoCodo);
      delay(TIEMPO);
    }
  }
}

// Girará a la izquierda la muñeca.
void izquierdaMuneca(int grados) {
  totalGrados = posicionServoMuneca - grados;
  if (totalGrados > 0) {
    for (; posicionServoMuneca  >= totalGrados; posicionServoMuneca -= PASOS) {
      servoMuneca.write(posicionServoMuneca);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoMuneca >= 0; posicionServoMuneca -= PASOS) {
      servoMuneca.write(posicionServoMuneca);
      delay(TIEMPO);
    }
  }
}

// Girará a la derecha la muñeca.
void derechaMuneca(int grados) {
  totalGrados = posicionServoMuneca + grados;
  if  (totalGrados < 115) {
    for (; posicionServoMuneca <= totalGrados; posicionServoMuneca += PASOS) {
      servoMuneca.write(posicionServoMuneca);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoMuneca <= 115; posicionServoMuneca += PASOS) {
      servoMuneca.write(posicionServoMuneca);
      delay(TIEMPO);
    }
  }
}

// Esta función permite que la pinza se abra.
void abrirPinza(int grados) {
  totalGrados = posicionServoPinza + grados;
  if  (totalGrados < 120) {
    for (; posicionServoPinza <= totalGrados; posicionServoPinza += PASOS) {
      servoPinza.write(posicionServoPinza);
      delay(TIEMPO);
    }

  } else {
    for ( ; posicionServoPinza <= 120; posicionServoPinza += PASOS) {
      servoPinza.write(posicionServoPinza);
      delay(TIEMPO);
    }
  }
}

// Esta función permite que la pinza se cierre.
void cerrarPinza(int grados) {
  totalGrados = posicionServoPinza - grados;
  if (totalGrados >= 20) {
    for (; posicionServoPinza  >= totalGrados; posicionServoPinza -= PASOS) {
      servoPinza.write(posicionServoPinza);
      delay(TIEMPO);
    }
  } else {
    for ( ; posicionServoPinza >= 20; posicionServoPinza -= PASOS) {
      servoPinza.write(posicionServoPinza);
      delay(TIEMPO);
    }
  }
}

// Se utiliza para determinar que servo mover, donde el boton y tiempoMov es la información que viene desde el serial.
void movimientoBrazo(int boton, int tiempoMov) {
  int grados = 0;
  switch (boton) {
    case 0: //Base gira a la izquierda

      break;
    case 1: //Base gira a la derecha

      break;
    case 2: //Hombro levantar
      grados = milisegundnosAGrados(tiempoMov);
      levantarHombro(grados);
      break;
    case 3: //Hombro bajar
      grados = milisegundnosAGrados(tiempoMov);
      bajarHombro(grados);
      break;
    case 4: //subir codo
      grados = milisegundnosAGrados(tiempoMov);
      subirCodo(grados);
      break;
    case 5: //Bajar codo
      grados = milisegundnosAGrados(tiempoMov);
      bajarCodo(grados);
      break;
    case 6://Muñeca gira izquierda
      grados = milisegundnosAGrados(tiempoMov);
      izquierdaMuneca(grados);
      break;
    case 7://Muñeca gira derecha
      grados = milisegundnosAGrados(tiempoMov);
      derechaMuneca(grados);
      break;
    case 8://Pinza abrir
      grados = milisegundnosAGrados(tiempoMov);
      abrirPinza(grados);
      break;
    case 9://Pinza cerrar
      grados = milisegundnosAGrados(tiempoMov);
      cerrarPinza(grados);
      break;
  }
}

//Esta funcion convierte en grados los milisegundos que se le pasen en el parametro, para asi indicar cuantos grados se tiene que mover un servo.
int milisegundnosAGrados(int milisegundos) {
  int resultado;
  milisegundos = milisegundos * 6;
  resultado = (milisegundos * 5) / 1800;
  return resultado;
}

//Indica las posiciones iniciales que tiene todos los servos por defecto.
void posicionesIniciales() {
  Serial.println("Posiciones iniciales");
  delay(500);
  servoPinza.write(60);
  delay(500);
  servoMuneca.write(18);
  delay(500);
  servoCodo.write(90);
  delay(500);
  servoHombro.write(145);
  delay(500);
}
