#ifndef STRINGEDIT_H
#define STRINGEDIT_H

#include <QDialog>
#include <string>


namespace Ui {
class StringEdit;
}

class StringEdit : public QDialog
{
    Q_OBJECT

public:
    explicit StringEdit(QWidget *parent = 0);
    ~StringEdit();
    void init(std::string* attachString, std::string title);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::StringEdit *ui;
    std::string* stringEdit;
};

#endif // STRINGEDIT_H
