package estructuras;

import java.util.ArrayDeque;
import java.util.Deque;

// Pila de deshacer/rehacer sobre comandos de torre (patron Command).
public class HistorialComandos {
    private final Deque<ComandoTorre> pilaDeshacer;
    private final Deque<ComandoTorre> pilaRehacer;

    public HistorialComandos() {
        this.pilaDeshacer = new ArrayDeque<>();
        this.pilaRehacer = new ArrayDeque<>();
    }

    // Una accion nueva invalida cualquier "rehacer" pendiente (rama alternativa).
    public void registrar(ComandoTorre c) {
        pilaDeshacer.push(c);
        pilaRehacer.clear();
    }

    // pop() del tope, se deshace y pasa a la pila de rehacer.
    public void deshacer() {
        ComandoTorre c = pilaDeshacer.pop();
        c.deshacer();
        pilaRehacer.push(c);
    }

    // Simetrico a deshacer(): pop() de rehacer, se vuelve a ejecutar y
    // regresa a la pila de deshacer.
    public void rehacer() {
        ComandoTorre c = pilaRehacer.pop();
        c.ejecutar();
        pilaDeshacer.push(c);
    }

    public boolean puedeDeshacer() {
        return !pilaDeshacer.isEmpty();
    }

    public boolean puedeRehacer() {
        return !pilaRehacer.isEmpty();
    }
}
