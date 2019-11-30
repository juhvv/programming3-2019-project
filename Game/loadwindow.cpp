#include "loadwindow.hh"
#include "ui_loadwindow.h"

LoadWindow::LoadWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);

    connect(ui->loadGameBtn, &QPushButton::clicked, this, &LoadWindow::accept);
    connect(ui->loadGameBtn, &QPushButton::clicked, this, &LoadWindow::loadGameBtnPushed);
    connect(ui->browseBtn, &QPushButton::clicked, this, &LoadWindow::browseBtnPushed);

}

LoadWindow::~LoadWindow()
{
    delete ui;
}

void LoadWindow::loadGameBtnPushed()
{
    qDebug()<<"loadGameBtn pushed,,,!!";
    QString filePathName = ui->pathEdit->text()+"/"+ui->fileNameEdit->text()+".txt";
    emit sendLoadFileName(filePathName);
}

void LoadWindow::browseBtnPushed()
{
    qDebug()<<"jessus!";
    QString path = QFileDialog::getExistingDirectory(this, "Select directory");
    ui->pathEdit->setText(path);
}
