#include "./ui_mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QScreen>

#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTableWidget>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QSqlRecord>
#include <QFile>
#include <QDir>
#include <QToolButton>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QPainter>
#include <QtSvgWidgets/QSvgWidget>

#include "mainwindow.h"
#include "mainmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->checkBox_42, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged(int)));
    connect(ui->checkBox_35, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged(int)));
    connect(ui->checkBox_47, SIGNAL(stateChanged(int)), this, SLOT(on_checkBox_stateChanged(int)));
    if (db_1.db1.open()) {
   qDebug() << "Соединение с базой данных установлено.";

        model = new QSqlTableModel(this, db_1.db1);
        model->setTable("Cars");
        model->select();
    }


    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
 //ui->tableView->setColumnHidden(3, true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->vid->setPlaceholderText(QString("Від"));
    ui->do_1->setPlaceholderText(QString("До"));
    ui->lineEdit->setPlaceholderText(QString("Пошук"));
    QPixmap pixmap("D:/c++/kursovaya/arrow.svg");

    QIcon icon(pixmap);
    ui->pushButton_5->setGeometry(0,0,50,50);
    ui->pushButton_5->setIconSize(QSize(50,50));
    ui->pushButton_5->setStyleSheet("background-color: transparent; border: none;");
    ui->pushButton_5->setIcon(icon);

}

MainWindow::~MainWindow()
{

    delete ui;

}
// установка перечня комплектаций в комбобокс
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QSqlQuery query;
    ui->comboBox_2->clear();

    carId = ui->tableView->model()->data(index).toInt();
    query.prepare("SELECT model_name FROM models_of_the_car WHERE conf_id = :carId");
    query.bindValue(":carId", carId);

    if (query.exec()) {
        while (query.next()) {
            QString configuration = query.value("model_name").toString();
            ui->comboBox_2->addItem(configuration);
        }
    }

}

void MainWindow::on_comboBox_currentIndexChanged()
{
    currentConfiguration.clear();
    QSqlQuery query;
    currentConfiguration = ui->comboBox->currentText();
    query.prepare("SELECT price FROM configurations WHERE configuration_name = :configuration");
    query.bindValue(":configuration", currentConfiguration);
    ui->lineEdit_2->clear();
    if(!ui->comboBox->currentText().isEmpty())
    {
        if (query.exec()) {
            if (query.next()) {
                QString price = query.value("price").toString();
                ui->lineEdit_2->setText(price);
            }
        }
    }
}

void MainWindow::on_checkBox_stateChanged()
{
    QStringList brands;
    if(ui->checkBox_42->isChecked())
    {
        brands.append("'" + ui->checkBox_42->text() + "'");
    }

    if(ui->checkBox_35->isChecked())
    {
        brands.append("'" + ui->checkBox_35->text() + "'");
    }

    QString sql_statement;
    if (!brands.isEmpty()) {
        QString brandList = brands.join(",");
        sql_statement = QString("SELECT * FROM cars WHERE brand IN (%1)").arg(brandList);
    }
    else
    {
        sql_statement="SELECT * FROM cars";
    }
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(sql_statement,  db_1.db1);
    ui->tableView->setModel(model);
}


void MainWindow::on_pushButton_clicked()
{
    conf_name.append(currentConfiguration);
    model_name_List.append(name_model);
    static QStandardItemModel *model = new QStandardItemModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM cars WHERE id = :carId");
    query.bindValue(":carId", carId);
    if(query.exec())
    {
        while(query.next())
        {
            QList<QStandardItem*> items;
            for(int i = 0; i < query.record().count(); i++)
            {
                items.append(new QStandardItem(query.value(i).toString()));
            }
            model->appendRow(items);
        }
        ui->tableView_2->setModel(model);
    }

}



void MainWindow::on_comboBox_2_currentIndexChanged()
{
    QSqlQuery query;
    ui->comboBox->clear();
    name_model = ui->comboBox_2->currentText();
    QString queryString = "SELECT model_id FROM models_of_the_car WHERE model_name = '" + name_model + "'";
    query.prepare(queryString);
    if (query.exec()) {
        if (query.next()) {
            int model_id1 = query.value(0).toInt();
            int vid = ui->vid->text().toInt();
            int do_ = ui->do_1->text().toInt();

            queryString = "SELECT configuration_name, price FROM configurations WHERE model_id = :model_id1";
            query.prepare(queryString);
            query.bindValue(":model_id1", model_id1);

            if (query.exec()) {
                while (query.next()) {
                    QString currentModel = query.value(0).toString();
                    int price =  query.value(1).toInt();
                    if(vid!=0 && do_!=0)
                    {
                        if(price >= vid && price <= do_)
                        {
                            ui->comboBox->addItem(currentModel);
                            if(ui->comboBox->currentText().isEmpty())
                                ui->lineEdit_2->clear();
                        }
                    }
                    else{
                        ui->comboBox->addItem(currentModel);
                    }
                }
            }
        }
    }
}


void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QSqlQuery query;

    QAbstractItemModel *model = ui->tableView_2->model();
    QModelIndex index_1 = model->index(index.row(), 1);
     brand = model->data(index_1, Qt::DisplayRole).toString();

    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    selectedIndexes = ui->tableView_2->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
        selectedIndex = selectedIndexes.first().row();
        ui->lineEdit_3->setText(conf_name[selectedIndex]);
         ui->lineEdit_5->setText(model_name_List[selectedIndex]);
        query.prepare("SELECT price, color, doors, seats, fuel_type, transmission, engine_volume, fuel_consumption, power FROM configurations WHERE configuration_name = :conf_name");
        query.bindValue(":conf_name", conf_name[selectedIndex]);

        if(query.exec()) {
            QStringList lineEdits = {"lineEdit_4", "lineEdit_6", "lineEdit_7", "lineEdit_8", "lineEdit_9", "lineEdit_10", "lineEdit_11", "lineEdit_12", "lineEdit_13"};
            QStringList queryValues = {"color", "doors", "seats", "engine_volume", "power", "fuel_consumption", "fuel_type", "transmission", "price"};

            while(query.next()) {
                for(int i = 0; i < lineEdits.size(); i++) {
                    this->findChild<QLineEdit*>(lineEdits[i])->setText(query.value(queryValues[i]).toString());
                }
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->show();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString confirmationText = "<h2>Подтверждение заказа:</h2><br>";
    confirmationText += "<b>Комплектація:</b> " + ui->lineEdit_3->text() + "<br>";
    confirmationText += "<b>Модель:</b> " + ui->lineEdit_5->text() + "<br>";
    confirmationText += "<b>Цвет:</b> " + ui->lineEdit_4->text() + "<br>";
    confirmationText += "<b>Количество дверей:</b> " + ui->lineEdit_6->text() + "<br>";
    confirmationText += "<b>Количество мест:</b> " + ui->lineEdit_7->text() + "<br>";
    confirmationText += "<b>Тип топлива:</b> " + ui->lineEdit_8->text() + "<br>";
    confirmationText += "<b>Тип трансмиссии:</b> " + ui->lineEdit_9->text() + "<br>";
    confirmationText += "<b>Объем двигателя:</b> " + ui->lineEdit_10->text() + "<br>";
    confirmationText += "<b>Расход топлива:</b> " + ui->lineEdit_11->text() + "<br>";
    confirmationText += "<b>Мощность:</b> " + ui->lineEdit_12->text() + "<br>";
    confirmationText += "<b>Цена:</b> " + ui->lineEdit_13->text() + "<br>";
    confirmationText += "<br><b>Дата и время оформления заказа:</b> " + currentDateTime.toString("dd.MM.yyyy HH:mm:ss") + "<br>";
    confirmationText += "<h3>Дякуємо за замовлення!</h3>";
    QPdfWriter pdfWriter("OrderConfirmation.pdf");
    QPainter painter(&pdfWriter);
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(150);
    painter.setFont(font);
    QTextDocument textDoc;
    textDoc.setDefaultFont(font);
    textDoc.setHtml(confirmationText);
    textDoc.setTextWidth(pdfWriter.width());
    textDoc.drawContents(&painter);
    painter.end();
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath() + "/OrderConfirmation.pdf"));
    //Insert_info_to_the_table();
}

void MainWindow::on_pushButton_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_2->selectionModel();

    if(select->hasSelection())
    {
        QModelIndexList selectedRows = select->selectedRows();
        for(int i = selectedRows.count() - 1; i >= 0; i--)
        {
            int selectedIndex = selectedRows.at(i).row();
            conf_name.removeAt(selectedIndex);
            model_name_List.removeAt(selectedIndex);
            ui->tableView_2->model()->removeRow(selectedIndex);
        }
    }
}


    void MainWindow::on_pushButton_4_clicked()
    {
        static QString numberphone;
        numberphone = Mainmenu::check_number;
        pw.SetInfo(numberphone);
    }



    void MainWindow::Insert_info_to_the_table()
    {
        QSqlQuery query;
        QString num = Mainmenu::check_number;
        QDate date = QDate::currentDate();
        int employee_id=0;
        query.prepare("SELECT employee_id FROM employee WHERE  number_of_the_phone  =:number");
        query.bindValue(":number", num);
        if(query.exec() && query.next()) {
            employee_id = query.value("employee_id").toInt();
        } else {
            qDebug() << "Query failed: " << query.lastError();
        }
        qDebug() << brand;
        query.prepare("INSERT INTO zamovlennya (employee_id, `Марка`, `Модель`, `Комплектація`, `Ціна`, `Дата оформлення замовлення`) VALUES (?, ?, ?, ?,?,?)");
        query.addBindValue(employee_id);
        query.addBindValue(brand);
        query.addBindValue(ui->lineEdit_5->text());
        query.addBindValue(ui->lineEdit_3->text());
        query.addBindValue(ui->lineEdit_13->text().toInt());
        query.addBindValue(date.toString(Qt::ISODate));

        if(!query.exec()) {
            qDebug() << "Insert query failed: " << query.lastError();
        }
    }

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->show();
}

