#include "Mapa.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Guarda la ruta tal cual se la pasan, la fuente de energia es la ultima
// casilla de esa ruta, y el arreglo de torres arranca lleno de nullptr.
Mapa::Mapa(const std::vector<Coordenada>& ruta_, int capacidadTorres_)
    : ruta(ruta_),
      fuenteEnergia(ruta_.back()),
      torres(capacidadTorres_, nullptr),
      capacidadTorres(capacidadTorres_),
      cantidadTorres(0) {}

bool Mapa::colocarTorre(Torre* t) {
    // No hay espacio: ya se llego a la capacidad maxima.
    if (cantidadTorres >= capacidadTorres) {
        return false;
    }
    // Ya hay otra torre en esa misma casilla.
    if (buscarTorreEn(t->getPosicion()) != nullptr) {
        return false;
    }
    // Se agrega al final del "arreglo" activo y se aumenta el contador.
    torres[cantidadTorres] = t;
    cantidadTorres++;
    return true;
}

void Mapa::quitarTorre(Torre* t) {
    // Primero se busca en que indice esta la torre.
    int indice = -1;
    for (int i = 0; i < cantidadTorres; i++) {
        if (torres[i] == t) {
            indice = i;
            break;
        }
    }
    // Si no se encontro, no hay nada que hacer.
    if (indice == -1) {
        return;
    }
    // Se recorre desde esa posicion hacia adelante, moviendo cada torre
    // un lugar hacia atras (esto "tapa" el hueco que deja la que se quito).
    for (int i = indice; i < cantidadTorres - 1; i++) {
        torres[i] = torres[i + 1];
    }
    // La ultima posicion activa queda libre otra vez.
    torres[cantidadTorres - 1] = nullptr;
    cantidadTorres--;
}

Torre* Mapa::buscarTorreEn(const Coordenada& pos) const {
    // Recorre solo la parte activa del arreglo (0 .. cantidadTorres-1) y
    // compara posiciones con equals().
    for (int i = 0; i < cantidadTorres; i++) {
        if (torres[i]->getPosicion().equals(pos)) {
            return torres[i];
        }
    }
    return nullptr;
}

void Mapa::imprimirMapa() const {
    // Primero se calcula cuantas filas y columnas necesita la grilla,
    // revisando tanto la ruta como las torres colocadas (por si alguna
    // esta mas alla del propio camino).
    int filas = 0;
    int columnas = 0;
    for (const Coordenada& c : ruta) {
        filas = std::max(filas, c.getFila() + 1);
        columnas = std::max(columnas, c.getColumna() + 1);
    }
    for (int i = 0; i < cantidadTorres; i++) {
        const Coordenada& p = torres[i]->getPosicion();
        filas = std::max(filas, p.getFila() + 1);
        columnas = std::max(columnas, p.getColumna() + 1);
    }

    // Se arma una grilla de caracteres, todo lleno de '.' (casilla libre)
    // al empezar.
    std::vector<std::vector<char>> grilla(filas, std::vector<char>(columnas, '.'));

    // Se marcan la entrada ('E') y la fuente de energia ('F').
    const Coordenada& entrada = ruta.front();
    grilla[entrada.getFila()][entrada.getColumna()] = 'E';
    grilla[fuenteEnergia.getFila()][fuenteEnergia.getColumna()] = 'F';

    // Se marca cada torre con la primera letra de su tipo ('A' de
    // Arquero, 'C' de Canon).
    for (int i = 0; i < cantidadTorres; i++) {
        const Coordenada& p = torres[i]->getPosicion();
        grilla[p.getFila()][p.getColumna()] = torres[i]->getTipo()[0];
    }

    // Se imprime fila por fila, con un espacio entre cada caracter para
    // que se vea como grilla y no como texto pegado.
    for (const std::vector<char>& fila : grilla) {
        std::ostringstream sb;
        for (char c : fila) {
            sb << c << ' ';
        }
        std::string linea = sb.str();
        // Se quita el espacio extra que queda al final de la linea.
        while (!linea.empty() && linea.back() == ' ') {
            linea.pop_back();
        }
        std::cout << linea << std::endl;
    }
}

const std::vector<Coordenada>& Mapa::getRuta() const { return ruta; }
const Coordenada& Mapa::getFuenteEnergia() const { return fuenteEnergia; }

// Copia solo la parte del arreglo que esta realmente en uso (los
// primeros cantidadTorres elementos), dejando fuera los nullptr sobrantes.
std::vector<Torre*> Mapa::getTorresActivas() const {
    return std::vector<Torre*>(torres.begin(), torres.begin() + cantidadTorres);
}
