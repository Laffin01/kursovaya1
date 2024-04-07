#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QStackedWidget>
#include <QLineEdit>
#include "mainwindow.h"

namespace Ui {
class Mainmenu;
}

class Mainmenu : public QDialog
{
    Q_OBJECT


public:
    explicit Mainmenu(QWidget *parent = nullptr);
    ~Mainmenu();
    static QString check_number;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_lineEdit_6_textChanged();
  void on_autorization_clicked();
    void on_lineEdit_7_textChanged();
    void on_pushButton_clicked();
    void on_password_textChanged();

private:

    Ui::Mainmenu *ui;
     MainWindow w;
    QString passwordlabel;
    QString password_1;
    QString passwordtext;
};

#endif // MAINMENU_H
