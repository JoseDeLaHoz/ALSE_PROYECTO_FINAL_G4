/**
 * @file mainw_datos.h
 * @authors Juan Felipe Otálora, José Luis de la Hoz y Victor Daniel Escobar
 * @date 10/12/2021
 * @brief Aquí es donde se crean las funciones y cuadros de texto que se usarán en la interfaz gráfica para la ventana que muestra los datos de los sensores del cultivo respectivo.
 */

#ifndef MAINW_DATOS_H
#define MAINW_DATOS_H

#include <QMainWindow>
#include <QTimer>
#include "Control_DB.h"
#include "dialoglogin.h"

namespace Ui {
class MainW_datos;
}
/**
 * @brief Definición de la clase MainW_datos. Aquí se maneja la interfaz donde se van a mostrar los datos de los sensores del cultivo respectivo.
 */
class MainW_datos : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainW_datos
     * @param parent
     */
    explicit MainW_datos(QWidget *parent = nullptr);
    /**
      *Destructor de MainW_Datos().
      */
    ~MainW_datos();


private slots:
    /**
     * @brief actualizarDatos ""
     */
    void actualizarDatos();
    /**
     * @brief setval ""
     */
    void setval();
    /**
     * @brief ingresoUsurio ""
     * @param Cultivo
     */
    void ingresoUsurio(int Cultivo);

private:
    /**
     * @brief ui ""
     */
    Ui::MainW_datos *ui;
    /**
     * @brief _Datos esta variable ""
     */
    double _Datos[6];
    /**
     * @brief _cont esta variable ""
     */
    int _cont=0;

    Control_DB _control{"Sensores.db"};
    /**
     * @brief w ""
     */
    DialogLogin w;
    /**
     * @brief timer ""
     */
    QTimer *timer;
    /**
     * @brief _cultivo es la variable que almacenará el tipo de cultivo del cual se quieren recibir los datos y alertas de los sensores, siendo 1 el cultivo de papa y 2 el cultivo de rosas, este dato será recibido desde la interfaz gráfica.
     */
    int _cultivo = 1;
};

#endif // MAINW_DATOS_H
