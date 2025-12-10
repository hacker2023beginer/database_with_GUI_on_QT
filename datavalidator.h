#ifndef DATAVALIDATOR_H
#define DATAVALIDATOR_H

#include <QSqlTableModel>
#include <QString>



class DataValidator
{
public:
    DataValidator();
    bool nameValidator(QString text);
    bool ageValidator(QString text);
    bool salaryValidator(QString text);
    bool positionValidator(QString text);
    bool isValidEmployee(QString name, QString position, QString salary);
    bool isUniqueName();
private:
    const QString AGE_REGEXP = "^[1-9][0-9]?$|^100$";
    const QString NAME_REGEXP = "^[A-Z][a-z]* [A-Z][a-z]*$";
    const QString SALARY_REGEXP = "^[0-9]+$";
    QSqlTableModel* model;
};

#endif // DATAVALIDATOR_H
