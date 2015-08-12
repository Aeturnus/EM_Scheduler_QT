#include "shifttimeedit.h"
#include "ui_shifttimeedit.h"

#include <QMessageBox>

ShiftTimeEdit::ShiftTimeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShiftTimeEdit)
{
    ui->setupUi(this);
}

ShiftTimeEdit::~ShiftTimeEdit()
{
    delete ui;
}

void ShiftTimeEdit::init(Scheduler* attachSchedule, Shift *attachShift)
{
    schedule = attachSchedule;
    shift = attachShift;
    ui->spinBoxStart->setValue(shift->getStart());
    ui->spinBoxEnd->setValue(shift->getEnd());
    QMessageBox::critical(this,tr("IMPORTANT"),tr("By changing the shift's time, this shift will be unassigned due to possible conflicting times with the assigned student's other shifts."));
}

void ShiftTimeEdit::on_buttonBox_accepted()
{
    schedule->unassign(shift,false);
    shift->setTime(ui->spinBoxStart->value(),ui->spinBoxEnd->value());
}
