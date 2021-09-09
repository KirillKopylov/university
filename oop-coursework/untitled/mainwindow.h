#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "database.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "editcustomer.h"
#include "addcustomer.h"
#include "addmoney.h"
#include "outputdocuments.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlTableModel *getModel();

private slots:
    void search(const QString &searchValue);
    void addCustomer();
    void removeCustomer();
    void editCustomer();
    void addMoney();
    void resizeTable();
    void updateTable();
    void clearTable();
    void contextMenu(QPoint pos);
    void selectRow();
signals:
    void customerRemoved();
private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    Database *db;
    QMessageBox *msgBox;
    EditCustomer *edit;
    AddCustomer *add;
    AddMoney *money;
    OutputDocuments *output;
    enum Columns {
        ID = 0,
        SURNAME,
        NAME,
        PATRONYMIC,
        BALANCE,
        CITY,
        STREET,
        BUILDING,
        APARTMENT,
        TYPE,
        TARIFF,
        CONNECTED,
        LAST_PAY,
        STATUS
    };
    void setupModel();
    void openDatabase();
    void setupWindow();
    void setConnects();
};

#endif // MAINWINDOW_H
