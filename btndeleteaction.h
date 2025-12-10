#ifndef BTNDELETEACTION_H
#define BTNDELETEACTION_H

#include "datavalidator.h"

#include <QDialog>
#include <QObject>
#include <QSqlTableModel>
#include <QWidget>



class BtnDeleteAction : public QObject
{
    Q_OBJECT
public:
    BtnDeleteAction(QSqlTableModel* model, QObject* parent);
    ~BtnDeleteAction();
    void onBtnDeleteClicked(QWidget* parent);
private:
    DataValidator validator;
    QSqlTableModel* model;
};

#endif // BTNDELETEACTION_H
