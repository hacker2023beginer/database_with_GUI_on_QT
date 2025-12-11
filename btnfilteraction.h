#ifndef BTNFILTERACTION_H
#define BTNFILTERACTION_H

#include <QObject>
#include <QSqlTableModel>



class BtnFilterAction : public QObject {
    Q_OBJECT
public:
    BtnFilterAction(QSqlTableModel *model, QObject *parent);
    void onBtnFilterClicked(QWidget* parent);
    void onBtnFilterResetClicked(QWidget* parent);
private:
    QSqlTableModel* model;
};

#endif // BTNFILTERACTION_H
