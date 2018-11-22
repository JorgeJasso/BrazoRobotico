# Brazo Robótico de 5 Ejes
## Presentación 
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/Presentacion.png">
## Introducción
> El siguiente proyecto consiste en un sistema para controlar y programar un Brazo Robot, simulando las funciones básicas de un robot industrial. 
El robot tiene dos funciones básicas:
*  Programar:  Registrar las posiciones de los brazos en tres dimensiones (cada registro es un "paso", cada registro es una serie de pasos).
*  Ejecutar : Se realiza en secuencia las posiciones registradas en el programa. El robot ejecta el programa hasta que se oprima el boton ABORTAR.

Estas son algunas de las características  principales del sistema:
* El proyecto se usa para controlar robots con 5 DOF ("Grados de libertas").
* El robot se controlar en modo "REMOTO" es decir a traves de un programa java por medio de un puerto serial.
* La información para el usuario se proporciona a traves de una pantalla LCD.
* Contiene un boton de paro de emergencia (Físico).
* Si existe un fallo de energía, despues de restablecerse la corriente el robot continua el programa (auqnue este no este conectado a la aplicación).

Los brazos robóticos  se pueden clasificar de acuerdo con el número de "articulaciones" o "grados de libertad" que tienen.
El brazo que ocuparemos es de 5 DOF:
* La base, que gira el brazo 360 grados.
* El hombro, es el responsable de levantar o bajar el brazo verticalmente.
* El codo, hará que el brazo avance o retroceda.
* La muñeca hará que el gire la pinza.
* La pinza funciona abriendose o cerrandose para agarrar cosas.

## Materiales
De Hardware
* Protoboard
* Arduino Mega 2560
* Display LCD 16x2
* 4 servo motores sg90
* 1 motor paso a paso
* Driver ULN2003 SMD
* chasis para el robot
* tuercas y tornillos milimétricos para anclaje
* una llave allen
* Potenciometro 10k
* 2 Push-Buttons
* Resistencias 330 ohms
* una bateria de 5V
* Cables Dupont(Jumpers) macho macho
* Cables de corriente
* Cable USB para arduino
* Computadora

De Software
* Arduino IDE
* OpenJDK
* OpenJRE
* Netbeans IDE
* Librería <LiquidCrystal.h>
* Librería RXTX

## Instalación de herramientas

### Instalación de Arduino IDE
Arduino IDE no se encuentra en los repositorios oficiales de Ubuntu, al menos la última versión, por lo que tenemos que utilizar la web oficial del Proyecto para conseguir este IDE. 
 https://www.arduino.cc/en/Main/OldSoftwareReleases 
 El archivo está comprimido y hay que extraerlo en una carpeta adecuada, recordando que se ejecutará desde allí.
 Una vez que tengamos esto, en la terminal escribimos lo siguiente:
```sh
$ sudo chmod +x install.sh 
```
Esta orden hará que el archivo de instalación pueda ejecutarse sin tener que ser root. Ahora ejecutamos en la terminal lo siguiente:
``` sh
$ ./install.sh 
```
Esto hará que comience la instalación de Arduino IDE en nuestro Ubuntu. Tras obedecer las órdenes del asistente y esperar varios segundos (o minutos, dependiendo del ordenador). Y ya está, ya tendremos Arduino IDE instalado en nuestro Ubuntu y un acceso directo en nuestro escritorio.

```sh
$ npm install --production
$ NODE_ENV=production node app
```

### Instalación de OpenJDK y OpenJRE

Abrimos la terminal y ejecutamos las siguientes instrucciones:
``` sh 
$ sudo apt-get install openjdk-8-jre openjdk-8-jdk
```
Al finalizar ejecutamos la siguiente instruccion para verificar la version instalada.
```sh
$ java -version
```
En caso de presentar el siguiente error:
No se pudo bloquear /var/lib/dpkg/lock – open (11: Recurso no disponible temporalmente). EJECUTAR los siguientes comandos: y volver a intentar la instalación.
``` sh
$ sudo fuser -vki  /var/lib/dpkg/lock
$ sudo rm -f /var/lib/dpkg/lock
$ sudo dpkg --configure -a
```

### Instalación de Netbeans IDE
Ir a la página oficial y descargar la última version de netbeans en  https://netbeans.org/downloads/start.html?platform=linux&lang=es&option=all.
Se extrae el archivo de la carpeta y se ejecuta en la terminal
```sh
$ sudo chmod +x netbeans-8.2-linux.sh
$ sudo ./netbeans-8.2-linux.sh
```
Ya iniciado el instalador nos permite realizar en un entorno gráfico, se recomienda quitar las opciones para instalar Apache Tomcat y GlassFish por el momento. y dar clic en “Next” hasta terminar el proceso de instalación.
Por ultimo Ya en nuestras aplicaciones buscamos “NetBeans IDE 8.2”, esperamos que inicie.

### Instalación de librería RXTX
Ejecutamos en la terminal los siguientes comandos.
```sh
$ sudo apt-get install librxtx-java
$ sudo cp -r /usr/lib/jni/librxtxSerial.so /usr/lib/x86_64-linux-gnu
$ sudo cp -r /usr/lib/jni/librxtxSerial.so /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64
```
### Instalación de la librería  LiquidCrystal
Descarga la libreria <LiquidCristal.h>, extrae los archivos de la carpeta comprimida y posterirormente pega toda la carpeta en las librerias de arduino.
https://playground.arduino.cc/Main/LiquidCrystal

## Montaje del circuito
### Display LCD y potenciometro
 * Conecte un jumper en la tierra del Arduino al negativo del Protoboard y otro jumper del voltaje al positivo.
 * Con el cable eléctrico debe puentear el negativo para que pase al otro lado del Protoboard.
 * Conecte el display LCD en el protoboard  conectando con cables de corriente los pines (VSS, RW, D0, D1, D2, D3, K)  a tierra y los pines (VDD, A) a voltaje, este ultimo mediante una resistencia. 
 * Conectamos el potenciometro al protoboard con cables de corriente la pata izquierda a voltaje y la pata derecha a tierra. la pata central ca conectaremos con el pin V0 del displya LCD.
 * conectar con cables jumpers los pines (RS, E, D4, D5,D6,D7) del display LCD  a los pines PWM (52, 50, 48, 46, 44, 42) del aruino.

### Push-Button
* Conectamos el primer push-button al protoboard y con cables de corriente puenteamos su pata izquierda con tierra y la pata derecha la conectaos en serie con una resitencia y despues a voltaje.
* Realizamos la conexión de la pata derecha del push-button con un cable jumper al pin PWM 20 del arduino.
* De la misma forma conectamos el segundo push-button, pero conectandolo al pin PWM 21 del arduino.
## Imagenes del montaje 
### Brazo robot
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/Brazo.jpg" width="400" height="400">
### Protoboard
### Display LCD y Botones
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgLCDBotones.jpg" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ProtoLCDBotones.jpg" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ProtoLCD.jpg" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ProtoBotones.jpg" width="400" height="400" >
### Arduino 
### Display LCD y botones
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ArduinoLCDBotones.jpg" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgLCD.jpg" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgBotones.jpg" width="400" height="400" >
### Servomotores
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgServos.png" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgServo2.jpg" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgServo3.jpg" width="400" height="400" >
### Motor paso a paso
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgMotorPasos.png" width="400" height="400" >
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/ImgServo1.jpg" width="400" height="400" >
### Interfaz de Software
<img src="https://github.com/JorgeJasso/BrazoRobotico/blob/master/Imagenes/Interfaz.jpg" width="400" height="400" >
