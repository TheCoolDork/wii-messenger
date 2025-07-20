#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <string>
#include "keyboard.h"

const char* keyLayout[5][10] = {
    { "1","2","3","4","5","6","7","8","9","0" },
    { "Q","W","E","R","T","Y","U","I","O","P" },
    { "A","S","D","F","G","H","J","K","L","⌫" },
    { "Z","X","C","V","B","N","M"," "," "," " },
    { "OK", "", "", "", "", "", "", "", "", "" }

};

int cursorRow = 0;
int cursorCol = 0;
std::string typedText;

void DrawKeyboard() {
    int startX = 80;
    int startY = 260;
    int keyW = 48;
    int keyH = 40;
    int spacing = 10;

    for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 10; c++) {
            int x = startX + c * (keyW + spacing);
            int y = startY + r * (keyH + spacing);
            u32 color = (r == cursorRow && c == cursorCol) ? RGBA(255, 255, 0, 255) : RGBA(200, 200, 200, 255);

            if (keyLayout[r][c][0] != '\0') {
                GRRLIB_Rectangle(x, y, keyW, keyH, color, true);
                GRRLIB_Printf(x + 12, y + 10, nullptr, 24, RGBA(0, 0, 0, 255), "%s", keyLayout[r][c]);
            }
        }
    }

    // Show preview
    GRRLIB_Printf(80, 250, nullptr, 28, RGBA(255,255,255,255), "Typed: %s", typedText.c_str());
}

void UpdateKeyboard() {
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);

    if (pressed & WPAD_BUTTON_LEFT) cursorCol = (cursorCol + 9) % 10;
    if (pressed & WPAD_BUTTON_RIGHT) cursorCol = (cursorCol + 1) % 10;
    if (pressed & WPAD_BUTTON_UP) cursorRow = (cursorRow + 3) % 4;
    if (pressed & WPAD_BUTTON_DOWN) cursorRow = (cursorRow + 1) % 4;

    if (pressed & WPAD_BUTTON_A) {
        const char* key = keyLayout[cursorRow][cursorCol];
        if (strcmp(key, "⌫") == 0 && !typedText.empty()) {
            typedText.pop_back();
        } else if (strcmp(key, "OK") == 0) {
            // You can finalize input here or signal a state change
        } else if (strlen(key) == 1 || strcmp(key, " ") == 0) {
            typedText += key;
        }
    }
}

const char* GetTypedText() {
    return typedText.c_str();
}

void ResetKeyboard() {
    typedText.clear();
    cursorRow = 0;
    cursorCol = 0;
}