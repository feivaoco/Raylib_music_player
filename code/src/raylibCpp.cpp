#include "raylibCpp.h"
#include <assert.h>
// #include <iostream>
bool operator == (Color c1, Color c2){
    if (c1.a != c2.a)
        return false;
    if (c1.b != c2.b)
        return false;
    if (c1.g != c2.g)
        return false;
    if (c1.r != c2.r)
        return false;
    return true;
}

bool raycpp::isPointInRec(Vec2<int> point, Rectangle rec){
    // Vec2<int> posMouse = GetPosMousePressed();
    bool auxX1 = point.GetX() >= rec.pos.GetX();
    bool auxX2 = point.GetX() <= rec.pos.GetX() + rec.width_Height.GetX();
    bool auxY1 = point.GetY() >= rec.pos.GetY();
    bool auxY2 = point.GetY() <= rec.pos.GetY() + rec.width_Height.GetY();
    if ((auxX1 && auxX2) && ( auxY1 && auxY2) ) return true;
    else return false;
}
Vec2<int> raycpp::GetPosMousePressed(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        // std::cout << GetMouseX() << " | " << GetMouseY() << std::endl;
        return Vec2<int>(GetMouseX(),GetMouseY());
    }
    return Vec2<int>(-99,-99);
}

void raycpp::DrawRectangleMouse(raycpp::Rectangle &rec){
    DrawRectangle(rec.pos, 
                  rec.width_Height, 
                  rec.c);
}

void raycpp::DrawRectangle(Vec2<int> pos, Vec2<int> width_Height, Color c){

    assert(pos.GetX() >= 0 && pos.GetY() >= 0 &&
        pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight());
    DrawRectangle(pos.GetX(), pos.GetY(), width_Height.GetX(), width_Height.GetY(), c);
}

void raycpp::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color c){
    assert(pos.GetX() >= 0 && pos.GetY() >= 0 &&
        pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight());
    assert(lineThick >0 );
    DrawRectangleLinesEx({(float)pos.GetX(), (float)pos.GetY(), (float)widthHeight.GetX(), (float)widthHeight.GetY()}, (float)lineThick, c);
}

void raycpp::DrawTextCpp(char const* s, Vec2<int> pos, int sizeFont, Color c){
    DrawText(s, pos.GetX(), pos.GetY(), sizeFont, c);
}
void raycpp::DrawButtonLinesEx(raycpp::Rectangle &rec, int lineThick, Color c){
    // std::cout << rec.pos.GetX() << " | "<< rec.pos.GetY() << std::endl;
    // std::cout << rec.width_Height.GetX() << " | "<< rec.width_Height.GetY() << std::endl;
    DrawRectangleLinesEx(rec.pos, rec.width_Height, lineThick, c);
}