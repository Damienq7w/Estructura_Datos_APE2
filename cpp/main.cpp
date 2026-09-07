#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "estructuras/ColaEnemigos.h"
#include "estructuras/GestorOleadas.h"
#include "estructuras/HistorialComandos.h"
#include "estructuras/Mapa.h"
#include "gestor/GestorJuego.h"
#include "modelo/CatalogoTorres.h"
#include "modelo/Coordenada.h"
#include "modelo/Oleada.h"
#include "modelo/Torre.h"

// Las torres se crean con "new" en CatalogoTorres::crear(); este vector es
// el dueno de todas ellas y las libera al terminar main (en Java de esto se
// encarga el recolector de basura).
static void imprimirMenu();
static void colocarTorre(GestorJuego& juego, Mapa& mapa,
                         std::vector<std::unique_ptr<Torre>>& torresCreadas);
static void mejorarTorre(GestorJuego& juego, Mapa& mapa);
static int leerEntero(const std::string& mensaje);
static Mapa crearMapaInicial();

int main() {
    Mapa mapa = crearMapaInicial();
    ColaEnemigos colaEnemigos;
    GestorOleadas gestorOleadas;
    HistorialComandos historial;
    GestorJuego juego(20, colaEnemigos, gestorOleadas, historial, mapa);

    std::vector<std::unique_ptr<Torre>> torresCreadas;

    // Se precargan 10 oleadas con dificultad creciente; GestorJuego las
    // libera una por una cuando la ruta queda vacia (ver procesarQuantum).
    for (int i = 1; i <= 10; i++) {
        gestorOleadas.agregarOleada(Oleada::generar(i));
    }

    bool finDelJuego = false;

    while (!finDelJuego) {
        juego.mostrarEstado();
        imprimirMenu();
        int opcion = leerEntero("Elige una opcion: ");

        switch (opcion) {
            case 1:
                colocarTorre(juego, mapa, torresCreadas);
                break;
            case 2:
                mejorarTorre(juego, mapa);
                break;
            case 3:
                juego.deshacerUltimaAccion();
                break;
            case 4:
                juego.rehacerUltimaAccion();
                break;
            case 5:
                juego.procesarQuantum();
                break;
            case 6:
                std::cout << "Saliendo del juego." << std::endl;
                finDelJuego = true;
                continue;
            default:
                std::cout << "Opcion invalida." << std::endl;
                continue;
        }

        // Se verifica derrota primero: si vidaJugador llega a 0 en el mismo
        // quantum en que se limpia la ultima oleada, gana la derrota.
        if (juego.juegoTerminado()) {
            juego.mostrarResultadoFinal(false);
            finDelJuego = true;
        } else if (juego.haGanado()) {
            juego.mostrarResultadoFinal(true);
            finDelJuego = true;
        }
    }

    return 0;
}

static void imprimirMenu() {
    std::cout << "1) Colocar torre" << std::endl;
    std::cout << "2) Mejorar torre" << std::endl;
    std::cout << "3) Deshacer" << std::endl;
    std::cout << "4) Rehacer" << std::endl;
    std::cout << "5) Avanzar quantum" << std::endl;
    std::cout << "6) Salir" << std::endl;
}

// Valida el indice antes de crear la torre para no dejar pasar
// un tipo inexistente a CatalogoTorres::crear().
static void colocarTorre(GestorJuego& juego, Mapa& mapa,
                         std::vector<std::unique_ptr<Torre>>& torresCreadas) {
    (void)mapa; // se recibe por paridad con la version Java; aqui no se usa
    CatalogoTorres::mostrarOpciones();
    int indiceTipo = leerEntero("Elige el tipo de torre: ");
    if (indiceTipo < 0 || indiceTipo >= static_cast<int>(CatalogoTorres::TIPOS.size())) {
        std::cout << "Tipo de torre invalido." << std::endl;
        return;
    }
    int fila = leerEntero("Fila: ");
    int columna = leerEntero("Columna: ");

    Torre* torre = CatalogoTorres::crear(indiceTipo, Coordenada(fila, columna));
    torresCreadas.emplace_back(torre); // el vector pasa a ser dueno de la torre
    bool colocada = juego.colocarTorreJugador(torre);
    std::cout << (colocada ? "Torre colocada."
                           : "No se pudo colocar (casilla ocupada o sin espacio).")
              << std::endl;
}

static void mejorarTorre(GestorJuego& juego, Mapa& mapa) {
    int fila = leerEntero("Fila de la torre a mejorar: ");
    int columna = leerEntero("Columna de la torre a mejorar: ");

    Torre* torre = mapa.buscarTorreEn(Coordenada(fila, columna));
    if (torre == nullptr) {
        std::cout << "No hay ninguna torre en esa posicion." << std::endl;
        return;
    }
    juego.mejorarTorreJugador(torre);
}

static int leerEntero(const std::string& mensaje) {
    std::cout << mensaje;
    int valor;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << mensaje;
    }
    return valor;
}

static Mapa crearMapaInicial() {
    std::vector<Coordenada> ruta = {
        Coordenada(0, 0),
        Coordenada(0, 1),
        Coordenada(0, 2),
        Coordenada(1, 2),
        Coordenada(2, 2),
        Coordenada(2, 3),
        Coordenada(2, 4)
    };
    return Mapa(ruta, 10);
}
