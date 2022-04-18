#pragma once
#include "raylib.h"
#include <string>
namespace settings{
    // Window stts
    inline constexpr int screenWidth = 800;
    inline constexpr int screenHeight = 600;
    inline constexpr int fps = 63;


    inline constexpr Color color_background = BLACK;
    inline constexpr Color color_gb0 = CLITERAL(Color){9,9,26,255};
    inline constexpr Color color_gb1 = CLITERAL(Color){68,42,140,255};
    inline constexpr Color color_gb2 = CLITERAL(Color){168,191,76,255};
    inline constexpr Color color_gb3 = CLITERAL(Color){244,245,233,255};

    inline constexpr const char * song_path = "songs/";
    // std::string so_ru(song_route);
}