#ifndef QSPOILER_H
#define QSPOILER_H
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QEvent>
#include <QPropertyAnimation>
    class QSpoiler : public QGroupBox
    {
    public:
        QSpoiler(QWidget * parent = 0);
        QSpoiler(const QString & title, QWidget * parent = 0);

    protected:
        bool event(QEvent *event) override
        {
            if (event->type() == QEvent::HoverEnter)
            {
                animation->setDuration(500);
                animation->setStartValue(size());
                animation->setEndValue(QSize(width(), sizeHint().height()));
                animation->start();
            }
            else if (event->type() == QEvent::HoverLeave)
            {
                animation->setDuration(500);
                animation->setStartValue(size());
                animation->setEndValue(QSize(width(), 30));
                animation->start();
            }

            return QGroupBox::event(event);
        }

    private:
        QPropertyAnimation *animation;
 };

#endif // QSPOILER_H
