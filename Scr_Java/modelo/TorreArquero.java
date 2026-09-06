package modelo;

public class TorreArquero extends Torre {

    // Bajo dano, buen alcance: dano 10, alcance 3, costo 50.
    public TorreArquero(Coordenada pos) {
        super(10, 3, 50, pos);
    }

    // Cada mejora suma +5 de dano y sube un nivel.
    @Override
    public void mejorar() {
        nivel++;
        dano += 5;
    }

    @Override
    public String getTipo() {
        return "Arquero";
    }
}
