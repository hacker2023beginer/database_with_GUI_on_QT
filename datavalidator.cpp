#include "datavalidator.h"

#include <QRegularExpression>

DataValidator::DataValidator()
{

}

bool DataValidator::ageValidator(QString text){
    if (text.isEmpty()) {
        return false;
    }
    QRegularExpression re(AGE_REGEXP);
    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        return true;
    }
    return false;
}

bool DataValidator::nameValidator(QString text){
    if (text.isEmpty()) {
        return false;
    }
    QRegularExpression re(NAME_REGEXP);
    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        return true;
    }
    return false;
}

bool DataValidator::positionValidator(QString text){
    if (text.isEmpty()) {
        return false;
    }
    return true;
}

bool DataValidator::salaryValidator(QString text){
    if (text.isEmpty()) {
        return false;
    }
    QRegularExpression re(SALARY_REGEXP);
    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        return true;
    }
    return false;
}

bool DataValidator::isValidEmployee(QString name, QString position, QString salary){
    return nameValidator(name) && salaryValidator(salary) && positionValidator(position);
}
