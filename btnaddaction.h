#include "datavalidator.h"

//#include <QDateEdit>
#include <QLineEdit>
#include <QObject>
#include <QSqlTableModel>

class BtnAddAction : public QObject {
    Q_OBJECT
public:
    explicit BtnAddAction(QSqlTableModel* model, QLineEdit* nameEdit,
                          QLineEdit* postEdit, QLineEdit* salaryEdit,
                          QLineEdit* dataEdit, QObject* parent = nullptr);
    void onAddClicked(const QString& name, const QString& position, QString& salary, const QString& date);

private:
    QSqlTableModel* model;
    DataValidator validator;
    QLineEdit* nameEdit;
    QLineEdit* postEdit;
    QLineEdit* salaryEdit;
    QLineEdit* dataEdit;
};
