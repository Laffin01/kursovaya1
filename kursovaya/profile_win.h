#ifndef PROFILE_WIN_H
#define PROFILE_WIN_H

#include <QDialog>
#include <DbConnection.h>
#include <QSqlquery>
#include <QSqlError>
namespace Ui {
class Profile_win;
}

class Profile_win : public QDialog
{
    Q_OBJECT

public:
    explicit Profile_win(QWidget *parent = nullptr);
    ~Profile_win();

private:
    Ui::Profile_win *ui;
    Connect db;
public slots:
    void SetInfo(QString number);
};

#endif // PROFILE_WIN_H
