#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include <vector>
#include <memory>
#include <QListWidget>
#include "Estudiante.h"
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

private slots:
    void on_Bton_Agregarestudiante_clicked();
    void on_pushButton_clicked();
    void on_lw_listadoestudiante_itemClicked(QListWidgetItem *item);

    void on_bton_eliminarEstudiante_clicked();

    void on_bton_AgregarAuto_clicked();

    void on_bton_Agregarcamion_clicked();

    void on_bton_seleccionarEmpleado_clicked();

private:
    Ui::cframe *ui;
    std::vector<std::unique_ptr<Estudiante>> estudiantes;

    void guardarEnArchivo();
    void cargarDesdeArchivo();
    void actualizarListadoEstudiantes();
    void cargarEstudiantesEnLista();
    Estudiante* buscarEstudiante(const std::string& nombre, int edad, const std::string& tipoClase);

    QTextEdit *te_AgregarCarro;
      QTextEdit *te_AgregarCamion;

};

#endif // CFRAME_H
