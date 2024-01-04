#ifndef WAVES_H
#define WAVES_H

#include "enemies.hpp"
#define MAX_WAVES 3

class WaveManager{
    private:
    static const string WAVE_PATH;
    Map* map;
    int currWave;
    int maxWave;
    double spawnInterval;
    double nextSpawnTime;
    bool active;
    Rectangle button; // temporary

    public:
    vector<baseEnemy*> remainingEnemies;
    vector<baseEnemy*> activeEnemies;
    WaveManager(Map* map);
    void clear_enemies();
    void add_enemies(char type, int amount);
    void load_enemies(int waveNum);
    void spawn_enemy();
    void start_wave();
    void update();
    void draw_enemies();
    void draw_ui(); // temporary, for testing
};

#endif