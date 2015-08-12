#ifndef OVERRIDESELECT_H
#define OVERRIDESELECT_H

#include <QDialog>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Student.h"

namespace Ui {
class OverrideSelect;
}

class OverrideSelect : public QDialog
{
    Q_OBJECT

public:
    explicit OverrideSelect(QWidget *parent = 0);
    ~OverrideSelect();

    void init(Scheduler* attachSchedule, Shift* attachShift, Student* attachStudent, Scheduler::AssignReturn type, bool* attachSuccess);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OverrideSelect *ui;

    Scheduler* schedule;
    Shift* shift;
    Student* student;
    bool* success;
};

#endif // OVERRIDESELECT_H
