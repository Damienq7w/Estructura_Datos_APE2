package gestor;

import estructuras.ColaEnemigos;
import estructuras.ComandoColocarTorre;
import estructuras.ComandoMejorarTorre;
import estructuras.GestorOleadas;
import estructuras.HistorialComandos;
import estructuras.Mapa;
import modelo.Cozy;
import modelo.Oleada;
import modelo.Torre;

// Orquesta el estado global del juego: vida, puntaje, oleadas y comandos.
// Es el unico punto de entrada que usa Main para avanzar el juego.
public class GestorJuego {
    private int vidaJugador;
    private int puntuacion;
    private int oleadaActual;

    private final ColaEnemigos colaEnemigos;
    private final GestorOleadas gestorOleadas;
    private final HistorialComandos historial;
    private final Mapa mapa;

    public GestorJuego(int vidaInicial, ColaEnemigos colaEnemigos, GestorOleadas gestorOleadas,
                        HistorialComandos historial, Mapa mapa) {
        this.vidaJugador = vidaInicial;
        this.puntuacion = 0;
        this.oleadaActual = 0;
        this.colaEnemigos = colaEnemigos;
        this.gestorOleadas = gestorOleadas;
        this.historial = historial;
        this.mapa = mapa;
    }

    // Si ya no quedan enemigos en ruta, carga la siguiente oleada pendiente
    // antes de procesar el quantum actual.
    public void procesarQuantum() {
        if (colaEnemigos.estaVacia() && gestorOleadas.hayOleadasPendientes()) {
            Oleada siguiente = gestorOleadas.siguienteOleada();
            oleadaActual = siguiente.getNumero();
            for (Cozy c : siguiente.getEnemigos()) {
                colaEnemigos.encolar(c);
            }
        }
        colaEnemigos.actualizarQuantum(mapa, this);
    }

    public void restarVida(int cantidad) {
        vidaJugador = Math.max(0, vidaJugador - cantidad);
    }

    public void sumarPuntaje(int cantidad) {
        puntuacion += cantidad;
    }

    // Crea el comando, lo ejecuta de inmediato y lo registra en el
    // historial para que quede disponible para deshacer.
    public boolean colocarTorreJugador(Torre t) {
        ComandoColocarTorre comando = new ComandoColocarTorre(t, mapa);
        comando.ejecutar();
        if (comando.isExitosa()) {
            historial.registrar(comando);
        }
        return comando.isExitosa();
    }

    public void mejorarTorreJugador(Torre t) {
        ComandoMejorarTorre comando = new ComandoMejorarTorre(t);
        comando.ejecutar();
        historial.registrar(comando);
    }

    public void deshacerUltimaAccion() {
        if (historial.puedeDeshacer()) {
            historial.deshacer();
        }
    }

    public void rehacerUltimaAccion() {
        if (historial.puedeRehacer()) {
            historial.rehacer();
        }
    }

    public boolean juegoTerminado() {
        return vidaJugador <= 0;
    }

    // Se superaron todas las oleadas y ya no queda ningun Cozy en la ruta.
    // Main solo llama esto si juegoTerminado() es false, para que una
    // derrota nunca se reporte como victoria.
    public boolean haGanado() {
        return !gestorOleadas.hayOleadasPendientes() && colaEnemigos.estaVacia();
    }

    public void mostrarEstado() {
        System.out.println("Vida: " + vidaJugador + " | Oleada: " + oleadaActual + " | Puntaje: " + puntuacion);
        mapa.imprimirMapa();
    }

    public void mostrarResultadoFinal(boolean victoria) {
        System.out.println(victoria ? "¡Victoria!" : "Derrota");
        System.out.println("Puntaje final: " + puntuacion + " | Oleada alcanzada: " + oleadaActual);
    }

    public Mapa getMapa() {
        return mapa;
    }

    public int getVidaJugador() {
        return vidaJugador;
    }

    public int getPuntuacion() {
        return puntuacion;
    }

    public int getOleadaActual() {
        return oleadaActual;
    }
}
