// btneditwindow.cpp
#include "btneditwindow.h"
#include "ui_btneditwindow.h"

#include <QToolTip>

BtnEditWindow::BtnEditWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BtnEditWindow)
{
    ui->setupUi(this);
}

BtnEditWindow::~BtnEditWindow() {
    delete ui;
}

QString BtnEditWindow::getEmployeeId() {
    return ui->LneEmployeeId->text();
}

QString BtnEditWindow::getNewName() {
    return ui->LneNewName->text();
}

QString BtnEditWindow::getNewPosition()  {
    return ui->LneNewPosition->text();
}

QString BtnEditWindow::getNewSalary()  {
    return ui->LneNewSalary->text();
}

QString BtnEditWindow::getNewDate()  {
    return ui->LneNewDate->text();
}
