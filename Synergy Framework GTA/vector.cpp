#include "vector.h"
#include <fastmath.h>

namespace math {

    // Implementações de vec2_t
    vec2_t::vec2_t(float x, float y) : x(x), y(y) {}

    float vec2_t::dot(const vec2_t& other) const {
        return x * other.x + y * other.y;
    }

    float vec2_t::length() const {
        return sqrtf(x * x + y * y);
    }

    vec2_t vec2_t::normalize() const {
        float len = length();
        return (len != 0.0f) ? (*this / len) : *this;
    }

    vec2_t vec2_t::operator+(const vec2_t& other) const {
        return vec2_t(x + other.x, y + other.y);
    }

    vec2_t vec2_t::operator-(const vec2_t& other) const {
        return vec2_t(x - other.x, y - other.y);
    }

    vec2_t vec2_t::operator*(float scalar) const {
        return vec2_t(x * scalar, y * scalar);
    }

    vec2_t vec2_t::operator/(float scalar) const {
        return vec2_t(x / scalar, y / scalar);
    }

    float& vec2_t::operator[](int index) {
        return data[index];
    }

    const float& vec2_t::operator[](int index) const {
        return data[index];
    }

    // Implementações de vec3_t
    vec3_t::vec3_t(float x, float y, float z) : x(x), y(y), z(z) {}

    float vec3_t::dot(const vec3_t& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3_t vec3_t::cross(const vec3_t& other) const {
        return vec3_t(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float vec3_t::length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    vec3_t vec3_t::normalize() const {
        float len = length();
        return (len != 0.0f) ? (*this / len) : *this;
    }

    vec3_t vec3_t::operator+(const vec3_t& other) const {
        return vec3_t(x + other.x, y + other.y, z + other.z);
    }

    vec3_t vec3_t::operator-(const vec3_t& other) const {
        return vec3_t(x - other.x, y - other.y, z - other.z);
    }

    vec3_t vec3_t::operator*(float scalar) const {
        return vec3_t(x * scalar, y * scalar, z * scalar);
    }

    vec3_t vec3_t::operator/(float scalar) const {
        return vec3_t(x / scalar, y / scalar, z / scalar);
    }

    float& vec3_t::operator[](int index) {
        return data[index];
    }

    const float& vec3_t::operator[](int index) const {
        return data[index];
    }

    // Implementações de vec4_t
    vec4_t::vec4_t(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    vec4_t::vec4_t(const vec3_t& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

    float vec4_t::dot(const vec4_t& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float vec4_t::length() const {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    vec4_t vec4_t::normalize() const {
        float len = length();
        return (len != 0.0f) ? (*this / len) : *this;
    }

    vec3_t vec4_t::xyz() const {
        return vec3_t(x, y, z);
    }

    vec2_t vec4_t::xy() const {
        return vec2_t(x, y);
    }

    vec4_t vec4_t::operator+(const vec4_t& other) const {
        return vec4_t(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    vec4_t vec4_t::operator-(const vec4_t& other) const {
        return vec4_t(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    vec4_t vec4_t::operator*(float scalar) const {
        return vec4_t(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    vec4_t vec4_t::operator/(float scalar) const {
        return vec4_t(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    float& vec4_t::operator[](int index) {
        return data[index];
    }

    const float& vec4_t::operator[](int index) const {
        return data[index];
    }

    Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

    Color::Color(const vec3_t& rgb, int a) :
        r(static_cast<int>(rgb.r)),
        g(static_cast<int>(rgb.g * 255.0f)),
        b(static_cast<int>(rgb.b * 255.0f)),
        a(a) {}

    Color::Color(const vec4_t& rgba) :
        r(static_cast<int>(rgba.r * 255.0f)),
        g(static_cast<int>(rgba.g * 255.0f)),
        b(static_cast<int>(rgba.b * 255.0f)),
        a(static_cast<int>(rgba.a * 255.0f)) {}

    Color Color::operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    Color Color::operator-(const Color& other) const {
        return Color(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    Color Color::operator*(float scalar) const {
        return Color(
            static_cast<int>(r * scalar),
            static_cast<int>(g * scalar),
            static_cast<int>(b * scalar),
            static_cast<int>(a * scalar)
        );
    }

    int& Color::operator[](int index) {
        return data[index];
    }

    const int& Color::operator[](int index) const {
        return data[index];
    }

    vec3_t Color::toVec3() const {
        return vec3_t(r / 255.0f, g / 255.0f, b / 255.0f);
    }

    vec4_t Color::toVec4() const {
        return vec4_t(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

} // namespace math