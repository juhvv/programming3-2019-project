#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H

#include <QObject>
#include <QMenu>

class CustomGraphicsScene;

class CustomGraphicsItem;

static const unsigned int TILE_SIZE = 128;  // defines tile size (px)

namespace objectTags {
    enum Tag {NO_BUILD, HAS_TREES, HAS_ROCK, IS_FLAT};
}


class GameObjectBase : public QObject

{
    Q_OBJECT
public:
    GameObjectBase() = delete;

    GameObjectBase(CustomGraphicsScene* scene);

    ~GameObjectBase();

    virtual void getMenuItems(QMenu &menu) = 0;

    virtual bool isMovable() const;

    virtual bool isSelectable() const;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene);

    virtual void getDescriptionBrief(std::string &desc);

    CustomGraphicsItem *getGraphicsItem() const;

    virtual bool hasTag(objectTags::Tag tag);

public slots:
    virtual void sendInfo();

protected:
    bool isMovable_;
    bool isSelectable_;

    CustomGraphicsItem *graphicsItem_;
    CustomGraphicsScene *scene_;

    std::vector<objectTags::Tag> tags_ = {};

};

#endif // GAMEOBJECTBASE_H
