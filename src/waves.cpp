#include "waves.hpp"

const string WaveManager::WAVE_PATH = "assets/waves";

WaveManager::WaveManager(Map* map){
    this->map = map;
    this->currWave = 1;
    this->spawnInterval = 1;
    this->active = false;
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
    cout << line;



    waveFile.close();
}
