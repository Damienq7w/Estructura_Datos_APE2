#ifndef COZY_H
#define COZY_H

#include <string>

// Enemigo del juego. Avanza por la ruta del mapa segun su velocidad
// y se retira cuando muere o llega al final (ver ColaEnemigos::actualizarQuantum).
class Cozy {
private:
    const std::string tipo;
    int pv;
    const int pvMax;
    int indiceRuta;
    const int velocidad;
    const int recompensa;

public:
    // Constructor que inicializa las caracteristicas principales del enemigo.
    Cozy(const std::string& tipo, int pvMax, int velocidad, int recompensa);

    // Nunca deja el pv negativo, asi estaVivo() queda bien definido con pv > 0.
    void recibirDano(int dano);

    // Determina si el enemigo continua con puntos de vida.
    bool estaVivo() const;

    // Incrementa la posicion del enemigo dentro de la ruta
    // de acuerdo con su velocidad.
    void avanzar();

    // "-1" porque el ultimo indice valido de la ruta es longitudRuta - 1
    // (la fuente de energia).
    bool llegoAlFinal(int longitudRuta) const;

    // Retorna el tipo de enemigo.
    const std::string& getTipo() const;

    // Retorna los puntos de vida actuales del enemigo.
    int getPv() const;

    // Retorna los puntos de vida maximos del enemigo.
    int getPvMax() const;

    // Retorna el indice actual del enemigo dentro de la ruta.
    int getIndiceRuta() const;

    // Retorna la velocidad de movimiento del enemigo.
    int getVelocidad() const;

    // Retorna la recompensa otorgada al eliminar al enemigo.
    int getRecompensa() const;
};

#endif // COZY_H