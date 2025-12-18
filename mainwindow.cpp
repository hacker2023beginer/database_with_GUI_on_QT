#include "mainwindow.h"
#include "btnaddaction.h"
#include "ui_mainwindow.h"
#include "btneditaction.h"
#include "btndeleteaction.h"
#include "clickontableheader.h"
#include "btnfilteraction.h"
#include "btnsavedatabaseaction.h"
#include "btnsearchaction.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QGuiApplication>
#include <qscreen.h>

void resetDatabase();
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800, 600);
    // Подключение к базе данных
    MainWindow::ConnectToDatabase();

    // Создание таблицы, если её нет
    MainWindow::CreateFields();

    //resetDatabase();

    // Настройка модели
    QSqlTableModel *model = MainWindow::SettingTable();

    // Привязка модели к таблице
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Подключение обработчика нажатия колонки
    ui->tableView->setSortingEnabled(true);

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

    BtnEditAction* editAction = new BtnEditAction(model, this);
    connect(ui->BtnEdit, &QPushButton::clicked, this, [=]() {
        editAction->onBtnEditClicked(this);
    });

    BtnDeleteAction* deleteAction = new BtnDeleteAction(model, this);
    connect(ui->BtnDelete, &QPushButton::clicked, this, [=]() {
        deleteAction->onBtnDeleteClicked(this);
    });

    BtnFilterAction* filterAction = new BtnFilterAction(model, this);
    connect(ui->btnFilter, &QPushButton::clicked, this, [=]() {filterAction->onBtnFilterClicked(this);});
    connect(ui->btnFilterReset, &QPushButton::clicked, this, [=]() {filterAction->onBtnFilterResetClicked(this);});
    BtnSaveDatabaseAction *saveAction = new BtnSaveDatabaseAction(model, this);
    connect(ui->BtnSaveToDatabase, &QPushButton::clicked, this, [=]() {
        saveAction->saveModelToJSON(model, this);
    });

    connect(ui->BtnSearch, &QPushButton::clicked, this, [=]() {
        QString kind = ui->comboBox->currentText();
        QString searchValue = ui->LneSearch->text();
        BtnSearchAction *searchAction = new BtnSearchAction(this);
        searchAction->search(kind, searchValue);
    });
    ui->actionSave_2->setVisible(true);
    connect(ui->actionSave_2, &QAction::triggered, this, [=](){
        saveAction->saveModelToJSON(model, this);
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
               "name TEXT UNIQUE, "
               "position TEXT, "
               "salary REAL, "
               "date_hired TEXT)");
}

QSqlTableModel* MainWindow::SettingTable(){
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable("employees");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(1, Qt::Horizontal, "Name"); //Имя
    model->setHeaderData(2, Qt::Horizontal, "Position"); //Должность
    model->setHeaderData(3, Qt::Horizontal, "Salary"); //Зарплата
    model->setHeaderData(4, Qt::Horizontal, "Date"); //Дата найма
    model->select();
    return model;
}

void resetDatabase()
{
    QSqlDatabase::database().close(); // обязательно закрыть соединение
    QFile::remove("employees.db");    // удаление файла
}
