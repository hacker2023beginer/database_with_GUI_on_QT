#include "btnfilteraction.h"
#include "btnfilterwindow.h"
#include "datavalidator.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QDate>

BtnFilterAction::BtnFilterAction(QSqlTableModel *model, QObject *parent) :
    QObject(parent),
    model(model)
{

}


void BtnFilterAction::onBtnFilterClicked(QWidget *parent){
    if (!model) {
        QMessageBox::warning(parent, "Warning", "Модель не инициализирована");
        return;
    }

    if (model->tableName().isEmpty()) {
        QMessageBox::warning(parent, "Warning", "Таблица не установлена в модели");
        return;
    }

    DataValidator validator;
    BtnFilterWindow *dlg = new BtnFilterWindow(parent);
    if (dlg->exec() == QDialog::Accepted) {
        QString name     = dlg->getName();
        QString salaryAt = dlg->getSalaryAt();
        QString salaryTo = dlg->getSalaryTo();
        QString position = dlg->getPosition();
        QString dateAt   = dlg->getDateAt();
        QString dateTo   = dlg->getDateTo();

        QStringList conditions;

        // salary
        if (salaryAt.isEmpty() && !salaryTo.isEmpty()) {
            QMessageBox::warning(parent, "Warning", "Установите начальное значение salary");
            return;
        } else if (!salaryAt.isEmpty() && salaryTo.isEmpty()) {
            QMessageBox::warning(parent, "Warning", "Установите конечное значение salary");
            return;
        } else if (!salaryAt.isEmpty() && !salaryTo.isEmpty()) {
            if (!validator.salaryValidator(salaryAt) || !validator.salaryValidator(salaryTo)) {
                QMessageBox::warning(parent, "Warning", "Неверное значение salary");
                return;
            }
            conditions << QString("salary BETWEEN %1 AND %2").arg(salaryAt, salaryTo);
        }

        // date
        if (dateAt.isEmpty() && !dateTo.isEmpty()) {
            QMessageBox::warning(parent, "Warning", "Установите начальное значение даты");
            return;
        } else if (!dateAt.isEmpty() && dateTo.isEmpty()) {
            QMessageBox::warning(parent, "Warning", "Установите конечное значение даты");
            return;
        } else if (!dateAt.isEmpty() && !dateTo.isEmpty()) {
//            QDate d1 = QDate::fromString(dateAt, "yyyy-MM-dd");
//            QDate d2 = QDate::fromString(dateTo, "yyyy-MM-dd");
//            if (!d1.isValid() || !d2.isValid()) {
//                QMessageBox::warning(parent, "Warning", "Неверный формат даты (ожидается yyyy-MM-dd)");
//                return;
//            }
            conditions << QString("date_hired BETWEEN '%1' AND '%2'")
                          .arg(dateAt, dateTo);
        }

        // position
        if (!position.isEmpty()) {
            if (!validator.positionValidator(position)) {
                QMessageBox::warning(parent, "Warning", "Неверное значение position");
                return;
            }
            conditions << QString("position = '%1'").arg(position);
        }

        // name
        if (!name.isEmpty()) {
            if (!validator.nameValidator(name)) {
                QMessageBox::warning(parent, "Warning", "Неверное значение name");
                return;
            }
            conditions << QString("name = '%1'").arg(name);
        }

        // применяем фильтр
        if (!conditions.isEmpty()) {
            QString filter = conditions.join(" AND ");
            model->setFilter(filter);
            model->select(); // обновляем таблицу
        }
    }

}

void BtnFilterAction::onBtnFilterResetClicked(QWidget *parent){
    if (!model) {
            QMessageBox::warning(parent, "Warning", "Модель не инициализирована");
            return;
        }

        if (model->tableName().isEmpty()) {
            QMessageBox::warning(parent, "Warning", "Таблица не установлена в модели");
            return;
        }

        model->setFilter("");
        model->select();
}
