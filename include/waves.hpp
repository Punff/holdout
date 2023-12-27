#ifndef WAVES_H
#define WAVES_H

#include "enemies.hpp"

class WaveManager{
    private:
    static const string WAVE_PATH;
    int currWave;
    int maxWave;
    vector<baseEnemy*> remainingEnemies;
    vector<baseEnemy*> activeEnemies;
    bool active;

    public:
    WaveManager();
    void load_enemies(int waveNum);
    void update();
};

#endif