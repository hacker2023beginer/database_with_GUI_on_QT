#ifndef BTNSAVEDATABASEACTION_H
#define BTNSAVEDATABASEACTION_H

#include <QSqlTableModel>
#include <QObject>


class BtnSaveDatabaseAction : public QObject
{
    Q_OBJECT
public:
    BtnSaveDatabaseAction(QSqlTableModel* model, QObject* parent);
    void saveModelToJSON(QSqlTableModel *model, QWidget* parent);
private:
    QSqlTableModel* model;
};

#endif // BTNSAVEDATABASEACTION_H
