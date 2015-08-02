#ifndef DISPLAYSCHEDULE_H
#define DISPLAYSCHEDULE_H

#include <QWidget>
#include <QLabel>

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

    void deleteMem(void);

    int PAD = 50;

    void update(void);

private:
    Ui::DisplaySchedule *ui;

    Scheduler* schedule;

    DisplayDateShifts** dateShiftWidgets;

    QLabel* weekdayLabel[7];


};

#endif // DISPLAYSCHEDULE_H
