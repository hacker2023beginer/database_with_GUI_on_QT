#ifndef BTNFILTERWINDOW_H
#define BTNFILTERWINDOW_H

#include <QDialog>

namespace Ui {
class BtnFilterWindow;
}

class BtnFilterWindow : public QDialog {
    Q_OBJECT
public:
    explicit BtnFilterWindow(QWidget *parent = nullptr);
    ~BtnFilterWindow();
    QString getName();
    QString getSalaryAt();
    QString getSalaryTo();
    QString getPosition();
    QString getDateAt();
    QString getDateTo();
private:
    Ui::BtnFilterWindow *ui;
};

#endif // BTNFILTERWINDOW_H
