#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <stdlib.h>
#include <string.h>

void DrawWiiStyleButton(int x, int y, int w, int h, bool hovered, const char* label, GRRLIB_ttfFont* font) {
    u32 fillColor = hovered ? RGBA(255, 255, 255, 255) : RGBA(240, 240, 240, 255);
    GRRLIB_Rectangle(x, y, w, h, fillColor, true);

    if (hovered) {
        GRRLIB_Rectangle(x - 2, y - 2, w + 4, h + 4, RGBA(180, 210, 255, 160), false);
    }

    GRRLIB_Rectangle(x, y, w, h, RGBA(200, 200, 200, 255), false);

    int textWidth = strlen(label) * 12;
    GRRLIB_PrintfTTF(x + w/2 - textWidth/2, y + h/2 - 12, font, RGBA(0, 0, 0, 255), label);
}

int main() {
    WPAD_Init();
    GRRLIB_Init();
    GRRLIB_InitTTF();

    GRRLIB_ttfFont *fontRodin = GRRLIB_LoadTTF("fonts/FOT-RodinPro-B_0.ttf", 24);

    while (1) {
        WPAD_ScanPads();
        u32 buttons = WPAD_ButtonsDown(0);
        ir_t ir = WPAD_Data(0)->ir;

        // Quit if HOME is pressed
        if (buttons & WPAD_BUTTON_HOME) break;

        // Background
        GRRLIB_FillScreen(RGBA(50, 50, 100, 255)); // Dark blue

        // Fancy UI element
        GRRLIB_Rectangle(100, 100, 200, 100, RGBA(255, 255, 255, 255), true);

        // Handle keyboard
        UpdateKeyboard();
        DrawKeyboard();

        // Hoverable button example
        bool hoverCompose = ir.valid && ir.x > 220 && ir.x < 420 && ir.y > 120 && ir.y < 168;
        DrawWiiStyleButton(220, 120, 200, 48, hoverCompose, "Compose", fontRodin);

        GRRLIB_Render();
        // Inside your main loop:
ir_t ir = WPAD_Data(0)->ir;
bool hoverWiiMenu = ir.valid && ir.x > 20 && ir.x < 170 && ir.y > 400 && ir.y < 440;
bool hoverHBC     = ir.valid && ir.x > 470 && ir.x < 620 && ir.y > 400 && ir.y < 440;

DrawWiiStyleButton(20, 400, 150, 40, hoverWiiMenu, "Wii", fontRodin);
DrawWiiStyleButton(470, 400, 150, 40, hoverHBC, "HBC", fontRodin);

if ((hoverWiiMenu || hoverHBC) && (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)) {
    // Do something: maybe set app state or exit
}
    }

    GRRLIB_FreeTTF(fontRodin);
    GRRLIB_Exit();
    return 0;
}

        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
    }

    GRRLIB_Exit();  // Cleanup when exiting
    return 0;
}

    // Main loop
    while(1) {
        WPAD_ScanPads(); // Update input

        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
            break;

        GRRLIB_FillScreen(RGBA(255, 255, 255, 255)); // Dark blue background

        // Draw a white rectangle
        GRRLIB_Rectangle(100, 100, 200, 100, RGBA(255, 255, 255, 255), true);

        // You’ll eventually add spoofed message text here 👀

        GRRLIB_Render();  // Show graphics
    }

    GRRLIB_Exit();       // Clean up
    exit(0);
}