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
#include <qspoiler.h>
#include "mainwindow.h"
#include "mainmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlTableModel *model;
    if (db_1.db1.open()) {
        qDebug() << "Соединение с базой данных установлено.";

        model = new QSqlTableModel(this, db_1.db1);
        model->setTable("Cars");
        model->select();
        SetTable(model);
    }

    chart = nullptr;
    series = nullptr;
    axisX = nullptr;
    axisY = nullptr;
    chartView = nullptr;
    layout = nullptr;
     set= nullptr;

    ui->lineEdit->setPlaceholderText(QString("Пошук"));

    ui->groupBox_5->raise();

    QPixmap pixmap("D:/c++/kursovaya/arrow.svg");
    QIcon icon(pixmap);
    ui->pushButton_5->setGeometry(0,0,50,50);
    ui->pushButton_5->setIconSize(QSize(50,50));
    ui->pushButton_5->setStyleSheet("background-color: transparent; border: none;");
    ui->pushButton_5->setIcon(icon);



    QSpoiler *spoiler1 = new QSpoiler("По маркам", this);
    QSpoiler *spoiler2 = new QSpoiler("По ціні", this);
    QSpoiler *spoiler3 = new QSpoiler("По країні виробнику", this);
    QSpoiler *spoiler4 = new QSpoiler("По типу кузова", this);

    vid->setPlaceholderText(QString("Від"));
    do_1->setPlaceholderText(QString("До"));
    QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(vid);
        layout->addWidget(do_1);

        spoiler1->Setbutton("Volvo", true);
        spoiler1->Setbutton("BMW", true);
        spoiler1->Setbutton("Mercedes-Benz", true);
       spoiler1->Setbutton("Audi", true);
       spoiler1->Setbutton("Peugeot", true);
        spoiler1->Setbutton("Toyota", true);
       spoiler1->Setbutton("Land-Rover", true);
        spoiler1->Setbutton("Porsche", true);
        spoiler1->Setbutton("Subaru", true);


        spoiler2->Setbutton("від 20000", false);
        spoiler2->Setbutton("до 40000", false);
        spoiler2->Setbutton("до 80000", false);



    layout->addWidget(spoiler1);
    layout->addWidget(spoiler2);
    layout->addWidget(spoiler3);
    layout->addWidget(spoiler4);

    ui->scrollArea->widget()->setLayout(layout);




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

// void MainWindow::on_checkBox_stateChanged()
// {
//     QStringList brands;
//     if(ui->checkBox_42->isChecked())
//     {
//         brands.append("'" + ui->checkBox_42->text() + "'");
//     }

//     if(ui->checkBox_35->isChecked())
//     {
//         brands.append("'" + ui->checkBox_35->text() + "'");
//     }

//     QString sql_statement;
//     if (!brands.isEmpty()) {
//         QString brandList = brands.join(",");
//         sql_statement = QString("SELECT * FROM cars WHERE brand IN (%1)").arg(brandList);
//     }
//     else
//     {
//         sql_statement="SELECT * FROM cars";
//     }
//     QSqlQueryModel *model = new QSqlQueryModel;
//     model->setQuery(sql_statement,  db_1.db1);
//     ui->tableView->setModel(model);
// }


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
            int vid_1 = vid->text().toInt();
            int do_ = do_1->text().toInt();

            queryString = "SELECT configuration_name, price FROM configurations WHERE model_id = :model_id1";
            query.prepare(queryString);
            query.bindValue(":model_id1", model_id1);

            if (query.exec()) {
                while (query.next()) {
                    QString currentModel = query.value(0).toString();
                    int price =  query.value(1).toInt();
                    if(vid!=0 && do_!=0)
                    {
                        if(price >= vid_1 && price <= do_)
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

        query.prepare("INSERT INTO zamovlennya (employee_id, `Марка`, `Модель`, `Комплектація`, `Ціна`, `Дата оформлення замовлення`, `ФІБ`, `Місто проживання`, `РНОКПП`, `Номер паспорта`, `Номер телефона`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(employee_id);
        query.addBindValue(brand);
        query.addBindValue(ui->lineEdit_5->text());
        query.addBindValue(ui->lineEdit_3->text());
        query.addBindValue(ui->lineEdit_13->text().toInt());
        query.addBindValue(date.toString(Qt::ISODate));
        query.addBindValue(ui->lineEdit_14->text());
        query.addBindValue(ui->lineEdit_15->text());
        query.addBindValue(ui->lineEdit_16->text());
        query.addBindValue(ui->lineEdit_17->text());
        query.addBindValue(ui->lineEdit_18->text());

        if(!query.exec()) {
            qDebug() << "Insert query failed: " << query.lastError();
        }
    }


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    Insert_info_to_the_table();
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
}




void MainWindow::create_graphic(QStringList x,  QStringList y1)
{
    QStringList categories;
    int max_y = 0;
          chart = new QChart();
           series = new QBarSeries(); // Создайте одну серию здесь

    for(int i=0; i < x.count(); i++)
    {
        int y;
        y=y1[i].toInt();

        if(y > max_y) {
            max_y = y;
        }


        set = new QBarSet(x[i]);
        *set << y;
        series->append(set);

    }

    chart->addSeries(series); // Добавьте серию в график здесь

    axisX = new QBarCategoryAxis();
    axisX->append("Кількість проданих автомобілей (по маркам)");
    chart->setAxisX(axisX);

    axisY = new QValueAxis();
    axisY->setRange(0, max_y);
    axisY->setTickType(QValueAxis::TicksFixed);
    axisY->setTickCount(max_y + 1);
    chart->setAxisY(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    if(ui->widget->layout() != nullptr && ui->widget->layout()->count() != 0) {
        delete ui->widget->layout();
    }

     ui->widget->setLayout(layout);

}


void MainWindow::on_radioButton_2_clicked()
{

    QSqlQuery query;
    qDebug() << "dsgsgssdgsg";
    QStringList brand;

    // Select distinct brands from the table
    query.prepare("SELECT DISTINCT Марка FROM zamovlennya");
    if(query.exec()) {
        while(query.next())
        {
            QString currentBrand = query.value("Марка").toString();
            qDebug() << currentBrand;
            brand.append(currentBrand);
        }
    }


    QStringList y1;
    for(int i=0; i < brand.count(); i++)
    {
        // Count the number of records for each brand
        query.prepare("SELECT COUNT(*) FROM zamovlennya WHERE Марка = :brand");
        query.bindValue(":brand", brand[i]);
        if(query.exec() && query.next()) {

            QString y = query.value(0).toString();
            qDebug() << y;
            y1.append(y);
        }
        else {
            qDebug() << "Query failed for brand:" << brand[i];
        }
    }

    // Create graphic using the retrieved data
  create_graphic(brand, y1);

}


void MainWindow::on_radioButton_clicked()
{
    QSqlQuery query;

    QStringList brand;
    query.prepare("SELECT DISTINCT Модель FROM zamovlennya");
    if(query.exec()) {
        while(query.next())
        {
            QString currentBrand = query.value("Модель").toString();
            brand.append(currentBrand);

        }
    }
    QStringList y1;
    for(int i=0; i < brand.count(); i++)
    {

        query.prepare("SELECT COUNT(*) FROM zamovlennya WHERE Модель = :brand");
        query.bindValue(":brand", brand[i]);
        if(query.exec()) {
            if(query.next()) {
                QString y = query.value(0).toString();
                y1.append(y);
            }
        }

    }
    create_graphic(brand, y1);

}



void MainWindow::on_radioButton_3_clicked()
{
    QSqlQuery query;
    QStringList brand;
    query.prepare("SELECT DISTINCT Комплектація FROM zamovlennya");
    if(query.exec()) {
        while(query.next())
        {
            QString currentBrand = query.value("Комплектація").toString();
            brand.append(currentBrand);

        }
    }
    QStringList y1;
    for(int i=0; i < brand.count(); i++)
    {

        query.prepare("SELECT COUNT(*) FROM zamovlennya WHERE Комплектація = :brand");
        query.bindValue(":brand", brand[i]);
        if(query.exec()) {
            if(query.next()) {
                QString y = query.value(0).toString();
                y1.append(y);
            }
        }

    }

   create_graphic(brand, y1);

}



// Добавьте в ваш класс MainWindow список выбранных марок


void MainWindow::mainfilter(QPushButton *button)
{
    QSqlQuery query;
    QSqlTableModel *model = new QSqlTableModel;
    QString textfrombutton = button -> text();

    // Проверяем, выбрана ли кнопка
    if(button->isCheckable())
    {
        // Если кнопка выбрана, добавляем марку в список
        if(!selectedBrands.contains(textfrombutton))
        {
            selectedBrands.append(textfrombutton);
        }
    }
    else
    {
        // Если кнопка не выбрана, удаляем марку из списка
        selectedBrands.removeOne(textfrombutton);
    }

    // Если выбрана хотя бы одна марка, обновляем фильтр модели
    if(!selectedBrands.isEmpty())
    {
        QString filter = "Марка IN ('" + selectedBrands.join("', '") + "')";
        model->setTable("cars");
        model->setFilter(filter);
        model->select();
    }
    else
    {
        // Если ни одна марка не выбрана, показываем все данные
        model->setTable("cars");
        model->select();
    }

    MainWindow::SetTable(model); // Установка модели для текущего экземпляра MainWindow
}


void MainWindow::SetTable(QSqlTableModel *model)
{

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
    //ui->tableView->setColumnHidden(3, true);

}



MainWindow::~MainWindow()
{

    delete ui;

}





