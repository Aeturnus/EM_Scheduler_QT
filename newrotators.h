#ifndef NEWROTATORS_H
#define NEWROTATORS_H

#include <QDialog>
#include <QLineEdit>
#include <string>
#include <vector>

namespace Ui {
class NewRotators;
}

class NewRotators : public QDialog
{
    Q_OBJECT

public:
    explicit NewRotators(QWidget *parent = 0);
    ~NewRotators();
    void init(std::vector<std::string>* studentNameVector);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewRotators *ui;

    std::vector<std::string>* studentNames;

    QLineEdit** nameEdits;


};

#endif // NEWROTATORS_H
