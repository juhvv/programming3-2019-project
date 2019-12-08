#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H

#include <QObject>
#include <QMenu>

class CustomGraphicsScene;

class CustomGraphicsItem;

static const unsigned int TILE_SIZE = 128;  // defines tile size (px)


namespace objectTags {
    /**
     * @brief The Tag enum type specifies tags that GameObjectBase
     * objects can have
     */
    enum Tag {NO_BUILD, HAS_TREES, HAS_ROCK, IS_FLAT};
}

/**
 * @brief The GameObjectBase class is base class for all gameobjects used in the game
 * \n and provides interface for CustomGraphicsItem to interact with GameObjects
 */
class GameObjectBase : public QObject

{
    Q_OBJECT
public:
    GameObjectBase() = delete;

    /**
     * @brief Constructor
     * @param scene This object's customGraphicsScene
     */
    GameObjectBase(CustomGraphicsScene* scene);

    /**
      * @brief Destructor. If graphics item is set, it is deleted.
      */
    ~GameObjectBase();

    /**
     * @brief Adds object's menu actions to paremeter 'menu'
     * @param menu QMenu in which the actions are inserted
     */
    virtual void getMenuItems(QMenu &menu) = 0;

    /**
     * @brief Inquires the object's movability
     * @return True if object can move, else false
     */
    virtual bool isMovable() const;

    /**
     * @brief Inquires the object's selectability
     * @return True if object can be selected, else false
     */
    virtual bool isSelectable() const;

    /**
     * @brief Sets object's graphics item. This funcion must be called on
     * \n the object before any other function. This method should be re-implemented
     * \n by derived classes.
     * @param graphicsItem Object's graphics item
     * @param scene Scene for graphics item
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) = 0;

    /**
     * @brief Inserts this object's description to the parameter
     * @param desc Reference to description string
     */
    virtual void getDescriptionBrief(std::string &desc);

    /**
     * @brief getGraphicsItem
     * @return Pointer to this object's graphics item
     */
    CustomGraphicsItem *getGraphicsItem() const;

    /**
     * @brief Check if this object has specific tag
     * @param tag Tag to be searched
     * @return True if object has the tag, else false
     */
    virtual bool hasTag(objectTags::Tag tag);

public slots:
    /**
     * @brief Slot for sendInfo functionality
     */
    virtual void sendInfo();

protected:
    bool isMovable_;
    bool isSelectable_;

    CustomGraphicsItem *graphicsItem_;
    CustomGraphicsScene *scene_;

    std::vector<objectTags::Tag> tags_ = {};

};

#endif // GAMEOBJECTBASE_H
