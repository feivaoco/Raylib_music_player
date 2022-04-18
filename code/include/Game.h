#pragma once
#include <string>
#include "raylib.h"
#include "Radio.h"
class Game{
    public:
        Game(int width, int height, std::string title, int fps);
        Game(const Game& other) = delete;
        Game& operator=(const Game& other) = delete;

        ~Game() noexcept;

        bool GameShouldClose() const;
        void Tick();

        void Execute();
    private:
        
        std::string getW_Name();

        void Draw();
        void Update();
        // Radio cancion;
        Radio listSongs;
};