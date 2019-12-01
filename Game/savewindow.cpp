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
   QString filePath = ui->pathEdit->text();
   if(filePath.endsWith(".txt")){
       emit sendSaveFileName(filePath);
   }
   else{
       filePath = filePath+".txt";
       emit sendSaveFileName(filePath);
   }
}

void SaveWindow::browseBtnPushed()
{
    QString filePath = QFileDialog::getSaveFileName(this,
        tr("Save file name"), "",
        tr("Text file (*.txt)"));
    ui->pathEdit->setText(filePath);
}

SaveWindow::~SaveWindow()
{
    delete ui;
}
