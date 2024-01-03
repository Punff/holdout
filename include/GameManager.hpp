#include "map.hpp"
#include "waves.hpp"

class GameManager {
    private:
    int screenWidth;
    int screenHeight;

    int playerHP;
    int money;
    
    Map* map;
    WaveManager* waveManager;

    public:
    GameManager();
    ~GameManager();
    void load_map(string mapName);
    void gameloop();
};