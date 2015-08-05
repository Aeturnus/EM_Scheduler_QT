#ifndef DISPLAYSTUDENT_H
#define DISPLAYSTUDENT_H

#include <QPushButton>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Student.h"

namespace Ui {
class DisplayStudent;
}

class DisplayStudent : public QPushButton
{
    Q_OBJECT

public:
    explicit DisplayStudent(QWidget *parent = 0);
    ~DisplayStudent();
    void init(Student* attachStudent, Scheduler* attachSchedule);

    void update(void);

    Student* getStudent(void);
private:
    Ui::DisplayStudent *ui;

    Student* student;
    Scheduler* schedule;

};

#endif // DISPLAYSTUDENT_H
