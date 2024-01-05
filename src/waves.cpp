#include "waves.hpp"
#include <sstream>

const string WaveManager::WAVE_PATH = "assets/waves";

WaveManager::WaveManager(Map* map){
    this->map = map;
    this->currWave = 1;
    this->maxWave = MAX_WAVES;
    this->spawnInterval = 1;
    this->nextSpawnTime = 0;
    this->active = false;
    this->waveShouldStart = false;
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
                remainingEnemies.push_back(new basicEnemy(map));
                break;
            case 'e':
                remainingEnemies.push_back(new eliteEnemy(map));
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
        if(waveShouldStart) {
            start_wave();
            this->waveShouldStart = false;

        }
    }
    else if(activeEnemies.empty() && remainingEnemies.empty()){
        currWave++;
        active = false;
        return;
    }

    nextSpawnTime -= GetFrameTime();
    if(nextSpawnTime <= 0){
        spawn_enemy();
        nextSpawnTime = spawnInterval;
    }

    for(auto el : activeEnemies){
        el->update();
    }

    for(int i = 0; i < activeEnemies.size(); i++){
        if(activeEnemies[i]->hp <= 0 || activeEnemies[i]->reachedEnd){
            activeEnemies.erase(activeEnemies.begin() + i);
        }
    }
}

void WaveManager::start_wave(){
    load_enemies(currWave);
    active = true;
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

    activeEnemies.push_back(remainingEnemies[0]);
    remainingEnemies.erase(remainingEnemies.begin());

}