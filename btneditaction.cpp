#include "btneditaction.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QInputDialog>
BtnEditAction::BtnEditAction(QSqlTableModel* model, QObject* parent): QObject(parent),
    model(model)
{

}

void BtnEditAction::updateEmployeeById(int row, const QString& name,
                              const QString& position, const QString& salary,
                              const QString& date) {
    if (row < 0 || row >= model->rowCount()) {
            qWarning() << "Некорректный индекс строки";
            return;
        }

        QSqlRecord record = model->record(row);

        record.setValue("name", name);
        record.setValue("position", position);
        record.setValue("salary", salary);
        record.setValue("hire_date", date);

        if (!model->setRecord(row, record)) {
            qWarning() << "Не удалось обновить запись в модели";
            return;
        }

        if (!model->submitAll()) {
            qWarning() << "Ошибка при сохранении:" << model->lastError().text();
            model->revertAll(); // откатить изменения
        }
}

void BtnEditAction::onBtnEditClicked(QWidget* parent)
{
    bool ok;
    int id = QInputDialog::getInt(parent,
                                  "Редактирование записи",
                                  "Введите ID сотрудника:",
                                  0,   // значение по умолчанию
                                  0,   // минимальное
                                  1000000, // максимальное
                                  1,   // шаг
                                  &ok);

    if (ok) {
//        EditEmployeeDialog dlg(parent);
//        if (dlg.exec() == QDialog::Accepted) {
//            QString newName = dlg.name();
//            QString newPosition = dlg.position();
//            QString newSalary = dlg.salary();
//            QString newDate = dlg.date();

//            updateEmployeeById(id, newName, newPosition, newSalary, newDate);
//         }
    }
}
