#ifndef LOADWINDOW_HH
#define LOADWINDOW_HH

#include <QDialog>
#include <QDebug>
#include <QFileDialog>


namespace Ui {
class LoadWindow;
}
/**
 * @brief This window class receives game loading parameters
 * \n and sends them to LoadGame
 */
class LoadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadWindow(QWidget *parent = 0);
    ~LoadWindow();

private:
    Ui::LoadWindow *ui;

public slots:
    /**
     * @brief Player pushed load game button in this window. Gather
     * \n game load file directory and emit sendFileName
     */
    void loadGameBtnPushed();
    /**
     * @brief Opens browse window that allows player to select file and
     * \n directory
     */
    void browseBtnPushed();

signals:
    /**
     * @brief Signal that is sent to LoadGame
     */
    void sendLoadFileName(QString fileName);
};

#endif // LOADWINDOW_HH
