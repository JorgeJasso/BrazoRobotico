package brazorobotico;

import java.io.BufferedReader;//Lee el texto de un flujo de entrada de caracteres y almacena en búfer los caracteres para proporcionar una lectura eficiente de los caracteres, matrices y líneas.
import java.io.File; //Libreria que se usa para trabajar con archivos de texto.
import java.io.FileReader; //Sirve para leer los archivos de texto.
import java.io.FileWriter; //Sirve para escribir en los archivos de texto.
import java.io.IOException;
import java.io.PrintWriter;//Imprime representaciones formateadas de objetos en un flujo de salida de texto.

public class Lector {

    private final File archivo; //Se define un archivo nulo que posteriormente se le asignara un valor.

    public Lector() {
        archivo = new File("/home/araceli/Descargas/BrazoRobotico/src/brazorobotico/secuencia.txt"); //Especifica la ruta donde se encuentra el archivo.
    }

    public String leer() throws IOException { //Este metodo devuelvo un ArrayList que sera rellenado con todos los mensajes que encuentre en el archivo de texto.
        FileReader fr = new FileReader(archivo); //Pasa como parametro el archivo para crear el FileReader.
        BufferedReader br = new BufferedReader(fr); //Pasa como parametro el fr para crear el BufferedReader.
        String linea = br.readLine();
        fr.close(); //Cierra el archivo para evitar futuros errores.
        return linea;
    }

    public void escribir(String secuencia) throws IOException { //Escribe el mensaje pasado como parametro en el archivo de texto junto con su fecha.
        PrintWriter pw = new PrintWriter(new FileWriter(archivo));
        pw.println(secuencia);
        pw.close(); //Se cieera el archivo.
    }
}
