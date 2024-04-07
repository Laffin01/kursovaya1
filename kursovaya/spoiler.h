#ifndef SPOILER_H
#define SPOILER_H

#include <QWidget>

namespace Ui {
class Spoiler;
}

class Spoiler : public QWidget
{
    Q_OBJECT

public:
    explicit Spoiler(QWidget *parent = nullptr);
    ~Spoiler();

private:
    Ui::Spoiler *ui;
};

class Spoiler : public QGroupBox
{
public:
    Spoiler(const QString & title, QWidget * parent = 0) : QGroupBox(title, parent)
    {
        setAttribute(Qt::WA_Hover, true);
        animation = new QPropertyAnimation(this, "size");
        resize(100, 20);
    }

protected:
    bool event(QEvent *event) override
    {
        if (event->type() == QEvent::HoverEnter)
        {
            animation->setDuration(500);
            animation->setStartValue(size());
            animation->setEndValue(QSize(100, 100));
            animation->start();
        }
        else if (event->type() == QEvent::HoverLeave)
        {
            animation->setDuration(500);
            animation->setStartValue(size());
            animation->setEndValue(QSize(100, 20));
            animation->start();
        }

        return QGroupBox::event(event);
    }

private:
    QPropertyAnimation *animation;
};
#endif // SPOILER_H
