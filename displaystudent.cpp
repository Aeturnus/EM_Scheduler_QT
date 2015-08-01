#include "displaystudent.h"
#include "ui_displaystudent.h"

DisplayStudent::DisplayStudent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DisplayStudent)
{
    ui->setupUi(this);
}

DisplayStudent::~DisplayStudent()
{
    delete ui;
}
