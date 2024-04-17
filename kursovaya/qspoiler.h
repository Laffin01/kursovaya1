#ifndef QSPOILER_H
#define QSPOILER_H
#include <QApplication>
#include <QPixmap>
#include <QRandomGenerator64>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

    class QSpoiler : public QWidget
    {
        Q_OBJECT

    public:
        QSpoiler(QString buttonName, QWidget *parent = nullptr)
            : QWidget(parent), button(new QPushButton(buttonName, this)), subButtons(new QFrame(this)), subLayout(new QVBoxLayout(subButtons))
        {

            QVBoxLayout *layout = new QVBoxLayout;

            button->setStyleSheet("QPushButton {"
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

        void Setbutton(QString Name_button)
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

            connect(button, &QPushButton::clicked, this, &QSpoiler::setIconOnChecked);

            subLayout->addWidget(button);
            subButtons->adjustSize();
        }

        void setIconOnChecked(bool checked)
        {
            QPushButton *button = qobject_cast<QPushButton *>(sender());
            if (button && checked) {
                QPixmap pixmap("C:/Users/boba/Downloads/icons8-галочка.svg");
                QIcon ButtonIcon(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                button->setIcon(ButtonIcon);
                button->setIconSize(QSize(30, 30));
            }
            else {
                button->setIcon(QIcon());
            }
        }



    private slots:
        void toggle()
        {
            if (subButtons->isVisible()) {
                subButtons->hide();
            } else {
                subButtons->show();
            }
        }

    private:
        QPushButton *button;
        QFrame *subButtons;
        QVBoxLayout *subLayout;
    };


#endif // QSPOILER_H
