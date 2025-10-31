#include <QObject>
#include <QSqlTableModel>

class BtnAddAction : public QObject {
    Q_OBJECT
public:
    explicit BtnAddAction(QSqlTableModel* model, QObject* parent = nullptr);
    void onAddClicked(const QString& name, const QString& position, double salary, const QDate& date);

private:
    QSqlTableModel* model;
};
