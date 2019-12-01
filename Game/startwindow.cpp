#include <QPushButton>

#include "startwindow.hh"
#include "ui_startwindow.h"

#include <string>
#include <QIcon>

Startwindow::Startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startwindow)
{
    ui->setupUi(this);

    QIcon color1icon = QIcon(QPixmap(":/resources/overlay faction1.PNG"));
    QIcon color2icon = QIcon(QPixmap(":/resources/overlay faction2.PNG"));
    ui->colorSelBox1->insertItem(0, color1icon, "Faction 1");
    ui->colorSelBox1->insertItem(1, color2icon, "Faction 2");

    ui->colorSelBox2->insertItem(0, color1icon, "Faction 1");
    ui->colorSelBox2->insertItem(1, color2icon, "Faction 2");
    ui->colorSelBox2->setCurrentIndex(1);

    connect(ui->startBtn, &QPushButton::clicked, this, &Startwindow::startBtnPushed);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &Startwindow::reject);

    connect(ui->player1Line, &QLineEdit::textEdited, this, &Startwindow::namesChanged);
    connect(ui->player2Line, &QLineEdit::textEdited, this, &Startwindow::namesChanged);


}



Startwindow::~Startwindow()
{
    delete ui;
}

void Startwindow::startBtnPushed(){
    std::string seed = ui->seedLine->text().toUtf8().constData();

    std::string player1 = ui->player1Line->text().toUtf8().constData(); //Change qString to std::string
    std::string player2 = ui->player2Line->text().toUtf8().constData();

    playerInfo info = {};
    info.push_back(std::make_pair(player1, ui->colorSelBox1->currentIndex()));
    info.push_back(std::make_pair(player2, ui->colorSelBox2->currentIndex()));

    std::vector<std::string> nameVct;
    nameVct.push_back(player1);
    nameVct.push_back(player2);
    emit startGame(info, stoi(seed));
    emit sendSeed(stoi(seed));
    emit sendPlayerNames(nameVct);    //Emit vector of player names to mapwindow
    accept();
}

void Startwindow::namesChanged()
{
    ui->startBtn->setDisabled(ui->player1Line->text() == ui->player2Line->text());
}



