package modelo;

import java.util.Objects;

public class Coordenada {
    private final int fila;
    private final int columna;

    public Coordenada(int fila, int columna) {
        this.fila = fila;
        this.columna = columna;
    }

    public int getFila() {
        return fila;
    }

    public int getColumna() {
        return columna;
    }

    // Distancia Manhattan: se usa para decidir si un enemigo esta dentro
    // del alcance de una torre (Torre.estaEnRango).
    public int distanciaA(Coordenada otra) {
        return Math.abs(this.fila - otra.fila) + Math.abs(this.columna - otra.columna);
    }

    // equals/hashCode son necesarios porque Coordenada se usa como clave logica
    // para comparar posiciones: ocupacion de casillas en Mapa y busqueda de torres.
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Coordenada)) return false;
        Coordenada that = (Coordenada) o;
        return fila == that.fila && columna == that.columna;
    }

    @Override
    public int hashCode() {
        return Objects.hash(fila, columna);
    }

    @Override
    public String toString() {
        return "(" + fila + ", " + columna + ")";
    }
}
