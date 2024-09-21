// vehiculo.h
#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>

class Vehiculo {
protected:
    std::string modelo;
    int año;
    float kilometraje;

public:
    Vehiculo(const std::string& modelo, int año, float kilometraje);
    virtual ~Vehiculo() = default;

    virtual float calcularMantenimiento() const = 0;

    std::string getModelo() const;
    int getAño() const;
    float getKilometraje() const;
};

#endif // VEHICULO_H
