package estructuras;

import modelo.Torre;

public class ComandoColocarTorre implements ComandoTorre {
    private final Torre torre;
    private final Mapa mapa;
    private boolean exitosa; // si colocar fallo (casilla ocupada/sin espacio), deshacer no debe quitar nada

    public ComandoColocarTorre(Torre torre, Mapa mapa) {
        this.torre = torre;
        this.mapa = mapa;
        this.exitosa = false;
    }

    @Override
    public void ejecutar() {
        exitosa = mapa.colocarTorre(torre);
    }

    @Override
    public void deshacer() {
        if (exitosa) {
            mapa.quitarTorre(torre);
        }
    }

    public boolean isExitosa() {
        return exitosa;
    }

    public Torre getTorre() {
        return torre;
    }
}
