package modelo;

// Lista fija de tipos de enemigo disponibles y fabrica de instancias Cozy.
public class CatalogoEnemigos {

    // Plantilla de un tipo de enemigo (stats base, antes de escalar por dificultad).
    public static class TipoEnemigo {
        final String nombre;
        final int pvBase;
        final int velocidad;
        final int recompensa;

        public TipoEnemigo(String nombre, int pvBase, int velocidad, int recompensa) {
            this.nombre = nombre;
            this.pvBase = pvBase;
            this.velocidad = velocidad;
            this.recompensa = recompensa;
        }
    }

    public static final TipoEnemigo[] TIPOS = {
        new TipoEnemigo("Normal", 20, 1, 10),
        new TipoEnemigo("Rapido", 12, 2, 8),
        new TipoEnemigo("Tanque", 45, 1, 20)
    };

    // Escala el pv base segun el factor de dificultad (numero de oleada):
    // pv = pvBase + 25% de pvBase por cada punto de factorDificultad.
    public static Cozy crear(int indiceTipo, int factorDificultad) {
        TipoEnemigo t = TIPOS[indiceTipo];
        int pvEscalado = t.pvBase + (t.pvBase * factorDificultad / 4);
        return new Cozy(t.nombre, pvEscalado, t.velocidad, t.recompensa);
    }
}
