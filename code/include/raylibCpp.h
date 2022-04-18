#pragma once
// #include <iostream>
#include "raylib.h"
#include "Vec2.h"
#include <functional>
bool operator == (Color c1, Color c2);

namespace raycpp{
    Vec2<int> GetPosMousePressed();

    struct Rectangle{
        Vec2<int> pos;
        Vec2<int> width_Height;
        Color c;
    };

    void DrawRectangleMouse(raycpp::Rectangle &rec);
    void DrawButtonLinesEx(raycpp::Rectangle &rec, int lineThick, Color c);
    void DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color c);
    bool isPointInRec(Vec2<int> point, Rectangle rec);
    void DrawRectangle(Vec2<int> pos, Vec2<int> width_Height, Color c);
    void DrawTextCpp(char const* s, Vec2<int> pos, int sizeFont, Color c);
    
    class Button{
        private:
            Rectangle rec;
            Color cDefault;
            Color cSelected;
            bool isSelected {0};
            
            std::function<void(void)> action;
        public:
            Button(Vec2<int> pos, Vec2<int> width_Height, Color c, Color cSelected){
                rec.pos = pos;
                rec.width_Height = width_Height;
                rec.c = c;
                cDefault = c;
                cSelected = cSelected;
            }
            void ChangeColor(){if (rec.c == cDefault) rec.c = cSelected; else rec.c = cDefault;}
            void Draw(){DrawRectangleMouse(rec);}
            void Update(){
                if(isPointInRec(GetPosMousePressed(), rec)){
                    // ChangeColor();
                    if(! isSelected){
                        isSelected = 1;
                        if(action != NULL)
                            action();
                    }
                    else
                        isSelected = 0;
                    
                    // std::cout << "{"<<(int)rec.c.r << ","<<(int)rec.c.b << ","<<(int)rec.c.g << ","<<(int)rec.c.a << "}" << std::endl;
                    
                }
                if (isSelected)
                    rec.c = cSelected;
                else
                    rec.c = cDefault;

            }
            bool GetIsSelected(){return isSelected;}
            void SetIsSelected(bool var){isSelected = var;}
            void SetAction(std::function<void(void)> function){action = function;}
            void SetLinesEx(int size, Color c){
                // std::cout << rec.width_Height.GetX() << std::endl;
                DrawButtonLinesEx(rec, size, c);
            }
    };
    
    
}