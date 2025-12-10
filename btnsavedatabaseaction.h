#ifndef BTNSAVEDATABASEACTION_H
#define BTNSAVEDATABASEACTION_H

#include <QSqlTableModel>
#include <QObject>


class BtnSaveDatabaseAction : public QObject
{
    Q_OBJECT
public:
    BtnSaveDatabaseAction(QSqlTableModel* model, QObject* parent);
    void saveModelToJSON(QSqlTableModel* model, const QString& fileName);
private:
    QSqlTableModel* model;
};

#endif // BTNSAVEDATABASEACTION_H
