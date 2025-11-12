#include "btnaddaction.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QToolTip>
//#include <QDateEdit>

BtnAddAction::BtnAddAction(QSqlTableModel* model,
                           QLineEdit* nameEdit,
                           QLineEdit* postEdit,
                           QLineEdit* salaryEdit,
                           QLineEdit* dataEdit,
                           QObject* parent)
    : QObject(parent),
      model(model),
      nameEdit(nameEdit),
      postEdit(postEdit),
      salaryEdit(salaryEdit),
      dataEdit(dataEdit)
{
}


void BtnAddAction::onAddClicked(const QString& name, const QString& position, QString& salary, const QString& date)
{
    if (!validator.nameValidator(name)) {
            nameEdit->setStyleSheet("border: 1px solid red;");
            QToolTip::showText(
                nameEdit->mapToGlobal(QPoint(0, nameEdit->height())),
                "Некорректное имя",
                nameEdit
            );
            return;
        } else {
            nameEdit->setStyleSheet(""); // сброс подсветки
        }
    if (!validator.positionValidator(position)) {
            postEdit->setStyleSheet("border: 1px solid red;");
            QToolTip::showText(
                postEdit->mapToGlobal(QPoint(0, postEdit->height())),
                "Некорректная позиция",
                postEdit
            );
            return;
        } else {
            postEdit->setStyleSheet(""); // сброс подсветки
        }
    if (!validator.salaryValidator(salary)) {
            salaryEdit->setStyleSheet("border: 1px solid red;");
            QToolTip::showText(
                salaryEdit->mapToGlobal(QPoint(0, salaryEdit->height())),
                "Некорректная зарплата",
                salaryEdit
            );
            return;
        } else {
            salaryEdit->setStyleSheet(""); // сброс подсветки
        }
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

