//--------------------------------------------------------------------LIBRERIAS A UTILIZAR.
#include <Servo.h> // Incluimos la biblioteca Servo
#include <LiquidCrystal.h> //Libreria para utilizar el display LCD.
#include <EEPROM.h> //Libreria para almacenar en memoria.

//-------------------------------------------------------------------DECLARACIÓN DE VARIABLES.
LiquidCrystal lcd(52, 50, 48, 46, 44, 42); //Se indican los pines que esta utilizando el LCD.

//----------PINES PWM a utilizar
const int PIN_PINZA = 5; //Indica el pin que usará la pinza.
const int PIN_MUNECA = 6; //Indica el pin que usará la muñeca.
const int PIN_CODO = 9; //Indica el pin que usará el codo.
const int PIN_HOMBRO = 10; //Indica el pin que usará el hombro.
const int BOTON_PARO = 20; //Indica cuando se parara la secuencia
const int BOTON_RESTABLECER = 21; //Indica cuando se puede restablecer la secuencia.

//----------Variables para los Servomotores
const char CARACTERES[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Se declara un arreglo de némeros que servira para convertir la información ASCII del Serial a números decimales.
const int TIEMPO = 50; // definimos el tiempo entre pasos del servo (velocidad).
const int PASOS = 2; //Se utiliza para definir cuando avanzará el servo en cada movimiento.
int posicionServoPinza = 60; //Se define el valor inicial de la pinza.
int posicionServoMuneca = 18; //Se define el valor inicial de la muñeca.
int posicionServoCodo = 90; //Se define el valor inicial para el codo.
int posicionServoHombro = 180; //Se define el valor inicial para el hombro.
int totalGrados = 0; //Serán los grados a donde se moverá el servo.
long grados = 0;
Servo servoPinza, servoMuneca, servoCodo, servoHombro; // Definimos los servos que vamos a utilizar

//----------Variables para motor a pasos
const int IN1 = 4; //Se define el pin para un motor
const int IN2 = 3; //Se define el pin para un motor
const int IN3 = 2; //Se define el pin para un motor
const int IN4 = 1; //Se define el pin para un motor
const int PASO [4][4] =//Define las posiciones que pueden tomar el motor a pasos.
{ {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};
int Steps = 0;
int steps_left = 4095;
int posicionInicialMotor = -2;

//----------Variables para ARREGLOS DINAMICOS
boolean realizarMovimiento = false; //Determina cuando se puede mover el brazo y cuando no.
volatile boolean realizarSecuencia = false; //Determina cuando realizar la secuencia completa.
String valor = ""; //Almacena los caracteres del Serial.
int posicion = 0; //Es la posicion de la lista que estará leyendo.
size_t cont; //Se especificara los elementos que tiene la lista.
size_t capacidad; //Variable para saber el tamaño de la lista.
String* lista; //Declara un arreglo que servira para almacenar todos los mensajes.

//----------Variables para guardar en memoria.
int Direccion = 0; //Se crea una variable con el valor de la posición de memoria en la que se va a almacenar el byte.

byte Val1;//Se crean una variable para leer los valores de la memoria EEPROM
byte Val2;//Se crean una variable para leer los valores de la memoria EEPROM

//--------------------------------------------------------------------------SETUP

void setup() {
  Serial.begin(9600); //Se inicia la comunicación serial en 9600.
  crearLista(100); //Crea la lista con un valor por defecto de 100.

  pinMode(52, OUTPUT); //He establecido el pin 52 como la alimentación del LED de la pantalla LCD.
  digitalWrite(52, HIGH); //Enciende el LED.
  lcd.begin(16, 2); //Se inicia el LCD.

  pinMode(BOTON_PARO, INPUT_PULLUP); //Establece la entrada del BOTON_PARO.
  attachInterrupt(digitalPinToInterrupt(BOTON_PARO), paro, LOW); //Se declara una interrupcion en el pin 20 que llamara la ISR paro.
  pinMode(BOTON_RESTABLECER, INPUT_PULLUP); //Establece la entrada del BOTON_RESTABLECER.
  attachInterrupt(digitalPinToInterrupt(BOTON_RESTABLECER), restablecer, LOW); //Se declara una interrupcion en el pin 21 que llamara la ISR restablecer.

  servoPinza.attach(PIN_PINZA);//Se indica el pin que utiliza servoPinza.
  servoMuneca.attach(PIN_MUNECA);//Se indica el pin que utiliza servoMuneca.
  servoCodo.attach(PIN_CODO);//Se indica el pin que utiliza servoCodo.
  servoHombro.attach(PIN_HOMBRO);//Se indica el pin que utiliza servoHombro.

  pinMode(IN1, OUTPUT);//Se definen los pines de salida para el motor a pasos de salida.
  pinMode(IN2, OUTPUT);//Se definen los pines de salida para el motor a pasos de salida.
  pinMode(IN3, OUTPUT);//Se definen los pines de salida para el motor a pasos de salida.
  pinMode(IN4, OUTPUT);//Se definen los pines de salida para el motor a pasos de salida.
  posicionesIniciales();//Posiciona el brazo en las posiciones iniciales por defecto.
  
  //Se almacena la información a guardar en un byte.
  byte Informacion = B11001;// La “B” indica que el formato es binario
}


//----------------------------------------------------------------------------LOOP

void loop() {
  while (Serial.available() > 0) { //Mientras haya caracteres que leer entrará al ciclo.
    delay(3);
    int dato = Serial.read(); //Lee el dato.
    if (dato == 44 || dato == 59) { //Compara si el valor ASCII del dato es 44 o 59, es decir una coma o punto y coma respectivamente.
      agregar(valor); //Agrega el valor a la lista.
      realizarMovimiento = true; //Indica que ya hay un movimiento por realizar.
	  EEPROM.write(Direccion, Informacion);
      EEPROM.write(Direccion + 1, valor);
      valor = "";
    } else {
      if (dato == 32) { //Si fue un espacio es decir 32 en codigo ASCII
        realizarSecuencia = true; //Indica que es momento de realizar toda la secuencia.
      } else {
        if (dato == 101) { //Sirve para ver cuando se quiere borrar la secuencia
          cont = 0;
          posicion = 0;
        } else {
          valor = valor + ASCII_a_Numero(dato);//Concatenas los caracteres en valor.
        }
      }
    }
  }
  if (realizarMovimiento) { //Realiza un movimiento individual en un servo.
    lcd.clear(); //Se limpia el LCD
    lcd.setCursor(0, 0); //Se posiciona en el renglon 1
    lcd.print("Estado:MOVIENDO");
    lcd.setCursor(0, 1); //Se posiciona en el renglon 1
    lcd.print("SERVO.");
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
    lcd.clear(); //Se limpia el LCD
    lcd.setCursor(0, 0); //Se posiciona en el renglon 1
    lcd.print("Estado:EJECUCION");
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
      delay(700);
    }
  }
}


//--------------------------------------------------------------------CREACIÓN DE FUNCIONES

/*
  La función crearLista recibe un parametro de la capacidad que sera el tamaño por defecto con la que empezará la lista, asi mismo se establece el cont
  a 0 indicando que aun no se encuentra ningún elemento en la lista.
*/
void crearLista(size_t parametroCapacidad) {
  lista = new String[parametroCapacidad];
  capacidad = parametroCapacidad;
  cont = 0;
}

/*
  La función agregar permite como su nombre lo indica agregar nuevos elemntos a la lista sin antes verificar si el cont (elementos existentes en la lista)
  es menor a la capacidad, de ser asi se agrega el elemento a la lista aumentando cont, y en caso contrario se llama a la función de rescalar la lista
  para permitir que se puedan almacenar más elementos.
*/
void agregar(String mensajeNuevo) {
  ++cont;
  if (cont > capacidad) {
    size_t nuevoTam = capacidad * 2;
    rescalar(nuevoTam);
  }
  lista[cont - 1] = mensajeNuevo;
}

/*
  Una vez que se haya comprobado que no hay espacio disponible en la lista para agregar elementos se procede a rescalarla esto para que tenga un
  tamaño mayor y asi nuevos elementos se puedan agregar sin problemas. Para realizar esto se borra crea una lista temporal con una mayor capacidad, se borra
  la lista anterior y por ultimo se asigna la lista temporal a la original.
*/
void rescalar(size_t nuevaCapacidad) {
  String* listaTemporal = new String[nuevaCapacidad];
  memmove(listaTemporal, lista, cont  * sizeof(int));
  delete[] lista;
  capacidad = nuevaCapacidad;
  lista = listaTemporal;
}

/*
  Debido a que las entradas recibidas por el Serial son numeros se tiene que realizar una conversion para devolver el valor original, esto se logra por el
  arreglo CARACTERES donde se definen los caracteres que el programa puede agregar.
  Se resta 48 a la entrada debido a que en el codigo ASCCI el primer numero es 48 y como nuestra lista comienza en 0
  se debe restar 48 para acceder al caracter que el Serial nos manda.
*/
char ASCII_a_Numero(int entrada) {
  entrada = entrada - 48;
  return CARACTERES[entrada];
}

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
  switch (boton) {
    case 0: //Base gira a la izquierda
      delay(30);
      steps_left = (tiempoMov / 5);
      if (steps_left > 4095) {
        steps_left = 4095;
      }
      while (steps_left > 0) {
        Serial.println("Girando izquierda");
        digitalWrite( IN1, PASO[Steps][0] );
        digitalWrite( IN2, PASO[Steps][1] );
        digitalWrite( IN3, PASO[Steps][2] );
        digitalWrite( IN4, PASO[Steps][3] );
        Steps++;
        Steps = ( Steps + 4 ) % 4 ;
        steps_left-- ;  // Un paso menos
        posicionInicialMotor++;
      }
      break;
    case 1: //Base gira a la derecha
      delay(30);
      steps_left = (tiempoMov / 5);
      if (steps_left > 4095) {
        steps_left = 4095;
      }
      while (steps_left > 0) {
        Serial.println("Girando derecha");
        digitalWrite( IN1, PASO[Steps][0] );
        digitalWrite( IN2, PASO[Steps][1] );
        digitalWrite( IN3, PASO[Steps][2] );
        digitalWrite( IN4, PASO[Steps][3] );
        Steps--;
        Steps = ( Steps + 4 ) % 4 ;
        steps_left-- ;  // Un paso menos
        posicionInicialMotor--;
      }
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
  delay(500);
  while (posicionInicialMotor != -2) {
    if (posicionInicialMotor > 0) {
      Steps--;
      posicionInicialMotor--;
    } else {
      Steps++;
      posicionInicialMotor++;
    }
    Steps = ( Steps + 4 ) % 4 ;
    Serial.print("Pasos: ");
    Serial.println(Steps);
    Serial.print("Posicion motor: ");
    Serial.println(posicionInicialMotor);
    digitalWrite( IN1, PASO[Steps][0] );
    digitalWrite( IN2, PASO[Steps][1] );
    digitalWrite( IN3, PASO[Steps][2] );
    digitalWrite( IN4, PASO[Steps][3] );
  }
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

//ISR que permite detener el proceso asignando false a la variable realizarSecuencia.
void paro() {
  realizarSecuencia = false;
  lcd.clear(); //Se limpia el LCD
  lcd.setCursor(0, 0); //Se posiciona en el renglon 1
  lcd.print("Estado: PARO DE");
  lcd.setCursor(0, 1); //Se posiciona en el renglon 1
  lcd.print("EMERGENCIA.");
}

//ISR que permite restablecer el proceso despues de un paro.
void restablecer() {
  realizarSecuencia = true;
}
