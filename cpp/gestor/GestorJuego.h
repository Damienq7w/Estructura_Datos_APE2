#ifndef GESTOR_JUEGO_H
#define GESTOR_JUEGO_H

// Orquesta el estado global del juego: vida, puntaje, oleadas y comandos.
// Es el unico punto de entrada que usa main para avanzar el juego.
//
// Se declaran las dependencias por adelantado (forward declaration) y solo
// se guardan referencias: asi este header no necesita incluir ColaEnemigos.h
// (que a su vez incluye este archivo) y se evita la inclusion circular.
class ColaEnemigos;
class GestorOleadas;
class HistorialComandos;
class Mapa;
class Torre;

class GestorJuego {
private:
    int vidaJugador;
    int puntuacion;
    int oleadaActual;

    ColaEnemigos& colaEnemigos;
    GestorOleadas& gestorOleadas;
    HistorialComandos& historial;
    Mapa& mapa;

public:
    GestorJuego(int vidaInicial, ColaEnemigos& colaEnemigos, GestorOleadas& gestorOleadas,
                HistorialComandos& historial, Mapa& mapa);

    // Si ya no quedan enemigos en ruta, carga la siguiente oleada pendiente
    // antes de procesar el quantum actual.
    void procesarQuantum();

    void restarVida(int cantidad);
    void sumarPuntaje(int cantidad);

    // Crea el comando, lo ejecuta de inmediato y, solo si la colocacion
    // fue exitosa, lo registra en el historial para poder deshacerlo.
    // Devuelve si la torre se pudo colocar o no.
    bool colocarTorreJugador(Torre* t);

    void mejorarTorreJugador(Torre* t);

    void deshacerUltimaAccion();
    void rehacerUltimaAccion();

    bool juegoTerminado() const;

    // Se superaron todas las oleadas y ya no queda ningun Cozy en la ruta.
    // main solo llama esto si juegoTerminado() es false, para que una
    // derrota nunca se reporte como victoria.
    bool haGanado() const;

    void mostrarEstado() const;
    void mostrarResultadoFinal(bool victoria) const;

    Mapa& getMapa() const;
    int getVidaJugador() const;
    int getPuntuacion() const;
    int getOleadaActual() const;
};

#endif // GESTOR_JUEGO_H
