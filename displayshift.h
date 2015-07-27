#ifndef DISPLAYSHIFT_H
#define DISPLAYSHIFT_H

#include <QWidget>
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

class DisplayShift : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayShift(QWidget *parent = 0);
    ~DisplayShift();
    void init(Shift* attachShift, Scheduler* attachSchedule);

private:
    Ui::DisplayShift *ui;
    void update(void);

    Shift* shift;           //Pointer to the shift
    Scheduler* schedule;    //Maintain a pointer to the original scheduler

    bool selected;

    QLabel* label_title;          //Name of shift or block reason
    QLabel* label_times;          //Times of shift
    QLabel* label_studentname;    //Name of student who took it
    QLabel* label_manual;         //Display if it's manual or autoassigned

    QFont* font_title;
    QFont* font_times;
    QFont* font_studentname;
    QFont* font_manual;
};

#endif // DISPLAYSHIFT_H
