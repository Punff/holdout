#include "gameUI.hpp"

void UI::draw_mainUI() {
    // Update

    // Draw
    GuiGroupBox((Rectangle) {leftCorner.x, leftCorner.y, width, height}, NULL);
    GuiGroupBox((Rectangle) {rightCorner.x, rightCorner.y, width, height}, NULL);
}

void UI::draw_HP() {
    // Update
    float HPvalue = 69.0f;

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
    int moneyValue = 150;

    // Draw
    GuiGroupBox((Rectangle){ rightCorner.x, rightCorner.y, width, height / 4 }, NULL);

    GuiValueBox((Rectangle){ rightCorner.x + width / 4, rightCorner.y + lineHeight, width / 2, height / 10 }, NULL, &moneyValue, 0, 50, false);
}

void UI::draw_shop() {
    GuiGroupBox((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + lineHeight + height / 4, tileSize, tileSize}, NULL);
    GuiButton((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + tileSize + lineHeight + height / 4, tileSize, tileSize / 4}, "Buy");

    GuiGroupBox((Rectangle){ rightCorner.x + tileSize + 2 * lineHeight, rightCorner.y + lineHeight + height / 4, tileSize, tileSize}, NULL);
    GuiButton((Rectangle){ rightCorner.x + tileSize + 2 * lineHeight, rightCorner.y + tileSize + lineHeight + height / 4, tileSize, tileSize / 4}, "Buy");

    GuiGroupBox((Rectangle){ rightCorner.x + 2 * tileSize + 3 * lineHeight, rightCorner.y + lineHeight + height / 4, tileSize, tileSize}, NULL);
    GuiButton((Rectangle){ rightCorner.x + 2 * tileSize + 3 * lineHeight, rightCorner.y + tileSize + lineHeight + height / 4, tileSize, tileSize / 4}, "Buy");
}
