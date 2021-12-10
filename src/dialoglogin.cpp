#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include "Control_DB.h"
#include "dia_createuser.h"
#include "mainw_datos.h"
#include <string>
#include <QMessageBox>


DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
}

DialogLogin::~DialogLogin()
{
    QMessageBox:: information(this, "Close","CHAU");
    delete ui;
}

void DialogLogin::on_pushButton_loging_clicked()
{
    int D_Us[7];
    for (int i = 0; i < 7; i++){
        D_Us[i] = 0;
    }
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    Control_DB control("Sensores.db");

    control.abrir_DB();
    control.Comprobar_U(username.toStdString(), password.toStdString(), D_Us);
    control.cerrar_DB();
    if (D_Us[0] >= 5 && D_Us[0] <= 20) {
        QMessageBox:: information(this, "Login","Usuario y contraseña correcta");
        //emit usuarioCorrecto(true);
        emit usuarioCorrecto(D_Us[6]);
        this->close();

    } else{
        QMessageBox:: warning(this, "Login","Usuario o contraseña incorrecta");
    }
}

void DialogLogin::on_pushButton_register_clicked()
{
    Dia_createUser cu;
    //cu.setModal(true);
    this->hide();
    cu.show();
    cu.exec();
    this->show();
}












