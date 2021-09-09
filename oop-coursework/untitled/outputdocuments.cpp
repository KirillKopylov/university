#include "outputdocuments.h"
#include "ui_outputdocuments.h"

OutputDocuments::OutputDocuments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutputDocuments)
{
    ui->setupUi(this);
    db = new Database(this);
    this->getDebtorsList();
    this->getPaymentsHistory();
    this->getSortedList(0);
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(check(int)));
    connect(ui->pbUpdate, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->pbPaymentsHistory, SIGNAL(clicked(bool)), this, SLOT(savePaymentsHistory()));
    connect(ui->pbDebtors, SIGNAL(clicked(bool)), this, SLOT(saveDebtorsList()));
    connect(ui->pbPrice, SIGNAL(clicked(bool)), this, SLOT(savePriceList()));
    connect(ui->cbSities, SIGNAL(currentIndexChanged(int)), this, SLOT(getSortedList(int)));
    connect(ui->pbSort, SIGNAL(clicked(bool)), this, SLOT(saveSortedList()));
}

OutputDocuments::~OutputDocuments()
{
    delete ui;
}

void OutputDocuments::getPaymentsHistory()
{
    ui->listPaymentsHistory->clear();
    QList<QString> payments = db->getPaymentsHistory();
    QString item;
    foreach (item, payments) {
        ui->listPaymentsHistory->addItem(item);
    }
}

void OutputDocuments::getDebtorsList()
{
    ui->listDebtors->clear();
    QList<QString> debtors = db->getDebtors();
    QString item;
    foreach (item, debtors) {
        ui->listDebtors->addItem(item);
    }
}

void OutputDocuments::savePaymentsHistory()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Зберегти історію платежів"), "",
                                                    tr("Log File (*.log)"));
    if(fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);
        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream stream(&file);
        QList<QString> payments = db->getPaymentsHistory();
        QString item;
        QString buffer;
        foreach (item, payments) {
            buffer += item + '\n';
        }
        stream << buffer;
    }
}

void OutputDocuments::saveDebtorsList()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Зберегти список боржників"), "",
                                                    tr("Log File (*.log)"));
    if(fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);
        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream stream(&file);
        QList<QString> debtors = db->getDebtors();
        QString item;
        QString buffer;
        foreach (item, debtors) {
            buffer += item + '\n';
        }
        stream << buffer;
    }
}

void OutputDocuments::getSortedList(int city)
{
    QString item;
    QList<QString> sorted;
    switch(city) {
    case 0:
        ui->listSort->clear();
        sorted = db->getCities("Маріуполь");
        foreach (item, sorted) {
            ui->listSort->addItem(item);
        }
        break;
    case 1:
        ui->listSort->clear();
        sorted = db->getCities("Покровськ");
        foreach (item, sorted) {
            ui->listSort->addItem(item);
        }
        break;
    case 2:
        ui->listSort->clear();
        sorted = db->getCities("Авдіївка");
        foreach (item, sorted) {
            ui->listSort->addItem(item);
        }
        break;
    }
}

void OutputDocuments::saveSortedList()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Зберегти список"), "",
                                                    tr("Log File (*.log)"));
    if(fileName.isEmpty()) {
        return;
    } else {
        QFile file(fileName);
        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream stream(&file);
        QString item;
        QString buffer;
        QList<QString> cities;
        int city = ui->cbSities->currentIndex();
        switch(city) {
        case 0:
            cities = db->getCities("Маріуполь");
            foreach(item, cities) {
                buffer += item + '\n';
            }
            stream << buffer;
            break;
        case 1:
            cities = db->getCities("Покровськ");
            foreach(item, cities) {
                buffer += item + '\n';
            }
            stream << buffer;
            break;
        case 2:
            cities = db->getCities("Авдіївка");
            foreach(item, cities) {
                buffer += item + '\n';
            }
            stream << buffer;
            break;
        }
    }
}

void OutputDocuments::savePriceList()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Зберегти прайс-лист"), "",
                                                    tr("Log File (*.log)"));
    if(fileName.isEmpty()) {
        return;
    } else {
        QFile list(fileName);
        list.open(QFile::WriteOnly | QFile::Text);
        QTextStream stream(&list);
        int cities = ui->spCities->value();
        int privateSector = ui->spPrivateSector->value();
        int masterCost = ui->spMaster->value();
        int ethernet = ui->spEthernet->value();
        int os = ui->spOperatingSystem->value();
        int hardware = ui->spHardware->value();
        QString price = "Вартість підключення (багатоповерхівки): " + QString::number(cities) + "\n" +
                "Вартість підключення (приватний сектор): " + QString::number(privateSector) + "\n" +
                "Виклик фахівця на об'єкт: " + QString::number(masterCost) + "\n" +
                "Метр звитої пари: " + QString::number(ethernet) + "\n" +
                "Налаштування ОС: " + QString::number(os) + "\n" +
                "Налаштування обладнання: " + QString::number(hardware);
        stream << price;
        list.close();
    }
}

void OutputDocuments::check(int index)
{
    if(index > 1)
        ui->pbUpdate->setEnabled(false);
    else
        ui->pbUpdate->setEnabled(true);
}

void OutputDocuments::update()
{
    this->getPaymentsHistory();
    this->getDebtorsList();
}
