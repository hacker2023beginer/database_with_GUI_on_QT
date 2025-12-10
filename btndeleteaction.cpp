#include "btndeleteaction.h"
#include "btndeletewindow.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
BtnDeleteAction::BtnDeleteAction(QSqlTableModel* model, QObject* parent) : QObject(parent),
    model(model)
{

}
BtnDeleteAction::~BtnDeleteAction(){

}

void BtnDeleteAction::onBtnDeleteClicked(QWidget* parent){
    // Проверяем, что модель валидна и имеет установленную таблицу
    if (!model) {
        QMessageBox::warning(parent, "Warning", "Модель не инициализирована");
        return;
    }
    
    // Проверяем, что таблица установлена
    if (model->tableName().isEmpty()) {
        QMessageBox::warning(parent, "Warning", "Таблица не установлена в модели");
        return;
    }
    
    // Убеждаемся, что модель обновлена
    if (!model->select()) {
        QMessageBox::warning(parent, "Warning", "Ошибка при обновлении модели: " + model->lastError().text());
        return;
    }
    
    BtnDeleteWindow *dlg = new BtnDeleteWindow(parent);
    if (dlg->exec() == QDialog::Accepted) {
        int id = dlg->getEmployeeId().toInt();
            // ищем строку, где поле "id" совпадает
        int row = -1;
            for (int i = 0; i < model->rowCount(); ++i) {
                QSqlRecord rec = model->record(i);
                if (rec.value("id").toInt() == id) {
                    row = i;
                    break;
                }
            }

            if (row == -1) {
                QMessageBox::warning(parent, "Warning", "Incorrect id");
                return;
            }

            // удаляем строку
            if (!model->removeRow(row)) {
                QMessageBox::warning(parent, "Warning", "Не удалось удалить запись из модели");
                return;
            }

            // сохраняем изменения в БД
            if (!model->submitAll()) {
                QMessageBox::warning(parent, "Warning", "Ошибка при удалении: " + model->lastError().text());
                model->revertAll(); // откат, если не удалось
            } else {
                model->select(); // обновляем отображение
            }

        }
}
