#ifndef SETDATE_H
#define SETDATE_H

#include <QDialog>
#include <QDate>

namespace Ui {
class SetDate;
}

class SetDate : public QDialog
{
    Q_OBJECT

public:
    explicit SetDate(QWidget *parent = 0);
    ~SetDate();

    void init(QDate* attachDate,QDate minDate);

private slots:

    void on_buttonBox_accepted();

private:
    Ui::SetDate *ui;

    QDate* date;
};

#endif // SETDATE_H
