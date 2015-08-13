#ifndef SHOWUNASSIGNED_H
#define SHOWUNASSIGNED_H

#include <QDialog>
#include <QScrollArea>

#include <vector>

#include "displayshift.h"

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"

namespace Ui {
class ShowUnassigned;
}

class ShowUnassigned : public QDialog
{
    Q_OBJECT

public:
    explicit ShowUnassigned(QWidget *parent = 0);
    ~ShowUnassigned();
    void init(Scheduler* attachSchedule);

private:
    void resizeEvent(QResizeEvent *event);

    Ui::ShowUnassigned *ui;
    Scheduler* schedule;
    std::vector<DisplayShift*> shiftWidgets;
    QWidget* container;
    QScrollArea* scrollArea;
};

#endif // SHOWUNASSIGNED_H
