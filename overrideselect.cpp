#include "overrideselect.h"
#include "ui_overrideselect.h"

#include <QString>
#include <QMessageBox>

OverrideSelect::OverrideSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OverrideSelect)
{
    ui->setupUi(this);
}

OverrideSelect::~OverrideSelect()
{
    delete ui;
}

void OverrideSelect::init(Scheduler *attachSchedule, Shift *attachShift, Student *attachStudent, Scheduler::AssignReturn type, bool* attachSuccess)
{
    schedule = attachSchedule;
    shift = attachShift;
    student = attachStudent;
    success = attachSuccess;
    QString typeString;
    switch(type)
    {
    case Scheduler::SUCCESS:
        this->close();
        break;
    case Scheduler::CONSEC:
        typeString = "Student will have too many consecutive shifts!";
        break;
    case Scheduler::MINTIME:
        typeString = "Student has a shift within 8 hours of this shift!";
        break;
    case Scheduler::OVERLAP:
        this->close();
        break;
    case Scheduler::OVERMAX:
        typeString = "Student has the maximum number of assignable shifts!";
        break;
    case Scheduler::ISNULL:
        this->close();
        break;
    }

    ui->labelError->setText(typeString);
}

void OverrideSelect::on_buttonBox_accepted()
{
    if(schedule->assign(shift,student,true,true) != Scheduler::SUCCESS)
    {
        QMessageBox::critical(this,tr("Error"),tr("Failed to assign."));
    }
    *success= true;
}
