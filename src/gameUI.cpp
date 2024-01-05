#include "gameUI.hpp"

UI::UI(GameManager* game) {
    this->game = game;
    this->map = game->map;
    this->tileSize = map->get_tile_size();
    this->mapTiles = map->mapTiles;
    this->height = tileSize * mapTiles;
    this->width = GetScreenWidth() / 4;
    this->leftCorner = {map->get_tile_xPos(0) - width, map->get_tile_yPos(0)};
    this->rightCorner = {map->get_tile_xPos(map->mapTiles), map->get_tile_yPos(0)};
    this->padding = 15.0f;
    this->lineHeight = 30.0f;
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 5);
}

void UI::draw_mainUI() {
    // Update

    // Draw
    GuiGroupBox((Rectangle) {leftCorner.x, leftCorner.y, width, height}, NULL);
    GuiGroupBox((Rectangle) {rightCorner.x, rightCorner.y, width, height}, NULL);
}

void UI::draw_HP() {
    // Update
    float HPvalue = game->playerHP;

    // Draw
    GuiSliderBar((Rectangle){ leftCorner.x + width / 4, leftCorner.y + lineHeight, width / 2, height / 10 }, NULL, NULL, &HPvalue, 0, 100);
}

void UI::draw_wave_info(WaveManager* wave) {
    // Update
    static int waveActive = 0;

    // Draw
    GuiGroupBox((Rectangle){ leftCorner.x, leftCorner.y + height / 4, width, height / 4 }, NULL);

    GuiValueBox((Rectangle){ leftCorner.x + width / 3, leftCorner.y + height / 4 + lineHeight, width / 3, height / 10 }, NULL, &waveActive, 0, 50, false);

    if (GuiButton((Rectangle){ leftCorner.x + width / 4, leftCorner.y + height / 4 + 5 * lineHeight, width / 2, height / 16 }, "Next wave") && !wave->active && wave->remainingEnemies.empty()) {
        wave->waveShouldStart = true;
        waveActive++;
    }
}

void UI::draw_money() {
    // Update
    int moneyValue = game->money;

    // Draw
    GuiGroupBox((Rectangle){ rightCorner.x, rightCorner.y, width, height / 4 }, NULL);

    GuiValueBox((Rectangle){ rightCorner.x + width / 4, rightCorner.y + lineHeight, width / 2, height / 10 }, NULL, &moneyValue, 0, 50, false);
}

void UI::draw_shop() {
    // Update
    int basicTowerPrice = 7;

    // Draw
    GuiGroupBox((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + lineHeight + height / 4, width / 4, width / 4}, NULL);
    if (GuiButton((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + width / 4 + lineHeight + height / 4, width / 4, width / 4 / 4}, "Buy") && game->money >= basicTowerPrice) {
        game->isPlacingTower = true;
        game->money -= basicTowerPrice;
    }

    GuiGroupBox((Rectangle){ rightCorner.x + width / 4 + 2 * lineHeight, rightCorner.y + lineHeight + height / 4, width / 4, width / 4}, NULL);
    if (GuiButton((Rectangle){ rightCorner.x + width / 4 + 2 * lineHeight, rightCorner.y + width / 4 + lineHeight + height / 4, width / 4, width / 4 / 4}, "Buy")) {

    }

    GuiGroupBox((Rectangle){ rightCorner.x + 2 * width / 4 + 3 * lineHeight, rightCorner.y + lineHeight + height / 4, width / 4, width / 4}, NULL);
    if (GuiButton((Rectangle){ rightCorner.x + 2 * width / 4 + 3 * lineHeight, rightCorner.y + width / 4 + lineHeight + height / 4, width / 4, width / 4 / 4}, "Buy")) {

    }
}
