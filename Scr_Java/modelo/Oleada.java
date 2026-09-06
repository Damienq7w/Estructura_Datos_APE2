package modelo;

import java.util.ArrayList;
import java.util.List;

// Grupo de enemigos que se libera de una sola vez. La dificultad crece con
// el numero de oleada: mas enemigos y tipos mas fuertes en oleadas altas.
public class Oleada {
    private final int numero;
    private final Cozy[] enemigos;

    private Oleada(int numero, Cozy[] enemigos) {
        this.numero = numero;
        this.enemigos = enemigos;
    }

    public static Oleada generar(int numero) {
        int cantidad = 3 + numero; // mas enemigos conforme avanza el juego
        List<Cozy> enemigos = new ArrayList<>();
        for (int i = 0; i < cantidad; i++) {
            int indiceTipo = elegirTipo(numero, i);
            enemigos.add(CatalogoEnemigos.crear(indiceTipo, numero));
        }
        return new Oleada(numero, enemigos.toArray(new Cozy[0]));
    }

    private static int elegirTipo(int numero, int posicion) {
        // Oleadas bajas: mayormente "Normal" (indice 0).
        // A partir de la oleada 3 aparecen "Rapido" (indice 1) y desde la 5, "Tanque" (indice 2).
        if (numero >= 5 && posicion % 3 == 0) {
            return 2;
        }
        if (numero >= 3 && posicion % 2 == 0) {
            return 1;
        }
        return 0;
    }

    public Cozy[] getEnemigos() {
        return enemigos;
    }

    public int getNumero() {
        return numero;
    }
}
