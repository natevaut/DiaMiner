// Nate Evans 21144882
#ifndef DM_ENTITY_H
#define DM_ENTITY_H

class DM_Entity
{
    //methods
public:
    DM_Entity(int x, int y, int health, int money)
        : xTile(x), yTile(y), health(health), money(money)
    {
    }

    virtual ~DM_Entity()
    {
    }
    
    virtual void tick() = 0;

    // instance variables
public:
    int health;
    int money;

protected:
    int xTile;
    int yTile;
};

#endif // DM_ENTITY_H