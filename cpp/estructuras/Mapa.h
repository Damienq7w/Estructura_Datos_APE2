#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include "Coordenada.h"
#include "Torre.h"

// Representa el tablero de juego: la ruta fija por donde caminan los
// enemigos, la fuente de energia que hay que proteger, y todas las
// torres que el jugador ha ido colocando.
class Mapa {
private:
    const std::vector<Coordenada> ruta;   // camino fijo, no cambia despues de construir el mapa
    const Coordenada fuenteEnergia;         // ultima casilla de la ruta (lo que hay que defender)
    std::vector<Torre*> torres;              // "arreglo" de torres colocadas, tamano fijo (capacidadTorres)
    const int capacidadTorres;                // cuantas torres caben como maximo
    int cantidadTorres;                         // cuantas hay colocadas ahora mismo

public:
    // ruta: la secuencia completa de casillas del camino (la primera es
    // la entrada, la ultima se guarda como fuenteEnergia).
    // capacidadTorres: tamano fijo del "arreglo" interno de torres.
    Mapa(const std::vector<Coordenada>& ruta, int capacidadTorres);

    // Intenta colocar una torre. Falla (devuelve false) si ya no hay
    // espacio o si la casilla ya tiene otra torre.
    bool colocarTorre(Torre* t);

    // Busca la torre en el arreglo interno y la saca, recorriendo el
    // resto una posicion hacia adelante para no dejar huecos.
    void quitarTorre(Torre* t);

    // Recorre las torres activas buscando una en esa posicion exacta.
    // Se usa, por ejemplo, cuando el jugador quiere mejorar una torre y
    // solo da las coordenadas de la casilla.
    Torre* buscarTorreEn(const Coordenada& pos) const;

    // Dibuja el mapa en consola: 'E' = entrada de la ruta, 'F' = fuente
    // de energia, la letra inicial del tipo para cada torre colocada, y
    // '.' para las casillas libres.
    void imprimirMapa() const;

    const std::vector<Coordenada>& getRuta() const;
    const Coordenada& getFuenteEnergia() const;

    // Devuelve una copia solo de las torres realmente colocadas (no todo
    // el arreglo interno, que puede tener espacios vacios al final).
    std::vector<Torre*> getTorresActivas() const;
};

#endif
