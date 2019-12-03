#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <QDialog>
#include <QDebug>

namespace Ui {
class Startwindow;
}

namespace MapSize {
    /**
     * @brief Type for defining different map sizes
     */
    enum Size {
        SMALL = 10,
        NORMAL = 20,
        LARGE = 30
    };
}
/**
 * @brief Alias for std::vector<std::pair<std::string, int>>
 */
using playerInfo = std::vector<std::pair<std::string, int>>;

/**
 * @brief This window class receives game starting parameters from players
 * \n and sends it to the main game
 */
class Startwindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Startwindow constructor
     * @param parent widget
     */
    explicit Startwindow(QWidget *parent = 0);
    ~Startwindow();

public slots:
    /**
     * @brief This slot processes inserted information and
     * \n sends it to the mapwindow
     */
    void startBtnPushed();

    /**
     * @brief This slot disables start button if players have same names
     */
    void namesChanged();

private:
    Ui::Startwindow *ui;

signals:
    /**
     * @brief Emits game start information
     * @param info vector storing player names and corresponding
     * \n icon indices as pairs
     * @param seed for the world generator
     * @param X and Y size of the map
     */
    void startGame(playerInfo info, unsigned int seed, MapSize::Size size);
};

#endif // STARTWINDOW_HH
