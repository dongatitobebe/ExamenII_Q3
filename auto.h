// auto.h
#ifndef AUTO_H
#define AUTO_H

#include "vehiculo.h"

class Auto : public Vehiculo {
public:
    Auto(const std::string& modelo, int año, float kilometraje);
    float calcularMantenimiento() const override;
};

#endif // AUTO_H
