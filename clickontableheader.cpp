#include "clickontableheader.h"
#include "QDebug"

ClickOnTableHeader::ClickOnTableHeader(QSqlTableModel* model, QObject* parent): QObject(parent),
    model(model)
{

}

void ClickOnTableHeader::onHeaderClicked(int column) {
    QString header = model->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
    if (header == "Дата найма"){

    }
}
