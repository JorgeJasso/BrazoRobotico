package brazorobotico;

public class Controlador {

    public Controlador() {
    }

    public void moverBrazo(int accion, long tiempo) {
        System.out.println(accion + "," + tiempo + ";"); //Impresion en consola de los valores que estamos enviando a arduino
    }
}
