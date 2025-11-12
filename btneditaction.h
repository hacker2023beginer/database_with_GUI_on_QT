#ifndef BTNEDITACTION_H
#define BTNEDITACTION_H

//#include <QDateEdit>
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
    QSqlTableModel* model;
};

#endif // BTNEDITACTION_H
