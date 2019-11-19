#include <QPushButton>

#include "startwindow.hh"
#include "ui_startwindow.h"

Startwindow::Startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startwindow)
{
    ui->setupUi(this);
    connect(ui->startBtn, &QPushButton::clicked, this, &Startwindow::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &Startwindow::reject);
}

Startwindow::~Startwindow()
{
    delete ui;
}
