#include "profile_win.h"
#include "ui_profile_win.h"

Profile_win::Profile_win(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Profile_win)
{
    ui->setupUi(this);
}
void Profile_win::SetInfo(QString num)
{
    QSqlQuery query;
    qDebug()<< num;
    query.prepare("SELECT employee_id, town, password, fib, birthdate FROM employee WHERE number_of_the_phone =:numberphone");
    query.bindValue(":numberphone", num);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:";
    } else if (query.next()) {
        QDate birthdate = query.value("birthdate").toDate();
        QString town = query.value("town").toString();
        QString password = query.value("password").toString();
        QString fib = query.value("fib").toString();
        ui->lineEdit->setText(fib);
        ui->lineEdit_2->setText(num);
        ui->dateEdit->setDate(birthdate);
        ui->lineEdit_3->setText(password);
        ui->lineEdit_4->setText(town);
        this->show();
    } else {
        qDebug() << "Запрос не вернул результатов.";
    }
}



Profile_win::~Profile_win()
{
    delete ui;

}
