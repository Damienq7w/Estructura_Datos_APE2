package modelo;

// Enemigo del juego. Avanza por la ruta del mapa segun su velocidad
// y se retira cuando muere o llega al final (ver ColaEnemigos.actualizarQuantum).
public class Cozy {
    private final String tipo;
    private int pv;
    private final int pvMax;
    private int indiceRuta;
    private final int velocidad;
    private final int recompensa;

    public Cozy(String tipo, int pvMax, int velocidad, int recompensa) {
        this.tipo = tipo;
        this.pvMax = pvMax;
        this.pv = pvMax;
        this.velocidad = velocidad;
        this.recompensa = recompensa;
        this.indiceRuta = 0;
    }

    // Nunca deja el pv negativo, asi estaVivo() queda bien definido con pv > 0.
    public void recibirDano(int dano) {
        pv = Math.max(0, pv - dano);
    }

    public boolean estaVivo() {
        return pv > 0;
    }

    public void avanzar() {
        indiceRuta += velocidad;
    }

    // "-1" porque el ultimo indice valido de la ruta es longitudRuta - 1
    // (la fuente de energia).
    public boolean llegoAlFinal(int longitudRuta) {
        return indiceRuta >= longitudRuta - 1;
    }

    public String getTipo() {
        return tipo;
    }

    public int getPv() {
        return pv;
    }

    public int getPvMax() {
        return pvMax;
    }

    public int getIndiceRuta() {
        return indiceRuta;
    }

    public int getVelocidad() {
        return velocidad;
    }

    public int getRecompensa() {
        return recompensa;
    }
}
