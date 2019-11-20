﻿#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include <QObject>
#include <QMainWindow>
#include <QTextBrowser>
#include <QDebug>
#include <QPushButton>
#include "interfaces/igameeventhandler.h"
#include "tiles/tilebase.h"

class GameEventHandler : public QObject, public Course::iGameEventHandler
{
    Q_OBJECT
public:
    explicit GameEventHandler();

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount) final;
    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);

    void nextTurn();    // called when a turn ends

    unsigned int getTurnNumber();   // returns current turn number

    void resetData();   // resets data
signals:


private:
    unsigned int turnNumber_;
    unsigned int maxTurns_;
};

#endif // GAMEEVENTHANDLER_HH
