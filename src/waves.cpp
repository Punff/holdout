#include "waves.hpp"
#include "GameManager.hpp"
#include <sstream>
#define BASE_SPAWN_INTERVAL 2

const string WaveManager::WAVE_PATH = "assets/waves";

WaveManager::WaveManager(GameManager* game){
    this->game = game;
    currWave = 1;
    maxWave = MAX_WAVES;
    spawnInterval = BASE_SPAWN_INTERVAL;
    nextSpawnTime = 0;
    active = false;
    waveShouldStart = false;
}

void WaveManager::clear_enemies(){
    for(int i = 0; i < remainingEnemies.size(); i++){
        delete remainingEnemies[i];
    }

    for(int i = 0; i < activeEnemies.size(); i++){
        delete activeEnemies[i];
    }

    remainingEnemies.clear();
    activeEnemies.clear();
}

void WaveManager::add_enemies(char type, int amount){
    for(int i = 0; i < amount; i++){
        switch(type){
            case 'b':
                remainingEnemies.push_back(new basicEnemy(game));
                break;
            case 'e':
                remainingEnemies.push_back(new eliteEnemy(game));
                break;
            case 'v':
                remainingEnemies.push_back(new veteran(game));
                break;
            case 'r':
                remainingEnemies.push_back(new brute(game));
                break;
            case 'd':
                remainingEnemies.push_back(new dasher(game));
                break;
            case 't':
                remainingEnemies.push_back(new tankEnemy(game));
                break;
            case 's':
                remainingEnemies.push_back(new superTank(game));
                break;
            case 'w':
                remainingEnemies.push_back(new delay(game));
                break;
        }
    }
}

void WaveManager::load_enemies(int waveNum){
    clear_enemies();

    ifstream waveFile(WAVE_PATH);
    if(!waveFile){
        cout << "!!! Could not find wave file\n";
        return;
    }

    string line;
    for(int i = 0; i < waveNum; i++){
        getline(waveFile, line);
    }

    stringstream lineStream(line);
    char type;
    int amount;
    while(!lineStream.eof()){
        lineStream >> type;
        lineStream >> amount;
        add_enemies(type, amount);
    }

    waveFile.close();
}

void WaveManager::update(){
    
    if(!active){
        if(currWave > maxWave){
            return;
        }
    }
    else if(activeEnemies.empty() && remainingEnemies.empty()){
        currWave++;
        active = false;
        spawnInterval = Lerp(BASE_SPAWN_INTERVAL, 0.2, (float)currWave / maxWave);
        return;
    }

    nextSpawnTime -= GetFrameTime();
    if(nextSpawnTime <= 0){
        nextSpawnTime = spawnInterval;
        spawn_enemy();
    }

    for(auto el : activeEnemies){
        el->update();
    }

    for(int i = 0; i < activeEnemies.size(); i++){
        if(activeEnemies[i]->hp <= 0){
            game->money += activeEnemies[i]->value;
            activeEnemies.erase(activeEnemies.begin() + i);
        }
        else if(activeEnemies[i]->reachedEnd){
            game->take_damage(activeEnemies[i]->damage);
            activeEnemies.erase(activeEnemies.begin() + i);
        }
    }
}

bool WaveManager::start_wave(){
    if(active || currWave > maxWave){
        return false;
    }
    else{
        load_enemies(currWave);
        active = true;
        return true;
    }
}

void WaveManager::draw_enemies(){
    for(auto el : activeEnemies){
        el->draw_enemy();
    }
}

void WaveManager::spawn_enemy(){
    if(remainingEnemies.empty()){
        return;
    }
    if(remainingEnemies[0]->isDelay){
        remainingEnemies.erase(remainingEnemies.begin());
        return;
    }
    activeEnemies.push_back(remainingEnemies[0]);
    remainingEnemies.erase(remainingEnemies.begin());
}
