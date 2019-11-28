#include "savewindow.hh"
#include "ui_savewindow.h"

SaveWindow::SaveWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveWindow)
{
    ui->setupUi(this);

    connect(ui->saveGameBtn, &QPushButton::clicked, this, &SaveWindow::accept);
    connect(ui->saveGameBtn, &QPushButton::clicked, this, &SaveWindow::saveGameBtnPushed);
}

void SaveWindow::saveGameBtnPushed()
{
    qDebug()<<"saveGameBtn pushed,,,!!";
    QString fileName = ui->fileNameEdit->text();
    emit sendSaveFileName(fileName);
}

SaveWindow::~SaveWindow()
{
    delete ui;
}
