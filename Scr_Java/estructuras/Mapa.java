package estructuras;

import modelo.Coordenada;
import modelo.Torre;

public class Mapa {
    private final Coordenada[] ruta;
    private final Coordenada fuenteEnergia;
    private final Torre[] torres;
    private int cantidadTorres;

    public Mapa(Coordenada[] ruta, int capacidadTorres) {
        this.ruta = ruta;
        this.fuenteEnergia = ruta[ruta.length - 1];
        this.torres = new Torre[capacidadTorres];
        this.cantidadTorres = 0;
    }

    // Pre: hay espacio en el arreglo y la casilla no esta ocupada por otra torre.
    public boolean colocarTorre(Torre t) {
        if (cantidadTorres >= torres.length) {
            return false;
        }
        if (buscarTorreEn(t.getPosicion()) != null) {
            return false;
        }
        torres[cantidadTorres] = t;
        cantidadTorres++;
        return true;
    }

    public void quitarTorre(Torre t) {
        int indice = -1;
        for (int i = 0; i < cantidadTorres; i++) {
            if (torres[i] == t) {
                indice = i;
                break;
            }
        }
        if (indice == -1) {
            return;
        }
        // Compacta el arreglo desplazando los elementos posteriores una posicion.
        for (int i = indice; i < cantidadTorres - 1; i++) {
            torres[i] = torres[i + 1];
        }
        torres[cantidadTorres - 1] = null;
        cantidadTorres--;
    }

    // Usado por la opcion "mejorar torre" del menu para ubicar la torre
    // por su posicion (se apoya en Coordenada.equals).
    public Torre buscarTorreEn(Coordenada pos) {
        for (int i = 0; i < cantidadTorres; i++) {
            if (torres[i].getPosicion().equals(pos)) {
                return torres[i];
            }
        }
        return null;
    }

    // Dibuja la grilla: E = entrada de la ruta, F = fuente de energia (final
    // de la ruta), letra inicial del tipo = torre, . = casilla libre.
    public void imprimirMapa() {
        int filas = 0;
        int columnas = 0;
        for (Coordenada c : ruta) {
            filas = Math.max(filas, c.getFila() + 1);
            columnas = Math.max(columnas, c.getColumna() + 1);
        }
        for (int i = 0; i < cantidadTorres; i++) {
            Coordenada p = torres[i].getPosicion();
            filas = Math.max(filas, p.getFila() + 1);
            columnas = Math.max(columnas, p.getColumna() + 1);
        }

        char[][] grilla = new char[filas][columnas];
        for (char[] fila : grilla) {
            java.util.Arrays.fill(fila, '.');
        }
        Coordenada entrada = ruta[0];
        grilla[entrada.getFila()][entrada.getColumna()] = 'E';
        grilla[fuenteEnergia.getFila()][fuenteEnergia.getColumna()] = 'F';
        for (int i = 0; i < cantidadTorres; i++) {
            Coordenada p = torres[i].getPosicion();
            grilla[p.getFila()][p.getColumna()] = torres[i].getTipo().charAt(0);
        }

        for (char[] fila : grilla) {
            StringBuilder sb = new StringBuilder();
            for (char c : fila) {
                sb.append(c).append(' ');
            }
            System.out.println(sb.toString().trim());
        }
    }

    public Coordenada[] getRuta() {
        return ruta;
    }

    public Coordenada getFuenteEnergia() {
        return fuenteEnergia;
    }

    public Torre[] getTorresActivas() {
        return java.util.Arrays.copyOf(torres, cantidadTorres);
    }
}