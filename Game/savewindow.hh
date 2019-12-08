#ifndef SAVEWINDOW_HH
#define SAVEWINDOW_HH

#include <QDialog>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class SaveWindow;
}

/**
 * @brief This window class receives game saving parameters
 * \n and sends them to the SaveGame
 */
class SaveWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SaveWindow(QWidget *parent = 0);
    ~SaveWindow();

private:
    Ui::SaveWindow *ui;

public slots:
    /**
     * @brief Player pushed save game button in this window. Gather
     * \n game save file directory and send it to SaveGame
     */
    void saveGameBtnPushed();
    /**
     * @brief Opens browse window that allows player to select file and
     * \n directory
     */
    void browseBtnPushed();

signals:
    /**
     * @brief Signal that is sent to SaveGame
     */
    void sendSaveFileName(QString fileName);

};

#endif // SAVEWINDOW_HH
