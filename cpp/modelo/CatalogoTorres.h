#ifndef CATALOGO_TORRES_H
#define CATALOGO_TORRES_H

#include <string>
#include <vector>
#include "Coordenada.h"
#include "Torre.h"

// Lista de todos los tipos de torre que el jugador puede comprar, mas
// una fabrica para crear la instancia concreta a partir del indice elegido.
class CatalogoTorres {
public:
    // Solo sirve para mostrar informacion en el menu (nombre, costo,
    // stats base). No se usa para construir la Torre real: cada
    // subclase (TorreArquero/TorreCanon) fija sus propios stats.
    struct TipoTorre {
        std::string nombre;
        int costo;
        int danioBase;
        int alcanceBase;

        TipoTorre(std::string nombre, int costo, int danioBase, int alcanceBase);
    };

    // Arreglo fijo con los dos tipos disponibles. El indice dentro de
    // este arreglo es el mismo indice que el jugador escribe en el menu.
    static const std::vector<TipoTorre> TIPOS;

    // Imprime por consola cada tipo con su indice, costo y stats.
    static void mostrarOpciones();

    // Recibe el indice que eligio el jugador y la posicion donde quiere
    // colocar la torre, y devuelve un puntero a la subclase correspondiente
    // ya creada con "new" (el que llama a crear() se queda con la
    // responsabilidad de borrarla mas adelante).
    static Torre* crear(int indiceTipo, const Coordenada& pos);
};

#endif