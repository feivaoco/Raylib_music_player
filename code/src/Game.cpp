#include "assert.h"
#include "Game.h"
#include "raylib.h"
// #include <iostream>
#include "Settings.h"
// #include <vector>
#include <string>
#include <stdlib.h>

Game::Game(int width, int height, std::string title, int fps)
    :
    listSongs()
    {
        assert(!GetWindowHandle());
        SetTargetFPS(fps);
        InitWindow(width, height, title.c_str());
        listSongs.SetHasInput(true);
        
}

Game::~Game() noexcept{
    assert(GetWindowHandle());
    CloseWindow();
}

bool Game::GameShouldClose() const{
    return WindowShouldClose();
}

void Game::Execute(){
    while (!GameShouldClose()){
        Tick();
    }
}

void Game::Tick(){
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void Game::Update(){
        
    // if(IsKeyPressed(KEY_RIGHT))
    //     listSongs.Foward();
    listSongs.Update();
    // std::cout << listSongs.GetSongs().front().stream.sampleRate << std::endl;
}

void Game::Draw(){
    ClearBackground(settings::color_gb1);
    listSongs.Draw();
    DrawFPS(0,0);

    // DrawRectangle(200, 200, 400, 12, LIGHTGRAY);
    // DrawRectangle(200, 200, (int)(listSongs.GetTimePlayed()/listSongs.GetTimeLength()*400), 12, RED);
    // DrawText(listSongs.GetNameSong().c_str(),215, 250, 20, RED);

    // if (listSongs.GetIsLoopingList())
    //     DrawRectangle(450,400,100,100,RED);
    // else
    //     DrawRectangle(450,400,100,100,BLUE);
    // if (listSongs.GetIsLoopingSong())
    //     DrawRectangle(250,400,100,100,GREEN);
    // else
    //     DrawRectangle(250,400,100,100,WHITE);

}


