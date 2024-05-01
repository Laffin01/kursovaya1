#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QAbstractItemModel>
#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "profile_win.h"
#include "DbConnection.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
class Graphic;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
     void SetTable(QSqlTableModel *model);
     void mainfilter(QPushButton *button);

private slots:

    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
    void on_radioButton_3_clicked();
    void on_tableView_clicked( const QModelIndex &index);


    void on_pushButton_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);
    void on_pushButton_3_clicked();
   void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
      void Insert_info_to_the_table();
    void on_pushButton_5_clicked();
       void on_pushButton_7_clicked();
    void create_graphic(QStringList x,  QStringList y1);

       void on_lineEdit_textChanged();

   void on_comboBox_2_currentIndexChanged(int index);



    void on_comboBox_currentIndexChanged(int index);



private:

   Ui::MainWindow *ui;
    QLineEdit *vid = new QLineEdit();
    QLineEdit *do_1= new QLineEdit();
    QLabel *filter = new QLabel();
      QChart *chart;
      QBarSeries *series;
      QBarCategoryAxis *axisX;
      QValueAxis *axisY;
      QChartView *chartView;
      QVBoxLayout *layout;
      QBarSet *set;
   QList<QString> selectedBrands;
    QString brand;
    QModelIndexList selectedIndexes;
   int selectedIndex;
       int IndextableView_2;
   Profile_win pw;
    QString name_model;
   QStringList model_name_List;
     QStringList  conf_name;
    Connect db_1;
   int carId;

   QString currentConfiguration;


};




#endif
