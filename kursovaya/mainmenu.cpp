#include "ui_mainmenu.h"
#include "QMessageBox"
#include <QSqlQuery>
#include <QSqlError>
#include "mainmenu.h"
#include "main.cpp"

QString Mainmenu::check_number = "";

Mainmenu::Mainmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mainmenu)
{
    ui->setupUi(this);

}

Mainmenu::~Mainmenu()
{
    delete ui;
}
void Mainmenu::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->show();
}


void Mainmenu::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->show();
}


void Mainmenu::on_lineEdit_6_textChanged() {
     passwordtext = ui->lineEdit_6->text();
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);
}
void Mainmenu::on_lineEdit_7_textChanged()
{
    password_1 = ui->lineEdit_7->text();
        ui->lineEdit_7->setEchoMode(QLineEdit::Password);
}

void Mainmenu::on_password_textChanged()
{
    passwordlabel=ui->password->text();
    ui->password->setEchoMode(QLineEdit::Password);
}

void Mainmenu::on_autorization_clicked()
{

    QString checknpassword;
    QString checkinname;
    QWidget* currentPage = ui->stackedWidget->currentWidget();
    QList<QLineEdit*> lineEdits = currentPage->findChildren<QLineEdit*>();
    bool allFieldsFilled = true;

    // Проверяем каждый QLineEdit на заполнение
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text().isEmpty()) {
            allFieldsFilled = false;
            break;
        }
    }

    if (!allFieldsFilled) {
        QMessageBox::warning(this, "Предупреждение", "Заполните все поля для регистрации.");
    }
    else {

         checknpassword = ui->password->text();
         checkinname = ui->namelabel->text();

        QSqlQuery query;
        query.prepare("SELECT number_of_the_phone, password FROM employee WHERE number_of_the_phone = :checkinname AND password = :checknpassword");
        query.bindValue(":checkinname", checkinname);
        query.bindValue(":checknpassword", checknpassword);
        query.exec();
        if (query.next()) {
            Mainmenu::check_number=ui->namelabel->text();
            qDebug()<<check_number;
            w.show();
            this->close();
        } else {
            QMessageBox::warning(this, "Предупреждение", "Неверное имя пользователя или пароль.");
        }
      }
  }


void Mainmenu::on_pushButton_4_clicked()
{
    QSqlQuery query;
    QWidget* currentPage = ui->stackedWidget->currentWidget();
    QList<QLineEdit*> lineEdits = currentPage->findChildren<QLineEdit*>();
    bool allFieldsFilled = true;

    // Проверяем каждый QLineEdit на заполнение
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text().isEmpty()) {
            allFieldsFilled = false;
            break;
        }
    }

    if (!allFieldsFilled) {
        QMessageBox::warning(this, "Предупреждение", "Заполните все поля для регистрации.");
    }
    else {
        QString password1;
        if(password_1 == passwordtext  && passwordtext.length() == password_1.length())
        {
            password1 = password_1;
        }
        else
        {
            QMessageBox::warning(this, "Предупреждение", "Пароли не совпадают.");
            return;
        }
        QString fib = ui->lineEdit_2->text();
        QString phoneNumber = ui->lineEdit_3->text();
        QDate birthdate = ui->dateEdit->date();
        QString town = ui->lineEdit_4->text();

        query.prepare("INSERT INTO employee (town, password, fib, number_of_the_phone, birthdate) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(town);
        query.addBindValue(password1);
        query.addBindValue(fib);
        query.addBindValue(phoneNumber);
        query.addBindValue(birthdate.toString(Qt::ISODate));

        if (!query.exec()) {
            QMessageBox::critical(this, "Ошибка", "Ошибка при выполнении запроса: " + query.lastError().text());
        } else {
            QMessageBox::information(this, "Успешно", "Регистрация прошла успешно.");
        }
    }
}

