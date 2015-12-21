#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent, QString *login, QString *pass);
    ~LoginDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_LoginDialog_finished(int result);

private:
    Ui::LoginDialog *ui;
    QString* usrLogin, *usrPass;
};

#endif // LOGINDIALOG_H
