#include "savewindow.hh"
#include "ui_savewindow.h"

SaveWindow::SaveWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveWindow)
{
    ui->setupUi(this);

    connect(ui->saveGameBtn, &QPushButton::clicked, this, &SaveWindow::accept);
    connect(ui->saveGameBtn, &QPushButton::clicked, this, &SaveWindow::saveGameBtnPushed);
    connect(ui->browseBtn, &QPushButton::clicked, this, &SaveWindow::browseBtnPushed);
}

void SaveWindow::saveGameBtnPushed()
{
    qDebug()<<"saveGameBtn pushed,,,!!";
    QString filePathName = ui->pathEdit->text()+"/"+ui->fileNameEdit->text()+".txt";
    emit sendSaveFileName(filePathName);
}

void SaveWindow::browseBtnPushed()
{
    qDebug()<<"jessus!";
    QString path = QFileDialog::getExistingDirectory(this, "Select directory");
    ui->pathEdit->setText(path);
}

SaveWindow::~SaveWindow()
{
    delete ui;
}
