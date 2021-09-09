#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QApplication>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    void connectToDatabase();
    void connectToDatabase(QString &filePath);
    void insertIntoTable(QVariantList &data);
    void dropTable();
    QList<QString> getPaymentsHistory();
    QList<QString> getDebtors();
    QList<QString> getCities(QString city);

private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // DATABASE_H
