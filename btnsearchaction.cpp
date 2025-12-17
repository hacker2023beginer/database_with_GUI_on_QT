#include "btnsearchaction.h"

#include <QTableView>

BtnSearchAction::BtnSearchAction(QObject* parent) : QObject(parent)
{

}

void BtnSearchAction::search(QString kind, QString searchValue){
    QString filter;
    if (kind == BY_ID)
    {
        filter = "id = " + searchValue;
    }
    else if (kind == BY_NAME)
    {
        filter = QString("name LIKE '%%1%'").arg(searchValue);
    }
    else if (kind == BY_SALARY)
    {
        filter = "salary = " + searchValue;
    }
    else
    {
        filter = QString("position LIKE '%%1%'").arg(searchValue);
    }
    QSqlTableModel* searchModel = new QSqlTableModel(this);
    searchModel->setTable("employees");
    searchModel->setFilter(filter);
    searchModel->select();

    QTableView* searchView = new QTableView;
    searchView->setModel(searchModel);
    searchView->show();

}
