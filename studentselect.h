#ifndef STUDENTSELECT_H
#define STUDENTSELECT_H

#include <QDialog>
#include <QSignalMapper>

#include "displaystudent.h"

#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Scheduler.h"

namespace Ui {
class StudentSelect;
}

class StudentSelect : public QDialog
{
    Q_OBJECT

public:
    explicit StudentSelect(QWidget *parent = 0);
    ~StudentSelect();
    void init(Shift* attachShift, Scheduler* attachSchedule);

private:
    Ui::StudentSelect *ui;

    Shift* shift;
    Scheduler* schedule;

    DisplayStudent** displayStudent;

    QSignalMapper* signalMapper;

public slots:
    void selected(QObject* objectClicked);
};

#endif // STUDENTSELECT_H
