#ifndef SAVEWINDOW_HH
#define SAVEWINDOW_HH

#include <QDialog>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class SaveWindow;
}

class SaveWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SaveWindow(QWidget *parent = 0);
    ~SaveWindow();

private:
    Ui::SaveWindow *ui;

public slots:
    void saveGameBtnPushed();
    void browseBtnPushed();

signals:
    void sendSaveFileName(QString fileName);

};

#endif // SAVEWINDOW_HH
