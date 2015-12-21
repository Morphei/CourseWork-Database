#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    login = new QString;
    pass = new QString;

    LoginDialog logDialog(this, login, pass);
    logDialog.setModal(true);
    logDialog.exec();

    if(logDialog.result())
        connectToDatabase();
    else exit(0);

    model = new QSqlRelationalTableModel(this, database);
    changeTable("product");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToDatabase()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName(*login);
    database.setPassword(*pass);
    database.setDatabaseName("musicshop");

    if(!database.open())
    {
        QMessageBox::warning(this, "Error", "Unable to connect to database");
        LoginDialog logDialog(this, login, pass);
        logDialog.setModal(true);
        logDialog.exec();

        if(logDialog.result())
            connectToDatabase();
        else exit(0);
    }
}

void MainWindow::addRecord()
{
    saveChanges();
    model->insertRow(model->rowCount());
}

void MainWindow::saveChanges()
{
    if(model->submitAll())
        qDebug() << "good";
    else qDebug() << "bad";
}

void MainWindow::changeTable(const QString table)
{
    model->setTable(table);


    if(table == "product")
    {
        model->setRelation(2, QSqlRelation("manufacturer", "man_id", "man_name"));
        model->setRelation(3, QSqlRelation("category", "category_id", "category_name"));
        model->setRelation(8, QSqlRelation("country", "country_id", "country_name"));
    }

    if(table == "bill")
    {
        model->setRelation(2, QSqlRelation("product", "product_id", "product_name"));
        model->setRelation(3, QSqlRelation("client", "client_id", "client_name"));
    }
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->hideColumn(0);
    ui->tableView->show();
}

void MainWindow::on_pushButton_clicked()
{
    addRecord();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    changeTable(arg1);
}

void MainWindow::on_pushButton_2_clicked()
{
    saveChanges();
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}
