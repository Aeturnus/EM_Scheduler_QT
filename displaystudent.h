#ifndef DISPLAYSTUDENT_H
#define DISPLAYSTUDENT_H

#include <QFrame>

namespace Ui {
class DisplayStudent;
}

class DisplayStudent : public QFrame
{
    Q_OBJECT

public:
    explicit DisplayStudent(QWidget *parent = 0);
    ~DisplayStudent();

private:
    Ui::DisplayStudent *ui;
};

#endif // DISPLAYSTUDENT_H
