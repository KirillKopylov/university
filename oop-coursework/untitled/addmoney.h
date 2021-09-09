#ifndef ADDMONEY_H
#define ADDMONEY_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QDate>
#include <QTimer>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class AddMoney;
}

class AddMoney : public QDialog
{
    Q_OBJECT

public:
    explicit AddMoney(QWidget *parent = 0);
    ~AddMoney();
    QDataWidgetMapper *mapper;
    void setModel(QAbstractItemModel *model);
private slots:
    void addMoney();
    void updateTime();
    void compare();
signals:
    void applyChanges();

private:
    Ui::AddMoney *ui;
    QTimer *timer;
};

#endif // ADDMONEY_H
