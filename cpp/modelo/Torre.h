#ifndef TORRE_H
#define TORRE_H

// TODO: clase base abstracta - mejorar() y getTipo() son virtuales puros
class Torre {
public:
    virtual ~Torre() = default;
    virtual void mejorar() = 0;
};

#endif
