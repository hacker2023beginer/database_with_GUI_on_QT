#include "btndeletewindow.h"
#include "ui_btndeletewindow.h"

BtnDeleteWindow::BtnDeleteWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::btndeletewindow)
{
    ui->setupUi(this);
}

BtnDeleteWindow::~BtnDeleteWindow(){
    delete ui;
}

QString BtnDeleteWindow::getEmployeeId(){
    return ui->LneDeleteId->text();
}
