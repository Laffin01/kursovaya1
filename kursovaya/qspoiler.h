#ifndef QSPOILER_H
#define QSPOILER_H
#include <QApplication>
#include <QPixmap>
#include <QRandomGenerator64>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <mainwindow.h>



    class QSpoiler : public QWidget
    {
        Q_OBJECT

    public:
        QSpoiler(QString buttonName, MainWindow* mainWindow = nullptr, QWidget *parent = nullptr)
            : QWidget(parent), button(new QPushButton(buttonName, this)), subButtons(new QFrame(this)), subLayout(new QVBoxLayout(subButtons)), mainWindow(mainWindow)
        {
            QVBoxLayout *layout = new QVBoxLayout;

            QPixmap pixmap;
    pixmap = QPixmap("C:/Users/boba/Downloads/down-arrow_icon-icons.com_64915.svg");
            QIcon ButtonIcon(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            button->setIcon(ButtonIcon);
            button->setIconSize(QSize(20, 20));

            button->setStyleSheet("QPushButton {"
                                  "text-align: left;"
                                  "background: transparent;"
                                  "border: none;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: rgb(112, 112, 112);"
                                  "}");


            layout->addWidget(button);
            layout->addWidget(subButtons);
            this->setLayout(layout);

           subButtons->hide();
            connect(button, &QPushButton::clicked, this, &QSpoiler::toggle);
        }


        void Setbutton(QString Name_button, bool checkable)
        {
            QPushButton *button = new QPushButton(Name_button);

            button->setCheckable(true);

            button->setStyleSheet("QPushButton {"
                                  "background: transparent;"
                                  "border: none;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: rgb(112, 112, 112);"
                                  "}"
                                  "QPushButton:checked {"
                                  "background-color: rgb(112, 112, 112);"
                                  "}");

            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            button->setFixedHeight(40);

             connect(button, &QPushButton::clicked, this, [=] {QSpoiler::setIconOnChecked(button, button->isChecked(), checkable);});

            subLayout->addWidget(button);
            subButtons->adjustSize();
        }


        void setIconOnChecked(QPushButton *button, bool checked, bool checkable)
        {
            QPixmap pixmap("C:/Users/boba/Downloads/icons8-галочка.svg");
            QIcon ButtonIcon(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            if (button && checked) {
                if (checkable != false) {
                    button->setIcon(ButtonIcon);
                    button->setIconSize(QSize(30, 30));
                }
                else  {
                    if (lastButton != nullptr) {
                        lastButton->setChecked(false);
                        lastButton->setIcon(QIcon());
                    }
                    button->setIcon(ButtonIcon);
                    button->setIconSize(QSize(30, 30));
                    lastButton = button;
                }
            }
            else {
                button->setIcon(QIcon());
                if (lastButton == button) {
                    lastButton = nullptr;
                }
            }

            if (button && checkable) {
              mainWindow->mainfilter(button);
            }
            else
                mainWindow->falsefilter(button);
        }





    private slots:
        void toggle()
        {
            QPixmap pixmap;


            if (subButtons->isVisible()) {
                pixmap = QPixmap("C:/Users/boba/Downloads/down-arrow_icon-icons.com_64915.svg");
                subButtons->hide();

            }
            else {
                pixmap = QPixmap("C:/Users/boba/Downloads/up-arrow_icon-icons.com_65094.svg");
                subButtons->show();
            }
            QIcon ButtonIcon(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            button->setIcon(ButtonIcon);
            button->setIconSize(QSize(20, 20));

        }

    private:

        QPushButton *button;
        QFrame *subButtons;
        QVBoxLayout *subLayout;
        QPushButton *lastButton = nullptr;
          MainWindow *mainWindow;
    };


#endif // QSPOILER_H
