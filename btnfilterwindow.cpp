#include "btnfilterwindow.h"
#include "ui_btnfilterwindow.h"

BtnFilterWindow::BtnFilterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BtnFilterWindow)
{
    ui->setupUi(this);
}

BtnFilterWindow::~BtnFilterWindow() {
    delete ui;
}

QString BtnFilterWindow::getName(){
    return ui->lneName->text();
}

QString BtnFilterWindow::getDateAt(){
    return ui->lneDateAt->text();
}

QString BtnFilterWindow::getDateTo(){
    return ui->lneDateTo->text();
}

QString BtnFilterWindow::getPosition(){
    return ui->lnePosition->text();
}

QString BtnFilterWindow::getSalaryAt(){
    return ui->lneSalaryAt->text();
}

QString BtnFilterWindow::getSalaryTo(){
    return ui->lneSalaryTo->text();
}
