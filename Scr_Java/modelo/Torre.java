package modelo;

// Base comun de todas las torres. Cada subclase define sus stats iniciales
// (en el constructor) y su propia progresion de mejora en mejorar().
public abstract class Torre {
    protected int dano;
    protected int alcance;
    protected final int costo;
    protected int nivel;
    protected final Coordenada posicion;

    protected Torre(int dano, int alcance, int costo, Coordenada posicion) {
        this.dano = dano;
        this.alcance = alcance;
        this.costo = costo;
        this.posicion = posicion;
        this.nivel = 1;
    }

    // Una torre solo puede atacar objetivos dentro de su alcance (distancia Manhattan).
    public boolean estaEnRango(Coordenada posEnemigo) {
        return posicion.distanciaA(posEnemigo) <= alcance;
    }

    public void atacar(Cozy objetivo) {
        objetivo.recibirDano(dano);
    }

    // Cada subclase define su propio incremento de dano/alcance al mejorar.
    public abstract void mejorar();

    public abstract String getTipo();

    // Revierte una mejora anterior. Usado exclusivamente por
    // ComandoMejorarTorre.deshacer() para volver al snapshot previo.
    public void restaurar(int nivel, int dano, int alcance) {
        this.nivel = nivel;
        this.dano = dano;
        this.alcance = alcance;
    }

    public int getDano() {
        return dano;
    }

    public int getAlcance() {
        return alcance;
    }

    public int getCosto() {
        return costo;
    }

    public int getNivel() {
        return nivel;
    }

    public Coordenada getPosicion() {
        return posicion;
    }
}
