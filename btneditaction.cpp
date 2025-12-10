#include "btneditaction.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QInputDialog>
#include <QMessageBox>
#include "btneditwindow.h"
#include "ui_btneditwindow.h"
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
    record.setValue("date_hired", date);

    if (!model->setRecord(row, record)) {
        qWarning() << "Не удалось обновить запись в модели";
        return;
    }

    if (!model->submitAll()) {
        qWarning() << "Ошибка при сохранении:" << model->lastError().text();
        if (!model->submitAll()) {
            qWarning() << "Ошибка сохранения:" << model->lastError().text();
            if (model->lastError().text().contains("UNIQUE")) {
                QMessageBox::warning(nullptr, "Warning", "Имя уже существует!");
            }
        }
        model->revertAll(); // откатить изменения
    }
}

void BtnEditAction::onBtnEditClicked(QWidget* parent)
{
    BtnEditWindow *dlg = new BtnEditWindow(parent);
    if (dlg->exec() == QDialog::Accepted) {
            // получаем данные из диалога
            //int row = dlg->getEmployeeId().toInt();   // индекс строки
        QString name = dlg->getNewName();
        QString position = dlg->getNewPosition();
        QString salary = dlg->getNewSalary();
        QString date = dlg->getNewDate(); // или поле в форме
        int id = dlg->getEmployeeId().toInt();

        if (!validator.isValidEmployee(name, position, salary)){
           QMessageBox::warning(nullptr, "Warning", "Incorrect input data");
           return;
        }


            int row = -1;

            // ищем строку, где поле "id" совпадает
            for (int i = 0; i < model->rowCount(); ++i) {
                QSqlRecord rec = model->record(i);
                if (rec.value("id").toInt() == id) {
                    row = i;
                    break;
                }
            }

            if (row == -1) {
                qWarning() << "Запись с id =" << id << " не найдена";
                return;
            }

            // обновляем запись
            updateEmployeeById(row, name, position, salary, date);
        }
    //show() if need to use main ui

}
