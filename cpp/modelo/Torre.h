#ifndef TORRE_H
#define TORRE_H

#include <string>
#include "Coordenada.h"
#include "Cozy.h"

// Clase base abstracta para todas las torres del juego. No se puede
// instanciar directamente (mejorar() y getTipo() son puramente virtuales);
// cada subclase (TorreArquero, TorreCanon) define sus propios stats
// iniciales y su propia forma de mejorar.
class Torre {
protected:
    int danio;              // danio que hace cada ataque
    int alcance;            // radio (en distancia Manhattan) donde puede atacar
    const int costo;         // costo en monedas para colocarla (no cambia nunca)
    int nivel;                // nivel actual, sube con mejorar()
    const Coordenada posicion; // casilla donde esta colocada (fija de por vida)

public:
    // El constructor solo lo llaman las subclases (via super/Torre(...))
    // para fijar sus stats base. nivel siempre arranca en 1.
    Torre(int danio, int alcance, int costo, const Coordenada& posicion);

    // Destructor virtual: necesario porque vamos a borrar torres a traves
    // de un puntero a Torre (la clase base), y asi se llama al destructor
    // correcto de la subclase real (TorreArquero/TorreCanon).
    virtual ~Torre() = default;

    // Compara la distancia hasta el enemigo contra el alcance de la torre.
    bool estaEnRango(const Coordenada& posEnemigo) const;

    // Le hace danio al enemigo indicado (usa el danio actual de la torre).
    void atacar(Cozy& objetivo) const;

    // Cada subclase decide cuanto sube el danio/alcance y el nivel.
    virtual void mejorar() = 0;

    // Nombre del tipo de torre ("Arquero", "Canon"), usado para el menu
    // y para dibujar la letra en el mapa.
    virtual std::string getTipo() const = 0;

    // Deja la torre exactamente como estaba antes de una mejora. Solo lo
    // usa ComandoMejorarTorre::deshacer() para revertir el ultimo mejorar().
    void restaurar(int nivel, int danio, int alcance);

    // Getters: solo devuelven el valor actual, no modifican nada.
    int getDano() const;
    int getAlcance() const;
    int getCosto() const;
    int getNivel() const;
    const Coordenada& getPosicion() const;
};

#endif