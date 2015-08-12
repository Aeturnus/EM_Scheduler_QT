#ifndef SHIFTTIMEEDIT_H
#define SHIFTTIMEEDIT_H

#include <QDialog>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"

namespace Ui {
class ShiftTimeEdit;
}

class ShiftTimeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ShiftTimeEdit(QWidget *parent = 0);
    ~ShiftTimeEdit();
    void init(Scheduler* attachSchedule, Shift* attachShift);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ShiftTimeEdit *ui;
    Shift* shift;
    Scheduler* schedule;
};

#endif // SHIFTTIMEEDIT_H
