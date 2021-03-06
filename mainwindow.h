#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

#include "logindialog.h"
#include "finddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_actionQuit_triggered();

    void on_actionFind_in_products_triggered();

    void on_actionFind_in_clients_triggered();

    void on_actionFind_in_bills_triggered();

private:
    QString* login, *pass;

    Ui::MainWindow *ui;
    FindDialog* findForm;

    QSqlDatabase database;
    QSqlRelationalTableModel* model;
    QLabel* statusBarLabel;

    void connectToDatabase();
    void addRecord();
    void saveChanges();
    void changeTable(const QString table);
};

#endif // MAINWINDOW_H
