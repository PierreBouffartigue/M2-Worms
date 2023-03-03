#pragma once

struct Vector2D {
    Vector2D(const float x, const float y) :
            _x(x),
            _y(y) {}

    Vector2D &operator+(Vector2D val) {
        _x += val._x;
        _y += val._y;

        return *this;
    }

    Vector2D &operator*(float val) {
        _x *= val;
        _y *= val;

        return *this;
    }

    float _x;
    float _y;
};
