// Nate Evans 21144881
#ifndef DM_ENEMY_H
#define DM_ENEMY_H

#include "DM_Entity.h"

enum class DM_Personality
{
    AGGRESSIVE,
    PASSIVE
};


class DM_Enemy : public DM_Entity
{
    //methods:
public:
    DM_Enemy(float x, float y);

    void tick() override;

    static DM_Personality randPersonality();

private:
    void randomMove();

    void mineBelow();

    //instance variables:
public:
    DM_Personality m_personality;
    bool m_isAttacking;
};

#endif // DM_ENEMY_H