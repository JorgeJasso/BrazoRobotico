package brazorobotico;

public class Controlador {

    Conexion conectar;

    public Controlador() {
        conectar = new Conexion(2); //Crea la conexion con el arduino para cuando se necesite mandarle información.
    }

    public void moverBrazo(int accion, long tiempo) {
        System.out.println(accion+","+tiempo+";"); //Impresion en consola de los valores que estamos enviando a arduino
        conectar.enviarDatos(accion +","+ tiempo + ";"); //Envia el mensaje a arduino.
    }
}
