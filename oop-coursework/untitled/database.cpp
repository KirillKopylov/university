#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
}

void Database::connectToDatabase()
{
    QString dbLocation = QApplication::applicationDirPath() + "/customers.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbLocation);
    if(!db.open()) {
        qDebug() << "Помилка підключення до БД за замовчуванням: " << db.lastError().text();
        return;
    } else {
        qDebug() << "Успішне підключення до БД за замовчуванням";
    }
}

void Database::connectToDatabase(QString &filePath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filePath);
    if(!db.open()) {
        qDebug() << "Помилка підключення до заданої БД: " << db.lastError().text();
        return;
    } else {
        qDebug() << "Успішне підключення до заданої БД";
    }
}

void Database::insertIntoTable(QVariantList &data)
{
    query.prepare("INSERT INTO Customers (SURNAME, NAME, PATRONYMIC, BALANCE, CITY, STREET, BUILDING, APARTMENT, TYPE, TARIFF, CONNECTED, LAST_PAY, STATUS) "
                  "VALUES (:SURNAME, :NAME, :PATRONYMIC, :BALANCE, :CITY, :STREET, :BUILDING, :APARTMENT, :TYPE, :TARIFF, :CONNECTED, :LAST_PAY, :STATUS)");
    query.bindValue(":SURNAME", data[0].toString());
    query.bindValue(":NAME", data[1].toString());
    query.bindValue(":PATRONYMIC", data[2].toString());
    query.bindValue(":BALANCE", data[3].toInt());
    query.bindValue(":CITY", data[4].toString());
    query.bindValue(":STREET", data[5].toString());
    query.bindValue(":BUILDING", data[6].toInt());
    query.bindValue(":APARTMENT", data[7].toInt());
    query.bindValue(":TYPE", data[8].toString());
    query.bindValue(":TARIFF", data[9].toString());
    query.bindValue(":CONNECTED", data[10].toString());
    query.bindValue(":LAST_PAY", data[11].toString());
    query.bindValue(":STATUS", data[12].toString());
    if(!query.exec()) {
        qDebug() << "Помилка додавання даних в БД: " << query.lastError();
        return;
    }
}

QList<QString> Database::getPaymentsHistory()
{
    QList<QString> payments;
    if(!query.exec("SELECT * FROM Customers WHERE LAST_PAY")) {
        qDebug() << "Помилка отримання даних з БД: " << query.lastError();
    }
    while(query.next()) {
        QString surname = query.value("SURNAME").toString();
        QString name = query.value("NAME").toString();
        QString patronymic = query.value("PATRONYMIC").toString();
        QString pay = query.value("LAST_PAY").toString();
        QString record = pay + " -> " + surname + " " + name + " " + patronymic;
        payments.append(record);
    }
    return payments;
}

QList<QString> Database::getDebtors()
{
    QList<QString> debtors;
    if(!query.exec("SELECT * FROM Customers WHERE STATUS = 'Відключений за борги'")) {
        qDebug() << "Помилка отримання даних з БД: " << query.lastError();
    }
    while(query.next()) {
        QString surname = query.value("SURNAME").toString();
        QString name = query.value("NAME").toString();
        QString patronymic = query.value("PATRONYMIC").toString();
        QString record = surname + " " + name + " " + patronymic;
        debtors.append(record);
    }
    return debtors;
}

QList<QString> Database::getCities(QString city)
{
    QList<QString> cities;
    if(!query.exec(QString("SELECT * FROM Customers WHERE CITY = '%1'").arg(city))) {
        qDebug() << "Помилка отримання даних з БД: " << query.lastError();
    }
    while(query.next()) {
        QString surname = query.value("SURNAME").toString();
        QString name = query.value("NAME").toString();
        QString patronymic = query.value("PATRONYMIC").toString();
        QString record = surname + " " + name + " " + patronymic;
        cities.append(record);
    }
    qDebug() << query.lastQuery();
    return cities;
}

void Database::dropTable()
{
    db.open();
    QSqlQuery q(db);
    if(!q.exec("DELETE FROM Customers")) {
        qDebug() << "Помилка видалення таблиці: " << query.lastError();
    }
}
