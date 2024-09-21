#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

class Empleado {
protected:
    std::string nombre;
    int edad;

public:
    Empleado(const std::string& nombre, int edad);
    virtual ~Empleado() = default;

    virtual float calcularSalario() const = 0;
    virtual void guardar(std::ofstream& out) const;
    virtual void cargar(std::ifstream& in);
};

class EmpleadoFijo : public Empleado {
private:
    float salarioFijo;

public:
    EmpleadoFijo(const std::string& nombre, int edad, float salarioFijo);
    float calcularSalario() const override;
    void guardar(std::ofstream& out) const override;
    void cargar(std::ifstream& in) override;
};

class EmpleadoContratado : public Empleado {
private:
    float tarifaPorHora;
    int horasTrabajadas;

public:
    EmpleadoContratado(const std::string& nombre, int edad, float tarifaPorHora, int horasTrabajadas);
    float calcularSalario() const override;
    void guardar(std::ofstream& out) const override;
    void cargar(std::ifstream& in) override;
};

class Empresa {
private:
    std::vector<std::unique_ptr<Empleado>> empleados;

public:
    void agregarEmpleado(Empleado* empleado);
    void eliminarEmpleado(int index);
    void guardarEmpleados(const std::string& archivo);
    void cargarEmpleados(const std::string& archivo);
};

#endif // EMPLEADO_H
