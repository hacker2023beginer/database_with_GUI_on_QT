// btneditwindow.h

#include <QDialog>

namespace Ui {
class BtnEditWindow;
}

class BtnEditWindow : public QDialog {
    Q_OBJECT
public:
    explicit BtnEditWindow(QWidget *parent = nullptr);
    ~BtnEditWindow();
    QString getEmployeeId();
    QString getNewName();
    QString getNewSalary();
    QString getNewPosition();
    QString getNewDate();
private:
    Ui::BtnEditWindow *ui;
};
