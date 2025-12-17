#ifndef BTNSEARCHACTION_H
#define BTNSEARCHACTION_H

#include <QObject>
#include <QSqlTableModel>



class BtnSearchAction : public QObject
{
    Q_OBJECT
public:
    BtnSearchAction(QObject* parent);
    void search(QString kind, QString searchValue);
private:
    const QString BY_NAME = "By name";
    const QString BY_ID = "By id";
    const QString BY_POSITION = "By position";
    const QString BY_SALARY = "By salary";
};

#endif // BTNSEARCHACTION_H
