#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QSqlDatabase>
#include <QDebug>

class Connect
{
public:
   QSqlDatabase db1 = getConnection();
QSqlDatabase getConnection() {
  static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("car_showroom");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("617318057Fil");
    return db;
}

};
#endif
