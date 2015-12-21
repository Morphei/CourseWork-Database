#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this, *db);
    database = db;
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    query = new QSqlQuery(*database);
}

void FindDialog::setTable(QString table)
{
    model->setTable(table);
    this->table = table;
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

    int i = 1;
    ui->comboBox->clear();
    while(i < model->columnCount())
    {
        ui->comboBox->addItem(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        i++;
    }
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_pushButton_clicked()
{
    query->prepare("SELECT * FROM "+ table + " WHERE " + ui->comboBox->currentText() + " =:value");
    query->bindValue(":value", ui->lineEdit->text());

    updateView();
}

void FindDialog::updateView()
{

    int count = model->columnCount();

    delete model;
    model = new QSqlRelationalTableModel(this, *database);

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

    ui->tableView->reset();
    ui->tableView->setModel(model);
    ui->tableView->update();

    if(!query->exec())
    {
        QMessageBox* box = new QMessageBox(this);
        box->setText(query->lastError().text());
        box->show();
    }
    else
    {
        int row = 0;
        while(query->next())
        {
            for(int i = 0; i < count; i++)
            {
                model->insertRow(row);
                model->setData(model->index(row, i), query->value(i));
            }
            model->submitAll();
            row++;
        }

        ui->tableView->update();
        ui->tableView->show();
    }


}
