#include "gameUI.hpp"

void UI::draw_mainUI() {
    // Update

    // Draw
    GuiGroupBox((Rectangle) {leftCorner.x, leftCorner.y, width, height}, NULL);
    GuiGroupBox((Rectangle) {rightCorner.x, rightCorner.y, width, height}, NULL);
}


void UI::draw_wave_info(WaveManager* wave) {
    // Update
    static int waveActive = 0;
    static bool firstButtonPress = true;
    string waves = "Wave #1;Wave #2;Wave #3";

    // Draw
    GuiGroupBox((Rectangle){ rightCorner.x, rightCorner.y, width, height / 4 }, NULL);

    if (firstButtonPress) {
        GuiComboBox((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + 0.5 * lineHeight, width / 3, height / 8 }, waves.c_str(), &waveActive);
        if (GuiButton((Rectangle){ rightCorner.x + lineHeight + padding, rightCorner.y + 5 * lineHeight, width / 3.5, height / 16 }, "Next wave") && !wave->active && wave->remainingEnemies.empty()) {
            wave->waveShouldStart = true;
            firstButtonPress = false;
        }
    } else {
        GuiComboBox((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + 0.5 * lineHeight, width / 3, height / 8 }, waves.c_str(), &waveActive);
        if (GuiButton((Rectangle){ rightCorner.x + lineHeight + padding, rightCorner.y + 5 * lineHeight, width / 3.5, height / 16 }, "Next wave") && !wave->active && wave->remainingEnemies.empty()) {
            wave->waveShouldStart = true;
            waveActive++;
        }
    }


}

