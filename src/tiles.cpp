#include "tiles.hpp"
#include "GameManager.hpp"
// base tile
baseTile::baseTile(int xPos, int yPos, int size, GameManager* game){
    this->game = game;
    hitbox.x = xPos;
    hitbox.y = yPos;
    hitbox.height = hitbox.width = size;
    is_path = false;
    is_occupied = false;
}

baseTile::~baseTile(){}

void baseTile::draw_tile(){
    DrawTexturePro(texture, {0, 0, 16, 16}, hitbox, {0, 0}, 0, WHITE);
}

// wireframe tile
void wireframeTile::draw_tile(){
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

// path tile
pathTile::pathTile(int xPos, int yPos, int size, GameManager* game) : baseTile(xPos, yPos, size, game){
    texture = game->assets->load_texture("text-tile-dirtpath.png");
    is_path = true;
    is_occupied = true;
}

// grass tile
grassTile::grassTile(int xPos, int yPos, int size, GameManager* game) : baseTile(xPos, yPos, size, game){
    texture = game->assets->load_texture("text-tile-grass.png");
}

// water tile
waterTile::waterTile(int xPos, int yPos, int size, GameManager* game) : baseTile(xPos, yPos, size, game){
    texture = game->assets->load_texture("text-tile-water.png");
    is_occupied = true;
}

// rock tile
rockTile::rockTile(int xPos, int yPos, int size, GameManager* game) : baseTile(xPos, yPos, size, game){
    texture = game->assets->load_texture("text-tile-rock-grass.png");
    is_occupied = true;
}
