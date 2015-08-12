#ifndef SHIFTSELECT_H
#define SHIFTSELECT_H

#include <QObject>
#include <QDialog>

#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Scheduler.h"

namespace Ui {
class ShiftSelect;
}

class ShiftSelect : public QDialog
{
    Q_OBJECT

public:
    explicit ShiftSelect(QWidget *parent = 0);
    ~ShiftSelect();
    void init(Shift* attachShift, Scheduler* attachSchedule);

    void update(void);

private slots:

    void on_pushButtonSetManual_clicked();

    void on_pushButtonUnsetManual_clicked();

    void on_pushButtonBlock_clicked();

    void on_pushButtonUnblock_clicked();

    void on_pushButtonUnassign_clicked();

    void on_pushButtonAssign_clicked();

    void on_pushButtonChangeName_clicked();

    void on_pushButtonChangeBlockReason_clicked();

    void on_pushButtonChangeTime_clicked();

private:
    Ui::ShiftSelect *ui;

    Shift* shift;
    Scheduler* schedule;
};

#endif // SHIFTSELECT_H
