#include "addmoney.h"
#include "ui_addmoney.h"

AddMoney::AddMoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMoney)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);
    timer = new QTimer(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    connect(ui->pbApply, SIGNAL(clicked(bool)), this, SLOT(addMoney()));
    connect(ui->pbCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->cbConnectionStatus, SIGNAL(currentIndexChanged(int)), this, SLOT(compare()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
}

AddMoney::~AddMoney()
{
    delete ui;
}

void AddMoney::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->spBalance, 4);
    mapper->addMapping(ui->label, 12);
    mapper->addMapping(ui->cbConnectionStatus, 13);
}

void AddMoney::addMoney()
{
    mapper->submit();
    ui->spBalance->setValue(0);
    emit applyChanges();
    close();
}

void AddMoney::updateTime()
{
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy, hh:mm:ss");
    ui->label->setText(date);
}

void AddMoney::compare()
{
    int index = ui->cbConnectionStatus->currentIndex();
    switch(index) {
    case 0:
        ui->spBalance->setReadOnly(false);
        mapper->addMapping(ui->label, 12);
        ui->spBalance->setMinimum(1);
        break;
    case 1:
        ui->spBalance->setReadOnly(false);
        ui->spBalance->setMinimum(0);
        break;
    case 2:
        ui->spBalance->setMinimum(-1);
        ui->spBalance->setValue(-1);
        ui->spBalance->setReadOnly(true);
        break;
    }
}
