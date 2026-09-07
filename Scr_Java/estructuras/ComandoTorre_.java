package estructuras;

// Patron Command: encapsula una accion sobre una torre para poder
// deshacerla/rehacerla despues, sin que HistorialComandos conozca los detalles.
public interface ComandoTorre {
    void ejecutar();
    void deshacer();
}
