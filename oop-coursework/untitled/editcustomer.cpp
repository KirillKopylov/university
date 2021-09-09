#include "editcustomer.h"
#include "ui_editcustomer.h"

EditCustomer::EditCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCustomer)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    connect(ui->pbApply, SIGNAL(clicked(bool)), this, SLOT(check()));
    connect(ui->pbCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    QRegExp expression("[А-ЯІЄ{1}][а-яґєії]{39}");
    QRegExpValidator *validator = new QRegExpValidator(expression, this);
    ui->lineName->setValidator(validator);
    ui->lineSurname->setValidator(validator);
    ui->lineStreet->setValidator(validator);
}

EditCustomer::~EditCustomer()
{
    delete ui;
}

void EditCustomer::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->lineSurname, 1);
    mapper->addMapping(ui->lineName, 2);
    mapper->addMapping(ui->linePatronymic, 3);
    mapper->addMapping(ui->cbCities, 5);
    mapper->addMapping(ui->lineStreet, 6);
    mapper->addMapping(ui->spBuilding, 7);
    mapper->addMapping(ui->spApartment, 8);
    mapper->addMapping(ui->cbConnectionTypes, 9);
    mapper->addMapping(ui->cbTariffs, 10);
}

void EditCustomer::editCustomer()
{
    mapper->submit();
    emit applyChanges();
    close();
}

void EditCustomer::check()
{
    if(ui->lineName->text().length() < 2
            || ui->lineSurname->text().length() < 2
            || ui->linePatronymic->text().length() < 2
            || ui->lineStreet->text().length() < 2)
        QMessageBox::warning(this, "Помилка вводу", "Перевірте введені дані");
    else
        this->editCustomer();
}
