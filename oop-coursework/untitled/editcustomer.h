#ifndef EDITCUSTOMER_H
#define EDITCUSTOMER_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMessageBox>

namespace Ui {
class EditCustomer;
}

class EditCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit EditCustomer(QWidget *parent = 0);
    ~EditCustomer();
    void setModel(QAbstractItemModel *model);
    QDataWidgetMapper *mapper;
private slots:
    void editCustomer();
    void check();
signals:
    void applyChanges();
private:
    Ui::EditCustomer *ui;
};

#endif // EDITCUSTOMER_H
