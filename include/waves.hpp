#ifndef WAVES_H
#define WAVES_H

#include "enemies.hpp"
#define MAX_WAVES 12
#define BASE_SPAWN_INTERVAL 1
#define BASE_BONUS 55
#define WAVE_BONUS 5 // scales per wave

class GameManager;
class WaveManager {
    private:
    static const string WAVE_PATH;
    GameManager* game;
    int lastFrameDamage;
    double spawnInterval;
    double nextSpawnTime;

public:
    int currWave;
    int maxWave;
    bool active;
    bool waveShouldStart;
    vector<baseEnemy*> remainingEnemies;
    vector<baseEnemy*> activeEnemies;
    WaveManager(GameManager* game);
    void clear_enemies();
    void add_enemies(char type, int amount);
    void load_enemies(int waveNum);
    void spawn_enemy();
    bool start_wave();
    void update();
    void draw_enemies();
};

#endif