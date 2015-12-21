#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0, QSqlDatabase* db = NULL);
    void setTable(QString table);
    ~FindDialog();

private slots:
    void on_pushButton_clicked();

private:
    void updateView();

    Ui::FindDialog *ui;
    QString table;
    QSqlRelationalTableModel* model;
    QSqlDatabase* database;
    QSqlQuery* query;
};

#endif // FINDDIALOG_H
