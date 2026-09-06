import estructuras.ColaEnemigos;
import estructuras.GestorOleadas;
import estructuras.HistorialComandos;
import estructuras.Mapa;
import gestor.GestorJuego;
import java.util.Scanner;
import modelo.CatalogoTorres;
import modelo.Coordenada;
import modelo.Oleada;
import modelo.Torre;

public class Main {

    public static void main(String[] args) {
        Mapa mapa = crearMapaInicial();
        ColaEnemigos colaEnemigos = new ColaEnemigos();
        GestorOleadas gestorOleadas = new GestorOleadas();
        HistorialComandos historial = new HistorialComandos();
        GestorJuego juego = new GestorJuego(20, colaEnemigos, gestorOleadas, historial, mapa);

        // Se precargan 8 oleadas con dificultad creciente; GestorJuego las
        // libera una por una cuando la ruta queda vacia (ver procesarQuantum).
        for (int i = 1; i <= 10; i++) {
            gestorOleadas.agregarOleada(Oleada.generar(i));
        }

        Scanner scanner = new Scanner(System.in);
        boolean finDelJuego = false;

        while (!finDelJuego) {
            juego.mostrarEstado();
            imprimirMenu();
            int opcion = leerEntero(scanner, "Elige una opcion: ");

            switch (opcion) {
                case 1:
                    colocarTorre(scanner, juego, mapa);
                    break;
                case 2:
                    mejorarTorre(scanner, juego, mapa);
                    break;
                case 3:
                    juego.deshacerUltimaAccion();
                    break;
                case 4:
                    juego.rehacerUltimaAccion();
                    break;
                case 5:
                    juego.procesarQuantum();
                    break;
                case 6:
                    System.out.println("Saliendo del juego.");
                    finDelJuego = true;
                    continue;
                default:
                    System.out.println("Opcion invalida.");
                    continue;
            }

            // Se verifica derrota primero: si vidaJugador llega a 0 en el mismo
            // quantum en que se limpia la ultima oleada, gana la derrota.
            if (juego.juegoTerminado()) {
                juego.mostrarResultadoFinal(false);
                finDelJuego = true;
            } else if (juego.haGanado()) {
                juego.mostrarResultadoFinal(true);
                finDelJuego = true;
            }
        }

        scanner.close();
    }

    private static void imprimirMenu() {
        System.out.println("1) Colocar torre");
        System.out.println("2) Mejorar torre");
        System.out.println("3) Deshacer");
        System.out.println("4) Rehacer");
        System.out.println("5) Avanzar quantum");
        System.out.println("6) Salir");
    }

    // Valida el indice antes de crear la torre para no dejar pasar
    // un tipo inexistente a CatalogoTorres.crear().
    private static void colocarTorre(Scanner scanner, GestorJuego juego, Mapa mapa) {
        CatalogoTorres.mostrarOpciones();
        int indiceTipo = leerEntero(scanner, "Elige el tipo de torre: ");
        if (indiceTipo < 0 || indiceTipo >= CatalogoTorres.TIPOS.length) {
            System.out.println("Tipo de torre invalido.");
            return;
        }
        int fila = leerEntero(scanner, "Fila: ");
        int columna = leerEntero(scanner, "Columna: ");

        Torre torre = CatalogoTorres.crear(indiceTipo, new Coordenada(fila, columna));
        boolean colocada = juego.colocarTorreJugador(torre);
        System.out.println(colocada ? "Torre colocada." : "No se pudo colocar (casilla ocupada o sin espacio).");
    }

    private static void mejorarTorre(Scanner scanner, GestorJuego juego, Mapa mapa) {
        int fila = leerEntero(scanner, "Fila de la torre a mejorar: ");
        int columna = leerEntero(scanner, "Columna de la torre a mejorar: ");

        Torre torre = mapa.buscarTorreEn(new Coordenada(fila, columna));
        if (torre == null) {
            System.out.println("No hay ninguna torre en esa posicion.");
            return;
        }
        juego.mejorarTorreJugador(torre);
    }

    private static int leerEntero(Scanner scanner, String mensaje) {
        System.out.print(mensaje);
        while (!scanner.hasNextInt()) {
            scanner.next();
            System.out.print(mensaje);
        }
        return scanner.nextInt();
    }

    private static Mapa crearMapaInicial() {
        Coordenada[] ruta = {
            new Coordenada(0, 0),
            new Coordenada(0, 1),
            new Coordenada(0, 2),
            new Coordenada(1, 2),
            new Coordenada(2, 2),
            new Coordenada(2, 3),
            new Coordenada(2, 4)
        };
        return new Mapa(ruta, 10);
    }
}
