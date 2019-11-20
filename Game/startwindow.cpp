#include <QPushButton>

#include "startwindow.hh"
#include "ui_startwindow.h"

#include <string>

Startwindow::Startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startwindow)
{
    ui->setupUi(this);
    connect(ui->startBtn, &QPushButton::clicked, this, &Startwindow::accept);
    connect(ui->startBtn, &QPushButton::clicked, this, &Startwindow::startBtnPushed);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &Startwindow::reject);

}



Startwindow::~Startwindow()
{
    delete ui;
}

void Startwindow::startBtnPushed(){
    std::string seed = ui->seedLine->text().toUtf8().constData();

    std::string player1 = ui->player1Line->text().toUtf8().constData(); //Change qString to std::string
    std::string player2 = ui->player2Line->text().toUtf8().constData();

    std::vector<std::string> nameVct;
    nameVct.push_back(player1);
    nameVct.push_back(player2);
    emit sendPlayerNames(nameVct);    //Emit vector of player names to mapwindow
    emit sendSeed(stoi(seed));

}

