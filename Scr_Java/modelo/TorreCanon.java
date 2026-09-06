package modelo;

public class TorreCanon extends Torre {

    // Alto dano, poco alcance: dano 25, alcance 2, costo 90.
    public TorreCanon(Coordenada pos) {
        super(25, 2, 90, pos);
    }

    // Cada mejora suma +10 de dano y sube un nivel.
    @Override
    public void mejorar() {
        nivel++;
        dano += 10;
    }

    @Override
    public String getTipo() {
        return "Canon";
    }
}
