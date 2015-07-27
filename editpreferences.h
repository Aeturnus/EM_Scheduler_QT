#ifndef EDITPREFERENCES_H
#define EDITPREFERENCES_H

#include <QDialog>
#include <string>


namespace Ui {
class EditPreferences;
}

class EditPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit EditPreferences(QWidget *parent = 0);
    ~EditPreferences();

    init(std::string* saved, std::string* savep, std::string* exportd, std::string* exportp);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditPreferences *ui;

    std::string* savedir;
    std::string* savepath;
    std::string* exportdir;
    std::string* exportpath;

};

#endif // EDITPREFERENCES_H
