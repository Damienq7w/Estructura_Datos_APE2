package estructuras;

import modelo.Torre;

public class ComandoMejorarTorre implements ComandoTorre {
    private final Torre torre;
    // Snapshot de los stats previos a mejorar(), para poder revertirlos exactamente.
    private int nivelAnterior;
    private int danoAnterior;
    private int alcanceAnterior;

    public ComandoMejorarTorre(Torre torre) {
        this.torre = torre;
    }

    @Override
    public void ejecutar() {
        nivelAnterior = torre.getNivel();
        danoAnterior = torre.getDano();
        alcanceAnterior = torre.getAlcance();
        torre.mejorar();
    }

    @Override
    public void deshacer() {
        torre.restaurar(nivelAnterior, danoAnterior, alcanceAnterior);
    }
}
