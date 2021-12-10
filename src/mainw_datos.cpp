#include "mainw_datos.h"
#include "ui_mainw_datos.h"
#include <QTimer>
#include <QTime>
#include <sstream>

MainW_datos::MainW_datos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainW_datos)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainW_datos::actualizarDatos);
    //connect(timer,&QTimer::timeout,this,&MainW_datos::setval);
    timer->start(1000);

    actualizarDatos();
    w.show();
    connect( &w, &DialogLogin::usuarioCorrecto, this, &MainW_datos::ingresoUsurio);

}

MainW_datos::~MainW_datos()
{
    delete ui;
    delete timer;
}

void MainW_datos::setval()
{
    ui->lineEdit_temperatura->setText(QString::number(_cont++));
}

void MainW_datos::ingresoUsurio(int ingreso)
{
    this->show();
    _cultivo = ingreso;
    if (_cultivo == 1) ui->label_Cultivo->setText("Alerta papa");
    else ui->label_Cultivo->setText("Alerta rosa");
}

void MainW_datos::actualizarDatos()
{

    double Datos[18];
    int Dias[2];
    for (int i = 0; i < 18; i++){
        Datos[i] = 0.0;
    }
    for (int i = 0; i < 2; i++){
        Dias[i] = 0.0;
    }

    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2)==0)
        text[2]=' ';
    _control.abrir_DB();
    _control.ObtenerDatos_DB(Datos);
    _control.ObtenerDias_DB(Dias);
    _control.cerrar_DB();

    stringstream sql;
    sql << Datos[0]<<" °C";
    ui->lineEdit_temperatura->setText(QString::fromStdString(sql.str()));
    sql.str("");
    sql << Datos[3]<<" %";
    ui->lineEdit_humedad->setText(QString::fromStdString(sql.str()));
    sql.str("");
    sql << Datos[6]<<" m/s";
    ui->lineEdit_velocidad->setText(QString::fromStdString(sql.str()));
    sql.str("");
    sql << Datos[9]<<" ° Norte";
    ui->lineEdit_direccion->setText(QString::fromStdString(sql.str()));
    sql.str("");
    sql << Datos[12]<<" mm";
    ui->lineEdit_precipitacion->setText(QString::fromStdString(sql.str()));
    sql.str("");
    sql << Datos[15]<<" lumen";
    ui->lineEdit_intensidadLuz->setText(QString::fromStdString(sql.str()));
    if (_cultivo == 1){
        if (Dias[0] == 0) ui->lineEdit_Alerta->setStyleSheet("background-color: green");
        else if (Dias[0] == 1) ui->lineEdit_Alerta->setStyleSheet("background-color: yellow");
        else ui->lineEdit_Alerta->setStyleSheet("background-color: red");
    }
    else{
        if (Dias[1] >= 0 && Dias[1] <= 30) ui->lineEdit_Alerta->setStyleSheet("background-color: red");
        else if (Dias[1] > 30 && Dias[1] < 90) ui->lineEdit_Alerta->setStyleSheet("background-color: yellow");
        else ui->lineEdit_Alerta->setStyleSheet("background-color: green");
    }


}



