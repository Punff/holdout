#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "Vec2.hpp"
#include "enemies.hpp"
#define RAIL_SHOT_LIFETIME 0.55

class GameManager;

class baseProjectile {
protected:
    Texture2D texture;
    GameManager* game;
    Vec2 position;
    Vec2 dir;
    float size;
    int damage;
    float speed;
    float lifetime;

public:
    bool shouldDelete;

    baseProjectile(GameManager* game, Vec2 position, Vec2 targetPos, int damage);
    virtual ~baseProjectile();
    virtual void update();
    virtual void draw_projectile() = 0;
};

class basicProjectile : public baseProjectile {
public:
    basicProjectile(GameManager* game, Vec2 position, Vec2 targetPos, int damage);
    void draw_projectile() override;
};

class flameRing : public baseProjectile {
private:
    float rotation;
    bool didDamage;
public:
    flameRing(GameManager* game, Vec2 position, Vec2 targetPos, int damage, float range);
    void update() override;
    void draw_projectile() override;
};

class bomb : public baseProjectile {
public:
    Sound sound;
    bomb(GameManager* game, Vec2 position, Vec2 targetPos, int damage);
    void update() override;
    void draw_projectile() override;
};

class explosion : public baseProjectile {
private:
    float maxLifetime;
    bool didDamage;
public:
    explosion(GameManager* game, Vec2 position, Vec2 targetPos, int damage);
    void update() override;
    void draw_projectile() override;
};

class arrow : public baseProjectile {
private:
    vector<baseEnemy*> hits;
    int pierces;
    bool enemy_was_hit(baseEnemy* enemy);
public:
    arrow(GameManager* game, Vec2 position, Vec2 targetPos, int damage);
    void update() override;
    void draw_projectile() override;
};

class railShot : public baseProjectile {
private:
    Vec2 targetPos;
public:
    railShot(GameManager* game, Vec2 position, Vec2 targetPos, int damage);
    void update() override;
    void draw_projectile() override;
};

#endif
