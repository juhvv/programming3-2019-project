#include <QPushButton>

#include "startwindow.hh"
#include "ui_startwindow.h"

#include <string>
#include <QIcon>
#include <ctime>

Startwindow::Startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startwindow)
{
    ui->setupUi(this);

    QIcon color1icon = QIcon(QPixmap(":/resources/overlay faction1.PNG"));
    QIcon color2icon = QIcon(QPixmap(":/resources/overlay faction2.PNG"));
    // add faction selection in the future
    ui->colorSelBox1->insertItem(0, color1icon, "Faction 1");
    ui->colorSelBox2->insertItem(0, color2icon, "Faction 2");

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
    // if seed is not specified, use seconds form epoch as seed
    unsigned int seed = std::time(0);
    if (!ui->seedLine->text().isEmpty()) {
        seed = std::stoi(ui->seedLine->text().toUtf8().constData());
    }

    std::string player1 = ui->player1Line->text().toUtf8().constData(); //Change qString to std::string
    std::string player2 = ui->player2Line->text().toUtf8().constData();

    playerInfo info = {};
    //info.push_back(std::make_pair(player1, ui->colorSelBox1->currentIndex()));
    //info.push_back(std::make_pair(player2, ui->colorSelBox2->currentIndex()));

    info.push_back(std::make_pair(player1, 0));
    info.push_back(std::make_pair(player2, 1));

    // if either name is empty, assign default name
    for (int i = 0 ; i < info.size() ; ++i) {
        qDebug() << info[i].first.c_str();
        if (info[i].first == "") {
            info[i].first = "Player " + std::to_string(i + 1);
        }
    }

    std::vector<std::string> nameVct;
    nameVct.push_back(player1);
    nameVct.push_back(player2);
    emit startGame(info, seed);
    accept();
}

void Startwindow::namesChanged()
{
    ui->startBtn->setDisabled(ui->player1Line->text() == ui->player2Line->text());
}



