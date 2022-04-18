#pragma once
#include "raylib.h"
#include "raylibCpp.h"
#include <string>
#include <iostream>
#include <vector>
#include "Settings.h"
#include "miniaudio.h"
// class Radio;

struct rAudioBuffer{
    ma_data_converter converter;
    AudioCallback callback;
    rAudioProcessor *processor;
    float volume;
    float pitch;
    float pan;

    bool playing;
    bool paused;
    bool looping;
    int usage;
    bool isSubBufferProcessed[2];
    unsigned int sizeInFrames;
    unsigned int frameCursorPos;
    unsigned int framesProcessed;
    unsigned char *data;
    rAudioBuffer *next;
    rAudioBuffer *prev;
};

class Radio{
    private:
        int index{0};
        bool isLoopingSong{false};
        bool isLoopingList{true};
        bool hasInput{false};
        // bool hasEnded{false};
        // bool hasStarted{false};
        Music m;
        std::vector <Music> songs;
        std::vector <std::string> namesSongs;
        std::vector<raycpp::Button> buttons;
        // raycpp::Button RecPlay;
        // raycpp::Button RecPause;
        // raycpp::Button RecStop;
        // raycpp::Button RecSkip;
        // raycpp::Button RecPrevious;

    // private:
    //     rAudioBuffe

        // float *delayBuffer = NULL;
        // unsigned int delayBufferSize = 0;
        // unsigned int delayReadIndex = 2;
        // unsigned int delayWriteIndex = 0;
        
    private: 
        void Loop();
        void UpdateButtons();
        void DrawButtons();
        void SetActionButtons();
    public:
        // std::string routeSongs = settings::song_route;
        // void Foo(){std::cout << routeSongs << std::endl;}
        Radio();
        Radio(std::string route);
        Radio(std::vector<std::string> routes);
        Radio(std::vector<std::string> routes, std::vector<std::string> names);
        ~Radio();

        void Draw();
        void Input();
        // void Play(){PlayMusicStream(m);}
        void Update();
        void Play();
        void Pause();
        void Stop();

        void Skip();
        void Previous();
        void Load();
        void Reload();

        // void Foward();
        // float Time();
        void SetIsLoopingSong(bool var){isLoopingSong = var; if(isLoopingSong && isLoopingSong == isLoopingList) isLoopingSong = false;}
        void SetIsLoopingList(bool var){isLoopingList = var; if(isLoopingList && isLoopingSong == isLoopingList) isLoopingList = false;}
        void SetHasInput(bool var){hasInput = var;}

        bool GetIsLoopingSong(){return isLoopingSong;}
        bool GetIsLoopingList(){return isLoopingList;}

        int GetIndex(){return index;}
        float GetTimeLength(){return GetMusicTimeLength(songs[index]);}
        float GetTimePlayed(){return GetMusicTimePlayed(songs[index]);}
        std::string GetNameSong();
        std::vector <Music> GetSongs(){return songs;}

        void Updatem(){UpdateMusicStream(m);}
        void Playm(){PlayMusicStream(m);}

};