
#include "vehiculo.h"

Vehiculo::Vehiculo(const std::string& modelo, int año, float kilometraje)
    : modelo(modelo), año(año), kilometraje(kilometraje) {}

std::string Vehiculo::getModelo() const {
    return modelo;
}

int Vehiculo::getAño() const {
    return año;
}

float Vehiculo::getKilometraje() const {
    return kilometraje;
}
