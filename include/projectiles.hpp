#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "Vec2.hpp"

class GameManager;

class baseProjectile {
protected:
    GameManager* game;
    Vec2 position;
    Vec2 dir;
    float size;
    int damage;
    float speed;
    float lifetime;

public:
    bool shouldDelete;

    baseProjectile(GameManager* game, Vec2 position, Vec2 targetPos);
    virtual ~baseProjectile();
    virtual void update();
    virtual void draw_projectile() = 0;
};

class basicProjectile : public baseProjectile {
private:
    Texture2D texture;
public:
    basicProjectile(GameManager* game, Vec2 position, Vec2 targetPos);
    ~basicProjectile();
    void draw_projectile() override;
};

#endif
