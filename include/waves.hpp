#ifndef WAVES_H
#define WAVES_H

#include "enemies.hpp"
#define MAX_WAVES 15

class GameManager;
class WaveManager {
    private:
    static const string WAVE_PATH;
    Map* map;
    GameManager* game;
    int currWave;
    int maxWave;
    int lastFrameDamage;
    double spawnInterval;
    double nextSpawnTime;

public:
    bool active;
    bool waveShouldStart;
    vector<baseEnemy*> remainingEnemies;
    vector<baseEnemy*> activeEnemies;
    WaveManager(GameManager* game);
    void clear_enemies();
    void add_enemies(char type, int amount);
    void load_enemies(int waveNum);
    void spawn_enemy();
    void start_wave();
    void update();
    void draw_enemies();
};

#endif