#include "addcustomer.h"
#include "ui_addcustomer.h"

AddCustomer::AddCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomer)
{
    ui->setupUi(this);
    database = new Database(this);
    connect(ui->pbApply, SIGNAL(clicked(bool)), this, SLOT(check()));
    connect(ui->pbCancel, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(ui->cbMoney, SIGNAL(clicked(bool)), ui->spBalance, SLOT(setVisible(bool)));
    ui->spBalance->setVisible(false);
    QRegExp expression("[А-ЯІЄ{1}][а-яґєії]{39}");
    QRegExpValidator *validator = new QRegExpValidator(expression, this);
    ui->lineName->setValidator(validator);
    ui->lineSurname->setValidator(validator);
    ui->linePatronymic->setValidator(validator);
    ui->lineStreet->setValidator(validator);
}

AddCustomer::~AddCustomer()
{
    delete ui;
}

void AddCustomer::addCustomer()
{
    QString name = ui->lineName->text();
    QString surname = ui->lineSurname->text();
    QString patronymic = ui->linePatronymic->text();
    int balance = ui->spBalance->text().toInt();
    QString city = ui->cbCities->currentText();
    QString street = ui->lineStreet->text();
    int building = ui->spBuilding->text().toInt();
    int apartment = ui->spApartment->text().toInt();
    QString type = ui->cbConnectionTypes->currentText();
    QString tariff = ui->cbTariffs->currentText();
    QString status;
    QString connected = QDateTime::currentDateTime().toString("dd.MM.yyyy, hh:mm:ss");
    QString last_pay;
    if(ui->cbMoney->isChecked() && ui->spBalance->value() > 0) {
        last_pay = connected;
        status = "Підключений";
    } else {
        last_pay = "";
        status = "Відключений";
    }
    foreach(QLineEdit *le, findChildren<QLineEdit*>()) {
        le->clear();
    }
    ui->cbMoney->setChecked(false);
    ui->spBalance->setVisible(false);
    ui->spBalance->setValue(0);
    QVariantList data;
    data.append(surname);
    data.append(name);
    data.append(patronymic);
    data.append(balance);
    data.append(city);
    data.append(street);
    data.append(building);
    data.append(apartment);
    data.append(type);
    data.append(tariff);
    data.append(connected);
    data.append(last_pay);
    data.append(status);
    database->insertIntoTable(data);
    emit applyChanges();
    close();
}

void AddCustomer::check()
{
    if(ui->lineName->text().length() < 2
            || ui->lineSurname->text().length() < 2
            || ui->linePatronymic->text().length() < 2
            || ui->lineStreet->text().length() < 2)
        QMessageBox::warning(this, "Помилка вводу", "Перевірте введені дані");
    else
        this->addCustomer();
}

void AddCustomer::closeWindow()
{
    foreach(QLineEdit *le, findChildren<QLineEdit*>()) {
        le->clear();
    }
    close();
}
