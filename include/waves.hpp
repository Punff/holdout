#ifndef WAVES_H
#define WAVES_H

#include "enemies.hpp"

class WaveManager{
    private:
    static const string WAVE_PATH;
    Map* map;
    int currWave;
    vector<baseEnemy*> remainingEnemies;
    float spawnInterval;
    bool active;

    public:
    vector<baseEnemy*> activeEnemies;

    WaveManager(Map* map);
    void clear_enemies();
    void add_enemies(char type, int amount);
    void load_enemies(int waveNum);
    void start_wave();
    void update();
};

#endif