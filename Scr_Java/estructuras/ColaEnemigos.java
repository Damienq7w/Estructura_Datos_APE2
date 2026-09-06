package estructuras;

import java.util.ArrayDeque;
import java.util.Queue;

import gestor.GestorJuego;
import modelo.Coordenada;
import modelo.Cozy;
import modelo.Torre;

// Cola circular: cada Cozy vivo que no llega al final se vuelve a encolar
// al final de la cola, simulando su avance continuo por la ruta.
public class ColaEnemigos {
    private static final int DANO_POR_FUGA = 1; // vida que pierde el jugador por cada fuga

    private final Queue<Cozy> colaCircular;

    public ColaEnemigos() {
        this.colaCircular = new ArrayDeque<>();
    }

    public void encolar(Cozy c) {
        colaCircular.add(c);
    }

    public void actualizarQuantum(Mapa mapa, GestorJuego estado) {
        // Se fija el tamanio ANTES del bucle: cada Cozy se procesa una sola vez
        // por quantum, aunque se vuelva a encolar dentro del mismo bucle.
        int cantidadAProcesar = colaCircular.size();
        Coordenada[] ruta = mapa.getRuta();
        Torre[] torresActivas = mapa.getTorresActivas();

        for (int i = 0; i < cantidadAProcesar; i++) {
            Cozy c = colaCircular.poll();
            Coordenada posActual = ruta[c.getIndiceRuta()];

            // Todas las torres en rango disparan sobre el enemigo en su posicion actual.
            for (Torre t : torresActivas) {
                if (c.estaVivo() && t.estaEnRango(posActual)) {
                    t.atacar(c);
                }
            }

            if (!c.estaVivo()) {
                estado.sumarPuntaje(c.getRecompensa());
                continue; // muere: se retira, no se re-encola
            }

            c.avanzar();
            if (c.llegoAlFinal(ruta.length)) {
                estado.restarVida(DANO_POR_FUGA);
                continue; // se fuga: se retira, no se re-encola
            }

            colaCircular.add(c); // sigue vivo en ruta: vuelve al final de la cola
        }
    }

    public boolean estaVacia() {
        return colaCircular.isEmpty();
    }

    public int tamanio() {
        return colaCircular.size();
    }
}
