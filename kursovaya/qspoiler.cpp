#include "qspoiler.h"

QSpoiler::QSpoiler(QWidget * parent) : QGroupBox(parent)
{


    animation = new QPropertyAnimation(this, "size");
    // Другие инициализации...
}

QSpoiler::QSpoiler(const QString & title, QWidget * parent) : QGroupBox(title, parent)
{

    animation = new QPropertyAnimation(this, "size");
    // Другие инициализации...
}
