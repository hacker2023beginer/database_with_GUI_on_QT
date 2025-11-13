#ifndef BTNEDITACTION_H
#define BTNEDITACTION_H

//#include <QDateEdit>
#include "datavalidator.h"

#include <QSqlTableModel>
#include <QString>


class BtnEditAction : public QObject {
    Q_OBJECT
public:
    BtnEditAction(QSqlTableModel* model, QObject* parent);
    void updateEmployeeById(int row, const QString& name,
                        const QString& position, const QString& salary,
                        const QString& date);
    void onBtnEditClicked(QWidget* parent);
private:
    DataValidator validator;
    QSqlTableModel* model;
};

#endif // BTNEDITACTION_H
