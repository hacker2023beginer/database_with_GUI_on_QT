#ifndef CLICKONTABLEHEADER_H
#define CLICKONTABLEHEADER_H

#include <QSqlTableModel>



class ClickOnTableHeader : public QObject {
        Q_OBJECT
public:
    ClickOnTableHeader(QSqlTableModel* model, QObject* parent);
    void onHeaderClicked(int column);
private:
    QSqlTableModel* model;
};

#endif // CLICKONTABLEHEADER_H
