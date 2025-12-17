#include "btnsavedatabaseaction.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

BtnSaveDatabaseAction::BtnSaveDatabaseAction(QSqlTableModel* model, QObject* parent) : QObject(parent),
    model(model)
{

}

void BtnSaveDatabaseAction::saveModelToJSON(QSqlTableModel *model, QWidget* parent){
    QString fileName = QFileDialog::getSaveFileName(
                parent,
                "Сохранить базу в JSON",
                QDir::homePath(),
                "JSON файлы (*.json)"
            );

    QJsonArray rows;
    for (int row = 0; row < model->rowCount(); ++row){
        QJsonObject obj;
        for (int col = 0; col < model->columnCount(); ++col){
            QString key = model->headerData(col, Qt::Horizontal).toString();
            obj[key] = model->data(model->index(row, col)).toString();
        }
        rows.append(obj);
    }
    QJsonDocument doc(rows);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
    }
}
