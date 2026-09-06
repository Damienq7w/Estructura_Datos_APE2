package estructuras;

import java.util.ArrayDeque;
import java.util.Queue;

import modelo.Oleada;

// Cola FIFO de oleadas pendientes: se liberan en el orden en que fueron agregadas.
public class GestorOleadas {
    private final Queue<Oleada> oleadas;

    public GestorOleadas() {
        this.oleadas = new ArrayDeque<>();
    }

    public void agregarOleada(Oleada o) {
        oleadas.add(o);
    }

    public Oleada siguienteOleada() {
        return oleadas.poll();
    }

    public boolean hayOleadasPendientes() {
        return !oleadas.isEmpty();
    }
}
