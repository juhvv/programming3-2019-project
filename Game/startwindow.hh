#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <QDialog>

namespace Ui {
class Startwindow;
}

class Startwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Startwindow(QWidget *parent = 0);
    ~Startwindow();

private:
    Ui::Startwindow *ui;
};

#endif // STARTWINDOW_HH
