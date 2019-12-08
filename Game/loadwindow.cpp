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
    emit sendLoadFileName(ui->pathEdit->text());
}

void LoadWindow::browseBtnPushed()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select save file"),"" ,tr("Text Files (*.txt)"));
    ui->pathEdit->setText(path);
}
