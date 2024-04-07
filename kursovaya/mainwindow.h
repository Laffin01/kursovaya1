#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QAbstractItemModel>
#include <QApplication>
#include <qspoiler.h>
#include "profile_win.h"
#include "DbConnection.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableView_clicked( const QModelIndex &index);
    void on_comboBox_currentIndexChanged();
    void on_checkBox_stateChanged();
    void on_pushButton_clicked();
    void on_comboBox_2_currentIndexChanged();
    void on_tableView_2_clicked();
    void on_pushButton_3_clicked();
   void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:

   Ui::MainWindow *ui;
   Profile_win pw;
    QString name_model;
   QStringList model_name_List;
     QStringList  conf_name;
    Connect db_1;
   int carId;
    QSqlTableModel *model;
   QString currentConfiguration;
};


#endif
