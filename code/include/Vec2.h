#pragma once

template <typename T>
class Vec2{
    private:
        T x;
        T y;

    public:
        Vec2() = default;
        constexpr Vec2(T x, T y)
            :
                x(x),
                y(y)
        {

        }

        constexpr void SetX(T xIn) {x = xIn;};
        constexpr void SetY(T yIn) {y = yIn;};

        constexpr T GetX() const {return x;};
        constexpr T GetY() const {return y;};


        constexpr bool operator==(const Vec2& rhs) const {
            return (x == rhs.x && y == rhs.y);
        }
        constexpr bool operator!=(const Vec2& rhs){
            return !(*this == rhs);
        }

        constexpr Vec2 operator+(const Vec2& rhs) const {
            return {x + rhs.x, y + rhs.y};
        }

        constexpr Vec2 operator+(const int rhs) const {
            return {x + rhs, y + rhs};
        }

        constexpr Vec2& operator+=(const Vec2& rhs) {
            return *this = *this + rhs;
        }

        constexpr Vec2 operator-(const Vec2& rhs) const {
            return {x - rhs.x, y - rhs.y};
        }

        constexpr Vec2 operator-(const int rhs) const {
            return {x - rhs, y - rhs};
        }

        constexpr Vec2& operator-=(const Vec2& rhs){
            return *this = *this - rhs;
        }

        constexpr Vec2 operator*(const Vec2& rhs) const {
            return {x * rhs.x, y * rhs.y};
        }

        constexpr Vec2 operator*(const int rhs) const {
            return {x * rhs, y * rhs};
        }

        constexpr Vec2& operator*=(const Vec2& rhs){
            return *this = *this * rhs;
        }

        // constexpr Vec2&
};