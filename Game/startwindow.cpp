#include "startwindow.hh"
#include "ui_startwindow.h"

Startwindow::Startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startwindow)
{
    ui->setupUi(this);
}

Startwindow::~Startwindow()
{
    delete ui;
}
