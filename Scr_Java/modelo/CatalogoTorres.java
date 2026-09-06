package modelo;

// Lista fija de tipos de torre disponibles para el jugador y fabrica de instancias.
public class CatalogoTorres {

    // Datos informativos de cada tipo (para mostrarOpciones()); no se
    // usan para construir la Torre, que fija sus propios stats en el constructor.
    public static class TipoTorre {
        final String nombre;
        final int costo;
        final int danoBase;
        final int alcanceBase;

        public TipoTorre(String nombre, int costo, int danoBase, int alcanceBase) {
            this.nombre = nombre;
            this.costo = costo;
            this.danoBase = danoBase;
            this.alcanceBase = alcanceBase;
        }
    }

    public static final TipoTorre[] TIPOS = {
        new TipoTorre("Arquero", 50, 10, 3),
        new TipoTorre("Canon", 90, 25, 2)
    };

    public static void mostrarOpciones() {
        for (int i = 0; i < TIPOS.length; i++) {
            TipoTorre t = TIPOS[i];
            System.out.println(i + ") " + t.nombre + " - Costo: " + t.costo
                    + " | Dano: " + t.danoBase + " | Alcance: " + t.alcanceBase);
        }
    }

    // Fabrica: traduce el indice elegido por el jugador en el menu a la
    // subclase concreta de Torre correspondiente.
    public static Torre crear(int indiceTipo, Coordenada pos) {
        switch (indiceTipo) {
            case 0:
                return new TorreArquero(pos);
            case 1:
                return new TorreCanon(pos);
            default:
                throw new IllegalArgumentException("Indice de torre invalido: " + indiceTipo);
        }
    }
}
