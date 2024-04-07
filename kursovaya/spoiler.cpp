#include "spoiler.h"
#include "ui_spoiler.h"

Spoiler::Spoiler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Spoiler)
{
    ui->setupUi(this);
}

Spoiler::~Spoiler()
{
    delete ui;
}
