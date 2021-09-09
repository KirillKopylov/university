#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msgBox = new QMessageBox(this);
    db = new Database(this);
    this->openDatabase();
    model = new QSqlTableModel(this);
    edit = new EditCustomer(this);
    add = new AddCustomer(this);
    money = new AddMoney(this);
    output = new OutputDocuments(this);
    this->setupModel();
    this->setupWindow();
    this->setConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlTableModel *MainWindow::getModel()
{
    return model;
}

void MainWindow::search(const QString &searchValue)
{
    model->setFilter(QString("SURNAME LIKE '%%1%'").arg(searchValue));
    if(searchValue.isEmpty()) {
        model->setFilter("");
        this->selectRow();
    }

}

void MainWindow::addCustomer()
{
    add->exec();
    this->selectRow();
}

void MainWindow::removeCustomer()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if(selectedRow >= 0) {
        msgBox->setWindowTitle("Видалення запису");
        msgBox->setIcon(QMessageBox::Question);
        msgBox->setText("Ви впевнені?");
        msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int res = msgBox->exec();
        if(res == QMessageBox::Ok) {
            model->removeRow(selectedRow);
            model->select();
            resizeTable();
            emit customerRemoved();
        } else {
            return;
        }
    }
}

void MainWindow::editCustomer()
{
    edit->mapper->setCurrentModelIndex(ui->tableView->currentIndex());
    edit->exec();
}

void MainWindow::addMoney()
{
    money->mapper->setCurrentModelIndex(ui->tableView->currentIndex());
    money->exec();
}

void MainWindow::resizeTable()
{
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::updateTable()
{
    model->select();
}

void MainWindow::clearTable()
{
    msgBox->setWindowTitle("Очищення таблиці");
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setText("Ви впевнені?");
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int res = msgBox->exec();
    if(res == QMessageBox::Ok) {
        db->dropTable();
        model->select();
    } else {
        return;
    }
}

void MainWindow::contextMenu(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    QAction *deleteCustomer = new QAction(tr("Видалити"), this);
    QAction *editCustomer = new QAction(tr("Редагувати"), this);
    QAction *addMoney = new QAction(tr("Керування балансом"), this);
    connect(deleteCustomer, SIGNAL(triggered(bool)), this, SLOT(removeCustomer()));
    connect(editCustomer, SIGNAL(triggered(bool)), this, SLOT(editCustomer()));
    connect(addMoney, SIGNAL(triggered(bool)), this, SLOT(addMoney()));
    menu->addAction(editCustomer);
    menu->addAction(addMoney);
    menu->addAction(deleteCustomer);
    menu->popup(ui->tableView->mapToGlobal(pos));
}

void MainWindow::selectRow()
{
    ui->tableView->selectRow(0);
}

void MainWindow::setupModel()
{
    model->setTable("Customers");
    model->select();
    edit->setModel(model);
    money->setModel(model);
    model->setHeaderData(ID, Qt::Horizontal,  QObject::tr("ID"));
    model->setHeaderData(SURNAME, Qt::Horizontal, QObject::tr("Прізвище"));
    model->setHeaderData(NAME, Qt::Horizontal, QObject::tr("Ім'я"));
    model->setHeaderData(PATRONYMIC, Qt::Horizontal, QObject::tr("По батькові"));
    model->setHeaderData(BALANCE, Qt::Horizontal, QObject::tr("Баланс"));
    model->setHeaderData(CITY, Qt::Horizontal, QObject::tr("Місто"));
    model->setHeaderData(STREET, Qt::Horizontal, QObject::tr("Вулиця"));
    model->setHeaderData(BUILDING, Qt::Horizontal, QObject::tr("Будинок"));
    model->setHeaderData(APARTMENT, Qt::Horizontal, QObject::tr("Квартира"));
    model->setHeaderData(TYPE, Qt::Horizontal, QObject::tr("Тип підключення"));
    model->setHeaderData(TARIFF, Qt::Horizontal, QObject::tr("Тариф"));
    model->setHeaderData(CONNECTED, Qt::Horizontal, QObject::tr("Підключений"));
    model->setHeaderData(LAST_PAY, Qt::Horizontal, QObject::tr("Остання оплата"));
    model->setHeaderData(STATUS, Qt::Horizontal, QObject::tr("Статус"));
}

void MainWindow::openDatabase()
{
    QString dbLocation = QApplication::applicationDirPath() + "/customers.sqlite";
    if(QFile(dbLocation).exists()) {
        db->connectToDatabase();
        this->setWindowTitle("Відкрита база даних - " + dbLocation);
    } else {
        msgBox->setWindowTitle("Не вдалося знайти БД за замовчуванням");
        msgBox->setIcon(QMessageBox::Question);
        msgBox->setText("Не вдалося знайти БД за замовчуванням\nВказати шлях до БД вручну?");
        msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int res = msgBox->exec();
        switch(res) {
        case QMessageBox::Ok: {
            QString path = QFileDialog::getOpenFileName(this, tr("Вибір БД вручну"), "", tr("База даних (*.sqlite)"));
            db->connectToDatabase(path);
            this->setWindowTitle("Відкрита база даних - " + path);
            break;
        }
        case QMessageBox::Cancel:
            exit(0);
        }
    }
}

void MainWindow::setupWindow()
{
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->selectRow(0);
}

void MainWindow::setConnects()
{
    connect(ui->lineSearch, SIGNAL(textChanged(QString)), this, SLOT(search(QString)));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
    connect(ui->mtbAddCustomer, SIGNAL(triggered(bool)), this, SLOT(addCustomer()));
    connect(ui->mtbEditCustomer, SIGNAL(triggered(bool)), this, SLOT(editCustomer()));
    connect(ui->mtbAddMoney, SIGNAL(triggered(bool)), this, SLOT(addMoney()));
    connect(ui->mtbRemoveCustomer, SIGNAL(triggered(bool)), this, SLOT(removeCustomer()));
    connect(ui->mtbDropTable, SIGNAL(triggered(bool)), this, SLOT(clearTable()));
    connect(ui->mtbOutputDocuments, SIGNAL(triggered(bool)), output, SLOT(exec()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editCustomer()));
    connect(add, SIGNAL(applyChanges()), this, SLOT(updateTable()));
    connect(add, SIGNAL(applyChanges()), this, SLOT(resizeTable()));
    connect(add, SIGNAL(applyChanges()), this, SLOT(selectRow()));
    connect(this, SIGNAL(customerRemoved()), this, SLOT(selectRow()));
}
