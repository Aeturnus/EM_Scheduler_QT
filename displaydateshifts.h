#ifndef DISPLAYDATESHIFTS_H
#define DISPLAYDATESHIFTS_H

/*
 * The purpose of this widget is to display an entire day's worth of shifts, spreadsheet style
 */

#include <QWidget>
#include <QLabel>

#include <vector>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Date.h"

#include "displayshift.h"

namespace Ui {
class DisplayDateShifts;
}

class DisplayDateShifts : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayDateShifts(QWidget *parent = 0);
    ~DisplayDateShifts();
    void init(Date* attachDate, Scheduler* attachSchedule);

    unsigned int getShiftNum(void);

    int WIDTH = 100;
    int HEIGHT = 100;
private:
    Ui::DisplayDateShifts *ui;
    Date* date;                     //Pass pointer of the selected date to it
    Scheduler* schedule;             //Pass the pointer to schedule to it
    std::vector<Shift*> shiftPtrVector;     //Vector of shifts attached to it
    unsigned int shiftNum;

    QLabel* labelDate;

    DisplayShift** shiftWidgets;    //Make an array of pointers to DisplayShifts
};

#endif // DISPLAYDATESHIFTS_H
