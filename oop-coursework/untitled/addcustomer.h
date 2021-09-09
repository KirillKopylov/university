#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class AddCustomer;
}

class AddCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomer(QWidget *parent = 0);
    ~AddCustomer();

private slots:
    void addCustomer();
    void check();
    void closeWindow();
signals:
    void applyChanges();

private:
    Ui::AddCustomer *ui;
    Database *database;
};

#endif // ADDCUSTOMER_H
