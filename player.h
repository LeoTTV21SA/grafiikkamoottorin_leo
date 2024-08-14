#pragma once
#include "gameobject.h"

class Player : public GameObject {
public:
    Player();
    ~Player();
    void input(int x, int y);

private:
   
};
