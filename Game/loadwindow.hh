#ifndef LOADWINDOW_HH
#define LOADWINDOW_HH

#include <QDialog>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class LoadWindow;
}

class LoadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadWindow(QWidget *parent = 0);
    ~LoadWindow();

private:
    Ui::LoadWindow *ui;

public slots:
    void loadGameBtnPushed();
    void browseBtnPushed();

signals:
    void sendLoadFileName(QString fileName);
};

#endif // LOADWINDOW_HH
