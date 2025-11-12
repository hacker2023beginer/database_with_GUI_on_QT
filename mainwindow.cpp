#include "mainwindow.h"
#include "btnaddaction.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>

void resetDatabase();
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключение к базе данных
    MainWindow::ConnectToDatabase();

    // Создание таблицы, если её нет
    MainWindow::CreateFields();

    //resetDatabase();

    // Настройка модели
    QSqlTableModel *model = MainWindow::SettingTable();

    // Привязка модели к таблице
    ui->tableView->setModel(model);

    // Создание обработчика
    BtnAddAction* addAction = new BtnAddAction(model, ui->LneName, ui->LnePosition, ui->LneSalary, ui->LneDate, this);

    // Подключение кнопки
    connect(ui->BtnAdd, &QPushButton::clicked, this, [=]() {
        QString name = ui->LneName->text();
        QString position = ui->LnePosition->text();
        QString salary = ui->LneSalary->text();
        QString date = ui->LneDate->text();

        addAction->onAddClicked(name, position, salary, date);
    });


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectToDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("employees.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
    }
}

void MainWindow::CreateFields(){
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS employees ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, "
               "position TEXT, "
               "salary REAL, "
               "date_hired DATE)");
}

QSqlTableModel* MainWindow::SettingTable(){
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable("employees");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(1, Qt::Horizontal, "Имя");
    model->setHeaderData(2, Qt::Horizontal, "Должность");
    model->setHeaderData(3, Qt::Horizontal, "Зарплата");
    model->setHeaderData(4, Qt::Horizontal, "Дата найма");
    model->select();
    return model;
}

void resetDatabase()
{
    QSqlDatabase::database().close(); // обязательно закрыть соединение
    QFile::remove("employees.db");    // удаление файла
}
