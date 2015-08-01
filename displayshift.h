#ifndef DISPLAYSHIFT_H
#define DISPLAYSHIFT_H

#include <QFrame>
#include <QLabel>
#include <QString>
#include <QFont>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Date.h"

namespace Ui {
class DisplayShift;
}

class DisplayShift : public QFrame
{
    Q_OBJECT

public:
    explicit DisplayShift(QWidget *parent = 0);
    ~DisplayShift();
    void init(Shift* attachShift, Scheduler* attachSchedule);

    void update(void);
private:
    Ui::DisplayShift *ui;

    Shift* shift;           //Pointer to the shift
    Scheduler* schedule;    //Maintain a pointer to the original scheduler

    bool selected;

    void mousePressEvent(QMouseEvent* event);
};

#endif // DISPLAYSHIFT_H
