#ifndef WAVES_H
#define WAVES_H

#include "enemies.hpp"

class WaveManager{
    private:
    static const string WAVE_PATH;
    Map* map;
    int currWave;
    vector<baseEnemy*> remainingEnemies;
    vector<baseEnemy*> activeEnemies;
    double spawnInterval;
    double nextSpawnTime;
    bool active;

    public:
    WaveManager(Map* map);
    void clear_enemies();
    void add_enemies(char type, int amount);
    void load_enemies(int waveNum);
    void spawn_enemy();
    void update();
    void draw_enemies();
};

#endif