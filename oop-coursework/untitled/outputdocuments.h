#ifndef OUTPUTDOCUMENTS_H
#define OUTPUTDOCUMENTS_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include "database.h"

namespace Ui {
class OutputDocuments;
}

class OutputDocuments : public QDialog
{
    Q_OBJECT

public:
    explicit OutputDocuments(QWidget *parent = 0);
    ~OutputDocuments();
private slots:
    void getPaymentsHistory();
    void getDebtorsList();
    void getSortedList(int city);
    void savePaymentsHistory();
    void saveDebtorsList();
    void saveSortedList();
    void savePriceList();
    void check(int index);
    void update();
private:
    Ui::OutputDocuments *ui;
    Database *db;
};

#endif // OUTPUTDOCUMENTS_H
