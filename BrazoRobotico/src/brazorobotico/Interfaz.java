/* En la siguente clase se crea la interfaz del sistema */
package brazorobotico;
//Importar todas las librerías que utilizaremos

import java.awt.Color;    //Libreria para asignar colores a los componentes.
import java.awt.event.ActionEvent;//Se declara para manejar eventos.
import java.awt.event.ActionListener;//Se declara para manejar eventos de tipo Action.
import java.awt.event.MouseAdapter; //Una clase de adaptador abstracta para recibir eventos del mouse
import java.awt.event.MouseEvent;//Un evento que indica que se produjo una acción del mouse en un componente
import java.io.IOException;//Señala que se ha producido una excepción de E / S de algún tipo.
import java.util.Date; //esta clase encapsula la fecha y hora actuales.
import java.util.logging.Level;//define un conjunto de niveles de registro estándar que se pueden usar para controlar la salida del registro. 
import java.util.logging.Logger; //se usa para registrar mensajes para un sistema específico o componente de aplicación.
import javax.swing.JButton;  // se agrega para poder trabajar con JButton.
import javax.swing.JFrame;  //Se agrega para poder trabajar con JFrame. 
import javax.swing.JLabel;  // se agrega esta libreria para poder trabajar con JLabel.
import javax.swing.JOptionPane;//apertura de un cuadro de diálogo estándar que solicita a los usuarios un valor o les informa de algo
import javax.swing.JPanel;  //Se agrega para poder trabajar con JPanel.

public class Interfaz extends JFrame { // indicamos que esta clase hereda de un JFrame
    //Declaración de variables

    final JPanel PANEL;  //Para usar el panel en Frame.
    private final JLabel ETIQUETA_BASE; //Etiqueta para Base
    final JButton BASE_GIRA_IZQUIERDA;  //Boton para girar la base a la izquierda
    final JButton BASE_GIRA_DERECHA;    //Boton para girar la base a la derecha
    private final JLabel ETIQUETA_HOMBRO; //Etiqueta para Hombro
    final JButton HOMBRO_LEVANTAR; //Boton para levantar el hombro
    final JButton HOMBRO_BAJAR; //Boton para bajar el hombro
    private final JLabel ETIQUETA_CODO; //Etiqueta para codo
    final JButton CODO_AVANZAR; //Boton para avanzar codo
    final JButton CODO_RETROCEDER;//Boton para retroceder codo
    private final JLabel ETIQUETA_MUNECA; //Etiqueta para muñeca
    final JButton MUNECA_GIRA_IZQUIERDA;//Boton para girar la muñeca a la izquierda
    final JButton MUNECA_GIRA_DERECHA;//Boton para girar la muñeca a la derecha
    private final JLabel ETIQUETA_PINZA; //Etiqueta para pinza
    final JButton PINZA_ABRIR; //Boton para abrir la pinza
    final JButton PINZA_CERRAR;//Boton para cerrar la pinza
    final JButton GUARDAR; //Boton para guardar la secuencia
    final JButton LIMPIAR;//Boton para limpiar la secuencia
    final JButton BOTONES[]; //arreglo de botones
    String secuencia = ""; //Cadena donde se concatenaran las secuencias
    final Controlador CONTROL; // instanciamos la clase Controlador

    public Interfaz() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);//Indicas que cuando se cierre se termine la aplicación.
        setResizable(false);//Indica que no se podra redimencionar.
        setSize(700, 600); //Se define el tamaño de nuestro frame.
        setBounds(350, 100, 700, 600);//Posiciona la ventana en el lugar deseado.

        EventosMouse evento = new EventosMouse(); //Clase para manejar eventos con el mouse
        EventosClic clic = new EventosClic(); //Clase para manejar eventos 
        CONTROL = new Controlador(); //Se crea el controlador

        PANEL = new JPanel(); //Para usar el panel en la clase Eventos.
        PANEL.setBackground(Color.GRAY); // Agregamos fondo gris al panel
        PANEL.setLayout(null);
 
        ETIQUETA_BASE = new JLabel(); //Propiedades para etiqueta Base
        ETIQUETA_BASE.setText("BASE");
        ETIQUETA_BASE.setBounds(145, 25, 100, 10);
        ETIQUETA_BASE.setForeground(Color.WHITE);
        PANEL.add(ETIQUETA_BASE);//Añade la etiqueta al panel.

        BASE_GIRA_IZQUIERDA = new JButton(); //Propiedades para boton base que gira a izquieda
        BASE_GIRA_IZQUIERDA.setText("Gira izquierda");
        BASE_GIRA_IZQUIERDA.setBounds(10, 60, 150, 30);
        BASE_GIRA_IZQUIERDA.addMouseListener(evento); //Pone a la escucha el boton BASE_GIRA_IZQUIERDA
        PANEL.add(BASE_GIRA_IZQUIERDA); //Añade el boton al panel.

        BASE_GIRA_DERECHA = new JButton(); //Propiedades para boton base que gira a la derecha
        BASE_GIRA_DERECHA.setText("Gira derecha");
        BASE_GIRA_DERECHA.setBounds(170, 60, 150, 30);
        BASE_GIRA_DERECHA.addMouseListener(evento); //Pone a la escucha el boton BASE_GIRA_DERECHA
        PANEL.add(BASE_GIRA_DERECHA); //Añade el boton al panel.

        ETIQUETA_HOMBRO = new JLabel(); //Propiedades para etiqueta hombro
        ETIQUETA_HOMBRO.setText("HOMBRO");
        ETIQUETA_HOMBRO.setBounds(505, 25, 100, 10);
        ETIQUETA_HOMBRO.setForeground(Color.WHITE);
        PANEL.add(ETIQUETA_HOMBRO);

        HOMBRO_LEVANTAR = new JButton(); //Propiedades para boton hombro que levanta
        HOMBRO_LEVANTAR.setText("Levantar");
        HOMBRO_LEVANTAR.setBounds(380, 60, 150, 30);
        HOMBRO_LEVANTAR.addMouseListener(evento);
        PANEL.add(HOMBRO_LEVANTAR);

        HOMBRO_BAJAR = new JButton(); //Propiedades para boton hombro que baja
        HOMBRO_BAJAR.setText("Bajar");
        HOMBRO_BAJAR.setBounds(540, 60, 150, 30);
        HOMBRO_BAJAR.addMouseListener(evento);
        PANEL.add(HOMBRO_BAJAR);

        ETIQUETA_CODO = new JLabel(); //Propiedades para etiqueta codo
        ETIQUETA_CODO.setText("CODO");
        ETIQUETA_CODO.setBounds(330, 140, 100, 10);
        ETIQUETA_CODO.setForeground(Color.WHITE);
        PANEL.add(ETIQUETA_CODO);

        CODO_AVANZAR = new JButton(); //Propiedades para boton codo que avanza
        CODO_AVANZAR.setText("Subir");
        CODO_AVANZAR.setBounds(195, 170, 150, 30);
        CODO_AVANZAR.addMouseListener(evento);
        PANEL.add(CODO_AVANZAR);

        CODO_RETROCEDER = new JButton(); //Propiedades para boton codo que retrocede
        CODO_RETROCEDER.setText("Bajar");
        CODO_RETROCEDER.setBounds(355, 170, 150, 30);
        CODO_RETROCEDER.addMouseListener(evento);
        PANEL.add(CODO_RETROCEDER);

        ETIQUETA_MUNECA = new JLabel(); //Propiedades para etiqueta muñeca
        ETIQUETA_MUNECA.setText("MUÑECA");
        ETIQUETA_MUNECA.setBounds(135, 250, 100, 10);
        ETIQUETA_MUNECA.setForeground(Color.WHITE);
        PANEL.add(ETIQUETA_MUNECA);

        MUNECA_GIRA_IZQUIERDA = new JButton(); //Propiedades para boton muñeca que gira a la izquierda
        MUNECA_GIRA_IZQUIERDA.setText("Gira izquierda");
        MUNECA_GIRA_IZQUIERDA.setBounds(10, 280, 150, 30);
        MUNECA_GIRA_IZQUIERDA.addMouseListener(evento);
        PANEL.add(MUNECA_GIRA_IZQUIERDA);

        MUNECA_GIRA_DERECHA = new JButton(); //Propiedades para boton muñeca que gira a la derecha
        MUNECA_GIRA_DERECHA.setText("Gira derecha");
        MUNECA_GIRA_DERECHA.setBounds(170, 280, 150, 30);
        MUNECA_GIRA_DERECHA.addMouseListener(evento);
        PANEL.add(MUNECA_GIRA_DERECHA);

        ETIQUETA_PINZA = new JLabel(); //Propiedades para etiqueta pinza
        ETIQUETA_PINZA.setText("PINZA");
        ETIQUETA_PINZA.setBounds(515, 250, 100, 10);
        ETIQUETA_PINZA.setForeground(Color.WHITE);
        PANEL.add(ETIQUETA_PINZA);

        PINZA_ABRIR = new JButton(); //Propiedades para boton pinza que abre
        PINZA_ABRIR.setText("Abrir");
        PINZA_ABRIR.setBounds(380, 280, 150, 30);
        PINZA_ABRIR.addMouseListener(evento);
        PANEL.add(PINZA_ABRIR);

        PINZA_CERRAR = new JButton(); //Propiedades para boton pinza que cierra
        PINZA_CERRAR.setText("Cerrar");
        PINZA_CERRAR.setBounds(540, 280, 150, 30);
        PINZA_CERRAR.addMouseListener(evento);
        PANEL.add(PINZA_CERRAR);

        GUARDAR = new JButton(); //Propiedades para boton guardar secuencia
        GUARDAR.setText("Guardar secuencia");
        GUARDAR.setBounds(150, 420, 190, 30);
        GUARDAR.addActionListener(clic);
        PANEL.add(GUARDAR);

        LIMPIAR = new JButton(); //Propiedades para boton limpiar secuencia
        LIMPIAR.setText("Limpiar secuencia");
        LIMPIAR.setBounds(350, 420, 190, 30);
        LIMPIAR.addActionListener(clic);
        PANEL.add(LIMPIAR);

        JButton temporal[] = {BASE_GIRA_IZQUIERDA, BASE_GIRA_DERECHA, HOMBRO_LEVANTAR, HOMBRO_BAJAR, CODO_AVANZAR, CODO_RETROCEDER, MUNECA_GIRA_IZQUIERDA, MUNECA_GIRA_DERECHA, PINZA_ABRIR, PINZA_CERRAR};
        BOTONES = temporal;

        add(PANEL); //se agrega el panel al Frame
        setVisible(true); // lo pone en modo visible
    }

    class EventosClic implements ActionListener { //Crea una clase interna para manejar los eventos de la clase Interfaz.

        @Override
        public void actionPerformed(ActionEvent evento) {
            if (evento.getSource() == GUARDAR) { //Verifica que el evento se produjo de GUARDAR.
                try {
                    Lector escribir = new Lector();  //Llama al Lector que se encuentra en el mismo paquete
                    escribir.escribir(secuencia);  //Le pasa el mensaje para que el metodo de escribir se haga cargo de el.
                    secuencia = ""; //restablece la secuencia a vacio 
                    JOptionPane.showMessageDialog(null, "Secuencia Guardada");
                } catch (IOException ex) {
                    Logger.getLogger(Interfaz.class.getName()).log(Level.SEVERE, null, ex);
                }
            } else {
                JOptionPane.showMessageDialog(null, "Se ha limpiado la secuencia");
                secuencia = "";
            }
        }
    }

    class EventosMouse extends MouseAdapter {

        private long tiempoInicial;
        private long tiempoFinal;

        @Override
        public void mousePressed(MouseEvent evento) {
            Date fechaInicio = new Date();
            tiempoInicial = fechaInicio.getTime();
        }

        @Override
        public void mouseReleased(MouseEvent evento) {
            Date fechaFinal = new Date();
            tiempoFinal = fechaFinal.getTime();
            long tiempo = tiempoFinal - tiempoInicial;
            for (int i = 0; i < BOTONES.length; i++) {
                if (evento.getSource() == BOTONES[i]) {
                    secuencia = secuencia + i + "," + tiempo + ";";
                    CONTROL.moverBrazo(i, tiempo);
                }
            }
        }
    }
}
