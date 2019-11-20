#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <QDialog>
#include <QDebug>

namespace Ui {
class Startwindow;
}

class Startwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Startwindow(QWidget *parent = 0);
    ~Startwindow();

public slots:
    void startBtnPushed();

private:
    Ui::Startwindow *ui;

signals:
    void sendPlayerNames(std::vector<std::string>);
    void sendSeed(unsigned int seed);
};

#endif // STARTWINDOW_HH
