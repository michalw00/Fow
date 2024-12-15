#include "core.h"

namespace fow {
    Core& Core::Get() {
        static Core instance;
        return instance;
    }

    void Core::Start() {
        // Initialization 

        // Main cycle
        Loop();

    }

    Core::Core() {
        InitWindow();
        current_screen_ = ScreenType::kMenu;
    }

    void Core::InitWindow() {
        window_.Init(1280, 720, "Fow");
        window_.SetFullscreen(0);
        window_.SetExitKey(KEY_NULL);
        window_.SetTargetFPS(60);
    }

    void Core::Loop() {
        while (!window_.ShouldClose()) {
            window_.BeginDrawing();
            ClearBackground(RAYWHITE);

            window_.EndDrawing();
        }

        window_.Close();
    }
}