#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <vector>
#include <algorithm>


class Estudiante {
protected:
    std::string nombre;
    int edad;
    std::vector<std::string> materias;
    std::vector<int> calificaciones;

public:
    Estudiante(const std::string& nombre, int edad);
    virtual ~Estudiante() {}

    void agregarMateria(const std::string& nombreMateria, int calificacion);

    virtual double promedio() const = 0;


    std::string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    std::vector<std::string> getMaterias() const { return materias; }
    std::vector<int> getCalificaciones() const { return calificaciones; }


    void mostrarInformacion() const;
};


class EstudianteLicenciatura : public Estudiante {
public:
    EstudianteLicenciatura(const std::string& nombre, int edad);
    double promedio() const override;
};


class EstudianteMaestria : public Estudiante {
public:
    EstudianteMaestria(const std::string& nombre, int edad);
    double promedio() const override;
};

#endif // ESTUDIANTE_H
