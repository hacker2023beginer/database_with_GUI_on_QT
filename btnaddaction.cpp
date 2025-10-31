#include "btnaddaction.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>

BtnAddAction::BtnAddAction(QSqlTableModel* m, QObject* parent)
    : QObject(parent), model(m) {

}

void BtnAddAction::onAddClicked(const QString& name, const QString& position, double salary, const QDate& date)
{
    QSqlRecord record = model->record();
    record.setValue("name", name);
    record.setValue("position", position);
    record.setValue("salary", salary);
    record.setValue("date_hired", date);

    if (!model->insertRecord(-1, record)) {
        qDebug() << "Ошибка при добавлении:" << model->lastError().text();
    } else {
        model->submitAll(); // сохраняет в БД
        model->select();    // обновляет отображение
    }
}

