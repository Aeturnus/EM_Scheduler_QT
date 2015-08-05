#ifndef EDITSCHEDULE_H
#define EDITSCHEDULE_H

#include <QDialog>

#include "../EM_Scheduler/Scheduler.h"

namespace Ui {
class EditSchedule;
}

class EditSchedule : public QDialog
{
    Q_OBJECT

public:
    explicit EditSchedule(QWidget *parent = 0);
    ~EditSchedule();
    void init(Scheduler* attachSchedule);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_toolButtonStudentNames_clicked();

private:
    Ui::EditSchedule *ui;
    Scheduler* schedule;
};

#endif // EDITSCHEDULE_H
