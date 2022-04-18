#include "Radio.h"
#include "Settings.h"
#include <filesystem>
#include <functional>
#include <string>
#include "raylibCpp.h"
// #include "raylib.h"
#include <cstring>
#include "Vec2.h"
// #include <iomanip>
namespace fs = std::filesystem;

void Radio::Load(){
    std::string path = settings::song_path;
    for (const auto & entry : fs::directory_iterator(path)){
        std::string nameSong = entry.path().filename().u8string(); 
        // std::wstring s = entry.path();                                        //
        // for (wchar_t c : s)                                                   // Intento de leer el archivo en japones
        //     std::cout << "Char code = 0x" << std::hex << int(c) << std::endl; //
        std::string route = path + nameSong;
        songs.push_back(LoadMusicStream(route.c_str()));
        
        std::string extension = entry.path().extension().u8string(); //
        std::string::size_type i = nameSong.find(extension);         // esto es pa quitarle la extension al nombre
        if (i != std::string::npos)                                  // por ejemplo
            nameSong.erase(i, route.length());                       // Nightcore.ogg ahora va ser Nightcore
        
        namesSongs.push_back(nameSong);                              // Aniade el nombre al vector de nombres
        // std::cout << entry << std::endl;
    }


}

Radio::Radio()
    :
    buttons({raycpp::Button(Vec2<int> (90,500),Vec2<int> (70,70), settings::color_gb3, settings::color_gb0),
             raycpp::Button(Vec2<int> (230,500),Vec2<int> (70,70), settings::color_gb3, settings::color_gb0),
             raycpp::Button(Vec2<int> (370,500),Vec2<int> (70,70), settings::color_gb3, settings::color_gb0),
             raycpp::Button(Vec2<int> (510,500),Vec2<int> (70,70), settings::color_gb3, settings::color_gb0),
             raycpp::Button(Vec2<int> (650,500),Vec2<int> (70,70), settings::color_gb3, settings::color_gb0)})
    {
    if (!IsAudioDeviceReady())
        InitAudioDevice();
    Load();
    Stop();
    // RecPlay.SetAction([this](){this -> Play();});
    SetActionButtons();
    
}


// Radio::Radio(std::string route){
//     if (!IsAudioDeviceReady())
//         InitAudioDevice();
//     m = LoadMusicStream(route.c_str());
// }
// Radio::Radio(std::vector<std::string> routes){
//     if (!IsAudioDeviceReady())
//         InitAudioDevice();
//     for (auto route : routes)
//         songs.push_back(LoadMusicStream(route.c_str()));
//     Stop();
// }

// Radio::Radio(std::vector<std::string> routes,std::vector<std::string> names){
//     if (!IsAudioDeviceReady())
//         InitAudioDevice();
    
//     for (auto route : routes)
//         songs.push_back(LoadMusicStream(route.c_str()));
//     for (auto name : names)
//         namesSongs.push_back(name);
//     Stop();
// }

Radio::~Radio(){
    for (auto song : songs)
        UnloadMusicStream(song);
    CloseAudioDevice();
}

void Radio::Reload(){
    if(IsMusicStreamPlaying(songs[index]))
        Stop();
    Load();
}

void Radio::Play(){
    PlayMusicStream(songs[index]);
}

void Radio::Update(){
    UpdateMusicStream(songs[index]);
    Loop();
    if(hasInput)
        Input();
}

void Radio::Loop(){
    if (!isLoopingSong){
        bool turnoff {0};
        if (!isLoopingList){
            if (index == (int)songs.size()-1)
                turnoff = 1;
        }
        if (GetTimePlayed() <= 0){
                Skip();
            if (turnoff)
                Stop();
        }
        
    }
}

void Radio::Pause(){
    // StopMusicStream(songs[index]);
    PauseMusicStream(songs[index]);
}
void Radio::Stop(){
    StopMusicStream(songs[index]);
    // PauseMusicStream(songs[index]);
}

void Radio::Skip(){
    if(!IsMusicStreamPlaying(songs[index]))
        Play();
    Stop();
    int maxIndex = songs.size();
    index++;
    if(index >= maxIndex)
        index = 0;
    Play();
}

void Radio::Previous(){
    if(!IsMusicStreamPlaying(songs[index]))
        Play();
    Stop();
    int maxIndex = songs.size();
    index--;
    if(index < 0)
        index = maxIndex - 1;
    Play();
}

std::string Radio::GetNameSong(){
    if (namesSongs[index] != "") 
        return namesSongs[index]; 
    return "Without-name";
}


void Radio::Input(){
    if(IsKeyPressed(KEY_O))
        Play();
    if(IsKeyPressed(KEY_P))
        Pause();
    if(IsKeyPressed(KEY_I))
        Stop();
    if(IsKeyPressed(KEY_N))
        Skip();
    if(IsKeyPressed(KEY_B))
        Previous();
    if(IsKeyPressed(KEY_F))
        SetIsLoopingList(true);
    if(IsKeyPressed(KEY_G))
        SetIsLoopingList(false);
    if(IsKeyPressed(KEY_H))
        SetIsLoopingSong(true);
    if(IsKeyPressed(KEY_J))
        SetIsLoopingSong(false);
    if(IsKeyPressed(KEY_DOWN))
        Reload();
    // raycpp::GetPosMousePressed();
    // RecPlay.Update();
    // buttons[0].Update();
    UpdateButtons();
}

void Radio::Draw(){
    raycpp::DrawRectangle(Vec2<int> (200,100),Vec2<int> (400,60), settings::color_gb3);
    raycpp::DrawRectangle(Vec2<int>(200, 100), Vec2<int>((int)GetTimePlayed()/GetTimeLength()*400,60), settings::color_gb0);
    raycpp::DrawRectangleLinesEx(Vec2<int> (200,100),Vec2<int> (400,60),3,settings::color_gb2);
    raycpp::DrawTextCpp(GetNameSong().c_str(), Vec2<int>(200, 170), 26, settings::color_gb0);
    DrawButtons();
}


void Radio::SetActionButtons(){
    buttons[0].SetAction([this](){this -> Play();});
    buttons[1].SetAction([this](){this -> Pause();});
    buttons[2].SetAction([this](){this -> Stop();});
    buttons[3].SetAction([this](){this -> Previous();});
    buttons[4].SetAction([this](){this -> Skip();});
    
}

void Radio::UpdateButtons(){
    for (int i = 0; i < (int)buttons.size(); i++)
        buttons[i].Update();
    if(IsMusicStreamPlaying(songs[index])){
        buttons[0].SetIsSelected(1);
        buttons[1].SetIsSelected(0);
    }
    else{
        buttons[0].SetIsSelected(0);
        buttons[1].SetIsSelected(1);
    }
    for(int i = 2; i <= 4;i++)
        if (buttons[i].GetIsSelected())
            buttons[i].SetIsSelected(false);
    // if (buttons[3].GetIsSelected())
    //     buttons[3].SetIsSelected(false);
    // if (buttons[4].GetIsSelected())
    //     buttons[4].SetIsSelected(false);
}

void Radio::DrawButtons(){
    for (auto button : buttons){
        button.Draw();
        button.SetLinesEx(5, settings::color_gb2);
    }
}

// void Radio::Foward(){
//     unsigned int framesToAdd = (unsigned int) ((songs[index].frameCount * 5 )/100);
//     songs[index].stream.buffer->framesProcessed += framesToAdd;
//     UpdateMusicStream(songs[index]);
// }-