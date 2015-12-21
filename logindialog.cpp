#include "logindialog.h"
#include "ui_logindialog.h"

#include <qdebug.h>

LoginDialog::LoginDialog(QWidget *parent, QString *login, QString *pass) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    usrLogin = login;
    usrPass = pass;

    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::on_buttonBox_clicked(QAbstractButton *button)
{

}

void LoginDialog::on_LoginDialog_finished(int result)
{
    if(this->result())
        {
            *usrLogin = this->ui->lineEdit->text();
            *usrPass = this->ui->lineEdit_2->text();
        }
    else exit(0);

    delete ui;
}
