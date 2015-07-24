#include "setdate.h"
#include "ui_setdate.h"

SetDate::SetDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDate)
{
    ui->setupUi(this);
}

SetDate::~SetDate()
{
    delete ui;
}

void SetDate::init(QDate *attachDate, QDate minDate)
{
    date = attachDate;
    ui->calendarWidget->setMinimumDate(minDate);
}

void SetDate::on_buttonBox_accepted()
{
    *date = ui->calendarWidget->selectedDate();
    //QDate temp = ui->calendarWidget->selectedDate();
    //date->setDate(temp.year(),temp.month(),temp.day());
}
