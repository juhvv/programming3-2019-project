#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <QDialog>
#include <QDebug>

namespace Ui {
class Startwindow;
}

using playerInfo = std::vector<std::pair<std::string, int>>;

class Startwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Startwindow(QWidget *parent = 0);
    ~Startwindow();

public slots:
    void startBtnPushed();
    void namesChanged();

private:
    Ui::Startwindow *ui;

signals:
    void startGame(playerInfo, unsigned int seed);
    void sendPlayerNames(std::vector<std::string> nameVct);
    void sendSeed(unsigned int seed);
};

#endif // STARTWINDOW_HH
