#ifndef DISPLAYSCHEDULE_H
#define DISPLAYSCHEDULE_H

#include <QWidget>

#include "../EM_Scheduler/Scheduler.h"

#include "displaydateshifts.h"
namespace Ui {
class DisplaySchedule;
}

class DisplaySchedule : public QWidget
{
    Q_OBJECT

public:
    explicit DisplaySchedule(QWidget *parent = 0);
    ~DisplaySchedule();

    void init(Scheduler* attachSchedule);

private:
    Ui::DisplaySchedule *ui;

    Scheduler* schedule;

    DisplayDateShifts** dateShiftWidgets;
};

#endif // DISPLAYSCHEDULE_H
