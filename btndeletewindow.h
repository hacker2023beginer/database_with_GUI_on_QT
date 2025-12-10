#ifndef BTNDELETEWINDOW_H
#define BTNDELETEWINDOW_H
#include <QDialog>

namespace Ui {
class btndeletewindow;
}

class BtnDeleteWindow : public QDialog {
    Q_OBJECT
public:
    explicit BtnDeleteWindow(QWidget *parent = nullptr);
    ~BtnDeleteWindow();
    QString getEmployeeId();
private:
    Ui::btndeletewindow *ui;
};
#endif // BTNDELETEWINDOW_H
