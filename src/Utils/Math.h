#pragma once

#include <cmath>

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

    Vector2D getNormalized() const {
        const float norm = std::sqrt(_x * _x + _y * _y);
        const float x = _x / norm;
        const float y = _y / norm;

        return Vector2D{x, y};
    }

    void Normalize() {
        const float norm = std::sqrt(_x * _x + _y * _y);
        _x /= norm;
        _y /= norm;
    }

    float _x;
    float _y;
};
